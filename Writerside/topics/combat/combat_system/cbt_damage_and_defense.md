# Dealing and Defending Damage
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Damage and Defense are handled via Gameplay Effects, Execution, and their respective components.</li>
        <li>The Combat System provides a dedicated Gameplay Effect Execution that incorporates Damage and Critical Chance attributes.</li>
        <li>Combatants can react to damage using Damage Handlers.</li>
    </ul>
</tldr>

Ninja Combat provides a very flexible **damage and defense system**, which covers a lot of scenarios, but can also be
modified or extended to adjust to your requirements.

## Damage Calculation
The Damage applied from an attack is defined by Gameplay Attributes related to damage - `BaseDamage`, `CriticalHitChance`
and `CriticalHitMultiplier`.

```Generic
var crit_roll = random(0.0, 1.0)
if critical_hit_chance > crit_roll 
then:
    return base_damage * critical_damage_multiplier
else:
    return base_damage
```

This logic is present in the `UCombatExecution_Damage` **Calculation Class**, present in the damage-related [](cbt_gameplay_effects.md).
The values used by this calculation can be fine-tuned in the following ways:

1. **Set By Caller Magnitudes**: You can override the base damage or critical hit chance/multiplier by setting their magnitudes using the appropriate **data tags**.
2. **Damage Multiplier Magnitude**: You can add a Damage Multiplier to the calculation, which will be applied to the **base damage**.
3. **Global Modifier**: Damage can be cancelled by the **Game Mode** or **Game State**.

Once the damage is defined, it is **added** to the target's `PendingDamage`.

> **Rewriting the Calculation**
> 
> Developers can replace the default `CombatExecution_Damage` class with a custom subclass to implement unique damage 
> types or rules. Make sure to follow the correct Gameplay Ability System API while doing so. 

## Defense Calculation
Incoming damage can be defended in many ways, which can be adjusted (or even removed) via Gameplay Attributes.

- **Block**: Usually from shields. Involves **block chance**, **reduction percent**, **reduction limit**, **angle** and a **stamina cost**.
- **Defense**: Any other extra defense layer. Has a **defense chance**, **reduction percent**, **reduction limit** and a **stamina cost**.
- **Armor**: Flat damage reduction provided by equipped gear.
- **Invulnerability**: Provides full damage cancellation. Usually granted by an ability (buff, evades, etc.)
- **Last Stand**: Reverts fatal damage, granting a certain **health percent** back and consuming **charges**.
- **Global Modifier**: Damage can be cancelled by the **Game Mode** or **Game State**.

The full defense stack is applied in this order, from most absolute (invulnerability) to least (flat armor):

```Generic
if invulnerable
then: 
    incoming_damage = 0
    mitigation_const = 0
    
if block_chance_test and block_stamina_test and block_angle_test
then:
    incoming_damage -= Min(incoming_damage * block_reduction, block_cap)
    mitigation_cost += block_cost * incoming_damage

if defense_chance_test and defense_stamina_test
then:
    incoming_damage -= Min(incoming_damage * defense_reduction, defense_cap)
    mitigation_cost += defense_cost * incoming_damage

incoming_damage -= armor_mitigation

if is_fatal_damage then:
    apply_last_stand
```

Here are some examples of how the mitigation can be configured, by adjusting their related Gameplay Attributes:

- If the block or defense chance is `1` (meaning 100%), then the character always blocks or defends damage.
- A block angle of `180` covers frontal arcs. A value of `360` allows blocking from behind as well.
- If the block or defense costs are `0`, then no stamina is required to block or defend, virtually disabling the stamina mechanic.
- If the block or defense limits are `0`, then they can mitigate as much damage as possible, virtually disabling the defense cap mechanic.

## Global Damage Modifier
The system provides an interface, `CombatDamageModifierInterface` that can be implemented by your **Game Mode** or **Game State**.
If you do that, then every damage being applied can be modified or completely cancelled.

The Global Damage Modifier has two important functions:

