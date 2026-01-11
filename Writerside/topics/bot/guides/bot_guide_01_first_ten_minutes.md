# Your First Ten Minutes
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

This guide walks through the essential steps you’ll tackle in your first few minutes with **Ninja Bot**, resulting in a 
functional **roaming and chasing AI**.

It is intended to give you a basic overview of Ninja Bot and its common workflows. By the end of this guide, you will have 
a simple AI agent with three states: **idle**, **roam**, and **chase**. The main trigger between these states is whether 
the player is sensed or not.

Before starting, make sure the following **pre-requisites** are completed:

1. **Install and configure Ninja Bot**, including the [**Asset Manager setup**](bot_setup_asset_manager.md).
2. Use a template, such as the Combat Third Person Template, and verify that a **Navigation Mesh** is present in the map.

It is also recommended that your **Gameplay Debugger** is configured, so you can inspect the Bot’s perception data and 
evaluate its active AI states during gameplay.

<procedure title="Create the Perception Configuration" collapsible="true" default-state="collapsed">
<step>
    <p>In your Perception Data folder, create a new <b>Perception Sense Profile</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Bot &rarr; Sense Profile.</p>
</step>
<step>
    <p>Add the <b>Sight</b> sense to the list of senses. Configure <b>Sight Radius</b> to <code>1200</code> and <b>Lose Sight Radius</b> to <code>1400</code>.</p>
</step>
<step>
    <p>Mark Enemies, Neutrals, and Friendlies in <b>Detection by Affiliation</b>.</p>
    <note>For now, no <b>Affiliation</b> or <b>Team Attitude</b> is configured. Once we complete that setup, we will revisit this configuration.</note>
</step>
<step>
    <p>Set <b>Sight</b> as the <b>Dominant Sense</b>.</p>
    <note>A dominant sense is <b>always required</b>, even if only a single sense is configured in the Perception Sense Profile.</note>
</step>
<img src="bot_guide_perception_sense_profile.png" alt="Perception Sense Profile" width="780" border-effect="line"/>
</procedure>

<procedure title="Create the Roaming Environment Query" collapsible="true" default-state="collapsed">
<tip>The roaming behavior is included for demonstration and completeness, but it does not involve any Ninja Bot-specific setup.</tip>
<step>
    <p>Create an <b>Environment Query</b> that retrieves random locations from the Navigation Mesh.</p>
</step>
<step>
    <p>Add a <b>Pathing Grid Generator</b> with <b>Grid Half Size</b> set to <code>1000</code> and <b>Space Between</b> set to <code>100</code>.</p>
    <img src="bot_guide_eqs_roam_generator.png" alt="EQS, Roam Generator" width="780" border-effect="line"/>
</step>
<step>
    <p>Add a <b>Distance Test</b> with <b>Float Value Min</b> set to <code>300</code> and <b>Float Value Max</b> set to <code>1200</code>.</p>
    <img src="bot_guide_eqs_roam_test_distance.png" alt="EQS, Distance Test" width="780" border-effect="line"/>
</step>
</procedure>

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<!-- BEGIN: BEHAVIOR TREE CONFIGURATION -->
<procedure title="Create the Blackboard" collapsible="true" default-state="collapsed">
<step>
    <p>In your AI folder, create a new <b>Blackboard</b> that will be used to store contextual data available to the AI agent.</p>
</step>
<step>
    <p>Create an entry for <b>SensedActor</b>, setting the <b>Key Type</b> to <code>Object</code> and the <b>Base Class</b> to <code>Actor</code>. Create a new <b>Entry Category</b> named <b>Perception</b>.</p>
    <img src="bot_guide_blackboard_sensed_actor.png" alt="Blackboard, Sensed Actor" width="780" border-effect="line"/> 
</step>
<step>
    <p>Create three new <b>float</b> Key Types: <b>CandidateScore</b>, <b>NormalizedCandidateScore</b>, and <b>AccumulatedAwareness</b>. Add them to the <b>Perception</b> category.</p>
</step>
<step>
    <p>Create an entry for <b>AwarenessLevel</b>, setting the <b>Key Type</b> to <code>Enum</code>. Set the <b>Enum Name</b> to <code>EBotPerceptionAwarenessLevel</code>. Add this entry to the <b>Perception</b> category.</p>
    <img src="bot_guide_blackboard_awareness_level.png" alt="Blackboard, Awareness Level" width="780" border-effect="line"/>
    <note>When setting the Enum Name, make sure the <b>Enum Type</b> is correctly assigned automatically and the <b>Default Value</b> is set to <code>Unaware</code>.</note>
