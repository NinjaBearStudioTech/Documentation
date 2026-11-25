# Have an AI Recover When Energy Runs Low
<primary-label ref="gas"/>
<secondary-label ref="guide"/>

Give an AI-controlled pawn the [Recover ability and Energy attribute](gas_guide_starting_abilities.md). The pawn should recover below 30 energy and resume its normal behavior afterward. Use the tree type that already drives your AI.

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt" id="behavior-trees">

<procedure title="Choose recovery from the Blackboard">
    <step><p>Give the pawn an AI Controller running your Behavior Tree. In its Blackboard, add a <b>Float</b> key called <code>CurrentEnergy</code>. Attach the <b>Update Attributes</b> service to a Selector that stays active during both recovery and normal behavior. Map <b>Energy</b> to <code>CurrentEnergy</code>.</p></step>
    <step><p>Make the Selector's first child a recovery Sequence and the second its normal behavior. Add a Blackboard decorator to recovery for <code>CurrentEnergy</code> less than 30. Set <b>Observer Aborts</b> to <b>Lower Priority</b> so a drop in energy can interrupt normal behavior.</p></step>
    <step><p>Add <b>Activate Gameplay Ability</b> to recovery. Choose <b>Ability Class</b> and select <code>GA_Recover</code>. For the instant recovery move, turn off <b>Wait for Ability to End</b>. For a move with a recovery animation, enable that option and end the ability when the animation finishes.</p></step>
</procedure>

If several recovery moves are available, the **Select Gameplay Ability** service can write a choice into a Blackboard **Class** key. Set the activation task to **Blackboard Class** to consume it. A custom C++ service can subscribe to `GetGameplayAttributeValueChangeDelegate` on the pawn's component to update another decision value. Read the initial value when binding and remove the delegate when the service stops.

</tab>
<tab title="State Tree" group-key="st" id="state-trees">

<procedure title="Choose recovery in a State Tree">
    <step><p>Give <code>GA_Recover</code> the asset tag <code>Ability.Training.Recover</code>. Create a Blueprint State Tree evaluator, add it to the tree, and expose a float called <code>CurrentEnergy</code>. Give it an initial value above 30 until the pawn is ready. On Tree Start and on Tick, use <b>Get Float Attribute</b> on the controlled pawn to read <b>Energy</b>. Only use the value when the attribute lookup succeeds.</p></step>
    <step><p>Place a <b>Recover</b> state before the normal state under a parent that selects its first eligible child. Bind a float comparison on Recover's enter conditions to the evaluator's output and test for less than 30. From normal behavior, add a conditional transition to Recover when energy drops below 30 so the tree checks it again while running.</p></step>
    <step><p>In Recover, add <b>Activate Gameplay Ability</b> and set <b>Ability Activation Tags</b> to <code>Ability.Training.Recover</code>. Enable <b>Should Finish State When Ability Completes</b>. Transition to normal behavior on success. If interruption should stop the move, enable <b>Should Cancel Ability When State Finishes</b>.</p></step>
</procedure>

For a move with a cooldown, a utility-based State Tree can use the **Ability Cooldown** consideration. Match the tag granted by its cooldown effect and give the state a lower score while that effect is active. To limit repeated moves, the <b>Ability Tracker</b> evaluator exposes <b>Consecutive Executions</b> for abilities matching its filter.

</tab>
</tabs>

A Blueprint listening outside either tree can use **Wait For Ability End** with a query for the recovery ability's asset tag. The callback reports whether the ability was cancelled.

## Try It in Play

Start the pawn at 25 energy. Watch the pawn's Blackboard or State Tree debugger alongside its ability system. Recovery should run once, raise energy to 75, and return the pawn to normal behavior. Apply an effect that takes 50 energy away. The same pawn should choose recovery again when its value drops to 25. If the value changes but the pawn stays idle, check the ability grant on the controlled pawn and the class or asset tag used by the activation task.
