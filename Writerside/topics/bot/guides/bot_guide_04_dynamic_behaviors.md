# Configuring Dynamic Behaviors
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Both Behavior Trees and State Trees support **Dynamic Assets**, and Ninja Bot simplifies their usage by providing a dedicated
area in the Bot Setup to catalog and manage these behaviors.

This is especially useful when you want to define a common base structure (for example, *Combat*, *Roam*, and *Idle*),
while allowing specific behaviors to **vary across different AI archetypes**. A zombie may roam between random locations,
whereas a guard may patrol predefined routes, all while sharing the same high-level decision flow.

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<!-- BEGIN: BOT SETUP WITH BEHAVIOR TREE -->
<procedure title="Create the Combat Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Duplicate your <b>Base Behavior Tree</b> and name the new asset <code>BT_Combat</code>.</p>
</step>
<step>
    <p>Remove everything except the <b>Combat</b> branch. Remove any <b>Services</b> and <b>Decorators</b> from this branch as well.</p>
    <img src="bot_guide_dynamic_bt_combat.png" alt="Dynamic Combat Behavior Tree" width="780" border-effect="line"/>
</step>
</procedure>

<procedure title="Create the Roam Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Duplicate your <b>Base Behavior Tree</b> and name the new asset <code>BT_Roam</code>.</p>
</step>
<step>
    <p>Remove everything except the <b>Roam</b> branch. Remove any <b>Services</b> and <b>Decorators</b> from this branch as well.</p>
    <img src="bot_guide_dynamic_bt_roam.png" alt="Dynamic Roam Behavior Tree" width="780" border-effect="line"/>
</step>
</procedure>

<procedure title="Create the Idle Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Duplicate your <b>Base Behavior Tree</b> and name the new asset <code>BT_Idle</code>.</p>
</step>
<step>
    <p>Remove everything except the <b>Idle</b> branch. Remove any <b>Services</b> and <b>Decorators</b> from this branch as well.</p>
    <img src="bot_guide_dynamic_bt_idle.png" alt="Dynamic Idle Behavior Tree" width="780" border-effect="line"/>
</step>
</procedure>

<procedure title="Update the Base Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Return to the <b>Base Behavior Tree</b> and add three <b>Run Behavior Dynamic</b> tasks.</p>
</step>
<step>
    <p>For each task, assign a <b>Behavior Tag</b>: <code>AI.Dynamic.Combat</code>, <code>AI.Dynamic.Patrol</code>, and <code>AI.Dynamic.Idle</code>. Also assign the corresponding Behavior Tree asset to each task.</p>
    <note>The Behavior Trees assigned to these tasks act as <b>fallback behaviors</b> if no dynamic behavior is configured for a given Gameplay Tag.</note>
</step>
<step>
    <p>Transfer the <b>Has Target?</b> decorator from the original Combat branch to the new dynamic Combat task. Connect the new tasks accordingly and remove the original static branches.</p>
    <img src="bot_guide_dynamic_bt_full.png" alt="Full Dynamic Tree" width="780" border-effect="line"/>
</step>
</procedure>

<procedure title="Update the Bot Setup for the Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Open your <b>Bot Setup</b>.</p>
</step>
<step>
    <p>Add one <b>Dynamic Behavior Tree</b> entry for each behavior, mapping the appropriate <b>Dynamic Tags</b> to their respective assets.</p>
    <img src="bot_guide_dynamic_bt_setup.png" alt="Setup for Dynamic Behavior Tree" width="780" border-effect="line"/>
    <note>For now, the same dynamic trees are injected, but later on you can inject different behaviors per AI archetype.</note>
</step>
</procedure>
<!-- END: BOT SETUP WITH BEHAVIOR TREE -->

</tab>
<tab title="State Tree" group-key="st">

<!-- BEGIN: BOT SETUP WITH STATE TREE -->
<procedure title="Create the Combat State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Duplicate your <b>Base State Tree</b> and name the new asset <code>ST_Combat</code>. Remove all states, keeping only the <b>Combat</b> state at the <b>Root</b>.</p>
</step>
<step>
    <p>Create a new <b>Global Parameter</b> named <b>SensedActor</b> and set its type to <code>Actor</code>. Update all existing <b>SensedActor</b> bindings to use <code>Parameters.SensedActor</code> instead.</p>
    <img src="bot_guide_dynamic_st_combat.png" alt="Dynamic Combat State Tree" width="780" border-effect="line"/>
</step>
<step>
    <p>Add an <b>On State Completed</b> transition to the <b>Wait</b> state and set it to <b>Tree Succeeded</b>.</p>
