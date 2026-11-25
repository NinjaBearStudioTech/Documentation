# Confirm an Interaction with a Hold Input Action
<primary-label ref="interaction"/>
<secondary-label ref="guide"/>

Make the player hold Use for 0.8 seconds before a switch activates. The player can release early with no effect, and another character can use the slot while the first player is deciding. Start with an [immediate switch](int_guide_immediate.md) and an active Enhanced Input mapping context.

<procedure title="Remember what the player started holding for">
    <step><p>Create a Boolean <b>IA_ConfirmInteraction</b>. Add a <b>Hold</b> trigger, set <b>Hold Time Threshold</b> to <code>0.8</code>, and enable <b>Is One Shot</b>. Map it to the interact key. Use this binding in place of the switch's press-to-start binding.</p></step>
    <step><p>On <b>Started</b>, use the pawn's Interaction Manager to get <b>Focused Interaction Targets</b>, then <b>Get Interaction Summaries for Target</b>. Choose the enabled, focused summary for <code>Interaction.Type.Interact</code> and store its <b>Summary Id</b> on the local player. Leave the slot free at this point.</p></step>
    <step><p>On <b>Ongoing</b>, you can show progress using the input event's elapsed seconds divided by <code>0.8</code>, clamped to 0–1. Clear the saved ID and bar on <b>Canceled</b> or if <code>OnFocusStateChanged</code> reports that the saved summary lost focus. Clear it on unregistration too.</p></step>
    <step><p>On <b>Triggered</b>, take the saved ID, clear the pending confirmation, and call <b>Try Initialize Interaction By Summary Id</b> (<code>TryInitializeInteractionBySummaryId</code>) once if the ID is valid. The server checks the selected slot is still focused, enabled, and claimable. Use <b>Completed</b> for local input cleanup.</p></step>
</procedure>

The slot uses **Duration 0** with the immediate tree. The input action owns the entire wait. If you want the slot reserved or need interaction progress to replicate during the wait, use [the State Tree timer](int_adv_interaction_duration.md).

## Try It in Play

Release halfway through the hold. The bar should reset and the light should stay as it was. Hold past the threshold to toggle it once. Finally, start holding on switch A, turn toward switch B, and finish holding. Neither switch should activate until a fresh press. If B reacts, check that confirmation uses the saved summary ID and that losing focus clears it.
