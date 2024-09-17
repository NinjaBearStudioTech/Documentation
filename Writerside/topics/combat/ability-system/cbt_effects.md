# Gameplay Effects
<primary-label ref="combat"/>

This page contains an extensive list of all Gameplay Effects used by Ninja Combat, to support its features. 

## Vital Stats

The following Gameplay Effects are related to main **vital stats**. 

| Effect                      | Description                                                                                         |
|-----------------------------|-----------------------------------------------------------------------------------------------------|
| `ReplenishHealth`           | Automatic Health regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.    |
| `ReplenishStamina`          | Automatic Stamina regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.   |
| `ReplenishMagic`            | Automatic Magic regeneration, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.     |
| `CancelStaminaRegeneration` | Applies the Gameplay Tag to cancel Stamina regeneration. Used by certain abilities, such as Evades. |
| `Dead`                      | Tentatively applied by damage effects. Sets the Dead tag and removes other Gameplay Effects.        |

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
3. It also allows a deliberate damage modifier that can be used to reduce or boost damage for certain Gameplay Effects.

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
