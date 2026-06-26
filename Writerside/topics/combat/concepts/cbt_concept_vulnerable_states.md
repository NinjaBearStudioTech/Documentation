# Damage Reactions and Vulnerable States
<primary-label ref="combat"/>

After damage is confirmed, combatants can react in different ways depending on the incoming hit, their current state,
and the systems configured for them.

These reactions can range from simple directional hit animations to stronger state changes such as stagger, knockdown,
recovery, riposte opportunities, or death. Some systems, such as parry windows, also create temporary vulnerabilities
before damage is applied, allowing other combatants to respond with a counterattack.

This page introduces the main Combat System features used to represent damage reactions, temporary vulnerabilities,
and follow-up opportunities.

## Hit Reactions

The **Hit Reaction Ability** executes hit reactions from confirmed, non-fatal damage. It supports directional hit reactions
and can map specific damage types or hit contexts to appropriate animations.

It is typically triggered by **Gameplay Events**, so it should usually be **granted by default** to all characters that
can react to incoming damage.

### Ability Trigger

By default, the Hit Reaction Ability is triggered by the **Combat Manager**, specifically from the **Damage Manager**
component.

Incoming hits are evaluated and, unless overridden by another effect such as **fatal damage**, may trigger the Hit Reaction
Ability. Since it is activated by a Gameplay Event, it can also be triggered by other systems as needed.

### Directional Hit Reactions

The Hit Reaction Ability uses the **Directional Hits Animation Provider**, which selects a **Montage Section** based on
the direction of the incoming attack. This allows a single Animation Montage to provide different reactions for hits from
the front, back, left, or right.

> **Section Montages**
>
> When using Montage Sections, make sure to **break their links** in the Montage Section panel. Otherwise, all sections
> will play in sequence.
{style="note"}

### Hit Angle Calculation

The Directional Hits Animation Provider calculates the hit angle using two sources: the **Hit Result Location** and the
**Attacker Location**.

You can control their influence using the **Hit Location Weight** and **Attacker Location Weight** properties. This
allows you to favor one source, ignore one entirely, or use a blended approach.

<img src="cbt_damage_hit_angle.png" alt="Hit Reaction Calculation"/>

### Contextual Hit Reactions

The Animation Provider also supports **contextual hit reactions**, where animations are selected based on Gameplay Tags
found in the incoming damage.

Each context maps a tag filter to a specific Animation Montage, while still preserving the directional section selection
within that montage. For example, you might assign different hit reaction animations for knockback attacks, stagger hits,
or special blows.

If no context matches the incoming damage, the **default Animation Montage** set in the Animation Provider is used.

### Gameplay Tag Filtering

Contexts are evaluated using **Gameplay Tag Filters**, which can inspect tags from both the instigator and the target.
These filters are defined by the **Instigator Tags Filter** and **Target Tags Filter** in the Animation Provider.

You can also extend the **Hit Reaction Animation Provider** in Blueprint or C++ to add custom evaluation logic or dynamic
montage selection.

## Stagger

## Knockdown and Recovery

**Knockdown** is an optional fatal damage reaction. When enabled, fatal damage can place a combatant into a temporary
knocked down state instead of immediately starting the normal death flow.

This is handled by the **Knock Down Damage Outcome**. When fatal damage is received, the outcome checks whether the
combatant can enter knockdown, whether the incoming damage allows knockdown, and whether the required knockdown attributes
are configured. If all checks pass, the fatal hit is resolved as a knockdown, the `Combat.Event.KnockedDown` Gameplay Event
is broadcast, and fatal resolution stops.

### Enabling Knockdown

To enable knockdown for a combatant:

1. Add the **Knock Down Damage Outcome** to the combatant's Damage Data outcome pipeline.
2. Enable knockdown on the combatant's Damage Manager or Combat Manager.
3. Grant the **Knock Down Ability** to the combatant.
4. Grant the **Knock Down Recovery Ability** if the combatant can be recovered.
5. Configure valid values for the knockdown attributes.

The Combat System provides the following **Gameplay Attributes** to support knockdown.

| Attribute                | Description                                                          |
|--------------------------|----------------------------------------------------------------------|
| `KnockDownDuration`      | Defines how long the combatant can remain knocked down before dying. |
| `KnockDownHealthPercent` | Defines how much health is restored when recovering from knockdown.  |

Both attributes must be configured with values greater than zero for the default Knock Down outcome to resolve fatal damage
as a knockdown.

### Knock Down Ability

The **Knock Down Ability** is activated by the `Combat.Event.KnockedDown` Gameplay Event. It plays the knockdown animation
and applies the **Knocked Down Gameplay Effect**, which adds the `Combat.State.KnockedDown` Gameplay Tag.

This Gameplay Tag represents the actual knocked down state. It can be used by other abilities, UI, animation systems, or
gameplay logic to detect that the combatant is currently knocked down.

The default **Knocked Down Gameplay Effect** also cancels health, mana, and stamina regeneration while the state is active.

### Knockdown Duration

Once the Knock Down Ability starts, it waits for the duration defined by the `KnockDownDuration` attribute.

If the duration expires before the combatant recovers, the ability applies the death effect and starts the death flow. The
same can happen if a `Combat.Event.GiveUp` Gameplay Event is sent while the combatant is knocked down.

