# User Interface Handlers
<primary-label ref="input"/>

These Input Handlers are meant to be used with the user interface layer.

## Send UI Event

This sends a Gameplay Event represented by a Gameplay Tag, to the current **HUD** class. This event can be cascaded down
to any specific Widget managed by the HUD class.

Gameplay Events are represented by **Gameplay Tags** and are sent to the HUD class via the `HUDEventDispatcherInterface`,
which has only one method: `HandleInputEvent`.

Make sure to implement the Interface in your HUD class and to set the appropriate HUD class to your **Game Mode**.

> **UI Navigation**
>
> These events are not meant to be used for UI Navigation. More appropriate use cases would be opening a Game Menu,
> Inventory Window and so on.
> 
> For UI Navigation, it's recommended to stick to the current UI navigation mechanisms for the default UI system or 
> Common UI, including the Common UI integration with the Enhanced Input.
{style="note"}