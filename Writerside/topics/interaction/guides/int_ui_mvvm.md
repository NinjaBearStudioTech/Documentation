# Show a Prompt and Timed Progress
<primary-label ref="interaction"/>
<secondary-label ref="guide"/>

Show **Search** above a terminal and fill a bar while its [State Tree search](int_adv_interaction_duration.md) is running. Use the supplied `W_Interaction` widget as a starting point, or create a widget derived from **Interaction Prompt Widget**.

<procedure title="Connect the prompt to the terminal">
    <step><p>Add an <b>Interaction Widget Component</b> to the terminal and assign the prompt widget as its widget class. Position it above the mesh. This component supplies the target actor to the widget.</p></step>
    <step><p>For a custom widget, add the <b>Interaction Target ViewModel</b> with creation type <b>Resolver</b> and choose the <b>Interaction Resolver</b>. It binds the widget to the owning player and its target. Add an <b>Interaction Summary ViewModel</b> with <b>Manual</b> creation. Bind <b>Get Focused Interaction Summaries</b> to the prompt's <b>Update Focused Summary</b> and display the selected summary's <b>Display Text</b>. Use a priority or tag query if the target offers several actions.</p></step>
    <step><p>For the progress bar, use <b>Get Active Interaction Summary</b> on the target ViewModel. Bind it to the prompt's <b>Update Active Summary</b>, then bind <b>Get Elapsed Time Percent</b> to the bar's <b>Percent</b>. Show the bar while the interaction is accumulating time and hide it on finish or cancellation.</p></step>
</procedure>

<img src="int_ui_widget_component_on_target.png" alt="Interaction Widget Component positioned on a target" width="740" border-effect="line"/>

## Put the Prompt on the HUD

For a single prompt near the crosshair, create the widget for the local player. Listen to the pawn manager's `OnFocusStateChanged` and pass the focused target actor through **Set Interaction Target**. Clear the old target when focus leaves, and bind the new target's summaries. For a search already underway, keep the progress bar bound to the active summary through completion. For an [input-timed hold](int_guide_hold_input.md), fill the bar from the pending local input's elapsed time.

## Customize the Feedback

On **Interaction Prompt Widget**, override `NotifyInteractionPresented` and `NotifyInteractionDismissed` to fade the label, `NotifyProgressStarted` and `NotifyProgressStopped` to show or hide the bar, and `NotifyInteractionCompleted` or `NotifyInteractionCancelled` for the outcome. The **Interaction Summary ViewModel** exposes the text, type, priority, duration, and elapsed percentage for one slot.

## Try It in Play

Face the terminal, start a two-second search, then cancel halfway through. The label should identify the terminal, and the bar should hide and start empty on the next attempt. If the label is correct but the bar never fills, check that its binding follows the active summary and that the tree started time accumulation.
