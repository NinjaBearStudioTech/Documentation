# Managing Input Setups
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>The <b>Input Manager</b> can have <b>default</b> Input Setups available in all situations.</li>
        <li>Input Setups can be <b>added</b> or <b>removed</b> using the appropriate functions in the <b>Input Manager</b>: <code>AddInputSetupData</code> and <code>RemoveInputSetupData</code>.</li>
        <li>New Pawns set to a <b>Player Controller</b> can grant their own Input Sets via <code>InputSetupProviderInterface</code>. They are automatically added and removed when the pawn is <b>possessed</b> and <b>unpossessed</b>.</li>
    </ul>
</tldr>

Following the **Enhanced Input** philosophy supporting **multiple Input Mapping Contexts**, the Input System allows you 
to define various **Input Setups**.

You can categorize Input Setups as:

- **Default**: Always available to the player pawn.
- **Situational**: Added or removed based on specific contexts.

## Default Input Setups

Default Input Setups are **always active** and are assigned within the Input Manager Component’s **Default Settings**.

The system supports multiple Default Input Setups, providing the flexibility to organize your inputs into as many 
**logical bundles** as needed.

The specifics of which default setups to add will vary depending on the project's scope. Smaller games might benefit 
from having all setups added as default. In contrast, larger games may require more deliberate management of input contexts.

> **Context Priorities**
>
> If you have overlapping Setups/Contexts (e.g., **Basic Locomotion** and **Mount Locomotion**), consider adjusting 
> their priorities to ensure that the more specific context (like Mount Locomotion) takes precedence and properly 
> **consumes the input**.
{style="note"}

## Situational Input Setups

Situational Input Setups are **activated on-demand** and are triggered by specific events, allowing for the addition or 
removal of Input Setups as needed.

### Add and Remove Functions

The **Input Manager Component** provides dedicated functions to add or remove Input Setups whenever necessary. It’s 
important to ensure that any context you add is properly removed later to avoid unexpected behavior.

> **Input Context Mapping Duplicates**
>
> The Input Manager Component does not allow **duplicate contexts**. Attempting to add a context that has already been 
> processed will generate a warning in the `LogNinjaInput` category.
{style="note"}

### Input Setup Provider Interface

Situational Input Setups can also be managed via the **Input Setup Provider Interface**.

This interface can be implemented by any pawn. When a Player Controller possesses such a pawn, its Input Manager 
Component checks for this interface and automatically adds the provided setups. The setups are then removed when the 
pawn is unpossessed.

> **Player Controller Requirement**
>
> This approach requires the Input Manager Component to be added to the **Player Controller** so it can respond to Pawns 
> being **possessed** and **unpossessed**.

### User Interface Input

Depending on your design, you might want to add or remove dedicated Input Setups when your User Interface is active, 
allowing the player to navigate the UI with specific inputs.

Here are some options for managing Input Contexts for UI:

- Change the **Input Mode** when the User Interface is active.
- Use **Common UI** to manage inputs, including its own **Enhanced Input** integration.
- Use **Ninja Input** to add/remove a dedicated setup with high priority when the UI is activated.

