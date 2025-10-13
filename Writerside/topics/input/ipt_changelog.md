# Changelog
<primary-label ref="input"/>

## 5.5.13 - 13/10/2025
```
[improvement] Expanded logs and organized their locations to promote category reusability.
[fix] Remove assertion for Enhanced Input Subsystem on endplay.
[fix] Ensured that the Input Buffer only activates on the local player.
```

## 5.5.10 - 03/09/2025
```
[fix] Added missing plugin dependency ModelViewViewModel.
```

## 5.5.9 - 01/09/2025
```
[added] Introduced a custom Input User Settings that includes common input modifiers (mouse sensitivity, gamepad sensitivity, etc.)
[added] Input Modifiers that apply values from the settings class to the Input Actions. 
[added] Introduced settings, functionalities ViewModels related to key remapping.
[added] Input Handler to print debug strings. Meant to be used in the editor, while testing input setups.
[added] Input Handler specifically designed for Ninja Combat's Combo Input system.
[improvement] You can provide your own "ModifyContextOptions", per Input Mapping Context, when registering these data assets.
[improvement] Added DefaultToSelf metadata to relevant functions in the BP library.
[improvement] Organized internal folders for input files, so they are grouped under `Input`.
[fix] Added missing descriptions for the DefaultHoldCombo handler.
```

## 5.0.5 - 04/07/2025
```
[improvement] Default Combo Check and dedicated Combo Tags/Events for the Default/Hold/Combo handler.
[improvement] An options to provide hold-durations as Gameplay Event magnitudes.
[improvement] New Elapsed Time function parameter for Completed and Cancelled handler functions.
[improvement] Option to add standalone Input Mapping Contexts, not related to an Input Setup.
[improvement] Exposed a gameplay tag container to the Input Manager that blocks mouse rotation.
```

## 5.0.0 - 21/04/2025
> **Important Changes in this version**
>
> 1. **Momentary** and **Toggled** are not set in the handler anymore. Instead, they are set by ability tags, in each ability.
> 2. The **Forward Reference Tag** has been changed to `Input.Component.ForwardReference`.

```
[added] Input Handler for "Press" and "Hold" activations.
[added] Momentary and Toggled Input Gameplay Tags, replacing the flags in ability activation handler, to make these behaviors dynamic, per-ability.
[improvement] Separate the Gameplay Event function from the "Send Gameplay Event" Handler, so it can be reused in different scenarios.
[improvement] Introduced a library function to provide the "Hold Duration" for Hold triggers.
[improvement] Added a return type to activation and cancellation of the abilities.
[improvement] Added the option to perform a check before sending gameplay events.
[improvement] Exposed activation and cancellation functions to Blueprints.
[improvement] Added a function library method to provide the mouse cursor position in world space.
[improvement] Added extra checks for the "Rotate to Mouse Cursor" functionality, so it better integrates with Common UI input modes.
[improvement] Renamed the Forward Reference Tag, so it matches the naming convention for component tags: `Input.Component.ForwardReference`
[bugfix] Added gameplay tag container include to the InputBufferInterface to avoid build issues.
```

## 4.10.25 - 31/01/2025
```
[added] Added buffer channels to the Input buffer. 
[added] Added the TraversalMovementInputInterface, providing a viable extension point for GASP's Jump and/or other similar implementations.
[improvement] Updated the Jump Handler to accommodate the new TraversalMovementInputInterface.
[improvement] Updated the Crouch Handler to simplify toggle/momentary setup.
[improvement] Added extension points to define Instigator Tags, Target Tags and the second Optional Object, for the Send Gameplay Event Handler.
[improvement] Added the option to conditionally cancel the ability for false activations (before, this was always the case).
[improvement] Exposed the "Rotate to Mouse Cursor" function so it can be used in other locations.
[bugfix] Improved the Input Buffer Notify, to properly handle different times from scaled animations. Added a fallback logic so it won't rely only on the End Notify event.
[bugfix] Ensured that the automatic Control Rotation will respect the "Input.Block.Rotation" tag.
```

