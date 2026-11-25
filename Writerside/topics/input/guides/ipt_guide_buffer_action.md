# Buffer an Action
<primary-label ref="input"/>
<secondary-label ref="guide"/>

Let the player press an action early and see it execute when a montage window ends. Use the controller from [First Steps](ipt_first_steps.md) and a montage you can already play on the locally controlled pawn.

<procedure title="Set up a visible response">
    <step><p>Create a Boolean action with a <b>Pressed</b> trigger and map it to a spare key. In the active Input Setup, add <b>Debug: Show String</b>. Assign the action and set its display string to <b>Released {action} for {pawn}</b>.</p></step>
    <step><p>Enable <b>Can Be Buffered</b> on that handler and choose <code>Input.Buffer.Channel.Default</code> as its Buffer Channel Tag. On the Input Manager, set <b>Input Buffer Mode</b> to <b>Last Command</b>.</p></step>
</procedure>

<procedure title="Mark the window">
    <step><p>In the montage notify track, add the <b>Input Buffer</b> Notify State. Place it across a visible stretch of the animation and end it a few frames before the montage ends. Set its Buffer Channel Tag to the same tag as the handler.</p></step>
    <step><p>Save the montage and play it on the local player. To control the window from an ability or another Blueprint instead, use <b>Open Input Buffer</b> and <b>Close Input Buffer</b> on the enabled buffer with that same tag.</p></step>
</procedure>

<img src="ipt_input_buffer_blueprint.png" alt="Opening and closing a buffer channel from Blueprint" width="720" border-effect="line"/>

## Try It in Play

Press once before the montage. The message should appear immediately. Play the montage and press twice inside the window. Expect one message at the normal close. Press again afterward and expect an immediate message. To test cancellation explicitly, open the channel in Blueprint, press the key, and close it with **Cancelled** enabled. The pending message should be discarded. If every press runs immediately, compare the channel tags and confirm buffering is enabled on both the manager and the handler.
