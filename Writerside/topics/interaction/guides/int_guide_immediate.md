# Run an Immediate Interaction in a State Tree
<primary-label ref="interaction"/>
<secondary-label ref="guide"/>

Make a switch toggle a light as soon as the player presses Use. Start with a [source and target that can focus each other](int_first_steps.md). This same tree can run after a Hold action confirms or after a proximity pickup is selected.

<procedure title="Give the switch a one-step tree">
    <step><p>Duplicate <code>ST_Interaction_Generic</code> into your game folder or create a State Tree with the <b>Interaction</b> schema. Add or keep the <b>Interaction State</b> evaluator.</p></step>
    <step><p>Make <b>Use Switch</b> the first active state and add <b>Trigger Target Behavior</b>. Bind <b>Target Actor</b> and <b>Smart Object Claim Handle</b> from Interaction State. Keep <b>Release Handle Automatically</b> on for this short action. On state success, finish the tree successfully. On failure, finish as failed.</p></step>
    <step><p>Assign this tree to the switch slot's <b>Execute Interaction</b> configuration. Use <code>Interaction.Type.Interact</code> for both the type and the slot's runtime tag. Set <b>Duration</b> to <code>0</code>. The first state should go straight to the behavior, with no wait, movement, or montage.</p></step>
    <step><p>Keep the base actor's immediate <b>Finished</b> result from <b>Start Interaction</b>. On its target component's <b>On Interaction Finished</b>, toggle the light once. For a shared light in multiplayer, change its state on the server and replicate the result.</p></step>
</procedure>

## Try It in Play

Focus the switch and press once. The light should change immediately. Keep holding the key and check that the light changes only once per press. Release and press again to switch it back. If it toggles twice, check that the input sends one request and that only one finish handler toggles the light.