</step>
<step>
    <p>Remove the <b>Perception Evaluator</b> inherited from the base State Tree.</p>
</step>
</procedure>

<procedure title="Create the Roam State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Duplicate your <b>Base State Tree</b> and name the new asset <code>ST_Roam</code>. Remove all states, keeping only the <b>Roam</b> state at the <b>Root</b>.</p>
</step>
<step>
    <p>Add an <b>On State Completed</b> transition to the <b>Move to Location</b> state and set it to <b>Tree Succeeded</b>. Remove the <b>Perception Evaluator</b>.</p>
    <img src="bot_guide_dynamic_st_roam.png" alt="Dynamic Roam State Tree" width="780" border-effect="line"/>
</step>
</procedure>

<procedure title="Create the Idle State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Duplicate your <b>Base State Tree</b> and name the new asset <code>ST_Idle</code>. Remove all states, keeping only the <b>Idle</b> state at the <b>Root</b>.</p>
</step>
<step>
    <p>Add an <b>On State Completed</b> transition to the <b>Wait</b> state and set it to <b>Tree Succeeded</b>. Remove the <b>Perception Evaluator</b>.</p>
    <img src="bot_guide_dynamic_st_idle.png" alt="Dynamic Idle State Tree" width="780" border-effect="line"/>
</step>
</procedure>

<procedure title="Update the Base State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Return to the <b>Base State Tree</b>, remove all state implementations, and add a single <b>Child State</b> to each main state: Combat &rarr; Run Combat Behavior, Roam &rarr; Run Roam Behavior, Idle &rarr; Run Idle Behavior.</p>
</step>
<step>
    <p>In the <b>Run Combat Behavior</b> state, set the <b>Tag</b> to <code>AI.Dynamic.Combat</code>, set the type to <b>Linked Asset</b>, and assign the Combat State Tree. This enables overriding the Combat Tree’s <b>SensedActor</b> parameter. Override it to use <code>UpdatePerception.SensedActor</code>.</p>
    <note>The State Trees assigned to each state act as <b>fallback behaviors</b> if no dynamic state is configured for a given Tag.</note>
    <img src="bot_guide_dynamic_st_full_01.png" alt="Full Dynamic Tree, Combat" width="780" border-effect="line"/>
</step>
<step>
    <p>In the <b>Run Roam Behavior</b> state, set the <b>Tag</b> to <code>AI.Dynamic.Roam</code>, set the type to <b>Linked Asset</b>, and assign the Roam State Tree. Add a <b>Tick</b> transition to <b>Combat</b> with <b>high priority</b> and a <b>Valid Object</b> condition that checks whether <code>UpdatePerception.SensedActor</code> is valid.</p>
    <note>The State Trees assigned to each state act as <b>fallback behaviors</b> if no dynamic state is configured for a given Tag.</note>
    <img src="bot_guide_dynamic_st_full_02.png" alt="Full Dynamic Tree, Roam" width="780" border-effect="line"/>
</step>
<step>
    <p>In the <b>Run Idle Behavior</b> state, set the <b>Tag</b> to <code>AI.Dynamic.Idle</code>, set the type to <b>Linked Asset</b>, and assign the Idle State Tree. Add a <b>Tick</b> transition to <b>Combat</b> with <b>high priority</b> and a <b>Valid Object</b> condition that checks whether <code>UpdatePerception.SensedActor</code> is valid.</p>
    <note>The State Trees assigned to each state act as <b>fallback behaviors</b> if no dynamic state is configured for a given Tag.</note>
    <img src="bot_guide_dynamic_st_full_03.png" alt="Full Dynamic Tree, Idle" width="780" border-effect="line"/>
</step>
</procedure>

<procedure title="Update the Bot Setup for the State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Open your <b>Bot Setup</b>.</p>
</step>
<step>
    <p>Add one <b>Dynamic State Tree</b> entry for each behavior, mapping the appropriate <b>Dynamic Tags</b> to their respective assets.</p>
    <img src="bot_guide_dynamic_st_setup.png" alt="Setup for Dynamic State Tree" width="780" border-effect="line"/>
    <note>For now, the same dynamic trees are injected, but later on you can inject different behaviors per AI archetype.</note>
</step>
</procedure>
<!-- END: BOT SETUP WITH STATE TREE -->

</tab>
</tabs>

Your Bot’s behavior should still remain the same. However, by using the **same base asset**, you can now mix and match multiple
authored behaviors to create different AI archetypes, and even swap behaviors dynamically based on context, such as:

- Patrol Points with their own set of dynamic behaviors.
- Different combat strategies based on the currently equipped weapon.
- Unique idle states for different types of idle breaks.
