# Melee Combat
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The Weapon or Character must implement the <b>Melee Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Melee Attacks</b>. Once it activates, it will listen to many <b>Gameplay Events</b>.</li>
        <li><b>Melee Scans</b> events are sent usually by the <b>Melee Scan Notify</b> and will initiate a per-frame <b>Scan</b>.</li>
        <li>At the end of each frame, the <b>Damage Gameplay Effect</b> is applied to all targets collected by the <b>Melee Scan</b>.</li>
    </ul>
</tldr>

The **Melee Combat** functionality is designed to connect animations, scans and targeting in a cohesive way so that 
Melee Attacks can be configured in multiple ways, for many types of combat systems.

<code-block lang="mermaid">
sequenceDiagram
    ASC->>AttackAbility: activate
    activate AttackAbility
        AttackAbility->>AttackAbility: listen for events
        AttackAbility->>Animation: play
        activate Animation
            Animation->>MeleeScanNotifyState: begin
            activate MeleeScanNotifyState
                MeleeScanNotifyState->>MeleeScanInstance: initialize
                activate MeleeScanInstance
                    MeleeScanInstance-->>MeleeScanNotifyState: instance
                deactivate MeleeScanInstance
                MeleeScanNotifyState->>AttackAbility: gameplay event
                Animation->>MeleeScanNotifyState: end
            deactivate Animation
            deactivate MeleeScanNotifyState
            AttackAbility->>MeleeScanTask: initialize
            activate MeleeScanTask
                MeleeScanTask-->>AttackAbility: instance
            deactivate MeleeScanTask
            AttackAbility->>MeleeScanTask: activate
            activate MeleeScanTask
                MeleeScanTask->>MeleeScanInstance: scan
                activate MeleeScanInstance
                    MeleeScanInstance->>MeleeScan: scan
                    MeleeScanInstance-->>MeleeScanTask: targets
                deactivate MeleeScanInstance
            MeleeScanTask-->>AttackAbility: targets
            deactivate MeleeScanTask
            loop each Target
                AttackAbility->>Target: apply GE
            end
    deactivate AttackAbility
</code-block>

## Attack Ability

A Melee Combat starts with the **Attack Ability**. This Ability defines important elements for a **Melee Attack**. 

<img src="cbt_melee_ability.png" alt="Melee Ability" border-effect="line" thumbnail="true"/>

First, the **Animation Provider** determines which animation should be played during the Attack. The default animation
provider uses a single Animation Montage and a Section Name, but you could create other Animation Providers that will
pick certain animations using any **criteria**, such as the type of Weapon currently in use.

The next section, **Motion Warping**, allows you to define a way to collect targets, via the **Targeting Preset** to 
warp the animation. **Motion Warping** is a technique where the animation's **Root Motion** is scaled enough to travel a 
specific distance and/or to rotate to a certain target. You can also apply a **Warp Offset** that will reduce the 
distance to travel between the attacker and the target.

## Melee Scan

Once the selected Animation starts, it will listen for certain **Gameplay Events**. The ones relevant to Melee Attacks
are:

| Gameplay Event                 | Description                                                                                                                 |
|--------------------------------|-----------------------------------------------------------------------------------------------------------------------------|
| `Combat.Event.MeleeScan.Start` | Starts the Melee Scan Task. The Melee Scan instance must be present in the **Payload**, as one of its **Optional Objects**. |
| `Combat.Event.MeleeScan.Stop`  | Stops the Melee Scan Task.                                                                                                  |

These Gameplay Events can be triggered by any object in the system, the only requirement is having a valid **Melee Scan
Transfer Object** in the payload.

The most common way to trigger these events is via the **Melee Scan Notify State**, which can be added to the **Animation
Montage** played by the Attack Ability.

### Melee Scan Notify State

The most common way to trigger the appropriate **Melee Scan Gameplay Events** are using the equivalent **Animation Notify
State**, added to the **Animation Montage** set in the Attack Ability.

<img src="cbt_melee_anim_notify.png" alt="Melee Scan Notify State" border-effect="line" thumbnail="true"/>

This Animation Notify State has important properties to know about:

