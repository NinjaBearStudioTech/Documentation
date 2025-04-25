# Motion Warping
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

Ninja Combat uses **Motion Warping** to modify the **Root Motion** in combat-related animations, so they can take into
consideration a target's **positions** and **"look at" rotations**.

**Motion Warping** is useful in multiple combat-related situations such as:

- **Attacks**: Attack animations often cover a fixed distance. Motion Warping ensures attackers properly **connect with their targets** without **over-reaching**.
- **Evades**: It is common to modify the length of an evade, maybe based on potential targets, edges or even ability modifiers. Motion Warping can be used to fine-tune the movement's **distance** and **precision**.

This page will walk you through the Motion Warping components and how to configure it for your abilities.

## Motion Warping Interface
Within Ninja Combat, all interactions with the Motion Warping component happen through the `CombatMotionWarpingInterface`.
This interface is designed to abstract combat-specific functionalities, **without relying on a specific implementation**.

## Motion Warping Component
The Combat System provides its own Motion Warping Component, which extends on the Motion Warping Component provided by
Unreal Engine and implements the `CombatMotionWarpingInterface`.

> **Component Conflicts**
>
> If your character already uses the Motion Warping component provided by Unreal Engine, then you need to **replace it
> with the one provided by the Combat framework**!
>
> Furthermore, any Actor Component implementing `CombatMotionWarpingInterface` can be used as a valid substitution, which
> allows you to provide your own implementation, even if it is not based on the Unreal Engine's default component.
{style="warning"}

<procedure title="Adding the Motion Warping Component" collapsible="true" default-state="expanded">
    <step>In your Character Blueprint or Base class, add <code>NinjaCombatMotionWarpingComponent</code>.</step>
    <step>Implement <code>GetMotionWarpingComponent</code> from the <code>CombatSystemInterface</code>, returning the <b>Motion Warping Component</b>.</step>
</procedure>

The default Motion Warping Component provided by Ninja Combat also provides the following features:

| Feature               | Details                                                                                                                                                                                                          |
|-----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Transform Calculation | The target **location** and **rotation** can be extended by overriding `CalculateWarpLocation` and `CalculateWarpRotation`.                                                                                      |
| Melee Attack Range    | When warping **melee attack animations** the ability's **optimal distance** is taken into consideration.                                                                                                         |
| Warp Scale            | You can **scale the final warp value**, per-axis, to fine-tune the warp effect (e.g., disable vertical warping for large enemies). This can be done via `WarpScale` or dynamically via `ApplyWarpLocationScale`. |
| Debug Mode            | Enabling debug mode, per component, renders spheres and arrows that visually represent the **warp location and rotation**.                                                                                       |

## Gameplay Targeting System
The default Motion Warping Component provided by Ninja Combat relies on the **[Gameplay Targeting System][1]** to find
eligible **warp targets**. Targeting Presets are executed **asynchronously**.

Let's break down a Targeting Preset that could be used for Motion Warping.

<img src="cbt_advanced_motion_warping_preset.png" alt="Targeting Preset" border-effect="line" thumbnail="true" width="600"/>

| Targeting Task        | Type      | Details                                                                                                                                                                |
|-----------------------|-----------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Current Target        | Selection | Selects the target currently assigned as the **Target Lock**.                                                                                                          |
| Targets in Area       | Selection | Selects all targets in a **sphere, within a given radius**. **Make sure to ignore the source actor and instigator.**                                                   |
| Filter by Distance    | Filter    | Removes targets that are **too far away**. Particularly relevant since we are not only collecting targets in a radius, **but we are also collecting the Target Lock**. |
| Filter by Actor Class | Filter    | Defines class pre-requisites and exceptions. You can add your **base enemy class as a requirement** and remove the **player class** from the filter for extra-safety.  |
| Filter by Dead        | Filter    | Removes actors that are **dead**, from the Combat System's perspective.                                                                                                |
| Filter by Facing      | Filter    | Removes targets that are **not in front** of the targeting source, to avoid warping to a target that is **behind** the player.                                         |
| Sort by Distance      | Sorting   | Sorts all selected targets, by distance. **The closest target will be the priority**.                                                                                  |

> **The Task Order Matters**
>
> Targeting Tasks are executed in their order, in the Targeting Preset. Make sure that all your tasks are defined in the
> correct order: **Selection** > **Filtering** > **Sorting**.
{style="note"}

