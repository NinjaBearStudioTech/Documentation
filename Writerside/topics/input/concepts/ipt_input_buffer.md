# Input Buffering
<primary-label ref="input"/>

A player presses the next action just before an animation finishes. Open a buffer for that part of the animation and the action can run when the window closes. An action outside the window takes its normal path immediately.

## Choose What to Keep

Give the handler a **Buffer Channel Tag** and enable **Can Be Buffered**. Open the same channel on the buffer. **Last Command** keeps the most recent input on that channel. **First Command** keeps the earliest one in version 6.1.20. If several handlers match that input on the channel, they can run together. Closing normally releases the saved input. Closing with **Cancelled** discards it.

Use separate channels when inputs should be remembered independently. For example, a queued movement press and a queued ability press can each have a window. **Disabled** turns off the built-in buffer for the manager.

## Drive a Window from Gameplay

Use `IInputBufferInterface::OpenInputBuffer` and `CloseInputBuffer` from Blueprint or C++ when a gameplay state owns the timing. Pass the channel tag to both calls. Pass true for cancellation when the action should be discarded. `IsInputBufferOpen` tests a channel, and `ResetInputBuffer` clears all pending commands.

To implement another policy, provide a component implementing `IInputBufferInterface` and disable the manager's built-in buffer. Return true from `IsInputBufferEnabled` on the replacement. Implement `BufferInputCommands` to store the matching handlers for one action/event, then release or discard them when the channel closes. Subclassing `UNinjaInputBufferComponent` lets you reuse the existing window handling.

[Buffer an action during a montage](ipt_guide_buffer_action.md).
