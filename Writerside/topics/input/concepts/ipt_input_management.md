# Input Setups and Ownership
<primary-label ref="input"/>

Put the manager on the **Player Controller** when a player can change pawns. Keep common actions such as Pause there. Let the character supply on-foot controls and a vehicle supply steering. A pawn-owned manager also works for a game with a single pawn type.

## What Makes a Setup Active?

An **Input Setup** contains one mapping context, its priority, and its handlers. A higher-priority Enhanced Input context gets the first opportunity to consume an overlapping key. Give each simultaneously active setup its own context. Use **Standalone Contexts** for supporting keys, such as a modifier used by a chord. Add a handler when the action should also perform a gameplay response of its own.

| To do this | Use this hook |
| --- | --- |
| Give each pawn its own controls | Implement **Input Setup Provider Interface** (C++: `IInputSetupProviderInterface`) on the pawn and return its assets from `GetInputSetups`. A controller-owned manager adds them on possession and removes them when possession changes. |
| Enable a control scheme temporarily | Call `AddInputSetupData` when entering the mode and `RemoveInputSetupData` when leaving. Use `HasSetupData` to check whether that setup is active. |
| Pause the manager during a cutscene | Call `DisableInputProcessing` and later `EnableInputProcessing`. Disabling also resets the manager's buffer. |
| Change what happens to a held key when a context is added | Override `CreateModifyContextOptions` on the manager. Its defaults wait for held keys to be released and notify user settings about the context. |

<img src="ipt_handlers_setup_provider.png" alt="A pawn returning its Input Setups in Blueprint" width="720" border-effect="line"/>

## Which Way Is Forward?

For top-down movement with a fixed direction, add an Arrow to the pawn, enable **Absolute Rotation**, and add the component tag `Input.Component.ForwardReference`. The Move handler can use that reference through `GetForwardVector` and `GetRightVector`. Use **Should Create Forward Reference** if you want the manager to create an arrow. Override `CreateForwardReference` to supply a different component.

For a pawn with a custom movement system, implement `ILastInputProviderInterface::GetLastInputVector` to supply its last movement input. For rotation driven by an input action, set the trace channel on **Character: Rotate to Cursor**. For continuous cursor-facing through the manager, enable **Should Rotate Controller to Mouse Cursor** there. Override the manager's `IsAllowedToRotateToMouseCursor` to suspend its rotation during an action.

[Create a handler and switch input setups](ipt_guide_custom_handler.md).
