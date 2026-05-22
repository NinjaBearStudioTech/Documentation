# Creating and Using Patrol Points
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Having **dynamic behaviors** configured opens the opportunity to mix and match assets and create **diverse AI archetypes**.
In this chapter, we will leverage that flexibility by creating another AI agent, replacing the previous **random roaming**
behavior with a **patrolling behavior**.

To achieve this, we will create the following assets:

1. A **Patrol Point Blueprint** that can be further customized to fit your project’s needs.
2. A **Dynamic Behavior/State Tree** (_search_) defining the actions the AI performs upon reaching a patrol point.
3. A **Dynamic Behavior/State Tree** (_patrol_) that overrides the roaming behavior, allowing the AI to locate and use patrol points.
4. A new **Bot Setup** and an additional **AI Character Blueprint** that will use this configuration.

<procedure title="Create and Place Patrol Points" collapsible="true" default-state="collapsed">
<step>
    <p>Create a Blueprint based on <code>ANinjaBotPatrolPointActor</code>.</p>
</step>
<step>
    <p>Place <b>four Patrol Point Blueprints</b> in your map so they form a square.</p>
</step>
<step>
    <p>Select the <b>first patrol point</b> and assign the <b>second patrol point</b> as its <b>Next Patrol Point</b>.</p>
</step>
<step>
    <p>Select the <b>second patrol point</b> and assign the <b>third patrol point</b> as its <b>Next Patrol Point</b>.</p>
</step>
<step>
    <p>Select the <b>third patrol point</b> and assign the <b>fourth patrol point</b> as its <b>Next Patrol Point</b>.</p>
</step>
<step>
    <p>Select the <b>fourth patrol point</b> and assign the <b>first patrol point</b> as its <b>Next Patrol Point</b>, completing the patrol path.</p>
</step>
<step>
    <p>Select all patrol points and add a Gameplay Tag to <b>Patrol Point Tags</b> that identifies the <b>patrol path</b>, such as <code>AI.Patrol.Lookout</code>.</p>
</step>
</procedure>

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<!-- BEGIN: SEARCH BEHAVIOR TREE -->
<procedure title="Create the Search Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Create a new <b>Behavior Tree</b> for the <b>Search Behavior</b>, name it <code>BT_Search</code>, and assign the shared <b>Enemy Blackboard</b>.</p>
</step>
<step>
    <p>Create a <b>Sequence</b> and name it <b>Look Around</b>.</p>
</step>
<step>
    <p>Add an Animation Montage or Gameplay Ability task that represents the search action. After that, add a <b>Wait</b> task with a duration of <code>3</code>.</p>
    <img src="bot_guide_behavior_tree_search.png" alt="Search Behavior Tree" width="780" border-effect="line"/>
    <note><a href="gas_overview.md" alt="Ninja GAS"><b>Ninja GAS</b></a> provides tasks to activate Gameplay Abilities by class or by Gameplay Tag.</note>
</step>
<step>
    <p>Open your Patrol Point Blueprint, set its <b>Logic Type</b> to <b>Behavior Tree</b>, and assign <code>BT_Search</code> as its <b>Behavior Tree Asset</b>.</p>
    <img src="bot_guide_patrol_point_behavior_tree.png" alt="Patrol Point with a Behavior Tree" border-effect="line"/>
    <note>You can also configure the logic type and asset per Patrol Point instance placed in the level.</note>
</step>
</procedure>
<!-- END: SEARCH BEHAVIOR TREE -->

</tab>
<tab title="State Tree" group-key="st">

<!-- BEGIN: SEARCH STATE TREE -->
<procedure title="Create the Search State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Create a new <b>State Tree</b> for the <b>Search Behavior</b>, name it <code>ST_Search</code>, using the <b>AI Component Schema</b>.</p>
</step>
<step>
    <p>Rename the <b>Root State</b> to <b>Search</b> and create two <b>Child States</b> from it.</p>
</step>
<step>
    <p>In the first child state, add an Animation Montage or Gameplay Ability task that represents the search action. In the second state, add a <b>Wait</b> task with a duration of <code>3</code>.</p>
    <img src="bot_guide_state_tree_search.png" alt="Search State Tree" width="780" border-effect="line"/>
    <note><a href="gas_overview.md" alt="Ninja GAS"><b>Ninja GAS</b></a> provides tasks to activate Gameplay Abilities by class or by Gameplay Tag.</note>
</step>
<step>
    <p>Open your Patrol Point Blueprint, set its <b>Logic Type</b> to <b>State Tree</b>, and assign <code>ST_Search</code> as its <b>State Tree Asset</b>.</p>
    <img src="bot_guide_patrol_point_state_tree.png" alt="Patrol Point with a State Tree" border-effect="line"/>
    <note>You can also configure the logic type and asset per Patrol Point instance placed in the level.</note>
