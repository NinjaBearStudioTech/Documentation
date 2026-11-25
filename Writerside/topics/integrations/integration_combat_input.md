# Combat and Input: Drive Combat Abilities
<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="input-sec"/>

Give a player one attack button that starts a combo and advances it on a well-timed second press. Start with a [working Input Setup](ipt_first_steps.md) and a combatant that can already perform a [branching combo](cbt_guide_combos.md).

## Combo Inputs

<procedure title="Bind the opening swing and follow-up">
    <step><p>Map a Boolean attack action with a <b>Pressed</b> trigger in the player's active mapping context. In the Input Setup, add a <b>GAS: Combat Combo</b> handler for that action and select <b>Triggered</b>.</p></step>
    <step><p>Enable <b>Handles Activation</b> and set <b>Activation Tags</b> to the granted combo ability's tag, such as <code>Combat.Ability.Combo</code>. Set <b>Combo State Tag</b> to <code>Combat.State.ComboWindow</code>, the tag the Combat Combo Manager applies while the montage window is open.</p></step>
    <step><p>Enable <b>Handles Advancement</b> and set <b>Advancement Tag</b> to the opening state's follow-up event, for example <code>Combat.Event.Combo.Attack.Primary</code>. A second button can send the secondary branch's event. Leave activation off on that handler if it should only continue an existing combo.</p></step>
</procedure>

<img src="integration_combat_input_combo.png" alt="Combo handler with activation and advancement settings" width="720" border-effect="line"/>

For a tap, hold, and combo branch on the same button, derive a handler from **GAS: Default, Hold, Combo**. Use a Hold trigger and choose the ability or event for each role. Override `IsFirstComboAttack` to return true when the pawn's Combo Manager reports `GetComboCount` is zero, and `IsInComboWindow` using its `InComboWindow` result. In C++, override the corresponding `_Implementation` methods. Use `GetHoldActivationType` or `GetComboActivationType` if your equipped weapon changes what that input does.

## Input Buffer

Once both presses work, enable **Can Be Buffered** on the follow-up handler. Open the handler's buffer channel just before the montage window and release the saved input while Combat can accept it. [Buffer an Action](ipt_guide_buffer_action.md) shows the notify and Blueprint paths.

## Ability Targeting

For an [aimed spell](cbt_guide_cast_flows.md), bind separate Pressed actions to **GAS: Ability Target Confirm** and **GAS: Ability Target Cancel**. Choose the ability component operation for a cast waiting on GAS confirmation. If your spell needs the targeting actor directly, override `GetAbilityTargetActor` on both handlers. Get the Input Manager's pawn, find its Combat Target Manager, and return that manager's `GetAbilityTargetActor` result. Choose the targeting actor operation. Aim once and cancel, then aim again and confirm. Only the confirmed cast should land.

<img src="integration_combat_input_confirm.png" alt="Confirmation handler resolving Combat's active targeting actor" width="720" border-effect="line"/>

## Target Lock

Grant [Target Lock](cbt_guide_target_lock.md), give it the ability asset tag `Input.Ability.Toggled`, and bind a Pressed action using **GAS: Activate Ability by Tags** with the lock ability's identifying tag. Press once to lock and again to release. For cycling, bind **GAS: Send Gameplay Event** to `Combat.Event.Target.Left` and `Combat.Event.Target.Right`. Use `Combat.Event.Target.Scan` for a fresh scan.

## Fire Intent

For a [firearm](cbt_guide_firearms.md), use a Boolean fire action with **Pressed** and **Released** triggers. In a custom handler's `HandleTriggeredEvent`, resolve the equipped weapon from the pawn's weapon query and get its Firearm Component. Call `TryOpenFire` on a true value and `TryCeaseFire` on false. Use `HandleTriggeredEvent_Implementation` in C++. This also lets the firearm handle its own rate of fire while the player holds the button.

<img src="integration_combat_input_fire_intent.png" alt="Passing a press or release to the equipped firearm" width="720" border-effect="line"/>

## Forward Reference

For a top-down evade, give the character an Arrow with **Absolute Rotation** and the component tags `Input.Component.ForwardReference` and `Combat.Component.ForwardReference`. Return that Arrow from `GetCombatForwardReference` so movement input and evades agree on direction. During a finisher, grant `Input.Block.Movement`, `Input.Block.Camera`, or `Input.Block.Rotation` for the controls you want to suspend, and remove those tags when the ability ends.

## Try It in Play

Test the combo first with buffering off. Press once, then press again during the window. The second press should play the follow-up. Wait out the opening move and the next press should start a fresh combo. If only the opener plays, inspect the pawn's owned tags while the window is open, then compare the handler's advancement tag with the tree transition. For a single attack with no combo, use [Activate an Ability from an Action](ipt_gas_handlers.md).
