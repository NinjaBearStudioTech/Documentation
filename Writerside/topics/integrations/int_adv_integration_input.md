# Input and Interaction: Start and Cancel an Interaction
<primary-label ref="integrations"/>
<secondary-label ref="input-sec"/>
<secondary-label ref="interaction-sec"/>

Let a player search a crate and stop the search by releasing Interact. Ninja Input reads the button. Ninja Interaction reserves the slot, counts the time, and reports whether the search finished. Start with a [working Input Setup](ipt_first_steps.md) and a [focused interaction target](int_first_steps.md).

## Start on Press and Let the Tree Count

<procedure title="Route press and release to the current pawn">
    <step><p>Set up a <a href="int_adv_interaction_duration.md">tree-timed search</a>. Map a Boolean <b>IA_Interact</b> action with no explicit triggers. Add a custom <b>Ninja Input Handler</b> to the active Input Setup, assign the action, and select <b>Started</b> and <b>Completed</b>.</p></step>
    <step><p>In <b>Handle Started Event</b>, call <code>GetPawn</code> on the supplied Input Manager, then <code>GetInteractionManagerComponent</code> for that pawn. Remember the focused search summary's ID on the pawn. Call <code>TryInitializeInteractionWithCurrentTarget</code> with the offered search type, such as <code>Interaction.Type.Search</code>.</p></step>
    <step><p>In <b>Handle Completed Event</b>, use <code>GetActiveInteractionSummary</code>. If the ID matches this press and the search is still waiting to commit, call <code>TryCancelCurrentInteraction</code> with <code>Interaction.Event.CancelledButtonPress</code>. Clear the saved ID. For a press-and-wait search, let the tree finish after release.</p></step>
</procedure>

In a C++ input handler, the corresponding overrides are `HandleStartedEvent_Implementation` and `HandleCompletedEvent_Implementation`. Keep the selection on the player or pawn so two players using the same handler have independent searches.

## Confirm After an Input Hold

For a switch that should stay available to others while the first player holds a button, use an immediate slot with a one-shot **Hold** trigger. On **Started**, save the focused summary ID. On **Triggered**, take and clear that ID and call `TryInitializeInteractionBySummaryId` once. Clear it on **Canceled**, loss of focus, or unregistration. Blueprint can bind `OnFocusStateChanged` on the manager. C++ can subscribe to `Native_OnFocusStateChanged` and remove the binding when the prompt closes. [Confirm an Interaction with a Hold Input Action](int_guide_hold_input.md) includes the progress bar.

## Block Movement During the Interaction

For a search animation that takes control of movement or facing, grant `Input.Block.Movement` or `Input.Block.Rotation` through its Gameplay Effect during playback. The corresponding Ninja Input handlers honor those tags. [Animate an Interaction](int_adv_interaction_animations.md) covers the effect and animation setup.

## Try It in Play

Release halfway through the crate search. The reserved slot should become available and the search should yield nothing. On the input-timed switch, release early and check that the interaction never starts. Then start holding on switch A and turn toward switch B. Neither should activate until a fresh press. If B activates, check that confirmation uses the saved ID.
