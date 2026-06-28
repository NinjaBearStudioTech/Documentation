# Damage and Mitigation
<primary-label ref="combat"/>

The **Damage and Mitigation** pipeline is responsible for calculating incoming damage, allowing the target to apply
defenses, and executing the gameplay and cosmetic consequences of the final result.

The pipeline is split into three main layers:

1. **Damage Execution** calculates the incoming damage value from Gameplay Effect data and captured attributes.
2. **Defense Pipeline** allows the target to reduce, redirect, consume resources for, or cancel incoming damage.
3. **Damage Outcomes and Cosmetics** handle the consequences of applied damage, such as death, damage senses, hit reactions,
   floating text, sounds, particles, and other feedback.

This page explains the high-level structure of the pipeline and how each part fits together.

## Pipeline Overview

Damage usually starts as a Gameplay Effect that runs the **Damage Execution**. From there, the Combat Manager resolves the
damage against the target's configured defense and damage data.

| Stage                 | Description                                                                                               |
|-----------------------|-----------------------------------------------------------------------------------------------------------|
| **Damage Execution**  | Calculates the incoming damage value and writes it to the target's **Pending Damage** attribute.          |
| **Defense Pipeline**  | Runs mitigation stages configured by the target's Defense Data Asset.                                     |
| **Damage Resolution** | Applies the final damage and records information such as blocked, critical, fatal, or cancelled damage.   |
| **Damage Outcomes**   | Executes gameplay consequences, such as death handling, damage senses, loot, corpse logic, or knockdowns. |
| **Damage Cosmetics**  | Executes client-facing feedback through **Gameplay Cues**.                                                |

Each layer has a different responsibility. Damage Execution determines **how much damage is incoming**. The Defense Pipeline
determines **how much of that damage should actually apply**. Outcomes and Cosmetics determine **what happens afterward**.

## Damage Execution

The default damage execution is `CombatExecution_Damage`, which can be added to **Gameplay Effects** applying damage.
This execution is added by default to base Combat Effects that represent damage from attacks and other abilities.

This execution calculates incoming damage using damage attributes present in the [**Combat Attribute Set**](cbt_reference_attributes.md),
**Set By Caller magnitudes**, **transient aggregators**, and **source and target tags**.

The execution captures the following attributes:

| Attribute               | Description                                                                                                                                                                                  |
|-------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `BaseDamage`            | Source attribute used as the base damage value.                                                                                                                                              |
| `BaseDamageBonus`       | Source attribute that increases base damage by a percentage.                                                                                                                                 |
| `BaseDamageReduction`   | Source attribute that reduces base damage by a percentage.                                                                                                                                   |
| `CriticalHitChance`     | Source attribute used to roll for a critical hit.                                                                                                                                            |
| `CriticalHitMultiplier` | Source attribute used to multiply damage when a critical hit succeeds.                                                                                                                       |
| `PendingDamage`         | Target attribute that receives the calculated incoming damage. Changes to this attribute trigger the defense pipeline. Successful damage being applied triggers the damage outcome pipeline. |

The Damage Execution calculates damage using **base damage** and optional **critical hit** values. Each value is captured
from a combat attribute, but can be overridden by a **Set By Caller Magnitude** using the related data tag.

| Value                   | Attribute               | Set By Caller Tag                   |
|-------------------------|-------------------------|-------------------------------------|
| **Base Damage**         | `BaseDamage`            | `Combat.Data.Damage`                |
| **Critical Hit Chance** | `CriticalHitChance`     | `Combat.Data.CriticalHitChance`     |
| **Critical Multiplier** | `CriticalHitMultiplier` | `Combat.Data.CriticalHitMultiplier` |

If a critical hit succeeds, the execution adds the critical damage tag, `Combat.Effect.Damage.Critical`, to the Gameplay
Effect Spec, allowing later systems to detect the hit as critical.

> **Damage Execution Scope**
>
> The Damage Execution calculates incoming damage, but it does not decide how the target defends against that damage.
> Target-side defenses are handled by the **Defense Pipeline**.
{style="tip"}

