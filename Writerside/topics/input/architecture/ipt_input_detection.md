# Input Detection
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>The Input System will automatically broadcast changes in the <b>Input Mode</b>.</li>
        <li>Input Modes are represented by <b>Gameplay Tags</b>, and by default, <b>Touch</b>, <b>Gamepad</b> and <b>Keyboard and Mouse</b> are detected.</li>
        <li>The <b>Player Controller</b>, <b>Player Pawn or Character</b> and <b>Player HUD</b> can react to changes via <code>InputModeAwareInterface</code> functions.</li>
    </ul>
</tldr>

The Input System can automatically detect what Input Mode is being used by the player. This is useful to adjust your 
**user interface**, turn features like **aim-assist** on or off and so on.

## Reacting to Input Mode Changes

Input Mode detection happens in the **Input Manager Component**. It will do so automatically, whenever an **Input Action**
is received and processed.

> **Keys Must be Registered**
> 
> Only keys mapped to Input Actions and added from an Input Mapping Context will trigger the Input Detection.
{style="note"}

Once a change is detected, it can be obtained in three ways:

1. Binding do the `OnInputModeChanged` delegate, available in the **Input Manager Component**.
2. Calling the `GetPlayerInputMode` function, from the `InputModeAwareInterface`, implemented in the **Input Manager Component**.
3. Implementing the `InputModeAwareInterface` in a **Player Controller**, **Player Pawn** or **Player HUD**.

Input Modes are represented by **Gameplay Tags**. By default, the following Input Modes and Gameplay Tags are supported:

| Input Mode         | Gameplay Tag                  |
|--------------------|-------------------------------|
| Keyboard and Mouse | `Input.Mode.KeyboardAndMouse` |
| Gamepad            | `Input.Mode.Gamepad`          |
| Touch              | `Input.Mode.Touch`            |

## Supporting Additional Input Modes 
<secondary-label ref="advanced"/>

The following table can be used as a reference if you need to support **additional Input Modes**, or completely 
**override** the Input Mode Detection. All functions are in the **Input Manager Component**.

| Function             | Purpose                                                                                                               |
|----------------------|-----------------------------------------------------------------------------------------------------------------------|
| `DetectInputType`    | Evaluates an Input Action and determines if Input Mode has changed. Can only be overridden in C++.                    |
| `SetPlayerInputMode` | Reacts to a new Input Mode Tag, broadcasting it and forwarding to other objects. Can be override in C++ or Blueprint. |
