# First Steps: Move a Template Character
<primary-label ref="input"/>

Make the Third Person character move, look, and jump using one controller-owned Input Manager. Complete [Setup](ipt_setup.md) and open the Game Mode used by your test map.

<procedure title="Connect actions to handlers">
    <step><p>Find the template mapping context in the Content Browser. Check which actions the movement keys, mouse axes, and jump button use. If it also maps unrelated actions, duplicate the context for this walkthrough and keep the mappings you intend to test.</p></step>
    <step><p>Choose <b>Ninja Bear Studio → Ninja Input → Input Setup</b>. Assign that mapping context. Add <b>Character: Move</b>, <b>Character: Look</b>, and <b>Character: Jump</b> to <b>Input Handlers</b>.</p></step>
    <step><p>Expand each handler and replace its sample Input Action with the matching action from your context. If the template uses separate mouse and stick look actions, assign both to Look. Save and validate the setup. The Message Log identifies a mapped action missing a handler.</p></step>
</procedure>

<img src="ipt_setup_input_setup_data.png" alt="An Input Setup with a mapping context and its handlers" width="720" border-effect="line"/>

<procedure title="Activate the setup for the player">
    <step><p>Open the Player Controller Blueprint used by the active Game Mode, or create one and assign it as the Game Mode's <b>Player Controller Class</b>.</p></step>
    <step><p>Add a <b>Ninja Input Manager Component</b> and add your new asset to its <b>Input Handler Setup</b> list. Compile. Keep one manager for this player.</p></step>
    <step><p>Remove the old bindings for the migrated actions as described in <a href="ipt_setup.md">Setup</a>. If you split a context, keep the other actions registered separately so each action has one owner.</p></step>
</procedure>

## Try It in Play

Move forward, turn the camera, and jump. Each input should respond once. If an action is silent, compare the action asset on its handler with the one assigned to the key. If movement doubles, check the original Character and Player Controller graphs for a second binding. Next, [give a pawn an extra action](ipt_guide_custom_handler.md).
