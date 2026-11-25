# Handlers and Trigger Events
<primary-label ref="input"/>

A handler answers two questions: which action and event should reach it, and what should the current pawn do when they arrive? For a horn, play a sound once on a press. For steering, use the current axis value for as long as the stick is moving.

## Pick an Event

| Enhanced Input event | Handler override | Typical use |
| --- | --- | --- |
| Started | `HandleStartedEvent` | Start a response when trigger evaluation begins. |
| Ongoing | `HandleOngoingEvent` | Update feedback while a hold is still being evaluated. |
| Triggered | `HandleTriggeredEvent` | Perform the action when its trigger succeeds. A Pressed trigger fires once. An axis can trigger each frame. |
| Completed | `HandleCompletedEvent` | End a response after a triggered action finishes. |
| Canceled | `HandleCancelledEvent` | Clean up a hold released before it qualified. |

In an Input Handler Blueprint, list the **Input Actions** and **Trigger Events** it accepts. Override the matching event. In C++, override the corresponding `_Implementation` method. `CanHandle` lets you customize the action/event match when bindings are built. Check temporary conditions, such as stamina, inside the event or the specialist hook. Keep per-player state on the pawn, controller, or component. The setup can share one handler across players.

## Adapt a Supplied Handler

| Gameplay need | Starting point |
| --- | --- |
| Change how a stick drives a character | **Character: Move**. Override `CanMove` to gate movement or `GetMovementInputScaleValue` for a different stick response. Use the manager's Analog Stick Behavior and the handler's walk/run scales for the supplied gaits. |
| Hand movement to a custom pawn | **Character: Move (Interface)** calls `IMovementInputProxyInterface::PrepareAndAddMovementInput` on the pawn with a world direction and scale. |
| Vault on jump or customize crouching | Implement `ITraversalMovementInputInterface::TryTraversalJumpAction` on the pawn. Return true when it handles the traversal. In the crouch handler, override `CanCrouch` or `ShouldUncrouch`. |
| Restrict camera movement | In **Character: Look**, override `CanLook`, `CanChangePitch`, or `CanChangeYaw`. Use **Character: Turn** for a separate turn action. |
| Open a screen | Choose **HUD: Send UI Event**, assign an Event Tag, and implement `IHUDEventDispatcherInterface::HandleInputEvent` on the Player Controller's HUD. Have the HUD use the tag to open the widget. |

The supplied character handlers can also read blocking tags from the pawn's ability system. For example, grant `Input.Block.Movement` during an interaction to suppress movement, or use `Input.Block.Camera.Pitch` to restrict looking up and down. If you override a gate such as `CanMove`, call the parent check to keep its tag and input-magnitude rules.

[Create a custom handler](ipt_guide_custom_handler.md) or [route an action to a gameplay ability](ipt_gas_handlers.md).
