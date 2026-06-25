# Changelog
<primary-label ref="input"/>

## 6.0.0 - 17/04/2026
```
[major] Updated internal functions to send gameplay events in the Input Manager, so they are more flexible taking a single struct attribute.
[change] Added support for run threshold and run/walk scale to the Move Handler.
[fix] Added missing "BlueprintPure = false" to support functions in the Input Manager Component. 
```

## 5.6.16 - 12/01/2026
```
[change] Creating new Input Handler blueprints will open a class selection modal.
[change] Organized/standardized all function categories.
```

## 5.6.14 - 17/11/2025
```
[build] Added support to Unreal Engine 5.7, removed Unreal Engine 5.4 support
```

## 5.6.13 - 21/10/2025
```
[add] Action-to-Handlers cache to improve access time to eligible handlers. 
[change] Expanded logs and organized their locations to promote category reusability.
[fix] Remove assertion for Enhanced Input Subsystem on endplay.
[fix] Ensured that the Input Buffer only activates on the local player.
```

## 5.5.10 - 03/09/2025
```
[fix] Added missing plugin dependency ModelViewViewModel.
```

## 5.5.9 - 01/09/2025
```
[add] Introduced a custom Input User Settings that includes common input modifiers (mouse sensitivity, gamepad sensitivity, etc.)
[add] Input Modifiers that apply values from the settings class to the Input Actions. 
[add] Introduced settings, functionalities ViewModels related to key remapping.
[add] Input Handler to print debug strings. Meant to be used in the editor, while testing input setups.
[add] Input Handler specifically designed for Ninja Combat's Combo Input system.
[change] You can provide your own "ModifyContextOptions", per Input Mapping Context, when registering these data assets.
[change] Added DefaultToSelf metadata to relevant functions in the BP library.
[change] Organized internal folders for input files, so they are grouped under `Input`.
[fix] Added missing descriptions for the DefaultHoldCombo handler.
```

## 5.0.5 - 04/07/2025
```
[change] Default Combo Check and dedicated Combo Tags/Events for the Default/Hold/Combo handler.
[change] An options to provide hold-durations as Gameplay Event magnitudes.
[change] New Elapsed Time function parameter for Completed and Cancelled handler functions.
[change] Option to add standalone Input Mapping Contexts, not related to an Input Setup.
[change] Exposed a gameplay tag container to the Input Manager that blocks mouse rotation.
```

## 5.0.0 - 21/04/2025
> **Important Changes in this version**
>
> 1. **Momentary** and **Toggled** are not set in the handler anymore. Instead, they are set by ability tags, in each ability.
> 2. The **Forward Reference Tag** has been changed to `Input.Component.ForwardReference`.

```
[add] Input Handler for "Press" and "Hold" activations.
[add] Momentary and Toggled Input Gameplay Tags, replacing the flags in ability activation handler, to make these behaviors dynamic, per-ability.
[change] Separate the Gameplay Event function from the "Send Gameplay Event" Handler, so it can be reused in different scenarios.
[change] Introduced a library function to provide the "Hold Duration" for Hold triggers.
[change] Added a return type to activation and cancellation of the abilities.
[change] Added the option to perform a check before sending gameplay events.
[change] Exposed activation and cancellation functions to Blueprints.
[change] Added a function library method to provide the mouse cursor position in world space.
[change] Added extra checks for the "Rotate to Mouse Cursor" functionality, so it better integrates with Common UI input modes.
[change] Renamed the Forward Reference Tag, so it matches the naming convention for component tags: `Input.Component.ForwardReference`
[fix] Added gameplay tag container include to the InputBufferInterface to avoid build issues.
```

## 4.10.25 - 31/01/2025
```
[add] Added buffer channels to the Input buffer. 
[add] Added the TraversalMovementInputInterface, providing a viable extension point for GASP's Jump and/or other similar implementations.
[change] Updated the Jump Handler to accommodate the new TraversalMovementInputInterface.
[change] Updated the Crouch Handler to simplify toggle/momentary setup.
[change] Added extension points to define Instigator Tags, Target Tags and the second Optional Object, for the Send Gameplay Event Handler.
[change] Added the option to conditionally cancel the ability for false activations (before, this was always the case).
[change] Exposed the "Rotate to Mouse Cursor" function so it can be used in other locations.
[fix] Improved the Input Buffer Notify, to properly handle different times from scaled animations. Added a fallback logic so it won't rely only on the End Notify event.
[fix] Ensured that the automatic Control Rotation will respect the "Input.Block.Rotation" tag.
```

