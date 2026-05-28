# Gameplay Effects
<primary-label ref="combat"/>

Ninja Combat uses Gameplay Effects to represent combat state, resource changes, damage, defense, cooldowns, regeneration, 
and temporary conditions.

Most projects can use the default effects as provided, but they can also be duplicated or subclassed when different values, 
tags, durations, or modifier behavior are needed.

This page lists the main Gameplay Effects provided by Ninja Combat and explains the most important usage notes.

## Vital Stat Effects

The following Gameplay Effects are related to main **vital stats**.

| Effect                      | Description                                                                                           |
|-----------------------------|-------------------------------------------------------------------------------------------------------|
| `ReplenishHealth`           | Automatic Health regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.      |
| `ReplenishStamina`          | Automatic Stamina regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.     |
| `ReplenishMana`             | Automatic Mana regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.        |
| `CancelStaminaRegeneration` | Applies the Gameplay Tag that cancels Stamina regeneration. Duration is based on the Delay Attribute. |
| `CancelManaRegeneration`    | Applies the Gameplay Tag that cancels Mana regeneration. Duration is based on the Delay Attribute.    |
| `Dead`                      | Tentatively applied by damage effects. Sets the Dead tag and removes other Gameplay Effects.          |

### Cancel Regeneration

Regeneration cancellation effects are usually applied as **additional effects** on ability costs. When an ability commits
successfully and its cost is applied, the cancellation effect interrupts resource regeneration for the configured delay.

<procedure title="Add Regeneration Cancellation to a Cost" collapsible="true" default-state="collapsed">
    <step>Add the <b>Gameplay Effect Component</b> for additional Gameplay Effects.</step>
    <step>Set the <b>Effect Class</b> to the desired cancellation effect, such as <code>CancelStaminaRegeneration</code> or <code>CancelManaRegeneration</code>.</step>
    <step>Configure the cost normally, using the attribute that should be spent, such as <b>Stamina</b> or <b>Mana</b>.</step>
    <img src="cbt_effect_replenish_cancellation.png" alt="Cancel Regeneration Example" border-effect="line"/>
</procedure>

The cancellation effect uses the appropriate **Regen Delay** Gameplay Attribute configured for the owner and interrupts
resource regeneration for that amount of time.

## Damage Effects

The following Gameplay Effects are used to apply **damage**.

| Effect        | Description                                                                                                           |
|---------------|-----------------------------------------------------------------------------------------------------------------------|
| `Damage`      | Base damage effect. Usually used as a parent for more specific damage effects. Uses the Damage Execution Calculation. |
| `MeleeHit`    | Damage effect tagged as a melee impact.                                                                               |
| `RangedHit`   | Damage effect tagged as a ranged impact.                                                                              |
| `FatalDamage` | Applies damage based on the target's current health, making the hit fatal.                                            |

For details about how damage is calculated, mitigated, modified, and applied, see [**Damage and Mitigation**](cbt_concepts_damage_and_mitigation.md).

## Defense Effects

The following Gameplay Effects are used to **defend** against incoming damage.

| Effect            | Description                                                                                                         |
|-------------------|---------------------------------------------------------------------------------------------------------------------|
| `BlockCooldown`   | Sets a cooldown so the target cannot block again for a certain amount of time. Usually applied after a breaker hit. |
| `BlockCost`       | Used by the Block Ability to check if a target can start blocking.                                                  |
| `Blocking`        | Indicates that a target is currently blocking.                                                                      |
| `EvadeCooldown`   | Sets a cooldown so the target cannot evade again for a certain amount of time.                                      |
| `Evading`         | Indicates that a target is currently evading.                                                                       |
| `Invulnerability` | Makes the target invulnerable and immune to damage.                                                                 |
| `LastStand`       | If the Last Stand aspect is configured, replenishes health by a certain amount and reduces charges for the aspect.  |

## Poise and Stagger Effects

The following Gameplay Effects are related to **Poise** and **Stagger**.

| Effect                | Description                                                                                   |
|-----------------------|-----------------------------------------------------------------------------------------------|
| `RecoverPoise`        | Constant Poise regeneration based on Gameplay Attributes.                                     |
| `DamagePoise`         | Damages Poise, temporarily interrupts regeneration, and attempts to apply the Stagger effect. |
| `CancelPoiseRecovery` | Temporarily interrupts Poise recovery, usually after damage has been inflicted.               |
| `Stagger`             | Staggers the target, potentially allowing certain Opportunity Attacks or reducing defenses.   |

> **Damage Effects**
>
> The main damage effects, **Melee Hit** and **Ranged Hit**, are subclasses of **Poise Damage**, so they inflict Poise
> Damage by default.
>
> Usually, you should not need to use Poise Damage by itself.
> {style="note"}

## Opportunity Attack Effects

The following Gameplay Effects are related to **Opportunity Attacks**.

| Effect                | Description                                                                               |
|-----------------------|-------------------------------------------------------------------------------------------|
| `OpportunityAttacker` | Effect applied to the attacker performing an Opportunity Attack. Applies invulnerability. |
| `OpportunityVictim`   | Effect applied to the victim of an Opportunity Attack.                                    |
| `ParryWindow`         | Determines the part of an attack that can be parried.                                     |

## Target Lock Effects

The following Gameplay Effects are related to **Target Lock**.

| Effect           | Description                                                                    |
|------------------|--------------------------------------------------------------------------------|
| `LockedBySource` | When applied, indicates that the owner has been locked by the effect's source. |
| `LockedOnTarget` | When applied, indicates that the owner is locked on a target.                  |

> **Strafe Integration**
>
> If the Combat Manager is set to grant "strafe ownership" to the target lock, via the `bTargetingControlsStrafingState`
> property, then locking on a target also enables strafing. This state is then broadcast to combat listeners, such as
> the [**Movement Component and Animation Instance**](cbt_concepts_components.md).
> {style="tip"}

## Locomotion Effects

The following Gameplay Effects are meant to enable integrations with external locomotion systems.

| Effect     | Description                                                                                       |
|------------|---------------------------------------------------------------------------------------------------|
| `Strafing` | Indicates that the character is strafing from an external source, such as a locomotion framework. |