</step>
<step>
    <p>Create three new <b>Vector</b> Key Types: <b>FirstPerceivedLocation</b>, <b>CurrentTargetLocation</b>, and <b>LastKnownLocation</b>. Add them to the <b>Perception</b> category.</p>
</step>
<step>
    <p>Create one additional <b>Vector</b> Key Type, <b>RoamLocation</b>. Add it to a new category named <b>Roam</b>.</p>
</step>
</procedure>

<procedure title="Create the Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Create a <b>Behavior Tree</b> and assign the <b>Blackboard</b> to it.</p>
</step>
<step>
    <p>From the Root node, create a <b>Selector</b> composite node and add the <b>Update Perception Service</b> to it. Match each property to the correct <b>blackboard key</b>.</p>
    <img src="bot_guide_behavior_tree_perception_service.png" alt="Behavior Tree, Update Perception Service" width="780" border-effect="line"/>
</step>
<step>
    <p>From the top Selector node, create a <b>Sequence</b> composite node for <b>Combat</b>. Add a <b>Blackboard Decorator</b> to check whether the <b>SensedActor</b> key is set. This Decorator should be configured to <b>abort both itself and lower priority nodes</b>.</p>
    <img src="bot_guide_behavior_tree_combat_branch_01.png" alt="Behavior Tree, Combat Branch 1" width="780" border-effect="line"/>
</step>
<step>
    <p>Add a <b>Move To</b> Task, using the <b>SensedActor</b> key as the <b>Target Location</b> and an <b>Acceptable Radius</b> of <code>50</code>. Add an <b>Is At Location</b> decorator using the same parameters, followed by a <b>Force Success</b> decorator. Lastly, add a <b>Wait</b> task set to <code>1 second</code> with a <b>Random Deviation</b> of <code>0.2</code>.</p>
    <img src="bot_guide_behavior_tree_combat_branch_02.png" alt="Behavior Tree, Combat Branch 2" width="780" border-effect="line"/>
</step>
<step>
    <p>From the top Selector node, create another <b>Sequence</b> composite node for <b>Roam</b>. Add a <b>Run EQS Query</b> task using the Environment Query created earlier, and configure it to write its result to the <b>RoamLocation</b> key. Add another <b>Move To</b> task using the <b>RoamLocation</b> key as the <b>Target Location</b>.</p>
    <img src="bot_guide_behavior_tree_roam_branch.png" alt="Behavior Tree, Roam Branch" width="780" border-effect="line"/>
</step>
<step>
    <p>Complete the Behavior Tree with another <b>Sequence</b> composite node for <b>Idle</b>. Add a <b>Wait</b> task set to <code>5 seconds</code>.</p>
    <img src="bot_guide_behavior_tree_idle_branch.png" alt="Behavior Tree, Idle Branch" width="780" border-effect="line"/>
</step>
</procedure>
<!-- END: BEHAVIOR TREE CONFIGURATION -->

</tab>
<tab title="State Tree" group-key="st">

<!-- BEGIN: STATE TREE CONFIGURATION -->
<procedure title="Create the State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Create a State Tree using the <b>State Tree AI Component</b> Schema.</p>
</step>
<step>
    <p>Add the <b>Update Perception</b> evaluator.</p>
    <img src="bot_guide_state_tree_perception_evaluator.png" alt="State Tree, Update Perception Evaluator" width="780" border-effect="line"/>
</step>
<step>
    <p>From the Root node, add a <b>Child State</b> named <b>Combat</b>. Add an <b>Object Is Valid</b> Enter Condition, checking <code>UpdatePerception.SensedActor</code>.</p>
    <img src="bot_guide_state_tree_combat_state_01.png" alt="State Tree, Combat State 1" width="780" border-effect="line"/>
</step>
<step>
    <p>From the Combat state, add a <b>Child State</b> named <b>Move to Target</b>. Add a <b>Distance Compare</b> Enter Condition comparing the <b>Bot</b> and <b>Target</b> locations, a <b>Move To</b> task targeting <code>UpdatePerception.SensedActor</code>, and a <b>State Completed</b> transition to the <b>Next State</b>.</p>
    <img src="bot_guide_state_tree_combat_state_02.png" alt="State Tree, Combat State 2" width="780" border-effect="line"/>
</step>
<step>
    <p>Add another state named <b>Wait</b>. Add a <b>Delay</b> task with a <b>Duration</b> of <code>1.0</code> and a <b>Random Deviation</b> of <code>0.2</code>.</p>
    <img src="bot_guide_state_tree_combat_state_03.png" alt="State Tree, Combat State 3" width="780" border-effect="line"/>
