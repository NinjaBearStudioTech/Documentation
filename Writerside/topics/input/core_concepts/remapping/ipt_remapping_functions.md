# Key Remapping Functions
<primary-label ref="input"/>
<secondary-label ref="experimental"/>

Ninja Input exposes several key functions for working with **Input Remapping**, all available in the **Input Manager 
Component**.

| Function               | Description                                                                                                                                             |
|------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|
| `GetInputUserSettings` | Returns the active **Input User Settings** instance. This will be the custom type `UNinjaInputUserSettings`, as configured in the [remapping setup][1]. |
| `RemapKey`             | Remaps a key using the provided `FMapPlayerKeyArgs`, which must contain the unique mapping ID and the new key.                                          |
| `SaveInputSettings`    | Saves the current input settings, typically after the player has finished configuring new bindings.                                                     |

## Saved Input Settings

Saving input settings happens **asynchronously**. You can track progress by overriding the `OnAsyncSaveComplete` function 
in your **User Settings** class.

It is also common to replace the default file-based serialization with a cloud save system (for example, Steam or Epic 
Online Services). To customize this behavior, override the `AsyncSaveSettings` function in your **User Settings** class.

## User Interface Integration

While you can call these functions at any time, the most common use case is through the **User Interface**.  

For handling the main **rebinding process**, the [ViewModels][2] provided by Ninja Input act as an **integration layer**,
bridging the Input Manager functions with your UI elements.

[1]: ipt_remapping_setup.md
[2]: ipt_remapping_ui.md