### Recovery

Recovery is handled by the **Knock Down Recovery Ability**, which is activated by the
`Combat.Event.RecoverFromKnockDown` Gameplay Event.

The recovery ability requires the combatant to currently have the `Combat.State.KnockedDown` Gameplay Tag. When activated,
it applies the recovery effect, restores health, removes the knocked down state, and plays the recovery animation.

By default, the recovered health is calculated from the combatant's maximum health and knockdown recovery percentage:
`MaxHealthTotal * KnockDownHealthPercent`. Once the knocked down Gameplay Tag is removed, the Knock Down Ability ends and 
the combatant exits the knocked down state.

### Animation State

The Combat Manager broadcasts changes to the knocked down state, and the Ninja Combat Animation Instance can use this
information to expose an animation-facing flag.

This allows Animation Blueprints to blend into knocked down poses, locomotion, recovery animations, or other animation
states while the combatant is knocked down.

## Parry and Riposte

Parries and ripostes are common **counterattack** mechanics, popularized by the _souls-like_ genre. They work by creating
moments where an attacker becomes vulnerable, allowing the victim to respond with a timed **parry**.

A successful parry opens the original attacker to a counterattack, or **riposte**. This is usually a stronger attack that
rewards the precise timing required to execute the parry.

In the Combat System, any attack can contain a parry window, and parry attacks and ripostes are usually variations of a
[**melee attack**](cbt_concept_melee_attacks.md).

### Parry Windows

**Parry windows** define moments when an attacker is vulnerable to a counterattack. They are defined using the **Parry
Window Animation Notify State**. This state can also apply a **Gameplay Cue**, which can be used to communicate the parry
opportunity through particles, sounds, or other cosmetic feedback.

### Parry Scans

The victim can then perform an attack using the **Parry Ability**, which scans for targets currently inside a parry window
and applies a dedicated Hit Gameplay Effect to them.

The Parry Ability can perform this scan directly when it is not relying on a montage-based Gameplay Event. When the ability
is driven by montage-based Gameplay Events, the animation should include a **Parry Scan Animation Notify State** to trigger
the scan at the correct moment.

The Parry Scan can also check whether a specific **Parry Scan Window** is currently available. Each **Parry Scan Animation
Notify State** has a `ParryScanWindowTag`, using tags under `Combat.Parry.Window`.

The default window is always available. Other windows are only available when the melee source, such as the owner or weapon,
allows that window through the **Combat Melee Interface**.

This makes it possible to add multiple Parry Scan windows to the same animation. For example, a single parry montage can
include different scan windows for different shield types, allowing each shield to enable the window that matches its own
parry efficiency, timing, or coverage.

### Riposte Opportunity

The performer of a **successful parry** receives a successful parry Gameplay Effect defined by the Parry Ability. This
Gameplay Effect is based on `CombatEffect_RiposteOpportunity` and usually has a duration that defines a counterattack,
or **riposte**, window via the `Combat.Opportunity.Riposte` Gameplay Tag.

### Riposte Attacks

You can then activate a Gameplay Ability based on the **Riposte Melee Attack**, which represents the counterattack and
requires the `Combat.Opportunity.Riposte` Gameplay Tag to be present on the avatar.

The Riposte Ability can also apply a successful riposte Gameplay Effect when the counterattack succeeds.

Other abilities may disregard the window, execute common attacks, and close the window. Attacks can do that automatically
via the `bRemoveRiposteEffect` property, but you can also deliberately remove active Gameplay Effects using the
`FGameplayEffectQuery` struct and `RemoveActiveEffects` from the Ability System Component.

The Combat System provides the following **Gameplay Attributes** to support this feature.

| Attribute                      | Description                                                                                  |
|--------------------------------|----------------------------------------------------------------------------------------------|
| `RiposteWindowDuration`        | Defines the duration of a Riposte Window when applied by the **Riposte Opportunity** effect. |
| `RiposteDamageBonusMultiplier` | Multiplies **base damage** when using the default **Combat Damage Execution**.               |

## Death

The **death flow** begins when **fatal damage** is received and no defense mechanisms, such as Last Stand, are available
to prevent it. Once initiated, it triggers the **Death Ability**, which manages the character's final actions and cleanup.

When the **Death Ability** ends, the character is destroyed and the death flow is completed. Alternatively, a **Gameplay
Event** can be sent manually, typically from a **Death Animation Notify**, to finalize the flow earlier.

### Death Ability

The **Death Ability** should be granted **by default** to all combatants. It can cancel active abilities and handle the
final phase of death, including animations and destruction logic.

You can configure the death animation to either **end naturally** or **loop** in a specific animation state.  
Looping is useful for holding ragdoll poses or collapsed states before cleanup.

<img src="cbt_death_animation.png" alt="Death Animation" thumbnail="true" border-effect="line"/>

### Interrupting Abilities

When a death occurs, other active abilities may need to be cancelled.  
To do that, configure the **Cancel Abilities With Tag** container in the Death Ability to include the relevant tags.

> **Opportunity Attacks**
>
> If you're using [**Paired Animations**](cbt_concept_paired_animations.md) for executions or similar mechanics, prevent
> the Death Ability from triggering while the `Combat.State.Opportunity.Victim` tag is active.
{style="tip"}