</step>
<step>
    <p>From the Combat state, add a <b>Sibling State</b> named <b>Roam</b>. Create a <b>Vector Parameter</b> named <b>Roam Location</b>.</p>
    <img src="bot_guide_state_tree_roam_state_01.png" alt="State Tree, Roam State 1" width="780" border-effect="line"/>
</step>
<step>
    <p>From the Roam state, add a <b>Child State</b> named <b>Find Location</b>. Add a <b>Run EQS Query</b> task, bind the <b>Result</b> to the <b>Roam Location</b> parameter, bind the <b>Query Owner</b> to the <b>Context Actor</b>, and set the <b>Query Template</b>. Add an <b>On State Completed</b> transition to <b>Next State</b>.</p>
    <img src="bot_guide_state_tree_roam_state_02.png" alt="State Tree, Roam State 2" width="780" border-effect="line"/>
</step>
<step>
    <p>Add another state named <b>Move to Location</b>, and from the <b>Roam</b> state add another sibling named <b>Idle</b>. For <b>Move to Location</b>, add a <b>Move To</b> task and bind the <b>AI Controller</b> from the <b>Context</b>, and the <b>Destination</b> to <code>Parameters.RoamLocation</code>. Add an <b>On State Completed</b> transition to <b>Idle</b>.</p>
    <img src="bot_guide_state_tree_roam_state_03.png" alt="State Tree, Roam State 3" width="780" border-effect="line"/>
</step>
<step>
    <p>From the Idle state, add a <b>Child State</b> named <b>Wait</b>. Add a <b>Delay</b> task with a <b>Duration</b> of <code>5.0</code>.</p>
    <img src="bot_guide_state_tree_idle_state.png" alt="State Tree, Idle" width="780" border-effect="line"/>
</step>
</procedure>
<!-- END: STATE TREE CONFIGURATION -->

</tab>
</tabs>

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<!-- BEGIN: BOT SETUP WITH BEHAVIOR TREE -->
<procedure title="Create the Bot Setup" collapsible="true" default-state="collapsed">
<step>
    <p>In your Bot Setup Data folder, create a new <b>Bot Setup</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Bot &rarr; Bot Setup.</p>
    <note>Bot Setup assets are <b>Primary Assets</b> and must be placed in a folder registered with the <a href="bot_setup_asset_manager.md"><b>Asset Manager</b></a>.</note>
</step>
<step>
    <p>Set the <b>Brain Type</b> to <b>Behavior Tree</b> and assign your Behavior Tree asset.</p>
    <img src="bot_guide_setup_basic_bt.png" alt="Bot Setup with Behavior Tree" width="780" border-effect="line"/>
</step>
</procedure>
<!-- END: BOT SETUP WITH BEHAVIOR TREE -->

</tab>
<tab title="State Tree" group-key="st">

<!-- BEGIN: BOT SETUP WITH STATE TREE -->
<procedure title="Create the Bot Setup" collapsible="true" default-state="collapsed">
<step>
    <p>In your Bot Setup Data folder, create a new <b>Bot Setup</b>, using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Bot &rarr; Bot Setup.</p>
    <note>Bot Setup assets are <b>Primary Assets</b> and must be added to the folder registered with the <a href="bot_setup_asset_manager.md"><b>Asset Manager</b></a>.</note>
</step>
<step>
    <p>Set the <b>Brain Type</b> to <b>State Tree</b> and add your State Tree asset.</p>
    <img src="bot_guide_setup_basic_st.png" alt="Bot Setup with State Tree" width="780" border-effect="line"/>
</step>
</procedure>
<!-- END: BOT SETUP WITH STATE TREE -->

</tab>
</tabs>

<procedure title="Create the Bot Character" collapsible="true" default-state="collapsed">
<step>
    <p>Create a new <b>Character</b> and add the <b>Bot Setup Provider Interface</b>.</p>
    <img src="bot_guide_character_bot_interface.png" alt="Adding the Bot Setup Provider Interface" width="780" border-effect="line"/>
</step>
<step>
    <p>Double-click <code>GetBotSetupData</code> from the list of Interface Functions. Drag from the <b>Return Value</b> and <b>Promote it to a Variable</b>. Set the Bot Setup as its <b>default value</b>.</p>
    <img src="bot_guide_character_setup_data.png" alt="Configuring the Bot Setup data" width="780" border-effect="line"/>
</step>
<step>
    <p>In the <b>Character Defaults</b>, locate the <b>AI Controller Class</b> and set it to <code>NinjaBotAIController</code>.</p>
    <img src="bot_guide_character_bot_controller.png" alt="Configuring the Bot Controller" width="780" border-effect="line"/>
</step>
</procedure>

At this point, you should have a Bot that **roams around the environment until it detects the player**. Once the player 
is sensed, the Bot transitions into a chase behavior and **actively pursues the target**.
