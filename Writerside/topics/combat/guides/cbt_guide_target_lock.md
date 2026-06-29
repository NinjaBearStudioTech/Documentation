# Configuring Target Locking
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

This guide shows how to implement **target locking** so players see a visual representation of their prioritized enemies
and can reuse the locked target for systems such as motion warping and strafing movement.

For more information, see the documentation for [**Target Locking**](cbt_concept_target_locking.md).

> **Melee Attacks**
>
> Parts of this guide are shared with the [**Melee Attacks**](cbt_guide_melee_attacks.md) guide. If you are working on
> both, you will be able to reuse and skip certain steps.

## Prerequisites

### Collision and Components

Your collision channels, combat components, and base character setup should already be configured. For more information,
see [**Combat Setup**](cbt_setup.md) and [**Combat First Steps**](cbt_first_steps.md).

### Input Handling

Make sure your input setup can activate gameplay abilities. For more information, see
[**Combat and Input Integration**](integration_combat_input.md). Integration with Ninja Input is optional, but input
handling for ability activation should already be configured.

## Motion Warping

[**Motion Warping**](cbt_concept_motion_warping.md) is commonly used by melee attacks to move the attacker closer to the
target by adjusting the animation's **root motion**.

This requires adding the **Motion Warping Component** to your character and implementing the appropriate getter function
from the **Combat System Interface**.

<procedure title="Add the Motion Warping Component" collapsible="true" default-state="collapsed">
    <step>In your Character Blueprint or base class, add <code>NinjaCombatMotionWarpingComponent</code>.</step>
    <step>Implement <code>GetMotionWarpingComponent</code> from the <code>CombatSystemInterface</code>, returning your <b>Motion Warping Component</b>.</step>
</procedure>

> **Component Conflicts**
>
> If your character already uses the Motion Warping Component provided by Unreal Engine, then you need to **replace it
> with the one provided by the Combat framework**.
{style="warning"}

## Targeting Preset

Motion Warping can use a **Targeting Preset** to find the target that the attack should warp toward. We will create a
preset that prioritizes the [**locked target**](cbt_concept_target_locking.md) first. If no locked target is available, the
preset will collect targets using a fallback area scan.

<procedure title="Create a Targeting Preset" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_melee_targeting_preset.png" alt="Targeting Preset" border-effect="line" thumbnail="true"/>
    <step>Create a new <b>Targeting Preset</b> asset.</step>
    <step>
        <p>Add the <b>Current Target Selection Task</b> and set the following properties:</p>
        <ul>
            <li>Set it to <b>Select Targets in Area</b>, so it will perform a scan as a fallback when no target is locked on.</li>
            <li>Set the <b>Maximum Distance for Target Lock</b> to <code>500</code>.</li>
            <li>Set the <b>Facing Angle Threshold</b> to <code>75</code>.</li>
            <li>Set the <b>Shape Type</b> to <b>Capsule</b>.</li>
            <li>Set the <b>Collision Channel</b> to <b>Combat Object</b>.</li>
            <li>Set the <b>Radius</b> to <code>200</code>, or any other value that fits your design.</li>
        </ul>
    </step>
    <step>Add the <b>Dead Filter Task</b>.</step>
    <step>Add the <b>Facing Filter Task</b> and set the <b>Maximum Angle</b> to <code>60</code>.</step>
    <step>Add the <b>Distance Sort Task</b>.</step>
</procedure>

## Target Lock Anchor

Every actor that can be locked on must have a scene component that represents the location where the Target Lock actor
should be attached to.

<procedure title="Configure the Anchor Scene Component" collapsible="true" default-state="collapsed">
    <step>Open your base combatant class and add a new <b>Scene Component</b> parented to the main mesh.</step>
    <step>Adjust its location as needed.</step>
    <step>Add <code>Combat.Component.TargetLockAnchor</code> to the list of <b>component tags</b>.</step>
</procedure>

## Target Lock Actor

The target lock actor is used by the Target Manager Component (by default, the Combat Manager) to represent the current
locked-on actor.

<procedure title="Create the Target Lock Actor" collapsible="true" default-state="collapsed">
    <step>Create a new <b>Gameplay Widget</b> to represent the marker (e.g., a simple <i>dot</i> or <i>arrow</i>).</step>
    <step>
        <p>In your Content Browser, create a new Actor based on <code>NinjaCombatMarkerActor</code>.</p>
        <img src="cbt_target_lock_marker_widget.png" alt="Marker Widget" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Assign the created <b>Widget</b> to the <b>Target Lock Widget Component</b> of your new actor.</p>
        <img src="cbt_target_lock_marker_actor.png" alt="Marker Actor" border-effect="line" thumbnail="true"/>
    </step>
    <step>Set the Target Lock Actor to <code>TargetMarkerActorClass</code> in the <b>Combat Manager</b>.</step>
</procedure>

## Target Lock Ability

The Target Lock Ability collects the target using a Targeting Preset and supports activation by tags or Gameplay Events.
It also supports additional events to scan for targets, cycle targets, and dismiss the current one.

<procedure title="Create the Target Lock Ability" collapsible="true" default-state="collapsed">
    <step>
        <p>Create a new <b>Gameplay Ability</b> based on <code>CombatAbility_TargetLock</code>. Set your <b>Targeting Preset</b> in the ability's properties.</p>
        <img src="cbt_target_lock_ability.png" alt="Target Lock Ability" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Set the <b>Gameplay Targeting Preset</b> previously created as the ability's <b>Targeting Preset</b>.</p>
    </step>
    <step>
        <p>Enable <b>Track Distance</b> and set a reasonable <b>Distance Threshold</b> for your project.</p>
    </step>
    <step>
        <p>Add an <b>Activation Tag</b> to the <b>Ability Tags</b> container, such as <code>Ability.Activation.TargetLock</code>.</p>
    </step>
    <step>
        <p>Optionally, if using <b>Ninja Input</b>, also add <code>Input.Ability.Toggled</code> to the list of <b>Ability Tags</b>.</p>
        <p>This will allow the ability to be activated by an input and then deactivated when the same input is received again.</p>
    </step>
    <step>
        <p>Grant the ability to your character.</p>
    </step>
</procedure>

The Target Lock Ability can be activated using common Ability Activation Techniques. If you are using [**Ninja Input**](ipt_overview.md),
make sure to check the [**Integration Page**](integration_combat_input.md) to see how to use Input Handlers to toggle
the ability and send Gameplay Events to scan for targets, cycle targets, and dismiss the current one.
