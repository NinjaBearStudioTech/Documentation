# Input Modes, Remapping, and Preferences
<primary-label ref="input"/>

Three things can change when a player picks up a controller. The prompt can show a gamepad button, the player can choose which button performs an action, and the stick can turn the camera at a different speed. Each has a different home.

| Player choice | Where to read or change it |
| --- | --- |
| Which device is in use? | The manager detects mapped input and publishes an input mode tag. Read `GetPlayerInputMode` for the current mode and listen to `OnInputModeChanged` for changes. |
| Which key performs Jump? | A player-mappable entry has a stable mapping name. Remap that name and slot on the local player's key profile. |
| How fast should the camera turn? | `UNinjaInputUserSettings` stores separate mouse X/Y sensitivity, gamepad sensitivity, and horizontal/vertical inversion. Apply the corresponding Input Modifier to the mapping that should use the preference. |

## React to a Device Change

Bind to **On Input Mode Changed** on the manager to update a widget. The delegate passes the new gameplay tag. A Player Controller, its possessed pawn, or its HUD can instead implement `IInputModeAwareInterface` and respond in `SetPlayerInputMode`. Use the tag to choose a prompt or switch an aim-assist setting. For a new device classification, override `DetectInputType` in a C++ manager subclass and use `SetPlayerInputMode` to publish the change.

## Save a Change

Call `GetInputUserSettings` on the manager for the local player. After applying the player's edits, call `SaveInputSettings`. Bind to `OnSaveSettingsStarted`, `OnSaveSettingsCompleted`, and `OnSaveSettingsFailed` on the settings object to show saving, dismiss it, or offer a retry. A custom settings class can override the C++ functions `AsyncSaveSettings` and `OnAsyncSaveComplete` for another storage system. Preserve those notifications for widgets using the save state.

For an options widget, the **Input Settings ViewModel** exposes the sensitivity and inversion setters. In a custom ViewModel, use `InitializeViewModel` to connect to the owning player and `ShutdownViewModel` to remove your bindings. For a C++ input modifier that uses another preference, derive from `UNinjaInputModifier` and read the local settings with `GetOrCacheSettings`.

[Build a key remapping menu](ipt_remapping_ui.md) or [adapt controls to the active device](ipt_input_detection.md).