| Property           | Description                                                                                                                   |
|--------------------|-------------------------------------------------------------------------------------------------------------------------------|
| Source             | Determines if this Melee Scan happens from the **owner** or from a **weapon**.                                                |
| Weapon Query       | For Melee Scans happening from the **weapon**, this query is used to retrieve the correct weapon from the **Weapon Manager**. |
| Scan Socket Prefix | A prefix used to collect all sockets in the source, user to perform the scan.                                                 |
| Scan Channel       | Channel used for the scan. You probably created a dedicated channel during the [initial setup](cbt_setup.md).                 |
| Scan Mode          | How the scan is performed (i.e. _line traces_ or _shape sweeps_. Appropriate settings will be shown for each option.          |
| Melee Hit Override | An optional **Gameplay Effect** that overrides the one set in the Ability or provided by the Source.                          |
| Melee Scan Class   | The class containing the Melee Scan data and logic.                                                                           |

### Melee Scan Instances

This object is used to transfer data from the animation and the correct mesh, to the Attack Ability and its internal Melee 
Scan Task. It also contains the logic to perform scans using the values provided to its properties.

If you need to **modify the Melee Scan logic**, this is the place to look into. You can set a Melee Scan Class to **each**
Melee Scan Animation Notify State, or **globally**, in the **Project Settings** for Ninja Combat.

> **Modifying the Melee Scan**
> 
> You can modify the Melee Scan logic executed by the Melee Scan Class in the `ScanForTargets` function. This function
> can be modified in Blueprints or C++.

## Motion Warping

Melee Attacks can benefit from **Motion Warping**, which is a technique where the **Root Motion** of the animation is 
modified to reach or rotate to a give target.

Use this feature to achieve "_stickiness_" in combat, ensuring that attackers will reach their targets and connect their
hits. 

### Motion Warping Component

Motion Warping is an **optional feature**. To opt-in, first you need to add the `NinjaCombatMotionWarpingComponent`, or
another component that implements `CombatMotionWarpingInterface` to your character, and then return this component from 
the `GetMotionWarpingComponent` function, in the `CombatSystemInterface`.

### Motion Warping Notify State

Next, you must add the **Motion Warping Notify State** to your animation and set the appropriate values to it. This
Notify State is provided by the default Motion Warping implementation in Unreal Engine, and you can read more about it
in the [official documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/motion-warping-in-unreal-engine).

<img src="cbt_melee_motion_warping.png" alt="Motion Warping Notify State" border-effect="line" thumbnail="true"/>

Here are a few important notes, related to the Combat System design:

1. Make sure that the **Warp Target Name** matches between the Notify State and the Attack Ability.
2. The length of the Notify State determines how fast your character will reach its target. You probably want to make that happen **before the Melee Scan**.
3. Depending on your animation, you might want to use yet another Motion Warping Notify State to allow the character to continue tracking the target **during the attack**.
4. The Attack Ability can apply an **offset** to the target, so it can better adjust to certain weapon ranges.

### Motion Warp Target Provider

Back to the Attack Ability, you need to make sure that Motion Warping is **Enabled**, the **Warp Target Name** matches
your Notify State, any **Warp Offset** is configured if applicable and finally, the appropriate **Warp Target Provider**.

The **Default Target Provider** will simply collect the current **Combat Target**, usually acquired by the [Target Lock System](cbt_target_locking.md).
This can be enough for some scenarios, but depending on how you configure your ranges, this can lead to some long root
motion stretches.

In cases where you need some fine-tuning for the target, you can use the **Targeting System Provider**. This alternative
uses a **Targeting Preset** to determine the best target to warp to.

> **Targeting Presets**
> 
> These are **Data Assets** created from the `TargetingPreset` class. This is part of the Unreal Engine's 
> [Gameplay Targeting System](https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-targeting-system-in-unreal-engine).

The Combat System provides additional **Selectors** and **Filters** for the Targeting System that can be used in this
scenario.

<img src="cbt_melee_targeting_preset.png" alt="Motion Warping Notify State" border-effect="line" thumbnail="true"/>

The example above uses two tasks.

1. A task that **selects** the current target acquired by the [Target Lock System](cbt_target_locking.md).
2. A task that **filters** targets by distance. If the target is too far, then the attacker should not warp. 

> **Prioritizing Current Targets**
> 
> For Melee Attacks using the Targeting System, make sure that **Prioritize Current Targets** in the Ability is disabled.
> That would always prioritize the current target and discard the Targeting Preset.

## Melee Weapon Interface



### Melee Hit Cosmetics

In the Damage Handling flow, you can have a **Damage Handler** to invoke **Combat Interfaces** on the **Damage Causer**,
which may likely be a **Weapon**. This triggers the `HandleMeleeDamageCosmetics` function, meant to play cosmetics like
**Sounds** and **Particles**.

The Default Weapon Actor will provide a preliminary structure to handle these assets, allowing you to set them in the
weapon's **Details Tab**. They are stored as **soft references** load on-demand.

> **Niagara Parameters**
>
> If you need to set parameters to the Niagara Component, override the `ModifyMeleeHitComponent` function. By default,
> this function will set: **Target**, **Hit Location** and **Hit Normal**.
{style="note"}