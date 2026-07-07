# Combat Abilities and Effects

<primary-label ref="combat"/>

Ninja Combat provides **Gameplay Abilities** and **Gameplay Effects** that define common combat actions and combat states.
Abilities usually perform actions, such as attacking, blocking, evading, or locking on a target. Effects usually represent
the resulting state, such as being blocked, staggered, invulnerable, locked on, or recovering resources.

These abilities and effects are designed to work with the provided [**Combat Attribute Set**](cbt_concept_attributes.md),
which defines values such as Health, Stamina, Mana, Poise, regeneration delays, damage, and other combat-related attributes.

Most projects can use the default abilities and effects as provided, but they can also be duplicated, subclassed, or extended
when different values, tags, durations, animations, or behavior are needed.

## Gameplay Abilities

The following Gameplay Abilities are provided by Ninja Combat.

| Ability             | Description                                                                                                            |
|---------------------|------------------------------------------------------------------------------------------------------------------------|
| `Block`             | Applies the blocking state. May also affect the provided Movement Component and Anim Instance.                         |
| `Cast`              | Provides flexible spellcasting modes, such as auras, buffs, debuffs, targeted effects, and other effect-based actions. |
| `Combo`             | Orchestrates abilities into a combo driven by a State Tree.                                                            |
| `Death`             | Handles fatal strikes and the death flow. May include context for specific death animations.                           |
| `Evade`             | Performs directional evades with optional invulnerability frames.                                                      |
| `HitReaction`       | Handles non-fatal strikes. May include context for specific hit reaction animations.                                   |
| `Knockdown`         | Handles a knockdown state.                                                                                             |
| `KnockdownRecovery` | Handles the recovery from a knockdown state.                                                                           |
| `LaunchProjectile`  | Launches projectile actors.                                                                                            |
| `MeleeAttack`       | Scans for targets using predefined melee scan policies.                                                                |
| `OpportunityAttack` | Plays paired animations using the Contextual Animation System. Supports camera animations.                             |
| `Parry`             | Specialized melee attack that parries an incoming attack.                                                              |
| `Riposte`           | Specialized post-parry attack.                                                                                         |
| `Stagger`           | Specialized reaction state that handles a stagger.                                                                     |
| `TargetLock`        | Locks on a target and supports target switching. May also affect the provided Movement Component and Anim Instance.    |

## Gameplay Effects

The following Gameplay Effects are provided by Ninja Combat.

| Category            | Effect                      | Description                                                                                                |
|---------------------|-----------------------------|------------------------------------------------------------------------------------------------------------|
| Vital Stats         | `ReplenishHealth`           | Restores Health over time, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.               |
| Vital Stats         | `ReplenishStamina`          | Restores Stamina over time, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.              |
| Vital Stats         | `ReplenishMana`             | Restores Mana over time, based on Gameplay Attributes. Can be cancelled via Gameplay Tags.                 |
| Vital Stats         | `CancelStaminaRegeneration` | Temporarily cancels Stamina regeneration. Duration is based on the Stamina regeneration delay attribute.   |
| Vital Stats         | `CancelManaRegeneration`    | Temporarily cancels Mana regeneration. Duration is based on the Mana regeneration delay attribute.         |
| Vital Stats         | `Dead`                      | Represents the dead state. Usually applied by fatal damage and removes other relevant combat effects.      |
| Damage              | `Damage`                    | Base damage effect. Usually used as a parent for more specific damage effects.                             |
| Damage              | `MeleeHit`                  | Damage effect tagged as a melee impact. Also applies Poise damage by default.                              |
| Damage              | `RangedHit`                 | Damage effect tagged as a ranged impact. Also applies Poise damage by default.                             |
| Damage              | `FatalDamage`               | Applies damage based on the target's current Health, making the hit fatal.                                 |
| Defense             | `BlockCooldown`             | Prevents the target from blocking again for a certain amount of time. Usually applied after a breaker hit. |
| Defense             | `BlockCost`                 | Used by the Block Ability to check if the target can start blocking.                                       |
| Defense             | `Blocking`                  | Indicates that the target is currently blocking.                                                           |
| Defense             | `EvadeCooldown`             | Prevents the target from evading again for a certain amount of time.                                       |
| Defense             | `Evading`                   | Indicates that the target is currently evading.                                                            |
| Defense             | `Invulnerability`           | Makes the target invulnerable and immune to damage.                                                        |
| Defense             | `LastStand`                 | If the Last Stand aspect is configured, restores Health and reduces the available Last Stand charges.      |
| Poise and Stagger   | `RecoverPoise`              | Restores Poise over time, based on Gameplay Attributes.                                                    |
| Poise and Stagger   | `DamagePoise`               | Damages Poise, temporarily interrupts Poise recovery, and attempts to apply the Stagger effect.            |
| Poise and Stagger   | `CancelPoiseRecovery`       | Temporarily interrupts Poise recovery, usually after damage has been inflicted.                            |
| Poise and Stagger   | `Stagger`                   | Staggers the target, potentially allowing Opportunity Attacks or reducing defenses.                        |
| Opportunity Attacks | `OpportunityAttacker`       | Applied to the attacker performing an Opportunity Attack. Also applies invulnerability.                    |
| Opportunity Attacks | `OpportunityVictim`         | Applied to the victim of an Opportunity Attack.                                                            |
| Opportunity Attacks | `ParryWindow`               | Indicates the part of an attack that can be parried.                                                       |
| Target Lock         | `LockedBySource`            | Indicates that the owner has been locked by the effect's source.                                           |
| Target Lock         | `LockedOnTarget`            | Indicates that the owner is currently locked on a target.                                                  |
| Locomotion          | `Strafing`                  | Indicates that the character is strafing from an external source, such as a locomotion framework.          |

> **Regeneration Cancellation**
>
> Regeneration cancellation effects are usually applied as **additional effects** on ability costs. When an ability commits
> successfully and its cost is applied, the cancellation effect interrupts resource regeneration for the configured delay.
> {style="tip"}

> **Damage and Poise**
>
> The main damage effects, such as `MeleeHit` and `RangedHit`, apply Poise damage by default. For most projects, these
> effects should be used instead of applying `DamagePoise` directly.
> {style="note"}

For details about how damage is calculated, mitigated, modified, and applied, see [**Damage and Mitigation**](cbt_concept_damage_and_mitigation.md).
