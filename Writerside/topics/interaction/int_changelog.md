# Changelog
<primary-label ref="interaction"/>

## 1.6.20 - 12/01/2026
```
[added] New interaction bookeping to better support multiple interactions from same target.
[added] New Interaction Task to Wait for Interaction, meant to replace the ootb Delay one.
[added] Base Interaction Widget that can be used as a base for both HUD and Actor prompts.
[added] Ability Task to detect interaction targets under the mouse cursor. 
[improvement] Reinforced policy for "wait interaction duration" task design in the state tree. 
[improvement] Organized/standardized all function categories.
[improvement] Cached interaction behaviors to reduce network requirements.
[improvement] Interaction Targets can broadcast changes in their internal state.
[improvement] Reviewed ViewModels to better handle scenarios where the pawn is not available yet (high latency).
[improvement] Reviewed ViewModels to remove distinction between actor-based and HUD-based widgets.
[improvement] Interaction Widget Component will natively/optionally support rotation to face the camera.
[improvement] Summary ViewModel will dynamically update the interaction text.
[improvement] Openable Interaction Actor will provide a dynamic prompt, based on its internal state.
[fix] Attempts to start an interaction with a current target respects its availability.
[fix] Elapsed time is always reset on clients before a new interaction starts.
[fix] Display Text is correctly stored by the Interaction Manager component. 
```

## 1.2.8 - 11/12/2025
```
[improvement] Provided a "toggleable" option for the Openable Actor.
[improvement] Provided an "auto-close" option for the Openable Actor.
```

## 1.2.6 - 17/11/2025
```
[added] A default Openable Actor that supports unlock/open/close interactions. Integrated with Keys on Ninja Inventory.
[improvement] Removed CanFinishState option from Trigger Interaction task, since it can be handled by State Trees.
[improvement] Made the Interaction Manager tick to be timer-based, to property support state trees not ticking or with long tick intervals.
[build] Added support to Unreal Engine 5.7
```

## 1.1.3 - 13/11/2025
```
[added] Support for automatic and disposable interaction traits. 
[fix] Created dedicated blueprint variants for GetInteractionSummary and GetInteractionSummaryForTarget in the Interaction Manager component.
[fix] Created a dedicated blueprint variant for GetInteractionSummaryForSlot in the Interaction Target component.
```

## 1.0.2 - 21/10/2025
```
[fix] Current/previous state tracking to ensure interaction events are triggered in the right order.
```

## 1.0.0 - 13/10/2025
First release for Unreal engine 5.6.