You can add the damage execution, `CombatExecution_Damage`, to any Gameplay Effect, or use a preset provided by Ninja 
Combat.

| Gameplay Effect          | Description                                                        |
|--------------------------|--------------------------------------------------------------------|
| `CombatEffect_Damage`    | Base damage class, not related to any specific type of damage.     |
| `CombatEffect_MeleeHit`  | Damage class that is identified as **damage from melee attacks**.  |
| `CombatEffect_RangedHit` | Damage class that is identified as **damage from ranged attacks**. |

## Defense Data

The **Defense Data Asset** configures the mitigation pipeline used by a combatant.

Defense data can be shared by groups of characters or configured for individual characters. Once assigned to the Combat
Manager, the asset defines which mitigation stages are executed and in which order.

The default Defense Data Asset creates a **mitigation pipeline**, executed in order. Each mitigation stage receives the
current output from previous stages and can add its own damage reduction, resource cost, or cancellation.

> **Pipeline Order**
>
> Mitigations are executed in the order defined by the Defense Data Asset. Place broad cancellation checks, such as
> damage modification and invulnerability, before regular reductions such as armor or absorption.
{style="tip"}

### Damage Calculation

The Defense Pipeline works with two main structures:

| Structure                 | Description                                                                                            |
|---------------------------|--------------------------------------------------------------------------------------------------------|
| `DamageCalculationInput`  | Immutable snapshot of the incoming damage context.                                                     |
| `DamageCalculationOutput` | Mutable accumulator containing reductions, resource costs, cancellation, and final damage information. |

The input contains the information needed to evaluate the incoming damage, including source tags, target state, and captured
attribute values. The output starts with the original incoming damage and is updated by each mitigation stage.

This separation keeps mitigations predictable. Each mitigation reads from the same initial snapshot, while all changes are
recorded in the shared output.

### Damage Mitigations

A **Damage Mitigation** is one stage in the Defense Pipeline. Each mitigation in the pipeline is implemented by a
`NinjaCombatDamageMitigation` object.

Mitigations are lightweight, instanced objects that receive an **immutable damage input** and a **mutable damage output**.
They can inspect the incoming damage, check target attributes, add reductions, consume resources, or cancel the damage event.

Each mitigation has a **Mitigation Tag**. When a mitigation modifies the output in a meaningful way, its tag is added to
the damage calculation result. This allows later systems to know which defenses participated in the final damage result.

Mitigations can perform the following operations:

| Operation                 | Description                                                                   |
|---------------------------|-------------------------------------------------------------------------------|
| **Add damage mitigation** | Reduces the amount of damage that will be applied.                            |
| **Add resource cost**     | Consumes a resource as part of the mitigation result.                         |
| **Add both**              | Reduces damage and consumes a resource in the same mitigation entry.          |
| **Cancel damage**         | Cancels the damage event entirely, including later consequences such as cues. |

> **Damage Cancellation**
>
> Cancelling damage is different from applying zero damage. When damage is **fully cancelled**, no Damage Outcomes or
> Damage Cosmetics are triggered.
>
> If **zero damage is applied** instead, the damage event still resolves normally. Damage Outcomes and Damage Cosmetics
> are triggered, and each handler can decide whether the result is relevant.
{style="note"}

The following mitigation types are available:

| Mitigation             | Purpose                                                                                                     |
|------------------------|-------------------------------------------------------------------------------------------------------------|
| **Modifier Interface** | Allows the **Game State** and **Game Mode** to modify or cancel damage via `CombatDamageModifierInterface`. |
| **Invulnerability**    | Allows damage to be cancelled before other defenses are evaluated.                                          |
| **Block**              | Handles blocking logic, based on **Block** attributes. By default, consumes **Stamina**.                    |
| **Defense**            | Applies generic defense-style mitigation. Based on **Defense** attributes.                                  |
| **Armor**              | Applies armor-style mitigation. Based on the **Armor** attribute.                                           |
| **Absorption**         | Applies absorption-style mitigation. Based on the **Absorption** attribute.                                 |

