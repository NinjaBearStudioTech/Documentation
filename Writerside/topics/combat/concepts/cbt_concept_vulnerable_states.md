# Vulnerable States
<primary-label ref="combat"/>

## Hit Reactions

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