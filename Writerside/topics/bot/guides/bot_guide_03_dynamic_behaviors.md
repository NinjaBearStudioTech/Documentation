# Switch Behaviors at Runtime
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Give a guard a usual activity and let a patrol stop replace it temporarily. For example, the guard can pause for one second at ordinary stops and look around for four seconds at a lookout. Use the tree from [First Steps](bot_first_steps.md). If your level has no patrol points yet, the [patrol route guide](bot_guide_04_create_patrols.md) shows how to connect them.

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<procedure title="Give the Behavior Tree two possible activities">
    <step><p>Create <b>BT_Pause</b> and <b>BT_Lookout</b> using your guard's Blackboard. Give each a Sequence with a Wait task. Use one second in Pause and four in Lookout.</p></step>
    <step><p>In the branch that runs after arriving at a stop, add <b>Run Behavior Dynamic</b>. Set its injection tag to <b>AI.Dynamic.Patrol</b> and its fallback asset to BT_Pause. Map the same tag to BT_Pause in <b>Bot Setup → Dynamic Behavior Trees</b>.</p></step>
    <step><p>Add the <b>Patrol Point Behavior</b> service to the sequence that uses the stop. Choose the Blackboard key holding the current point and the same injection tag. On the lookout point, set Logic Type to Behavior Tree and choose BT_Lookout. Leave the next point without an activity. The service reads each point when its branch becomes active.</p></step>
</procedure>

<img src="bot_guide_patrol_point_behavior_tree.png" alt="A Behavior Tree assigned to one patrol point" width="780" border-effect="line"/>

</tab>
<tab title="State Tree" group-key="st">

<procedure title="Give a linked State Tree a per-stop duration">
    <step><p>Create an AI State Tree named <b>ST_Pause</b>. Add a Float root parameter named <b>PauseSeconds</b> and bind it to the Duration of a Delay task. Finish the tree successfully after the delay. Compile it.</p></step>
    <step><p>In the patrol tree, set the state that runs on arrival to <b>Linked Asset</b>. Select ST_Pause and set the state tag to <b>AI.Dynamic.Patrol</b>.</p></step>
    <step><p>In <b>Bot Setup → Linked State Trees</b>, add that tag and select ST_Pause. Enable the override for PauseSeconds and enter 1. On the lookout point, set Logic Type to State Tree, choose ST_Pause, and override PauseSeconds to 4.</p></step>
    <step><p>Before entering the linked state, run <b>Set Patrol Point Behavior</b> with the current point and the same tag. Leave the following point without its own tree. On that visit the task restores the setup's reference, including the one-second override.</p></step>
</procedure>

</tab>
</tabs>

## Try It in Play

Watch a full lap. The guard should pause longer at the lookout, then return to its ordinary pause at the next stop. If every stop uses the same duration, check the point instance and compare the tag on the service or task with the tag on the dynamic branch.
