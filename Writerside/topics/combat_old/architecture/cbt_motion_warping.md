# Motion Warping
<primary-label ref="combat"/>

The system uses **Motion Warping** to properly adjust attack animations, and potentially others, so the animations
will position and rotate their owners based on their given targets.

## Pre-Requisites

To use Motion Warping, your Animation Montages must have **root motion**. You also need the **Motion Warping Component**, 
provided by the Combat System, added to any character that will use the feature.

Please check [this page](cbt_component_extensions.md) for more information about all components in the Combat System,
including the **Combat Motion Warping Component**.

## Motion Warping Flow

There are a few different participants that must work together for the warping to happen. The following diagram shows 
how a **Warp Target** is set for an Ability, so its animation's root motion can be modified via the **Motion Warping Notify State**.

<code-block lang="mermaid">
sequenceDiagram
    ASC->>Attack Ability: activate ability
    activate Attack Ability
        Attack Ability->>Warp Target Provider: request warp target
        activate Warp Target Provider
            Warp Target Provider->>Target Manager: get combat target
            activate Target Manager
                Target Manager-->>Warp Target Provider: combat target
            deactivate Target Manager
            Warp Target Provider-->>Attack Ability: receive combat target
        deactivate Warp Target Provider
        Attack Ability->>Motion Warping Component: set combat warp target
        Attack Ability->>Animation: play
        activate Animation
            Animation->>Motion Warping ANS: begin
            activate Motion Warping ANS
                Motion Warping ANS->>Motion Warping Component: add modifier
                Animation->>Motion Warping ANS: end
            deactivate Motion Warping ANS
            Animation->>Attack Ability: end
        deactivate Animation
        Attack Ability->>ASC: end ability
    deactivate Attack Ability
</code-block>

### Combat Animation Ability

All Combat Abilities playing animations, including the Attack Ability from the diagram above, extend `NinjaCombatAnimationAbility`.
This Ability collects the appropriate Warp Target from a **Warp Target Provider**, and sets it in the **Motion Warping Component**.

### Warp Target Provider

These classes are responsible for collecting what would be an appropriate **Warp Target** for a specific ability. Since
they have an **asynchronous design**, it is possible to perform tasks that will not return immediately, like using 
asynchronous Targeting Presets.

Once a Target Provider collects a target, it must provide this target back to the requesting ability, using the `CombatTargetReceiverInterface`.
Make sure to follow this pattern if you are creating your own Target Providers!

The following Warp Providers are available out-of-the-box:

| Target Provider           | Description                                         |
|---------------------------|-----------------------------------------------------|
| Default Target Provider   | Retrieves the target set in the **Target Manager**. |
| Targeting System Provider | Collects a target using a **Targeting Preset**.     |

> **Creating Warp Target Providers**
> 
> You can create your own Target Providers using `UNinjaCombatMotionWarpingTargetProvider` as your base class.
> Make sure to return your targets to the requesting Gameplay Ability using the `CombatTargetReceiverInterface`!
{style="note"}

### Motion Warping Component

The Motion Warping Component is responsible for storing certain targets by name and receiving **modifiers** that can 
affect the **Root Motion** in the animation.

The Combat System provides its own Motion Warping Component, based on the Motion Warping Component provided by Unreal 
Engine. You can provide your own component following the appropriate guidelines for [component extensions](cbt_component_extensions.md).

> **Component Conflicts**
>
> If your character already uses the Motion Warping component provided by Unreal Engine, then you need to **replace it 
> with the one provided by the Combat framework**! 
> 
> If you already have your own Motion Warping Component subclass, and you need to keep it, then you can **implement the 
> appropriate combat interface for the Motion Warping component**, as described in [](cbt_component_extensions.md).
{style="warning"}

### Motion Warping Animation Notify State

The Animation Montage used in the ability, that will have its Root Motion modified, must have one or more **Motion Warping Notify States**.

This Notify State is provided by Unreal Engine, and it interacts with its own Motion Warping Component to modify the Root
Motion, based on the state's configuration and the current target set in the component.

> **Motion Warping Duration**
> 
> The Warping happens **over the Notify State duration**. This means that you can control how fast or slow it will take
> to perform the root motion adjustments, based on the length of the Motion Warping Notify State.
{style="note"} 

### Refresh Target Warp Animation Notify

If you need to refresh the position set for a pre-defined Warp Target, you can do so by adding the **Refresh Target Warp** 
Animation Notify to your Animation Montage.

This Animation Notify collects the target from Target Manager component, and sets it again in the Motion Warping component,
so the location, rotation and offset can be refreshed.

## Target Locking Integration

The **[](cbt_target_locking.md)** is commonly used in conjunction with **Motion Warping**, since it would be expected that
certain abilities, such as attacks, should warp the attacker to the current target.

To that end, we already covered the **Default Target Provider** that collects targets from the **Target Manager** so they
are used as the **Warp Target**.

Please make sure to check the **[](cbt_target_locking.md)** design page and the **[](cbt_ability_target_lock.md)** ability
reference page for more information on this functionality.
