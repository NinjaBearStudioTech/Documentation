# Gameplay Effects
<primary-label ref="combat"/>

This page contains an extensive list of all Gameplay Effects used by Ninja Combat, to support its features. 

## Vital Stats

The following Gameplay Effects are related to main **vital stats**. 

| Effect                      | Description                                                                                        |
|-----------------------------|----------------------------------------------------------------------------------------------------|
| `ReplenishHealth`           | Automatic Health regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.   |
| `ReplenishStamina`          | Automatic Stamina regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.  |
| `ReplenishMagic`            | Automatic Magic regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.    |
| `CancelStaminaRegeneration` | Applies the Gameplay Tag to cancel Stamina regeneration. Duration is based on the Delay Attribute. |
| `CancelMagicRegeneration`   | Applies the Gameplay Tag to cancel Magic regeneration. Duration is based on the Delay Attribute.   |
| `Dead`                      | Tentatively applied by damage effects. Sets the Dead tag and removes other Gameplay Effects.       |

### Cancel Regeneration

These effects are meant to be used as an **additional effect**, applied with **costs**. That way, whenever an ability is
commited and its cost is successfully applied, the cancellation effect is applied as well and a resource replenishment
is interrupted for a while.

To add these effects to a cost, you need to do the following:

1. Add the **Gameplay Effect Component** for Gameplay Effects.
2. Configure the correct **Effect Class**, setting the desired cancellation Gameplay Effect.
3. Configure the cost as usual, setting the proper attribute to deduct a value from ("Stamina" for example).

<img src="cbt_effect_replenish_cancellation.png" alt="Cancel Regeneration Example" border-effect="line"/>

The Cancellation will take the appropriate **Regen Delay** Gameplay Attribute configured for the owner, and interrupt 
the resource regeneration for that amount of time.

## Damage

The following Gameplay Effects are used to inflict **damage** to the target.

| Effect            | Description                                                                                                            |
|-------------------|------------------------------------------------------------------------------------------------------------------------|
| `Damage`          | Most basic damage class. Usually a base class to other more specific types of damage. Uses the Damage Execution class. |
| `MeleeHit`        | A hit with tags that will define it as a melee impact.                                                                 |
| `RangedHit`       | A hit with tags that will define it as a ranged impact.                                                                |
| `FatalDamage`     | Applies a damage that is always fatal, based on the target's current health.                                           |

### Damage Execution Calculation

The Damage effect uses the **Damage Execution Calculation** class, which will calculate Critical Damage, based on the 
current Gameplay Attributes. This Calculation is very flexible and supports the following features:

1. Uses the Base Damage, Critical Hit Change and Critical Hit Damage from Gameplay Attributes.
2. Allows all these values to be overridden by _Set By Caller Magnitudes_ using the following tags: `Combat.Data.Damage`, `Combat.Data.CriticalHitChance`, `Combat.Data.CriticalHitMultiplier`.
3. It also allows a deliberate **Damage Modifier** that can be used to boost or reduce damage for certain Gameplay Effects.

> **Critical Damage**
> 
> If you decide to replace the Damage Calculation class, make sure to tag the Gameplay Spec with `Combat.Effect.Damage.Critical`,
> whenever a Critical Hit happens, so the system can differentiate those hits and react accordingly.
{style="note"}

#### Damage Override

You can override damage entries in the calculation, so you can use other Gameplay Attributes or more complex calculations
via Modifier Calculation classes. You can do that selecting any **Backing Data** available in the Calculation Execution, 
and change it as you see fit.

<img src="cbt_damage_override.png" alt="Damage Override" border-effect="line" width="600" thumbnail="true"/>

Alternatively, you can use a **Set By Caller Magnitude**, which allows external actors to set a direct value. This may
be useful if you want to use the same Damage Effect for multiple weapons with different damages. For that, you need to
set the appropriate magnitude data.

If your use case is specifically requiring _weapons_ or _projectiles_ to set this value, then make sure to check the 
related interfaces (Melee and Ranged), that can provide such values. If they do, the attack abilities provided by the
framework will set these values for you.

<img src="cbt_damage_override_magnitude.png" alt="Damage Override Magnitude" border-effect="line" width="600" thumbnail="true"/>

#### Damage Modifier

The **Damage Modifier** is a special **Backing Data** available in the `CombatExecution_Damage` calculation class. It
allows you to **boost** or **reduce** damage applied by the Gameplay Effect. It can be based on a Scalable Float, 
Backing Attribute, Set By Caller or yet another custom Calculation Class.

This is also a good way to **scale damage** based on something like _weapon level_. In this example, if the weapon level 
is translated to the Gameplay Effect level, you can have a **Curve Table** providing the modifiers, making this a very
flexible way to adjust the base damage.

For this, you should select the `Combat.Data.Damage.Multiplier` Backing Data from the Calculation Execution.

<img src="cbt_damage_modifier.png" alt="Damage Override Modifier" border-effect="line" width="600" thumbnail="true"/>

## Defense

The following Gameplay Effects are used to **defend** against incoming damage.

| Effect            | Description                                                                                                         |
|-------------------|---------------------------------------------------------------------------------------------------------------------|
| `BlockCooldown`   | Sets a cooldown so the target cannot block again for a certain amount of time. Usually applied after a breaker hit. |
| `BlockCost`       | Used by the Block Ability to ensure that a target can start blocking.                                               |
| `Blocking`        | Indicates that a target is currently blocking.                                                                      |
| `EvadeCooldown`   | Sets a cooldown so the target cannot evade again for a certain amount of time.                                      |
| `Evading`         | Indicates that a target is currently evading.                                                                       |
| `Invulnerability` | Makes the target invulnerable, immune to any damage.                                                                |
| `LastStand`       | If the Last Stand aspect is configured, replenishes health by a certain amount and reduces charges for the aspect.  |

## Combo

The following Gameplay Effects are related to the **Combo** functionality.

| Effect           | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| `LockedOnTarget` | Indicates that the receiver has a locked target. Usually triggers strafing. |

## Target Lock

The following Gameplay Effects are related to the **Target Lock** functionality.

| Effect        | Description                               |
|---------------|-------------------------------------------|
| `ComboWindow` | When applied, allows a combo to continue. |


## Opportunity Attacks

The following Gameplay Effects are related to the **Opportunity Attack** functionality.

| Effect                | Description                                                                               |
|-----------------------|-------------------------------------------------------------------------------------------|
| `OpportunityAttacker` | Effect applied to the attacker performing an Opportunity Attack. Applies invulnerability. |
| `OpportunityVictim`   | Effect applied to the victim of an Opportunity Attack.                                    |
| `ParryWindow`         | Determines the part of an attack that can be parried.                                     |

## Poise and Stagger

The following Gameplay Effects are related to the **Poise and Stagger** functionality.

| Effect                | Description                                                                                  |
|-----------------------|----------------------------------------------------------------------------------------------|
| `RecoverPoise`        | Constant Poise regeneration based on Gameplay Attributes.                                    |
| `DamagePoise`         | Damages Poise. Temporarily interrupts regeneration and attempts to apply the Stagger effect. |
| `CancelPoiseRecovery` | Temporarily interrupts Poise recovery, usually after damage has been inflicted.              |
| `Stagger`             | Staggers the target, potentially allowing certain Opportunity Attacks or reducing defenses.  |

> **Damage Effects**
> 
> The main damage effects, **Melee Hit** and **Ranged Hit** are subclasses of the **Poise Damage**, so they inflict 
> Poise Damage by default. 
> 
> Usually, you should not need to use the Poise Damage by itself.