## 4.8.18 - 30/12/2024
```
[added] Added "Mac" to the list of Allowed Build Platforms.
[improvement] Added GASP features to Look and Move handlers.
```

## 4.8.16 - 22/11/2024
```
[improvement] Refactored "Replicated Move" to be more intuitive. It was renamed to "Move (Interface)" and it connects to IMovementInputProxyInterface. 
[improvement] Refactored "CanXYZ" methods for "Move", "Look" and "Turn", so they also receive the actual value to unify their input value magnitude checks.
[bugfix] Fixed jump handler so it will correctly consider "blocked tags".
```

## 4.8.13 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
```

## 4.7.13 - 19/10/2024
```
[added] Function to rotate controller to face the mouse pointer.
[added] Added support for Linux.
[added] Added the "ToggleRotationDuringRootMotion" to allow control rotation during Root Motion animations.
[improvement] Passed details about the Action Instance to internal extensible methods in the Input Manager.
[improvement] Parameterized minimum magnitudes in the movement/look and turn handlers.
[improvement] Ability Activation now supports axis values as well, in addition to boolean ones.
[improvement] Added methods to query the current control method.
[improvement] Updated the Function Library component finder to handle any viable input - pawn or player controller.
[bugfix] Ensured that control mode and controller rotation are correctly handled in multiplayer.
```

## 4.4.7 - 24/09/2024
```
[added] Added support functionalities for Common UI, including a router.
[added] Added decicated blocker tags for Camera, so you can disable only pitch, only yaw, or both.
```

## 4.3.5 - 08/09/2024
```
[added] Added methods to completely disable/enable input handling.
[bugfix] Ensured that the Input Buffer can be found, when the Input Manager is added to Controllers.
[bugfix] Removed an ensure condition that was not necessary.
```

## 4.2.3 - 23/08/2024
```
[major] Replaced the Input Detection Handlers/IMC with an automated detection in the Input Manager.
[added] Added an option to automatically create forward references, instead of requiring a pre-existing arrow.
[added] Added an optional code to rotate the Player Controller to the Mouse cursor, since Input Actions cannot do a value stream.
[improvement] Renamed all default assets (Actions, Mappings and Setup) so their names are different than the assets you get from the Unreal Templates, which were leading to some confusion before.
[Improvement] Data Validation of the setup is not optional anymore. It will check for missing data and also for mismatches between handlers and the context.
[deprecation] Removed the State Switch handler, since that was mostly meant to help transitioning from the old input system to the new one.
[deprecation] UI Events (Interface and Handler) will be reworked for next version and will most likely change a lot, also to keep up with Common UI.
```

## 3.0.1 - 08/07/2024
```
[bugfix] Added the missing UFUNCTION macro to the Make Function for MakeBufferedInputCommand.
```

## 3.0.0 - 04/07/2024
```
[major] Input Handlers now expose Elapsed Time for inputs, via additional parameters for the handler functions for "Triggered" and "Ongoing".
[improvement] Modified the Input Handler function call hierarchy, so it can be extended with access to the original Input Action Instance.
```

## 2.5.2 - 05/05/2024
```
[added] Added the new IInputSetupProviderInterface that allows you to provide new Input Setups when pawns are possessed/unpossessed. Useful when you set the input manager in controller classes.
[improvement] Added support to Unreal Engine 5.4.
[bugfix] Fixed a bug that was keeping old setups when pawns were being unpossessed.
```

## 2.4.2 - 31/03/2024
```
[added] Added a "Double Tap" trigger.
[improvement] Introduced the UNinjaInputAbilityActivationCheck which can handle odd ability activation cases (such as the tap trigger).
```

## 2.3.1 - 27/02/2024
```
[bugfix] Fixed the Forward Reference retrieval for controller-based setup.
[deprecation] Removed support for Unreal Engine 5.1 and 5.2.
```

## 2.3.0 - 01/10/2023
```
[added] Added GetPawn function to the Input Component. It returns the owning pawn, regardless of where the component was added, Pawn or Controller.
[added] In some cases, when adding Input Setups via Begin Play, the controller may not be possessing the pawn yet. A new flow was introduced for such scenarios.
[improvement] Organized C++ folders so they are homogeneous with other Ninja Bear plugins.
[bugfix] Fixed the initialization flow to avoid issues with networked respawns.
[bugfix] Fixed the Controller initialization (and reinitialization) flows.
[deprecation] Removed support for Unreal Engine 5.0.
```

## 2.2.0 - 20/05/2023
```
[added] Support for Unreal Engine 5.2.
[improvement] Input Handlers have a GetWorld method that can be used during a "Handle" function.
[improvement] Refactored the Ability Activation base class to make it easier to modify and extend this class' hierarchy.
[improvement]  Changed the Asset Color for Ninja Input assets to improve their readability.
[improvement] Added all default triggers available from the Enhanced Input to the Ninja Input event tracking (in the Settings Page).
[bugfix] Fixed a bug where the Input Buffer would remain active when the Notify is interrupted.
[bugfix] The actual boolean value of the Input Action is now being considered for Activating Abilities. This is relevant for Pressed/Released triggers.
[bugfix] Removed the tag check for toggled/gameplay event ability activation as it's redundant now due to the proper boolean check listed above.
[deprecation] Unreal Engine 5.0 is now deprecated and soon, updates won't be applied to that version (when 5.3 is out, at the latest).
```

## 2.1.0 - 22/02/2023
```
[added] Data Asset validation that will check for missing assets and optionally match all Handlers with the Context, to ensure all Actions are covered.
[improvement] Made the InputBufferInterface more flexible so it can depend less on the Input Manager Component. There's also a new NinjaInputBufferComponent that can be used as base for new Input Buffers.
[bugfix] Trigger events will now broadcast correctly and won't erroneously duplicate the state when an Input Action changes the trigger state in the same frame.
[deprecation] Removed deprecated properties from the Manager Component.
```

## 2.0.0 - 07/02/2023
```
[added] A new Data Asset (UNinjaInputSetupDataAsset) was introduced to create a centralized way to set up Contexts and Handlers. This is the official way to add/remove Input Configuration from now on.
[added] An animation-based Input Buffer was added and can be used. Please check the official documentation for more details about this functionality.
[added] Editor integration: new Blueprint Handlers and Data Assets can be created from the "Right Click/New" menu, under the Input category.
[added] In the plugin's Settings Page, you can enable on-screen messages to ensure that your Handlers are being triggered at all, even if they are not working as expected.
[improvement] Small tweaks on the Manager Component to improve readability, more documentation added.
[improvement] The Manager Component is only tracking the events that are actually relevant by default (as long as proper Input Triggers are used for the Input Actions).
[bugfix] All Gameplay Events are properly triggered on Local Client and Server now.
[deprecation] Configuring the Input Handlers directly in the Manager Component, while still supported, is now deprecated and will be removed in the near future. You can copy and paste your properties into a new Data Asset.
```

## 1.2.0 - 16/01/2023
```
[added] All ability activation handlers support events (for combo systems), which replaces the old "Combo Ability" handler.
[added] All ability activation handlers support toggling activations and interruptions, which replaces the old "Ability Switch" handler.
[added] Dedicated handlers for Ability Interruptions (by class, tags and input IDs).
[improvement] Improved Display Names for Handlers so they are easier to find.
[bugfix] All registered Input Handlers will properly trigger, instead of just the first one.
```

## 1.1.0 - 02/01/2023
```
[added] Replicated Movement Interface and equivalent Handler. This allows calling other movement inputs on the character, that are usually used for replication (the MoveIt plugin is a good use case).
[added] State Handler Interface and equivalent Handler. Useful for toggle/momentary switches of states, such as Aiming, Sprinting, etc.
[added] Gameplay Ability handlers for Confirm and Cancel abilities.
[added] A Combo Ability Handler that triggers the ability and from there will send a Gameplay Event on further activations.
[added] Ability Switch, which has the same behaviour as the switch above, but with GAS-related setup.
[bugfix] Wrong variable names, fixed plugin's documentation link and updated copyright info.
```

## 1.0.0 - 15/12/2022
First release for Unreal Engine 5.0