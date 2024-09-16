# Input Handlers
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>These are small pieces of code used to handle player input, from the <b>Enhanced Input Subsystem</b>.</li>
        <li>The Input System provides multiple handlers, but you can create your own from <code>NinjaInputHandler</code>, or extending from the other ones available.</li>
    </ul>
</tldr>

Input Handlers are responsible for handling **Player Inputs**. They are mapped to **Input Actions**, bundled into an
**Input Setup** and then triggered by the **Input Manager**.

## Input Handler Design

Input Handlers extend from `NinjaInputHandler`, which grants them the following **default properties**.

| Property        | Description                                                      |
|-----------------|------------------------------------------------------------------|
| Input Actions   | Input Actions compatible with the Input Handler.                 |
| Trigger Events  | For each provided action, which Trigger Events will be detected. |
| Can Be Buffered | Allows the Input Handler to be buffered .                        |

Input Handlers also inherit the following **functions**.

| Function   | Description                                                                                            |
|------------|--------------------------------------------------------------------------------------------------------|
| Can Handle | Determines if the Handler is compatible with an **Input Action** and **Input Trigger**.                |
| Handle     | Multiple Handle functions are available, differentiating the type of trigger that needs to be handled. |

The `CanHandle` check is purely a **compatibility** check and should not include temporary states. As for the `Handle`
functions, you only need to implement the ones that are actually used by your handler.

Both functions are marked as `const`, since the Input Handler is not supposed to have a **state**. If that is required,
then the state must be persisted somewhere else, such as the **Player Controller** or **Character**.