> **Mitigations are Stateless**
>
> Damage Mitigation objects are designed as reusable, data-driven stages. They should **not store runtime state**. If a
> mitigation needs state, store it on the combatant, the Combat Manager, or another gameplay system.
{style="tip"}

> **Invulnerability Mitigation and State**
>
> The Invulnerability mitigation evaluates if the character has the invulnerability state currently active. This is done
> by applying the **Invulnerability Gameplay Effect** (`UCombatEffect_Invulnerability`).
> 
> Additionally, if you are implementing invulnerability during an **Evade Ability**, you can use the **Invulnerability
> Notify State**, which sends the proper Gameplay Event back to the ability.

### Mitigation Blocking Tags

Each mitigation can define **Mitigation Blocking Tags**. If the incoming damage contains one of these source tags, **that
mitigation is skipped**. This allows specific damage types or ability effects to bypass certain defenses.

For example, a piercing attack could include a tag that prevents armor mitigation, while still allowing other stages in
the pipeline to run.

### Mitigation Attributes

Mitigation classes may need to access certain **Gameplay Attributes** to evaluate mitigation outcomes. These are available 
in the `AttributeSnapshot` property, from the `FDamageCalculationInput` struct, provided as parameter to each mitigation class.

When the **Ninja Combat Attribute Set** prepares the Damage Calculation Input, it searches for all **Attribute Sets**
associated with the Ability System Component, looking for instances implementing `CombatMitigationAttributeSetInterface`.

These Attribute Sets provide their mitigation attributes via `GetAttributesRelevantForDamageMitigation`. Attributes
returned by this function will be available in the mitigation struct.

## Damage Data

The **Damage Data Asset** configures what happens after damage has been resolved.

It contains:

| Property              | Description                                                         |
|-----------------------|---------------------------------------------------------------------|
| **Lifespan On Death** | Lifespan used when the owner is destroyed after death is finalized. |
| **Death Time Limit**  | Fallback time limit to ensure death cleanup eventually completes.   |
| **Damage Outcomes**   | Gameplay consequences executed after damage is resolved.            |
| **Damage Cosmetics**  | Cosmetic handlers executed through Gameplay Cues.                   |

### Damage Outcomes

A **Damage Outcome** represents an authoritative or replicated gameplay consequence of resolved damage. The following
outcomes are available.

