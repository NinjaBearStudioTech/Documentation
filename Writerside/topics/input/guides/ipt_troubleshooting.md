# Diagnose Missing or Duplicate Input
<primary-label ref="input"/>
<secondary-label ref="guide"/>

Trace a key from its mapping context to the gameplay response. Use a single press in Play In Editor so repeated Triggered events from a held key are easy to distinguish from duplicate bindings.

<procedure title="Find where the input stops">
    <step><p>In <b>Project Settings → Ninja Input</b>, enable <b>Show Screen Debug Messages</b>. In the Input Setup, temporarily add <b>Debug: Show String</b> to the action. Give it a message such as <code>{pawn}: {action} = {value}</code> and use a trigger the action actually produces.</p></step>
    <step><p>Play as the affected pawn. Check <b>Has Setup Data</b> on its manager and <b>Has Compatible Input Handler</b> for the action and event. If the setup fails validation, open the Message Log and fix the missing action, handler, or trigger it names.</p></step>
    <step><p>If the debug handler fires, put a Blueprint breakpoint in the gameplay handler. Inspect its pawn, value, blocking tags, and any open buffer channel. If movement works but the camera does not rotate, check the Look action and whether the spring arm uses pawn control rotation.</p></step>
</procedure>

## If a Press Runs Twice

Start with a **Pressed** trigger to get one Triggered event per press. Check for a template action event still bound on the pawn, a second manager on the controller, or two handlers accepting the same action and phase. If two active contexts share an action, inspect the handlers contributed by both setups.

## See Setup and Buffer Activity

In the Output Log, enter `Log LogNinjaInputManagerComponent VeryVerbose` to trace setup and context changes. Use `Log LogNinjaInputHandler VeryVerbose` for handlers and `Log LogNinjaInputBufferComponent Verbose` for window activity. Repeat the same press after each change.

## Try It in Play

Test the key on the original pawn, switch pawns, and test again. You should see one response from each intended handler on the correct pawn. Remove the temporary debug handler after confirming the result.