## Animation Warping
The most common way to configure a **motion warp** is by adding **Animation Notify States** to the **Animation Montage** 
that needs warping. For that, two Notify States are used:

| Notify State             | Details                                                                                                                                                                 |
|--------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Motion Warping           | Configures **how the warp will behave**. Provided by the Unreal Engine's Motion Warping module. Meant to be used in conjunction with its core Motion Warping component. |
| Track Motion Warp Target | Determines when the Motion Warping starts, and for how long it will last. Based on the **[Gameplay Targeting System][1]**.                                              |

<procedure title="Configuring an Attack Motion Warping" collapsible="true" default-state="expanded">
    <step>Open the <b>Attack Animation Montage</b> related to the <b>Melee Attack</b> that will benefit from the Motion Warping.</step>
    <step>
        <p>In the Animation Montage, add the <b>Track Motion Warp Target</b>, set the warp name to <b>Combat Warp</b> and your <b>Targeting Preset</b>.</p>
        <img src="cbt_advanced_motion_warping_notify_track_target.png" alt="Track Target" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>In the Animation Montage, add the <b>Motion Warping</b>, set the modifier to <b>Skew Warp</b> and the warp name to <b>Combat Warp</b>, matching the previous step.</p>
        <img src="cbt_advanced_motion_warping_notify_motion_warping.png" alt="Track Target" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

> **Root Motion**
>
> Root Motion is a pre-requisite for Motion Warping. Make sure that your Animation Sequence has root motion, and that
> it is currently enabled in the Animation Sequence settings.
{style="note"}

## Setting Warp Targets
You can also set warp targets directly, via the Interface/Component. For that you will commonly use an **Instanced Struct**
that represents the **Warp Context**. Ninja Combat provides the following options:

| Warp Context             | Details                                                         |
|--------------------------|-----------------------------------------------------------------|
| Combat Warp Context      | Default option that uses an **Actor** as the Warp Target.       |
| Targeting Preset Context | An option that collects the Actor using a **Targeting Preset**. |

You can derive your own struct from `FCombatWarpContext`, overriding attributes like target acquisition logic or validation 
rules. When sending contexts directly to the Motion Warping Component, the following attributes should be considered:

- **Handled**: Informs that the actor set in the context is verified and ready to use.
- **Track Target**: Informs that the actor's location should be continuously tracked. When tracking is enabled, the system will update the warp location every tick. This is useful for abilities that chase moving enemies for a few frames, before contact.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="cbt_advanced_motion_warping_set_warp.png" alt="Add Warp Targets" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="cbt_advanced_motion_warping_set_warp.cpp"/>
    </tab>
</tabs>

> **Clear Warp Targets**
>
> You can clear warp targets via `ClearCombatWarpTarget` or stop tracking their locations, but keep the warp target set
> via `StopTrackingWarpTarget`. Both functions only require the **Warp Name**.
> 
> Calling `ClearCombatWarpTarget` will also stop tracking the target, so you do not need to call both functions.
{style="note"}

## Modifying Warp Calculations
The default Motion Warping Component calculates warp **location** and **rotation** using the `CalculateWarpLocation` 
and `CalculateWarpRotation` functions. These can be overridden to modify or completely replace the default behavior.

Additionally, you can fine-tune warp **adjustments** by customizing `ApplyMeleeOptimalDistance` and `ApplyWarpLocationScale`.

### Melee Optimal Distance
Some Combat Abilities define an **optimal distance** for execution. The Warp Component respects this by modifying the 
warp location only when the avatar is **farther** than that distance.

If the avatar is already within the optimal distance, the warp location remains unchanged **by default**.

To change this behavior and allow the avatar to be **pushed back** to exactly the optimal distance, enable the 
`bAllowMeleePushback` flag on the Motion Warping Component. When this flag is set, the warp will adjust the location 
even if the avatar is already too close.

To customize or extend this behavior, override the `ApplyMeleeOptimalDistance` function in Blueprints or C++.

### Warp Location Scale
The default component includes a `WarpScale` property that scales the **delta** between the warp location and the 
avatar's current position.

This can be especially useful for axis adjustments, such as removing vertical offset (Z-axis), to ensure the character 
remains grounded when warping.

To customize this logic, override the `ApplyWarpLocationScale` function in Blueprints or C++.

## Debug Mode
To enable a visual representation of each warp target and calculation, enable **Debug Mode** in the component's **Details Panel**.

[1]: cbt_gameplay_targeting_system.md