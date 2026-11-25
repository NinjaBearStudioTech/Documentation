# Sources, Targets, and Selection
<primary-label ref="interaction"/>

Put an **Interaction Manager** on the pawn that acts and an **Interaction Target Component** on the object that responds. Each source keeps its own list of nearby targets. Two players can look at the same door, or one can focus the door while the other focuses a switch.

## How the Player Selects an Object

**Registered** means the target is in the source's scan area. **Eligible** means it can be considered for focus. **Focused** means the search has selected it. A target can be registered while the player is looking elsewhere. A focused target can offer several slots, such as Open and Inspect.

Choose the **Interaction Task Class** on a subclass of `InteractionAbility_FindInteractableActor` to suit your controls.

| How the player selects | Search task |
| --- | --- |
| Face a nearby object | **Find Closest Interaction Target** considers objects overlapping the focus shape, using distance and facing to choose among them. |
| Aim the camera | **Trace Interaction Target** looks along the camera's center line for a registered target. Configure the camera trace channel so the target can be hit. |
| Point with the mouse | **Mouse Cursor Interaction Target** uses the cursor hit to select a registered target. |

The search checks availability and Smart Object slot preconditions. If objects can be used through walls, check the search task's line-of-sight option and the channel used for blocking geometry. For a different selection rule, extend `UNinjaInteractionSearchAbilityTask` and choose it on the find ability. Override `InitializeInteractionAbilityTask` to customize how the ability creates the task. The find ability also exposes `HandleInteractionTargetFound` and `HandleInteractionTargetLost` for source-side responses. Override `InitializeInteractionRequest` when your game needs a different rule for choosing a slot on the selected actor.

## React to Discovery and Focus

| Where | Hook | Example |
| --- | --- | --- |
| Interaction Manager | `OnInteractionRegistered`, `OnInteractionUnregistered` | Add or remove one slot's offer from a nearby-actions list. The event carries the summary ID, type, and slot tags. |
| Interaction Manager | `OnFocusStateChanged`, or `Native_OnFocusStateChanged` in C++ | Move the highlight or discard a pending input confirmation when the selected slot loses focus. |
| Target component | `OnTargetRegistered`, `OnTargetUnregistered`, `OnFocusEligible`, `OnFocusApplied`, `OnFocusRemoved` | Give a switch a faint outline in range and a brighter one when selected. Each event identifies the source. |
| Target actor | `IsAvailableForInteraction`, `CanHandleInteraction` | Implement these on the **Interaction Target Interface** to hide an exhausted machine or allow Open only while a door is closed. |

The supplied interaction actors already implement the interface. On your own actor, implement `IInteractionTargetInterface` and return its component from `GetInteractionTargetComponent`. The component forwards callbacks such as `HandleFocusApplied` and `HandleFocusRemoved` to that actor.

Use [First Steps](int_first_steps.md) for a focused switch. For a proximity action that should work independently of the current selection, follow [Interact Without Focus](int_guide_without_focus.md).
