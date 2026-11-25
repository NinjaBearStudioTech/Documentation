# Use Faction Attitude in AI Decisions
<primary-label ref="factions"/>
<secondary-label ref="guide"/>

Make a guard greet a friendly target and chase a hostile one. Start with a guard whose AI Controller already runs a tree and has a target actor. The target can come from perception or from a reference you supply for testing. For perception through Ninja Bot, see [Bot and Factions](integration_bot_factions.md).

## Behavior Tree

<procedure title="Choose a branch using the Blackboard">
    <step><p>In the Blackboard, add <b>Target</b> (Object, base class Actor), <b>TeamID</b> (Int), <b>FactionName</b> (Name), and <b>Alignment</b> (Enum, <code>ETeamAttitude</code>). Have the controller write the current target to <b>Target</b>.</p></step>
    <step><p>Attach the <b>Faction Data</b> service to the selector that contains both reactions. Set <b>Faction Member Key</b> to Target. Map the three output keys to TeamID, FactionName, and Alignment. <b>Attitude Towards Agent Key</b> holds the guard's attitude toward the target.</p></step>
    <step><p>Add a <b>Check Attitude</b> decorator to the chase branch. Select Alignment as its <b>Attitude Key</b> and <b>Hostile</b> as its <b>Attitude Test</b>. Add another to the greeting branch and choose <b>Friendly</b>. Require a valid Target on both branches and leave a patrol or wait branch for other cases.</p></step>
</procedure>

<tabs>
    <tab title="Service"><img src="fct_bt_service.png" alt="Faction Data service writing the target's team, faction name, and alignment" width="780" border-effect="line"/></tab>
    <tab title="Decorator"><img src="fct_bt_decorator.png" alt="Check Attitude decorator testing a Blackboard key" width="780" border-effect="line"/></tab>
</tabs>

## State Tree

<procedure title="Choose a state using the target actor">
    <step><p>Run the State Tree on the guard's controller and expose the current target actor for binding. On the chase state's <b>Enter Conditions</b>, add <b>Check Attitude</b>, bind <b>Target</b> to that actor, and set <b>Attitude Test</b> to <b>Hostile</b>. The condition asks how the controller sees that actor.</p></step>
    <step><p>Give the greeting state its own <b>Check Attitude</b> condition set to <b>Friendly</b>. Leave a patrol or wait state available when neither condition passes. Arrange for the tree to select a state again when you change targets.</p></step>
    <step><p>If a task also needs the target's team ID or faction tag, add the <b>Faction Data</b> evaluator and bind its <b>Faction Member</b> to the target. Tasks can then read its outputs. The enter condition only needs the target actor.</p></step>
</procedure>

<img src="fct_st_evaluator.png" alt="Faction Data evaluator with a member input and team, faction, and attitude outputs" width="780" border-effect="line"/>

## Try It in Play

With **Simple Attitude Check**, configure the guard's faction as Friendly toward itself and Hostile toward other factions. Give it an ally as the target, then an outsider. Expect the greeting branch for the ally and the chase branch for the outsider. Clear the target and confirm the guard can resume its patrol. If the wrong branch runs, print **Get Attitude** with the guard as Source and the current target as Target, then compare it with the value the tree uses.