## 4.8.18 - 30/12/2024
```
[add] Added "Mac" to the list of Allowed Build Platforms.
[change] Added GASP features to Look and Move handlers.
```

## 4.8.16 - 22/11/2024
```
[change] Refactored "Replicated Move" to be more intuitive. It was renamed to "Move (Interface)" and it connects to IMovementInputProxyInterface. 
[change] Refactored "CanXYZ" methods for "Move", "Look" and "Turn", so they also receive the actual value to unify their input value magnitude checks.
[fix] Fixed jump handler so it will correctly consider "blocked tags".
```

## 4.8.13 - 16/11/2024
```
[add] Support for Unreal Engine 5.5.
```

## 4.7.13 - 19/10/2024
```
[add] Function to rotate controller to face the mouse pointer.
[add] Added support for Linux.
[add] Added the "ToggleRotationDuringRootMotion" to allow control rotation during Root Motion animations.
[change] Passed details about the Action Instance to internal extensible methods in the Input Manager.
[change] Parameterized minimum magnitudes in the movement/look and turn handlers.
[change] Ability Activation now supports axis values as well, in addition to boolean ones.
[change] Added methods to query the current control method.
[change] Updated the Function Library component finder to handle any viable input - pawn or player controller.
[fix] Ensured that control mode and controller rotation are correctly handled in multiplayer.
```

## 4.4.7 - 24/09/2024
```
[add] Added support functionalities for Common UI, including a router.
[add] Added decicated blocker tags for Camera, so you can disable only pitch, only yaw, or both.
```

## 4.3.5 - 08/09/2024
```
[add] Added methods to completely disable/enable input handling.
[fix] Ensured that the Input Buffer can be found, when the Input Manager is added to Controllers.
[fix] Removed an ensure condition that was not necessary.
```

## 4.2.3 - 23/08/2024
```
[major] Replaced the Input Detection Handlers/IMC with an automated detection in the Input Manager.
[add] Added an option to automatically create forward references, instead of requiring a pre-existing arrow.
[add] Added an optional code to rotate the Player Controller to the Mouse cursor, since Input Actions cannot do a value stream.
[change] Renamed all default assets (Actions, Mappings and Setup) so their names are different than the assets you get from the Unreal Templates, which were leading to some confusion before.
[change] Data Validation of the setup is not optional anymore. It will check for missing data and also for mismatches between handlers and the context.
[deprecation] Removed the State Switch handler, since that was mostly meant to help transitioning from the old input system to the new one.
[deprecation] UI Events (Interface and Handler) will be reworked for next version and will most likely change a lot, also to keep up with Common UI.
```

## 3.0.1 - 08/07/2024
```
[fix] Added the missing UFUNCTION macro to the Make Function for MakeBufferedInputCommand.
```

## 3.0.0 - 04/07/2024
```
[major] Input Handlers now expose Elapsed Time for inputs, via additional parameters for the handler functions for "Triggered" and "Ongoing".
[change] Modified the Input Handler function call hierarchy, so it can be extended with access to the original Input Action Instance.
```

## 2.5.2 - 05/05/2024
```
[add] Added the new IInputSetupProviderInterface that allows you to provide new Input Setups when pawns are possessed/unpossessed. Useful when you set the input manager in controller classes.
[change] Added support to Unreal Engine 5.4.
[fix] Fixed a bug that was keeping old setups when pawns were being unpossessed.
```

## 2.4.2 - 31/03/2024
```
[add] Added a "Double Tap" trigger.
[change] Introduced the UNinjaInputAbilityActivationCheck which can handle odd ability activation cases (such as the tap trigger).
```

## 2.3.1 - 27/02/2024
```
[fix] Fixed the Forward Reference retrieval for controller-based setup.
[deprecation] Removed support for Unreal Engine 5.1 and 5.2.
```

