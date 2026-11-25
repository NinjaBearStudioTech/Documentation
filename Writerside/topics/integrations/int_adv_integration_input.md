# Input and Interaction: Start and Cancel an Interaction
<primary-label ref="integrations"/>
<secondary-label ref="input-sec"/>
<secondary-label ref="interaction-sec"/>

Give the player an Interact button that starts the selected interaction on press. For timed interactions, release it before the action commits to cancel. Start with a [detectable interaction target](int_first_steps.md) and a [working input manager](ipt_first_steps.md).

<procedure title="Send the button to the Interaction Manager">
    <step><p>Create a Boolean action named <b>IA_Interact</b> with a <b>Pressed</b> trigger. Add a <b>Released</b> trigger if the player can interrupt the interaction. Map the action to a key in your active context.</p></step>
    <step><p>Create a <b>Ninja Input Handler</b>, assign IA_Interact and choose <b>Triggered</b>. Override <b>Handle Triggered Event</b>. Use the supplied Input Manager to get its pawn and find the pawn's Interaction Manager.</p></step>
    <step><p>Connect the incoming Value to a Boolean Branch. On true, call <b>Try Initialize Interaction With Current Target</b>. On false, call <b>Try Cancel Current Interaction</b> with the reason <code>Interaction.Event.CancelledButtonPress</code>. Add the handler to the active Input Setup.</p></step>
</procedure>

<img src="int_integration_input_handler.png" alt="Input handler starting or canceling the interaction on the current pawn" width="720" border-effect="line"/>

## Block Movement During the Interaction

Use the Gameplay Effect applied by the [interaction animation ability](int_ability_play_animation.md) to grant `Input.Block.Movement` or `Input.Block.Rotation` while the animation owns movement or facing. The corresponding input handlers read those tags from the ability system.

## Try It in Play

Face a target and press Interact. Confirm the selected target responds. On a timed target, release before the commit point and watch the interaction stop. If a prompt appears but pressing does nothing, inspect the input handler and the target selected by the Interaction Manager.
