# Using a Movement Mode Adapter
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Movement Profiles are an **adapter** that translates movement changes to the underlying movement system (for example, the Character
Movement Component, GASP, Mover 2.0, or other custom movement solutions).

Before starting, make sure the following **pre-requisites** are completed:

1. You have a Bot configured to **roam** and **chase** targets, as described in the [**First Ten Minutes** guide](bot_guide_01_first_ten_minutes.md).
2. Since this guide creates a Movement Adapter for the **Character Movement Component**, your Bot must be based on a **Character**.
3. Ideally, you should have animation assets, such as an Animation Blendspace, that can properly showcase **walk** and **jog** states.

<procedure title="Create the CMC Movement Adapter" collapsible="true" default-state="collapsed">
<step>
    <p>In your AI Blueprint folder, create a new <b>Movement Adapter</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Bot &rarr; Movement Adapter. Select <code>MovementAdapter_CMC</code> as the base class.</p>
</step>
<step>
    <p>Add a new entry to <b>Profile Settings</b>, set the <b>Gameplay Tag Key</b> to <code>AI.Movement.Walking</code>, and configure the movement settings to match your walking animation set.</p>
    <img src="bot_guide_movement_adapter_walking.png" alt="Walking profile" width="780" border-effect="line"/>
    <note>
        <p>You can determine the average speed from your animations using the <b>Motion Extractor</b> Animation Modifier and extracting its <b>Translation Speed</b> curve.</p>
    </note>
</step>
<step>
    <p>Add another entry to <b>Profile Settings</b>, set the <b>Gameplay Tag Key</b> to <code>AI.Movement.Running</code>, and configure the movement settings to match your running animation set.</p>
    <img src="bot_guide_movement_adapter_running.png" alt="Running profile" width="780" border-effect="line"/>
</step>
</procedure>

<procedure title="Apply the CMC Movement Adapter" collapsible="true" default-state="collapsed">
<step>
    <p>Open your <b>Bot Setup</b> data asset created in the previous guide.</p>
</step>
<step>
    <p>Set the newly created Movement Adapter as the <b>Movement Mode Adapter Class</b>.</p>
    <img src="bot_guide_setup_movement_adapter.png" alt="Movement Adapter in the Bot Setup" width="780" border-effect="line"/>
</step>
</procedure>

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<!-- BEGIN: BEHAVIOR TREE CONFIGURATION -->
<procedure title="Use the Adapter from the Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Open your <b>Behavior Tree</b> configured for Combat, Roam, and Idle.</p>
</step>
<step>
    <p>In the <b>Combat</b> branch, add the <b>Set Movement</b> task before the <b>Move To</b> task. Configure it to use the <code>AI.Movement.Running</code> mode.</p>
    <img src="bot_guide_behavior_tree_movement_running.png" alt="Triggering the Running Behavior in the Behavior Tree" width="780" border-effect="line"/>
</step>
<step>
    <p>In the <b>Roam</b> branch, add the <b>Set Movement</b> task before the <b>Run EQS</b> task. Configure it to use the <code>AI.Movement.Walking</code> mode.</p>
    <img src="bot_guide_behavior_tree_movement_walking.png" alt="Triggering the Walking Behavior in the Behavior Tree" width="780" border-effect="line"/>
</step>
</procedure>
<!-- END: BEHAVIOR TREE CONFIGURATION -->

</tab>
<tab title="State Tree" group-key="st">

<!-- BEGIN: STATE TREE CONFIGURATION -->
<procedure title="Use the Adapter from the State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Open your <b>State Tree</b> configured for Combat, Roam, and Idle.</p>
</step>
<step>
    <p>In the <b>Combat</b> state, add a new Child State named <b>Start Running</b>. Add a <b>Set Movement</b> task and configure it to use the <code>AI.Movement.Running</code> mode. Add an <b>On State Completed</b> transition to <b>Next State</b>.</p>
    <img src="bot_guide_state_tree_movement_running.png" alt="Triggering the Running Behavior in the State Tree" width="780" border-effect="line"/>
</step>
<step>
    <p>In the <b>Roam</b> state, add a new Child State named <b>Start Walking</b>. Add a <b>Set Movement</b> task and configure it to use the <code>AI.Movement.Walking</code> mode. Add an <b>On State Completed</b> transition to <b>Next State</b>.</p>
    <img src="bot_guide_state_tree_movement_walking.png" alt="Triggering the Walking Behavior in the State Tree" width="780" border-effect="line"/>
</step>
</procedure>
<!-- END: STATE TREE CONFIGURATION -->

</tab>
</tabs>

At this point, you should still have a Bot that **roams around and chases the player when detected**. However, the Bot 
should now correctly alternate between **walking** while roaming and **running** while chasing.