| Outcome        | Description                                                                                    |
|----------------|------------------------------------------------------------------------------------------------|
| `Stagger`      | Handles [**stagger**](cbt_concept_vulnerable_states.md#stagger).                               |
| `Knockdown`    | Handles [**knockdown and recovery**](cbt_concept_vulnerable_states.md#knockdown-and-recovery). |
| `Last Stand`   | Replenishes health on **fatal damage**. Based on **Last Stand** attributes.                    |
| `Death`        | Handles death-related state and cleanup.                                                       |
| `Damage Sense` | Integrates damage with the perception system.                                                  |

Each outcome has an **Outcome Tag**. When the outcome handles damage successfully, that tag is added to the outcome context.
This allows the damage result to record which outcomes were executed.

Outcomes can also be configured to skip client execution. This is useful for **authority-only** logic that should only run
on the server.

> **Outcomes Are Gameplay Logic**
>
> Use Damage Outcomes for gameplay consequences. They may affect game state and can run on the server. Cosmetic-only logic
> should be placed in Damage Cosmetics instead.
{style="note"}

### Damage Cosmetics

A **Damage Cosmetic** handles visual, audio, and UI feedback for resolved damage.

Cosmetics are usually executed through the **Gameplay Cue** system and are expected to be cosmetic-only. They should not
contain authoritative gameplay logic, because they may not run on dedicated servers.

Damage Cosmetics can inspect the cue parameters to identify common damage states:

| Helper              | Description                                                                           |
|---------------------|---------------------------------------------------------------------------------------|
| `DamageApplied`     | Provides the damage that has been applied. Usually the same as the **cue magnitude**. |
| `IsMeleeDamage`     | Returns true if the damage was tagged as melee damage.                                |
| `IsRangedDamage`    | Returns true if the damage was tagged as ranged damage.                               |
| `IsRecurringDamage` | Returns true if the damage was recurring damage.                                      |
| `IsBlockedHit`      | Returns true if the hit was blocked.                                                  |
| `IsBreakerHit`      | Returns true if the hit was a guard breaker.                                          |
| `IsStaggerHit`      | Returns true if the hit caused stagger.                                               |
| `IsCriticalHit`     | Returns true if the hit was critical.                                                 |
| `IsFatalHit`        | Returns true if the hit was fatal.                                                    |
| `IsDead`            | Returns true if the cue represents death.                                             |

Cosmetics can also check whether the source or target is **authoritative** or **locally controlled**. This is useful for
choosing which feedback should play for the attacker, the victim, local players, remote clients, or simulated proxies.

> **Cosmetics Are Not Gameplay Logic**
>
> Damage Cosmetics should only handle feedback, such as particles, sounds, camera shakes, hit markers, floating text, or
> animation cues. Gameplay state changes should be handled by **Damage Outcomes**.
{style="warning"}

The following cosmetics are available.

| Cosmetic             | Description                                                                                                   |
|----------------------|---------------------------------------------------------------------------------------------------------------|
| `CameraShake`        | Plays a **camera shake** for the **target**, if controlled by a Player Controller.                            |
| `Cosmetics`          | Executes the Cosmetics from `CombatMeleeInterface` or `CombatProjectileInterface`.                            |
| `Physical Animation` | Plays physical animations using a Physical Animation Component defined by `CombatPhysicalAnimationInterface`. |

## Extension Points

The Damage and Mitigation pipeline is designed to be extended through data assets and object classes.

| Extension Point           | Description                                                                   |
|---------------------------|-------------------------------------------------------------------------------|
| Custom Damage Execution   | Override the execution logic used by the damage Gameplay Effect.              |
| Custom Defense Data Asset | Configure a different mitigation order for specific combatants.               |
| Custom Damage Data Asset  | Configure different outcomes and cosmetics for specific combatants.           |
| Custom Damage Mitigation  | Add new target-side defenses to the mitigation pipeline.                      |
| Custom Damage Outcome     | Add new gameplay consequences after damage is resolved.                       |
| Custom Damage Cosmetic    | Add new feedback handlers for damage and death cues.                          |
| Damage Modifier Interface | Allow project-level or actor-level logic to modify damage at specific points. |

## Common Patterns

### Different Combatants, Different Defense Rules

Defense Data Assets can be created per character type, faction, boss, minion, or individual combatant.

For example, a shielded enemy could use a Defense Data Asset that prioritizes block and absorption, while a ghost enemy
could use a Defense Data Asset that prioritizes invulnerability or special tag-based bypass rules.

### Gameplay Effects Define Incoming Damage

Gameplay Effects can provide damage through attributes, Set By Caller magnitudes, or both.

Use attributes when damage should come from the source's combat stats. Use Set By Caller magnitudes when the ability
needs to provide a specific value, such as weapon damage, projectile damage, or scripted damage.

### Tags Define Damage Meaning

Damage tags allow the pipeline to preserve semantic information about the hit.

Tags can identify damage as melee, ranged, recurring, critical, fatal, blocked, staggering, a guard breaker, or any
project-specific damage type. These tags can then be used by mitigations, outcomes, cosmetics, animation logic, UI, or AI.

> **Damage Tags**
>
> Damage semantics introduced by Ninja Combat use the `Combat.Effect.Damage` tag hierarchy.
>
> Examples include `Combat.Effect.Damage.Critical`, `Combat.Effect.Damage.Fatal`, and
> `Combat.Effect.Damage.Mitigated`.
{style="tip"}

### Data Assets Define Character Behavior

The same damage execution can be used across many abilities and characters, while Defense Data and Damage Data assets
customize how each target reacts to damage.

This keeps the damage system flexible without requiring custom Combat Manager subclasses for every character type.