- `ShouldCancelDamage`: Determines if the damage should be **cancelled**, which means no damage reactions would be triggered.
- `ModifyDamage`: **Modifies** the final damage value, but even a value of **zero** will still trigger hit reactions and damage visuals.

> **Ninja Factions Integration**
>
> Ninja Combat can be [integrated with Ninja Factions](cbt_integration_factions.md) to automatically disable **Friendly
> Fire**.

## Handling Damage
Once received damage is confirmed, a **Gameplay Event** will activate the [**Hit Reaction Ability**](cbt_ability_hit_reaction.md).
Unless it's a **fatal damage**, in which case a **Gameplay Event** will activate the [**Death Ability**](cbt_ability_death.md) instead.

### Damage Data
The **Damage Manager Component** (the default Combat Manager, or a component override) requires a **Data Asset**, based
on `NinjaCombatDamageDataAsset`, to customize certain aspects of the "death flow" and add cosmetics to each hit that has
been received.

<img src="cbt_damage_data.png" alt="Damage Data" thumbnail="true"/>

This data asset is set to the Damage Manager Component's **Damage Data**. It contains the following properties:

| Property          | Description                                                                                      |
|-------------------|--------------------------------------------------------------------------------------------------|
| `LifespanOnDeath` | Lifespan applied when destroying the owner. A value of zero destroys the character immediately.  |
| `DeathTimeLimit`  | Fallback mechanism to avoid relying on certain animations before the character can be destroyed. |
| `DamageHandlers`  | Cosmetic aspects played whenever a hit happens, fatal or not.                                    |

**Damage Handlers** can be used for certain cosmetic aspects and will be executed using **Local Gameplay Cues**. The
system provides the following handlers, and you can create your own from `NinjaCombatDamageHandler`.

| Handler            | Description                                                                                            |
|--------------------|--------------------------------------------------------------------------------------------------------|
| Camera Shake       | Plays a Camera Shake on the actor **receiving** damage.                                                |
| Combat Interfaces  | Invokes the Melee and Ranged Combat Interfaces on the **damage source**, to play their own cosmetics.  |
| Dissolve           | Dissolves the character, using the `NinjaCombatDissolveComponent` which will be created automatically. |
| Physical Animation | Triggers a Physical Animation, using a component implementing `CombatPhysicalAnimationInterface`.      |

## Damage Gameplay Cues
While working with the Damage Handlers, or any other objects related to damage cosmetics, such as certain methods in the
combat interfaces, you can gather information about the damage type from the Gameplay Cue's **Aggregated Source Tags**.

Any Gameplay Tags from the attacker, weapon and Gameplay Effects are available. The Combat System includes the following
types of damage:

| Damage Type                      | Description                                            |
|----------------------------------|--------------------------------------------------------|
| `Combat.Effect.Damage.Blocked`   | The attack was blocked.                                |
| `Combat.Effect.Damage.Breaker`   | The attack broke the blocking state.                   |
| `Combat.Effect.Damage.Critical`  | The attack was a critical hit.                         |
| `Combat.Effect.Damage.Fatal`     | The attack applied fatal damage.                       |
| `Combat.Effect.Damage.Knockback` | The attack was strong enough to result in a knockback. |
| `Combat.Effect.Damage.LastStand` | The attack was fatal but triggered a last stand.       |
| `Combat.Effect.Damage.Mitigated` | The attack was mitigated by a defense mechanism.       |
| `Combat.Effect.Damage.Melee`     | The attack was a melee attack.                         |
| `Combat.Effect.Damage.Ranged`    | The attack was a ranged attack.                        |
| `Combat.Effect.Damage.Stagger`   | The attack resulted in a stagger.                      |

> **Multiple Damage Types**
>
> The same attack can contain multiple types of damage, such as "Melee" and "Blocked", or "Ranged" and "Fatal". You can 
> filter tags by `Combat.Effect.Damage` to determine the full context of the incoming hit.
{style="note"}
