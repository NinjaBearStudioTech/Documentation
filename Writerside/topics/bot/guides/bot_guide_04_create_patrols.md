# Build a Patrol Route
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Give the [First Steps guard](bot_first_steps.md) four posts to visit in order. Start with a duplicate Bot Setup and a copy of its main tree. Keep the chase behavior and replace roaming in the copy. The original guard can still roam.

<procedure title="Place four connected stops">
    <step><p>Create a Blueprint based on <b>NinjaBotPatrolPointActor</b>. Place four instances on the navigation mesh in a loop. Set each instance's <b>Next Patrol Point</b> to the following stop and link the last to the first.</p></step>
    <step><p>Give all four points a common <b>Patrol Point Tag</b>, such as <b>AI.Patrol.Lookout</b>. Register that gameplay tag in your project if needed.</p></step>
    <step><p>Create an <b>Environment Query</b> with an <b>Actors of Class</b> generator for NinjaBotPatrolPointActor. Use a search radius of 1400 and start the guard within that distance of a stop. Add a <b>Gameplay Tag</b> filter for your route tag and a <b>Distance to Querier</b> test with inverse linear scoring to prefer the nearest stop.</p></step>
</procedure>

<img src="bot_guide_patrol_point_eqs.png" alt="Query that finds a nearby patrol point on the tagged route" width="780" border-effect="line"/>

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<procedure title="Replace the Roam sequence">
    <step><p>Add an Object Blackboard key named <b>PatrolPoint</b> with base class <b>NinjaBotPatrolPointActor</b>.</p></step>
    <step><p>In place of Roam, create a Patrol sequence. First add a Selector that succeeds if PatrolPoint is already set, or otherwise runs your EQS query and writes the result to PatrolPoint. For the first child, use a short Wait with a <b>PatrolPoint Is Set</b> decorator.</p></step>
    <step><p>Next add a sequence for using the point. Attach the <b>Patrol Point Behavior</b> service. Set its point key to PatrolPoint and its injection tag to <b>AI.Dynamic.Patrol</b>. Inside the sequence, <b>Move To</b> PatrolPoint, then <b>Run Behavior Dynamic</b> with the same tag and a short wait tree as the fallback.</p></step>
    <step><p>End the sequence with <b>Advance Patrol Point</b>, using PatrolPoint as its Blackboard key. Each new pass through the sequence now starts with the next stop.</p></step>
</procedure>

<img src="bot_guide_behavior_tree_patrol.png" alt="Example patrol branch in a Behavior Tree" width="780" border-effect="line"/>

</tab>
<tab title="State Tree" group-key="st">

<procedure title="Replace the Roam states">
    <step><p>Add a root parameter <b>PatrolPoint</b> of type <b>Actor Object Reference</b>. Under Patrol, create states for finding the first point, moving to it, running its activity, and advancing.</p></step>
    <step><p>Enter Find only while PatrolPoint is invalid. Run your EQS query with the context actor as owner and bind the result to PatrolPoint. On success, transition to Move. If the guard already has a valid point, start at Move.</p></step>
    <step><p>In Move, bind <b>Move To → Target Actor</b> and <b>Set Patrol Point Behavior → Patrol Point</b> to PatrolPoint. Set the behavior task's injection tag to <b>AI.Dynamic.Patrol</b>.</p></step>
    <step><p>On arrival, transition to a <b>Linked Asset</b> state with the same tag and a short wait tree. When it completes, run <b>Advance Patrol Point</b>, binding its input and Result to PatrolPoint. Return to the patrol sequence to use the new point. Keep the transition to Chase when a player is sensed.</p></step>
</procedure>

<img src="bot_guide_state_tree_patrol.png" alt="Example route through the patrol states" width="780" border-effect="line"/>

</tab>
</tabs>

<procedure title="Give the lookout its own activity">
    <step><p>In the duplicate Bot Setup, assign your patrol tree and map <b>AI.Dynamic.Patrol</b> to the ordinary wait tree. Give one placed patrol point a longer wait using the matching Logic Type and tree. See <a href="bot_guide_03_dynamic_behaviors.md">Switch Behaviors at Runtime</a> for both versions.</p></step>
    <step><p>Assign the duplicate setup to a guard and place it near the route.</p></step>
</procedure>

## Try It in Play

Stay out of view and watch the guard visit all four posts, pause longer at the lookout, and start a second lap. If it revisits the nearest post every time, check the Next Patrol Point links and make sure the query runs only when the stored point is empty.
