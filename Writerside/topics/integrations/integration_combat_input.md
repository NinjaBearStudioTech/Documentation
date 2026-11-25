# Combat and Input: Drive Combat Abilities
<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="input-sec"/>

Start with a [combatant](cbt_first_steps.md) that can already perform the action and a player with a [working Input Setup](ipt_first_steps.md). Bind the first attack, then add the controls your combat system uses.

## Gameplay Abilities

For a single attack, map a Pressed action in your context. Add **GAS: Activate Ability by Class** to the Input Setup, assign that action, and select the attack ability already granted to the combatant. [Input and G.A.S.](ipt_gas_handlers.md) covers activation by tags, momentary abilities, and toggles.

## Combo Inputs

<procedure title="Start a combo and advance it">
    <step><p>Grant the combo ability and set up its <a href="cbt_guide_combos.md">combo window</a>. Add <b>GAS: Combat Combo</b> for the first attack action. Assign <b>Triggered</b> as its event.</p></step>
    <step><p>Enable <b>Handles Activation</b> for a button that can start the combo and choose Activation Tags matching the granted ability. Enable <b>Handles Advancement</b> for a button that can continue it and set the Advancement Tag to the event expected by the combo branch.</p></step>
    <step><p>Press once to start, then press again while the combo window is open. If the first attack plays but the second does not, compare the handler's combo state and advancement tags with the ability and combo tree.</p></step>
</procedure>

<img src="integration_combat_input_combo.png" alt="Activation and advancement settings on a combo handler" width="720" border-effect="line"/>

## Default, Hold, Combo

When a single button needs a quick attack, a held attack, and a combo continuation, derive an Input Handler from **GAS: Default, Hold, Combo**. Use a Hold trigger so the handler can distinguish releasing early from reaching the hold time. Configure the abilities or events for those roles. Override `IsFirstComboAttack` to read the current pawn's Combo Manager and return true when `GetComboCount` is zero. Override `IsInComboWindow` to report whether that pawn can advance. For a project-specific choice of action, override the role selector, such as `GetHoldActivationType` or `GetComboActivationType`.

## Ability Targeting

Add **GAS: Ability Target Confirm** and **GAS: Ability Target Cancel** for a combat ability that waits for a target. To operate directly on Combat's targeting actor, subclass the corresponding handler. Override `GetAbilityTargetActor`, get the pawn from the Input Manager, and return the Combat Target Manager's current ability targeting actor. Set **Ability Targeting Operation** to the actor operation if that is where the ability expects confirmation.

<img src="integration_combat_input_confirm.png" alt="Returning the current targeting actor from a confirmation handler" width="720" border-effect="line"/>

## Target Lock

Grant the [Target Lock ability](cbt_guide_target_lock.md), add `Input.Ability.Toggled` to its ability tags, and bind a Pressed action using the activation-by-tags handler. Bind **GAS: Send Gameplay Event** for each extra control you support: `Combat.Event.Target.Scan` to scan, and `Combat.Event.Target.Left` or `Combat.Event.Target.Right` to cycle. Press the original toggle again to release the lock.

## Forward Reference

For a shared direction in top-down movement and directional evades, add an Arrow to the character. Use **Absolute Rotation** and tag it with both `Input.Component.ForwardReference` and `Combat.Component.ForwardReference`. Return that Arrow from Combat's `GetCombatForwardReference` interface function. Check the direction of an evade after rotating the pawn.

## Fire Intent

Bind a Boolean fire action with **Pressed** and **Released** triggers. In a custom handler's `HandleTriggeredEvent`, get the active weapon's Firearm Component using the weapon query for that pawn. Convert Value to Boolean and call `TryOpenFire` on press or `TryCeaseFire` on release. The [firearm guide](cbt_guide_firearms.md) covers the weapon and shoot ability.

<img src="integration_combat_input_fire_intent.png" alt="Sending press and release to the active firearm" width="720" border-effect="line"/>

## Disabling Input

Apply `Input.Block.Movement`, `Input.Block.Camera`, or `Input.Block.Rotation` during a finisher or target lock to gate the matching handlers. Remove the tags when the ability ends so the player regains control.

## Input Buffer

If an early press should advance a combo, enable **Can Be Buffered** on its handler and open its channel shortly before the next combo window. Time the release so the combo can accept the event. [Buffer an Action](ipt_guide_buffer_action.md) shows the montage and Blueprint paths.

## Try It in Play

Check one action at a time: start a combo, press again inside the window, confirm a target, then release a held fire input. If the handler receives the input but the ability does nothing, inspect the granted ability and its tags on the possessed combatant.