</step>
</procedure>
<!-- END: SEARCH STATE TREE -->

</tab>
</tabs>

<procedure title="Create the Patrol Point Environment Query" collapsible="true" default-state="collapsed">
<step>
    <p>Create a new <b>Environment Query</b> for the <b>Patrol Point Search</b>.</p>
</step>
<step>
    <p>Add an <b>Actors of Class</b> generator. Set <code>NinjaBotPatrolPointActor</code> as the <b>Searched Actor Class</b> and configure a <b>Search Radius</b> of <code>1400</code>.</p>
</step>
<step>
    <p>Add a <b>Gameplay Tag</b> test, set it to <b>Filter Only</b>, and configure the <b>Tag Query to Match</b> so it matches the identifying Gameplay Tag added to your patrol points (for example, <code>AI.Patrol.Lookout</code>).</p>
</step>
<step>
    <p>Add a <b>Distance to Querier</b> test. Set the <b>Float Max Value</b> to <code>1400</code> and the <b>Scoring Equation</b> to <code>Inverse Linear</code>, so closer patrol points are preferred.</p>
    <img src="bot_guide_patrol_point_eqs.png" alt="Patrol Point Search" border-effect="line"/>
</step>
</procedure>

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<!-- BEGIN: PATROL BEHAVIOR TREE -->
<procedure title="Update the Blackboard for the Patrol Point" collapsible="true" default-state="collapsed">
<step>
    <p>Open the shared <b>Enemy Blackboard</b> used by the main Behavior Tree.</p>
</step>
<step>
    <p>Create an additional <b>Object</b> Key Type named <b>PatrolPoint</b>. Set its <b>Base Class</b> to <code>NinjaBotPatrolPointActor</code> and add it to a new category named <b>Patrol</b>.</p>
    <img src="bot_guide_patrol_point_blackboard.png" alt="Patrol Point Blackboard" border-effect="line"/>
</step>
</procedure>

<procedure title="Create the Patrol Behavior Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Create a new <b>Behavior Tree</b> for the <b>Patrol Behavior</b>, name it <code>BT_Patrol</code>, and assign the shared <b>Enemy Blackboard</b>.</p>
</step>
<step>
    <p>Create a <b>Sequence</b> and name it <b>Patrol</b>.</p>
</step>
<step>
    <p>Add a <b>Set Movement</b> task and set the <b>Movement Profile Tag</b> to <code>AI.Movement.Walking</code>.</p>
</step>
<step>
    <p>Add a <b>Run EQS Query</b> task, rename it to <b>Find Patrol Point</b>, set the previously created <b>Query Template</b>, and configure the output <b>Blackboard Key</b> to <code>PatrolPoint</code>.</p>
</step>
<step>
    <p>Add a <b>Blackboard Decorator</b> to the <b>Find Patrol Point</b> task that checks whether the <b>PatrolPoint</b> key is <b>not set</b>. Also add a <b>Force Success</b> decorator to this task.</p>
</step>
<step>
    <p>Add a new <b>Sequence</b> composite node named <b>Use Patrol Point</b>. Add a <b>Blackboard Decorator</b> that checks whether the <b>PatrolPoint</b> key is <b>set</b>. Add the <b>Patrol Point Behavior Service</b> to this sequence, set the <b>Dynamic Injection Tag</b> to <code>AI.Dynamic.Patrol</code>, and select the appropriate <b>Patrol Point Key</b>.</p>
</step>
<step>
    <p>Within the <b>Use Patrol Point</b> sequence, add a <b>Move To</b> task using the <b>PatrolPoint</b> Blackboard entry as the target.</p>
</step>
<step>
    <p>Add a <b>Dynamic Behavior</b> task named <b>Run Patrol Behavior</b>. Set the <b>Injection Tag</b> to <code>AI.Dynamic.Patrol</code> and the <b>Default Behavior Asset</b> to the <b>Idle</b> Behavior Tree.</p> 
    <note>The <b>Default Behavior Asset</b> is used when the current patrol point does not provide a specific behavior.</note>
</step>
<img src="bot_guide_behavior_tree_patrol.png" alt="Patrol Behavior Tree" width="780" border-effect="line"/>
</procedure>
<!-- END: PATROL BEHAVIOR TREE -->

</tab>
<tab title="State Tree" group-key="st">

<!-- BEGIN: PATROL STATE TREE -->
<procedure title="Create the Patrol State Tree" collapsible="true" default-state="collapsed">
<step>
    <p>Create a new <b>State Tree</b> for the <b>Patrol Behavior</b>, name it <code>ST_Patrol</code>, using the <b>AI Component Schema</b>.</p>
