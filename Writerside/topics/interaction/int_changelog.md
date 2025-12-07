# Changelog
<primary-label ref="interaction"/>

## 1.2.7
<secondary-label ref="wip"/>
```
[improvement] Added a "toggleable" option for the Openable Actor.
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