## 2.3.0 - 01/10/2023
```
[add] Added GetPawn function to the Input Component. It returns the owning pawn, regardless of where the component was added, Pawn or Controller.
[add] In some cases, when adding Input Setups via Begin Play, the controller may not be possessing the pawn yet. A new flow was introduced for such scenarios.
[change] Organized C++ folders so they are homogeneous with other Ninja Bear plugins.
[fix] Fixed the initialization flow to avoid issues with networked respawns.
[fix] Fixed the Controller initialization (and reinitialization) flows.
[deprecation] Removed support for Unreal Engine 5.0.
```

## 2.2.0 - 20/05/2023
```
[add] Support for Unreal Engine 5.2.
[change] Input Handlers have a GetWorld method that can be used during a "Handle" function.
[change] Refactored the Ability Activation base class to make it easier to modify and extend this class' hierarchy.
[change]  Changed the Asset Color for Ninja Input assets to improve their readability.
[change] Added all default triggers available from the Enhanced Input to the Ninja Input event tracking (in the Settings Page).
[fix] Fixed a bug where the Input Buffer would remain active when the Notify is interrupted.
[fix] The actual boolean value of the Input Action is now being considered for Activating Abilities. This is relevant for Pressed/Released triggers.
[fix] Removed the tag check for toggled/gameplay event ability activation as it's redundant now due to the proper boolean check listed above.
[deprecation] Unreal Engine 5.0 is now deprecated and soon, updates won't be applied to that version (when 5.3 is out, at the latest).
```

## 2.1.0 - 22/02/2023
```
[add] Data Asset validation that will check for missing assets and optionally match all Handlers with the Context, to ensure all Actions are covered.
[change] Made the InputBufferInterface more flexible so it can depend less on the Input Manager Component. There's also a new NinjaInputBufferComponent that can be used as base for new Input Buffers.
[fix] Trigger events will now broadcast correctly and won't erroneously duplicate the state when an Input Action changes the trigger state in the same frame.
[deprecation] Removed deprecated properties from the Manager Component.
```

## 2.0.0 - 07/02/2023
```
[add] A new Data Asset (UNinjaInputSetupDataAsset) was introduced to create a centralized way to set up Contexts and Handlers. This is the official way to add/remove Input Configuration from now on.
[add] An animation-based Input Buffer was added and can be used. Please check the official documentation for more details about this functionality.
[add] Editor integration: new Blueprint Handlers and Data Assets can be created from the "Right Click/New" menu, under the Input category.
[add] In the plugin's Settings Page, you can enable on-screen messages to ensure that your Handlers are being triggered at all, even if they are not working as expected.
[change] Small tweaks on the Manager Component to improve readability, more documentation added.
[change] The Manager Component is only tracking the events that are actually relevant by default (as long as proper Input Triggers are used for the Input Actions).
[fix] All Gameplay Events are properly triggered on Local Client and Server now.
[deprecation] Configuring the Input Handlers directly in the Manager Component, while still supported, is now deprecated and will be removed in the near future. You can copy and paste your properties into a new Data Asset.
```

## 1.2.0 - 16/01/2023
```
[add] All ability activation handlers support events (for combo systems), which replaces the old "Combo Ability" handler.
[add] All ability activation handlers support toggling activations and interruptions, which replaces the old "Ability Switch" handler.
[add] Dedicated handlers for Ability Interruptions (by class, tags and input IDs).
[change] Improved Display Names for Handlers so they are easier to find.
[fix] All registered Input Handlers will properly trigger, instead of just the first one.
```

## 1.1.0 - 02/01/2023
```
[add] Replicated Movement Interface and equivalent Handler. This allows calling other movement inputs on the character, that are usually used for replication (the MoveIt plugin is a good use case).
[add] State Handler Interface and equivalent Handler. Useful for toggle/momentary switches of states, such as Aiming, Sprinting, etc.
[add] Gameplay Ability handlers for Confirm and Cancel abilities.
[add] A Combo Ability Handler that triggers the ability and from there will send a Gameplay Event on further activations.
[add] Ability Switch, which has the same behaviour as the switch above, but with GAS-related setup.
[fix] Wrong variable names, fixed plugin's documentation link and updated copyright info.
```

## 1.0.0 - 15/12/2022
First release for Unreal Engine 5.0