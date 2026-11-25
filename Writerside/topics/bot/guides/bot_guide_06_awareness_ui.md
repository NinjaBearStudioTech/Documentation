# Display an Awareness Indicator
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Add a meter above the guard from [Tune Detection and Awareness](bot_guide_05_awareness_setup.md). This example runs in single-player Play In Editor, where the widget can read the guard's AI Controller.

<procedure title="Build the widget">
    <step><p>Create a Widget Blueprint derived from <b>Ninja Bot Awareness Tracker Widget</b>. In Designer, add a Progress Bar named <b>AwarenessProgress</b> and optionally a Text Block named <b>AwarenessText</b>.</p></step>
    <step><p>In the widget's Viewmodels panel, add <b>Bot Awareness ViewModel</b>. Choose the <b>Resolver</b> creation type and <b>Bot Resolver</b>. Use the field notification bindings to send changes from the ViewModel to the widget.</p></step>
    <step><p>Bind <b>Get Progress to Aware State</b> one way to the bar's <b>Percent</b>. Bind <b>Awareness Level</b> to the widget's <b>Update Awareness Level</b> function. The tracker uses that function to change its visibility, text and color.</p></step>
    <step><p>In Class Defaults, choose visibility for each stage. The default hides the widget while Unaware. Compile and save.</p></step>
</procedure>

<procedure title="Connect the guard and the viewing player">
    <step><p>Add a <b>Widget Component</b> to the guard Blueprint. Set its Widget Class to your tracker, choose Screen space, and position it above the guard.</p></step>
    <step><p>Once the guard has its AI Controller and the component has initialized its widget, get the component's <b>User Widget Object</b> and cast it to your tracker Blueprint. From that widget get its Bot Awareness ViewModel.</p></step>
    <step><p>On that ViewModel call <b>Set Component Owner</b> with the guard's <b>Get Controller</b> result. The resolver uses the widget's owning player. For this single-player example, call <b>Set Owning Player</b> on the ViewModel with <b>Get Player Controller (0)</b> if the widget component has no owning player.</p></step>
</procedure>

## Try It in Play

Approach the guard and stay in view. The meter should appear at Suspicious, change as the level rises, and fill at Aware. Leave view. The meter follows the reading while you remain the selected target and resets when that target clears. If the tree shows rising awareness but the meter stays hidden, check the level binding and the two controllers passed to the ViewModel.
