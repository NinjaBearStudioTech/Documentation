# Input and Interaction: Start and Cancel an Interaction
<primary-label ref="integrations"/>
<secondary-label ref="input-sec"/>
<secondary-label ref="interaction-sec"/>

Use a Ninja Input handler to send Interact to the current pawn's Interaction Manager. Start with a [working Input Setup](ipt_first_steps.md) and a [working interaction target](int_first_steps.md). Choose who owns the wait before configuring the handler.

## Start on Press and Let the Tree Count

<procedure title="Route press and release to the current pawn">
    <step><p>Create a Boolean <b>IA_Interact</b> in the active mapping context. For a press-and-release binding, leave its triggers empty. Create a <b>Ninja Input Handler</b>, assign this action, select <b>Started</b> and <b>Completed</b> as its trigger events, and add the handler to the active Input Setup.</p></step>
    <step><p>Override <b>Handle Started Event</b>. Get the supplied Input Manager's pawn and its <b>Interaction Manager</b>. Call <b>Try Initialize Interaction With Current Target</b> with the offered type, for example <code>Interaction.Type.Search</code>.</p></step>
    <step><p>If releasing should interrupt a timed search, handle <b>Completed</b>. Check the same search is still waiting, then call <b>Try Cancel Current Interaction</b> with <code>Interaction.Event.CancelledButtonPress</code>. For a press-and-wait action, omit this cancellation.</p></step>
</procedure>

Set the wait on the slot and tree as shown in [Time an Interaction in the State Tree](int_adv_interaction_duration.md).

## Confirm After an Input Hold

Use a separate **Hold** action with **Is One Shot** enabled and an immediate slot. In its handler, select **Started**, **Triggered**, and **Canceled**. In `HandleStartedEvent`, save the offered summary ID for that pawn. In `HandleTriggeredEvent`, submit it once with `TryInitializeInteractionBySummaryId`. In `HandleCancelledEvent` or on loss of focus, clear the pending choice. A handler reused by several pawns needs separate pending selections for each player. [Confirm an Interaction with a Hold Input Action](int_guide_hold_input.md) covers the input progress bar and focus-change test.

## Block Movement During the Interaction

If the animation should own movement or facing, use its Gameplay Effect to grant `Input.Block.Movement` or `Input.Block.Rotation` during playback. The corresponding Ninja Input handlers read these tags. See [Animate an Interaction](int_adv_interaction_animations.md).

## Try It in Play

Start a tree-timed search and release early. It should cancel only when you enabled release-to-cancel. On the Hold setup, release early and check that the interaction never starts. Holding past the threshold should run the immediate action once.
