# Input and G.A.S.: Activate an Ability from an Action
<primary-label ref="integrations"/>
<secondary-label ref="input-sec"/>
<secondary-label ref="gas-sec"/>

Use a button to activate an ability already granted to the possessed pawn. Start with a [working Input Setup](ipt_first_steps.md) and a character that [exposes its Ability System Component](gas_first_steps.md). The example also works with a project-provided Unreal Gameplay Ability System.

<procedure title="Bind one action to one ability">
    <step><p>Grant an ability with an observable effect to the pawn, for example through its Ninja G.A.S. Setup Data. Verify it is present on the initialized Ability System Component. For a Player State-owned system, the pawn must still provide access to that component.</p></step>
    <step><p>Create a Boolean Input Action with a Pressed trigger, map it in the active context, and add <b>GAS: Activate Ability by Class</b> to the matching Input Setup. Assign the same action, the granted ability class, and the Triggered event.</p></step>
    <step><p>Press the key in play. A successful activation should produce the same effect as activating the ability directly. If the input arrives with no effect, check the grant and its cost, cooldown, or blocking tags.</p></step>
</procedure>

## Choose a Hold, Toggle, or Event

Use the activation-by-tags handler when different characters bind the same action to different granted abilities. Use the input-ID handler for a project that already assigns GAS input IDs. An inventory action can follow the same pattern once its ability has a valid item selection.

- For a hold, give the ability the tag `Input.Ability.Momentary` and configure **Pressed** and **Released** triggers so the handler receives both edges. Releasing the button cancels the active ability.
- For a toggle, give the ability `Input.Ability.Toggled` and use a Pressed trigger. A second press cancels the active ability. For a separate cancel button, use an **Interrupt Ability** handler by class, tags, or input ID.
- To send a follow-up to an active ability, enable **Send Event If Active** on the activation handler and choose its **Active Event Tag** and delivery settings. For a dedicated event button use **GAS: Send Gameplay Event** and choose the tag the ability is listening for.

## Customize How the Ability Receives Input

The supplied activation check already handles Tap and Double Tap, which can succeed on release with a zero value. For a custom trigger, derive from `UNinjaInputAbilityActivationCheck`, override `ShouldActivate`, and assign the class to **Ability Activation Check Class** on the handler. On the gameplay event handler, override `CanSendGameplayEvent` to gate the event, or `GetInstigatorTags`, `GetTargetTags`, and `GetOptionalObject2` to supply context such as the selected item.

For an ability waiting for an aim confirmation, use **GAS: Ability Target Confirm** and **GAS: Ability Target Cancel**. Override `GetAbilityTargetActor` if the targeting operation needs your active target actor. [Combat and Input](integration_combat_input.md#ability-targeting) shows an implementation.

## Try It in Play

Press, hold, and release a momentary ability, then press a toggled ability twice. Watch the active ability on the same pawn used by the Input Manager. If the hold starts but never ends, check that the Released trigger reaches the handler.
