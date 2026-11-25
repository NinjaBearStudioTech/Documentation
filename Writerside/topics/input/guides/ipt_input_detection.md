# Adapt Controls to the Active Device
<primary-label ref="input"/>
<secondary-label ref="guide"/>

Show a keyboard or gamepad prompt and let the player adjust camera sensitivity. Start with a working [Input Setup](ipt_first_steps.md) with mappings for the devices you want to test.

<procedure title="Update the prompt">
    <step><p>Create the prompt widget for the local player. From the player's Input Manager read <b>Get Player Input Mode</b> for the initial prompt and bind a custom event to <b>On Input Mode Changed</b>. Use a fallback prompt until a device has been detected.</p></step>
    <step><p>Send the initial value and the event's new tag to the same widget function. Choose keyboard artwork for <code>Input.Mode.KeyboardAndMouse</code>, gamepad artwork for <code>Input.Mode.Gamepad</code>, and touch controls for <code>Input.Mode.Touch</code>. Remove the binding when disposing of the widget.</p></step>
</procedure>

<procedure title="Apply a saved preference">
    <step><p>Enable the settings classes from <a href="ipt_remapping_ui.md">Build a Key Remapping Menu</a>. On the mouse Look mapping add <b>Mouse Sensitivity</b>. On its stick mapping add <b>Gamepad Sensitivity</b>. Use <b>Invert XY Axis</b> on mappings where the player can reverse an axis.</p></step>
    <step><p>On your slider's change event, get <b>Input User Settings</b> from the manager. Call <b>Set Mouse Sensitivity X</b> and <b>Set Mouse Sensitivity Y</b>, or <b>Set Gamepad Sensitivity</b> for the stick. Bind an inversion checkbox to <b>Set Invert Vertical Axis</b>. Call <b>Save Input Settings</b> on Apply.</p></step>
</procedure>

## Try It in Play

Press a mapped keyboard key, then a mapped gamepad button. The prompt should change on each switch. Change the mouse slider and move the mouse the same distance again. The camera should turn a different amount while stick sensitivity stays the same. If the prompt stays put, try a mapped action that produces a nonzero value. If the slider changes but the camera feels identical, inspect the modifiers on the active mapping.