</step>
<step>
    <p>Rename the <b>Root State</b> to <b>Patrol</b> and create two <b>Child States</b> from it. Add a new <b>Parameter</b> named <b>PatrolPoint</b> and set its type to <b>Vector</b>.</p>
</step>
<step>
    <p>Rename the first child state to <b>Start Walking</b>. Add a <b>Set Movement</b> task applying the <code>AI.Movement.Walking</code> profile, then add an <b>On State Completed</b> transition to the <b>Next State</b>.</p>
</step>
<step>
    <p>Rename the second child state to <b>Iterate Patrol Points</b> and create four <b>Child States</b> from it.</p>
</step>
<step>
    <p>Rename the first new state to <b>Find Patrol Point</b>. Add an <b>Object Valid</b> Enter Condition, bind it to <code>Parameters.PatrolPoint</code>, and <b>invert</b> the condition.</p>
</step>
<step>
    <p>In the <b>Find Patrol Point</b> state, add a <b>Run EQS Query</b> task. Bind the <b>Result</b> to <code>Parameters.PatrolPoint</code>, the <b>Query Owner</b> to the context <b>Actor</b>, and set the previously created <b>Query Template</b>. Add an <b>On State Completed</b> transition to the <b>Next State</b>.</p>
</step>
<step>
    <p>Rename the second state in <b>Iterate Patrol Points</b> to <b>Update and Move to Patrol Point</b>. Add two <b>Enter Conditions</b>: first, verify that <code>Parameters.PatrolPoint</code> is a <b>valid object</b>, and second, verify that it is a <b>valid subclass</b> of <code>NinjaBotPatrolPointActor</code>.</p>
</step>
<step>
    <p>In the <b>Update and Move to Patrol Point</b> state, add a <b>Move To</b> task and bind the <b>Target Actor</b> to <code>Parameters.PatrolPoint</code>. Then add a <b>Set Patrol Point Behavior</b> task, binding the <b>Patrol Point</b> to <code>Parameters.PatrolPoint</code> and the <b>Dynamic Injection Tag</b> to <code>AI.Dynamic.Patrol</code>. Add an <b>On State Completed</b> transition to the <b>Next State</b>.</p>
</step>
<step>
    <p>Rename the third state in <b>Iterate Patrol Points</b> to <b>Execute Patrol Logic</b>. Set its <b>Tag</b> to <code>AI.Dynamic.Patrol</code>, its <b>Type</b> to <b>Linked Asset</b>, and set the <b>Idle</b> State Tree as the <b>Default Asset</b>. Add an <b>On State Completed</b> transition to the <b>Next State</b>.</p>
</step>
<step>
    <p>Rename the fourth state to <b>Advance Patrol Point</b>. Add the <b>Advance Patrol Point</b> task and bind both the <b>Patrol Point</b> and <b>Result</b> to <code>Parameters.PatrolPoint</code>. Add an <b>On State Completed</b> transition back to <b>Iterate Patrol Points</b>.</p>
    <note>Routing the final transition back to <b>Iterate Patrol Points</b> ensures the AI continuously follows the patrol path until the <b>Enemy State Tree</b> interrupts execution.</note>
</step>
<img src="bot_guide_state_tree_patrol.png" alt="Patrol State Tree" width="780" border-effect="line"/>
</procedure>
<!-- END: PATROL STATE TREE -->

</tab>
</tabs>

<procedure title="Create the Second Bot" collapsible="true" default-state="collapsed">
<step>
    <p>Duplicate your existing <b>Bot Setup Asset</b>, including all configured dynamic tags and assets.</p>
</step>
<step>
    <p>Change the asset assigned to <code>AI.Dynamic.Roam</code> so it uses the new <b>Patrol</b> asset.</p>
</step>
<step>
    <p>Duplicate your <b>AI Pawn or Character Blueprint</b> and assign the new <b>Bot Setup Asset</b> to it.</p>
</step>
</procedure>

The new **Patrol Behavior** may appear more complex at first, but it follows a clear and **repeatable flow**:

1. If no patrol point is currently set, the AI searches for one using an EQS query.
2. The selected patrol point is stored, the AI moves toward it, and any logic provided by that patrol point is executed (falling back to an idle behavior when no logic is defined).
3. Once completed, the next patrol point is retrieved from the current one, and the process repeats.
4. This loop is driven by the primary Enemy Tree and continues until the main context changes (for example, when a target is sensed and selected).

At this point, you should have a second Bot that follows a defined **patrol path** in the level. Upon reaching each patrol point,
the Bot triggers an additional **dynamic behavior**, such as a _search_ action.

Meanwhile, your original Bot remains unchanged and continues to wander by selecting random locations from the Navigation Mesh.
Together, these setups illustrate how behaviors can be specialized for different requirements and combined into distinct AI
archetypes through **aggregation** and composition of Data Assets.
