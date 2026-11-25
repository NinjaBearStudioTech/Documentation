# Input and G.A.S.: Activate an Ability from an Action
<primary-label ref="integrations"/>
<secondary-label ref="input-sec"/>
<secondary-label ref="gas-sec"/>

Give the player a Recover button. Ninja G.A.S. grants the ability and its starting Energy. Ninja Input routes a key press to the possessed pawn. Begin with a [working Input Setup](ipt_first_steps.md) and the [Recover ability](gas_guide_starting_abilities.md), which restores 50 energy.

<procedure title="Bind Recover to a single press">
    <step><p>Assign the bundle containing <code>GA_Recover</code> to the ability owner. Check that the character starts with 25 energy and the ability appears in its grant list. If the Player State owns the component, the possessed pawn must expose that same component.</p></step>
    <step><p>Create a Boolean <b>IA_Recover</b> action with a <b>Pressed</b> trigger. Map it in the active context. In the player's Input Setup, add <b>GAS: Activate Ability by Class</b>, select this action and its <b>Triggered</b> event, and set the ability class to <code>GA_Recover</code>.</p></step>
</procedure>

## Choose a Hold, Toggle, or Event

| What the player does | What to configure |
| --- | --- |
| Holds a shield up until release | Give the shield ability the asset tag `Input.Ability.Momentary`. Use Pressed and Released triggers so the handler receives the button value on both edges. |
| Presses once to aim and again to stop | Give a lasting aim ability the asset tag `Input.Ability.Toggled` and use a Pressed trigger. For a separate cancel key, use an Interrupt Ability handler by class, tags, or input ID. |
| Signals a move already in progress | Enable **Send Event If Active**, choose its **Active Event Tag**, and select local or server delivery to match the ability's listener. |
| Confirms a spell preview | Use **GAS: Ability Target Confirm** and **GAS: Ability Target Cancel**. [Combat and Input](integration_combat_input.md#ability-targeting) shows how to return a custom targeting actor. |

For a button shared by characters with different moves, use **GAS: Activate Ability by Tags** with their common ability tag. For a custom input trigger, derive from `NinjaInputAbilityActivationCheck`, override `ShouldActivate` in Blueprint or `ShouldActivate_Implementation` in C++, and assign the class to **Ability Activation Check Class**. The built-in check already handles Tap and Double Tap actions that trigger on release with a zero value.

## Use the Same Pattern for a Quick Slot

With Ninja Inventory, a **Use Bandage** action can send `Inventory.Event.Consume` to the pawn's granted Consume ability. The gameplay event handler puts the Input Action in **Optional Object**. Use **Optional Object 2** for the selected live item. The handler exposes `CanSendGameplayEvent` to check eligibility and `GetOptionalObject2`, `GetInstigatorTags`, and `GetTargetTags` to fill its payload. If the selection lives on the player, build the request in a custom `HandleTriggeredEvent` using that manager's pawn and call `SendGameplayEventToOwner`. Leave the Consume ability's fallback item query empty when only the selected stack should be eligible. [Use, Store, and Drop Items](inv_gameplay_abilities.md) covers the Consume ability and its item fragment.

## Try It in Play

Start at 25 energy and press Recover once. Expect 75, even if you keep the key down. If the handler receives the press but energy stays at 25, check the ability grant on the possessed pawn, then its cost and cooldown. For a hold or toggle test, use an ability that stays active until cancelled and watch its active state on release or on the second press.
