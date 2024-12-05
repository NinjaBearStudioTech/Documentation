# Input Handlers
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>These are small and dedicated objects, used to handle player input detected by the <b>Enhanced Input Module</b>.</li>
        <li>The Input System provides multiple handlers, but you can create your own extending from the base <code>NinjaInputHandler</code>, or from any other handler.</li>
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

Input Handlers also contain the following relevant **functions**.

| Function   | Description                                                                                            |
|------------|--------------------------------------------------------------------------------------------------------|
| Can Handle | Determines if the Handler is compatible with an **Input Action** and **Input Trigger**.                |
| Handle     | Multiple Handle functions are available, differentiating the type of trigger that needs to be handled. |

The `CanHandle` check is purely a **compatibility** check and should not include temporary states. As for the `Handle`
functions, you only need to implement the ones that are actually used by your handler.

Both functions are marked as `const`, since the Input Handler is not supposed to have a **state**. If that is required,
then the state must be persisted somewhere else, such as the **Player Controller** or **Character**.

## Creating Input Handlers

Input Handlers can be created from the `NinjaInputHandler` class, or any other Handler class available in the system 
that better fits your goals.

### Handler Methods

As previously mentioned, you have multiple **Handle** functions, respective to the main **input events** triggered by 
the Enhanced Input system:

- **Started**: An input action has started but have not yet triggered. "Started" and "Triggered" may happen during the same frame.
- **Triggered**: An input action was triggered. The moment when this happens depends on the type of trigger set in the Input Action. For example, the "_Pressed_" trigger will send this event as soon as the actuation happens.
- **Ongoing**: An input action has been triggered, and it is still ongoing. For example, the "_Down_" trigger will send this event while the tracked button is pressed.
- **Completed**: An input action has been fully handled. "Completed" and "Triggered" may happen during the same frame.
- **Cancelled**: An input action has started, but was interrupted before reaching the "Triggered" event.

> **Common Inputs**
> 
> The **Triggered** event is usually the best option, if you want to react to a successful _single_ input. If you are 
> tracking _continuous_ inputs, then react to **Triggered** and **Ongoing**.
{style="note"}

You can determine is a key was pressed or released with the appropriate **Pressed** and **Released** Input Action 
Triggers. They provide appropriate `true` and `false` values that you can use. You can convert the value provided by the
Handler to a boolean, using the conversion functions provided by the Enhanced Input library.

<img src="ipt_handler_convert_boolean.png" alt="Boolean Conversion" thumbnail="true" border-effect="line"/>

> **Boolean Value Conversion**
> 
> The conversion function is an _autocast_ function, meaning you won't be able to find it in the context menu. Instead, 
> you must **drag** the Value parameter pin to the Branch's Condition parameter, to automatically create the conversion.

The following image shows the beginning of a custom **Input Handler** along with some strategies to access data from it.

<img src="ipt_create_handler_event.png" alt="Handler Function Example" thumbnail="true" border-effect="line"/>

In the image above, you can see that the `HandleTriggeredEvent` function was implemented. From its input parameters, you
can access relevant information:

- **Manager**: The Actor Component assigned to the owning character invoking this handler. You can access your **Player Pawn**, **Controller** and **Ability System Component** from this component. 
- **Value**: Final Action value to be applied to the owning character. Make sure to access the value in a way that is coherent with the Input Action value type.
- **Input Action**: Additional information about the Input Action that triggered this handler. 
- **Elapsed Time**: Total time the action has been evaluating triggering. Only relevant for Ongoing and Triggered events.

> **Migrating Default Functions**
> 
> When migrating default input code to Input Handlers, from one of the templates provided by Unreal Engine for example,
> you will usually need to access the Character or its components. 
> 
> You can access this instance through the Input Manager reference. Also, consider creating **interfaces** when needed if 
> you want to reuse Handler between different types of Characters or Pawns.
{style="note"}

### Compatibility Checks

Handlers need to determine if they are compatible with an action or not. This can be done via the `CanHandle` function.

The default handler already provides a behavior that checks if the Input Handler is compatible with the **Input Action** 
and **Trigger Event**, which are defined by the Handler's default properties, `InputActions` and `TriggerEvents`. 

the following image shows an additional check for a custom Input Action Data Asset that may contain project-specific
information, that could even be used in the test itself.

<img src="ipt_create_handler_check.png" alt="Check Function Example" thumbnail="true" border-effect="line"/>

> **Parent Function**
> 
> Make sure to call the **Parent Function** to retain the original tests, unless you actually want to fully override 
> them in your new function!
{style="note"}

> **`CanHandle` Logic**
> 
> Do not add _situational_ checks to the `CanHandle` function. Tests done in this function are meant to be _static_, to
> ensure the compatibility between a handler and an incoming action!
{style="warning"}