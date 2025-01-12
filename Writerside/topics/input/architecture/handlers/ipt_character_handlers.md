# Character Handlers
<primary-label ref="input"/>

These Input Handlers are meant to be used with **character-related actions**, such as **Move** or **Jump**.

## Crouch

Changes the Character's **Movement Mode** to **Crouched**. It can be used in two ways: **Momentary** and **Toggle**:

- **Momentary**: Result of an Input Action with **Pressed** and **Released** Trigger Events.
- **Toggle**: Result of an Input Action with a **Pressed** Trigger Event.

Crouching will not be triggered under the following conditions:

- The value of `BlockCrouchTags` is set, and the owning character has any of these Gameplay Tags.
- Crouch is disabled in the **Character Movement Component** (`bCanEverCrouch`).

## Jump

Triggers the Character's **Jump** and **Stop Jumping** functions. These are executed from **Triggered** and **Completed**
events, respectively.

The Jump Handler is also compatible with `TraversalMovementInputInterface`, allowing the character to perform a traversal
movement, such as *vaulting*, before actually executing the jump. 

To implement this functionality, add the `TraversalMovementInputInterface` to the Character, and implement 
`TryTraversalJumpAction`, that will be invoked by the Jump Handler during **Started** and **Triggered** events. 

Here's an implementation example, based on the GASP source.

<img src="ipt_handler_jump_traversal.png" alt="Traversal Jump example" thumbnail="true" border-effect="line" width="600"/>

## Look

Moves the Controller's Yaw and Pitch, based on the incoming **2D input values**. It will execute from **Triggered** and 
**Ongoing** events. Supports blocking the camera, via the presence of **Gameplay Tags**.

To achieve the expected results, the **Spring Arm Component** attached to the owning pawn/character must have the 
property `bUsePawnControlRotation` set to `true`.

## Move (Standard)

Moves a Pawn or Character, based on the incoming **2D input values**. It will execute from **Triggered** and **Ongoing** 
events. Supports blocking the movement, via the presence of **Gameplay Tags**.

For certain setups, such as _top-down with WASD movement_, a **[](ipt_forward_reference.md)** is required.

## Move (Interface)

A version of the **Move Handler** that routes incoming **2D input values** to an **interface**, instead of the usual 
Pawn Movement functions.

This allows developers to do something with the input, before forwarding it to the Pawn Movement Functions, such as
storing and then replicating these values. This technique is common in popular locomotion frameworks.

When using this version of the Handler, implement `MovementInputProxyInterface` in the Pawn or Character, store or 
replicate the incoming values as needed, and then forward them to the usual Pawn Movement functions.

## Turn

Rotates the character based on a 2D Input Value. Very common for _Twin-Stick Movement_. It will execute from **Triggered** 
and **Ongoing** events. Supports blocking the rotation, via the presence of **Gameplay Tags**.

Primarily meant to be used as the **gamepad right thumbstick**. Handling a **Look At Mouse Cursor** setup is not supported
by default Input Actions, since their value will not trigger continuously without changes in the input.

To handle that, the Input Manager Component can **rotate the controller**, using the **mouse cursor location** as a target.
The following properties and functions can be used to enable and adjust this functionality:

- `bShouldRotateControllerToMouseCursor`: Enables the rotation to mouse cursor.
- `MouseChannel`: **Collision Channel** used to capture the **mouse cursor** in the world.
- `ControlRotationInterpSpeed`: Used to **smooth** the rotation by **interpolating** between current and target positions.
- `RotateControllerToMouseCursor`: Rotates the Player Controller the current mouse cursor. Can be overwritten in Blueprints or C++.

> **Component Tick**
> 
> The Input Manager does not have its **Tick** function enabled by default. However, enabling this functionality will
> enable the tick, when the **Input Mode** is set to **Keyboard and Mouse**, so it can rotate the owning controller.