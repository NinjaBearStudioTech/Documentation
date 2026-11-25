# First Steps: Roam, Detect, and Chase
<primary-label ref="bot"/>

Build a guard that walks around until it sees the player, then follows them. Start with [Set Up Ninja Bot](bot_setup.md), a playable character, and a level with a **Nav Mesh Bounds Volume** covering the test area. Press **P** in the level viewport to check that the floor is green.

<procedure title="Give the guard sight">
    <step><p>In the Content Browser, choose <b>Ninja Bear Studio → Ninja Bot → Sense Profile</b>. Add <b>Sight</b> to its senses.</p></step>
    <step><p>Set <b>Sight Radius</b> to 1200 and <b>Lose Sight Radius</b> to 1400. Under <b>Detection by Affiliation</b>, enable enemies, friendlies and neutrals for this first test.</p></step>
    <step><p>Set <b>Dominant Sense</b> to Sight. Save the profile.</p></step>
</procedure>

<img src="bot_guide_perception_sense_profile.png" alt="Sight profile for the first guard" width="780" border-effect="line"/>

<procedure title="Give the guard somewhere to roam">
    <step><p>Create an <b>Environment Query</b> and add a <b>Pathing Grid</b> generator around the querier. Set <b>Grid Half Size</b> to 1000 and <b>Space Between</b> to 100.</p></step>
    <step><p>Add a <b>Distance</b> test from the querier. Filter for points between 300 and 1200 units away. Save the query as <b>EQS_Roam</b>.</p></step>
</procedure>

<img src="bot_guide_eqs_roam_generator.png" alt="Pathing grid for reachable roaming destinations" width="780" border-effect="line"/>

## Choose One Tree

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

Create these keys so the sight service and the roaming query each have somewhere to write their results.

| Key                                                              | Blackboard type                                            |
|------------------------------------------------------------------|------------------------------------------------------------|
| SensedActor                                                      | Object, base class Actor                                   |
| FirstPerceivedLocation, CurrentTargetLocation, LastKnownLocation | Vector                                                     |
| CandidateScore, NormalizedCandidateScore, AccumulatedAwareness   | Float                                                      |
| AwarenessLevel                                                   | Enum, with Enum Name set to `EBotPerceptionAwarenessLevel` |
| RoamLocation                                                     | Vector                                                     |

<procedure title="Build the Behavior Tree">
    <step><p>Create a <b>Blackboard</b> with the keys listed above. RoamLocation holds the destination the guard picks for itself.</p></step>
    <step><p>Create a <b>Behavior Tree</b> using that Blackboard. Add a <b>Selector</b> under Root. Attach the <b>Update Perception</b> service and match its outputs to the Blackboard keys of the same name. Leave RoamLocation for the query.</p></step>
    <step><p>Add a <b>Chase</b> sequence as the leftmost child. Give it a Blackboard decorator checking that SensedActor <b>Is Set</b>, with <b>Observer Aborts → Both</b>. Add <b>Move To</b> using SensedActor and a short <b>Wait</b> after it.</p></step>
    <step><p>Add a <b>Roam</b> sequence to the right. Run <b>EQS_Roam</b>, store the result in RoamLocation, then <b>Move To</b> that key. Add <b>Wait</b> as the last child of the selector for when the query fails.</p></step>
</procedure>

<img src="bot_guide_behavior_tree_perception_service.png" alt="Perception service fields paired with their Blackboard keys" width="780" border-effect="line"/>

<img src="bot_guide_behavior_tree_roam_branch.png" alt="The Roam sequence finds a location and moves to it" width="780" border-effect="line"/>

</tab>
<tab title="State Tree" group-key="st">

<procedure title="Build the State Tree">
    <step><p>Create a <b>State Tree</b> with the <b>State Tree AI Component</b> schema. Add the <b>Update Perception</b> evaluator and a Vector root parameter named <b>RoamLocation</b>.</p></step>
    <step><p>Under Root, add <b>Chase</b>, <b>Roam</b>, and <b>Idle</b> in that order. Give Chase an enter condition that checks whether <b>Update Perception → Sensed Actor</b> is valid. In Chase, use <b>Move To</b> with that actor as the target.</p></step>
    <step><p>Under Roam, add <b>Find Location</b> and <b>Walk</b>. In Find Location, run <b>EQS_Roam</b> with the context actor as Query Owner and RoamLocation as Result. On success, go to Walk. On failure, go to Idle. In Walk, move to RoamLocation, then go to Idle.</p></step>
    <step><p>In Idle, add a <b>Delay</b> of one second, then transition to Roam. Give Roam and Idle a high-priority <b>On Tick</b> transition to Chase when Sensed Actor is valid.</p></step>
    <step><p>Give Chase an <b>On Tick</b> transition back to Roam when Sensed Actor becomes invalid. On completion, return to Root so the guard can choose again. Compile the tree.</p></step>
</procedure>

<img src="bot_guide_state_tree_perception_evaluator.png" alt="Update Perception evaluator in the State Tree" width="780" border-effect="line"/>

</tab>
</tabs>

<procedure title="Connect the tree and place the guard">
    <step><p>In the folder registered with the Asset Manager, choose <b>Ninja Bear Studio → Ninja Bot → Bot Setup</b>. Select your <b>Brain Type</b>, assign the tree you just made, and set <b>Perception Sense Profile</b> to your sight profile.</p></step>
    <step><p>Create a <b>Character</b> Blueprint. In <b>Class Settings</b>, add <b>Bot Setup Provider Interface</b>. Open <b>Get Bot Setup Data</b> and return your Bot Setup asset.</p></step>
    <step><p>In Class Defaults, set <b>AI Controller Class</b> to <code>NinjaBotAIController</code> and <b>Auto Possess AI</b> to <b>Placed in World or Spawned</b>. Compile and place the guard on navigable ground.</p></step>
</procedure>

<img src="bot_guide_character_setup_data.png" alt="The character returns the Bot Setup it will use" width="780" border-effect="line"/>

## Try It in Play

Start outside sight range. The guard should pick a destination and walk. Step in front of it and it should change course to follow you. Leave sight range and watch it return to roaming when the target clears.

If it stands still, inspect the active tree and check the navigation mesh. If it roams but ignores you, check the sight profile on the setup and the [player's sight registration](bot_setup.md). Next, [give roaming and chasing different speeds](bot_guide_01_movement_profile.md).
