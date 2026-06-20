# Vulnerable States
<primary-label ref="combat"/>

## Hit Reactions

The **Hit Reaction Ability** is responsible for executing hit reactions from confirmed, non-fatal damage. It supports 
directional hit reactions and can map specific damage types or hit contexts to appropriate animations.

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

Each context **maps a tag filter to a specific Animation Montage**, while still preserving the directional section selection 
within that montage. For example, you might assign different hit reaction animations for knockback attacks, stagger hits, or special blows. 

If no context matches the incoming damage, the **default Animation Montage** set in the Animation Provider is used.

### Gameplay Tag Filtering

Contexts are evaluated using **Gameplay Tag Filters**, which can inspect tags from both the instigator and the target. 
These filters are defined by the **Instigator Tags Filter** and **Target Tags Filter** in the Animation Provider.

You can also extend the **Hit Reaction Animation Provider** in Blueprint or C++ to add custom evaluation logic or dynamic 
montage selection.

## Stagger

## Knockdown and Recovery

## Parry and Riposte

### Parry Windows

**Parry windows** define moments when an attacker is vulnerable to a counterattack. They are defined using the **Parry 
Window Animation Notify State**. This state can also apply a **Gameplay Cue**, which can be used to communicate the parry 
opportunity through particles, sounds, or other cosmetic feedback.

### Parry Scans

The victim can then perform an attack using the **Parry Ability**, which scans for targets currently inside a parry window 
and applies a dedicated Hit Gameplay Effect to them.

The Parry Ability can perform this scan directly, when it is not relying on a montage-based Gameplay Event. When the ability 
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
or "riposte", window via the `Combat.Opportunity.Riposte` Gameplay Tag.

### Riposte Attacks

Then, you can activate a Gameplay Ability based on the **Riposte Melee Attack**, which represents the counterattack and 
requires the `Combat.Opportunity.Riposte` Gameplay Tag to be present on the avatar.

The Riposte Ability can also apply a successful riposte Gameplay Effect when the counterattack succeeds.

Other abilities may disregard the window, execute common attacks, and close the window. Attacks can do that automatically 
via the `bRemoveRiposteEffect` property, but you can also **deliberately remove active gameplay effects** using the 
`FGameplayEffectQuery` struct and `RemoveActiveEffects` from the Ability System Component.

The Combat System provides the following **Gameplay Attributes** to support this feature.

| Attribute                      | Description                                                                                  |
|--------------------------------|----------------------------------------------------------------------------------------------|
| `RiposteWindowDuration`        | Defines the duration of a Riposte Window when applied by the **Riposte Opportunity** effect. |
| `RiposteDamageBonusMultiplier` | Multiplies **base damage** when using the default **Combat Damage Execution**.               |

## Death