# Create a Handler and Switch Input Setups
<primary-label ref="input"/>
<secondary-label ref="guide"/>

Give the [First Steps character](ipt_first_steps.md) an Inspect action that is available only while carrying a scanner. Keep movement on the controller. Toggle a second setup for the scanner so you can see precisely when its key starts and stops working.

<procedure title="Create the scanner input">
    <step><p>Create a Boolean Input Action named <b>IA_Inspect</b> with a <b>Pressed</b> trigger. Create a mapping context named <b>IMC_Scanner</b> and map an unused key to that action.</p></step>
    <step><p>In the Content Browser choose <b>Ninja Bear Studio → Ninja Input → Input Handler</b>. Select <b>Ninja Input Handler</b> as the parent and name the Blueprint <b>IH_Inspect</b>. In Class Defaults add IA_Inspect under Input Actions and Triggered under Trigger Events.</p></step>
    <step><p>Override <b>Handle Triggered Event</b>. For this test, call <b>Get Pawn</b> on the supplied Manager and print the pawn's display name followed by "inspected". In a game, use this same pawn to call your scanner component. Compile the handler.</p></step>
</procedure>

<img src="ipt_handlers_function_overrides.png" alt="Choosing an event override in an Input Handler Blueprint" width="720" border-effect="line"/>

<procedure title="Switch the controls on and off">
    <step><p>Create a second <b>Input Setup</b>, select IMC_Scanner and add IH_Inspect to its handler list. Leave the scanner setup out of the controller defaults.</p></step>
    <step><p>In the scanner equip event, get the player's Input Manager and call <b>Add Input Setup Data</b> with the scanner setup. In the unequip event, call <b>Remove Input Setup Data</b> with the same asset. To test without an equipment system, call those nodes from two temporary key events in the Level Blueprint.</p></step>
</procedure>

<img src="ipt_add_remove_setup.png" alt="Adding and removing the same setup on the Input Manager" width="720" border-effect="line"/>

## Implement the Same Handler in C++

For a native handler, derive from `UNinjaInputHandler`. Declare this override in your class header, then configure IA_Inspect and Triggered on its entry in the Input Setup just as you would for the Blueprint version.

```cpp
virtual void HandleTriggeredEvent_Implementation(
    UNinjaInputManagerComponent* Manager, const FInputActionValue& Value,
    const UInputAction* InputAction, float ElapsedTime) const override;
```

In the implementation file, include `Components/NinjaInputManagerComponent.h` and `GameFramework/Pawn.h`. For a first check, log the pawn receiving the press.

```cpp
void UInspectInputHandler::HandleTriggeredEvent_Implementation(
    UNinjaInputManagerComponent* Manager, const FInputActionValue& Value,
    const UInputAction* InputAction, float ElapsedTime) const
{
    if (APawn* Pawn = Manager->GetPawn())
    {
        UE_LOG(LogTemp, Display, TEXT("%s inspected"), *Pawn->GetName());
    }
}
```

## When Possession Should Switch Controls

For a drivable vehicle, implement **Input Setup Provider Interface** on the vehicle pawn and return the driving setup from **Get Input Setups**. With a controller-owned manager and **Reset Setup for New Pawn** enabled, possession handles adding and removing those controls. Keep shared actions on the controller.

## Try It in Play

Press Inspect before equipping, while equipped, and after unequipping. Only the middle press should print the pawn name. Movement should work throughout. If Inspect still runs after unequipping, look for a second binding or a scanner context also registered at startup.
