# Changelog
<primary-label ref="inventory"/>

## 1.0.0 - 12/08/2024
First release for Unreal Engine 5.3 and 5.4.

## 1.0.10 - 25/08/2024
```
[improvement] Organizing the code to eventually auto-generate Mesh Components for slots.
[improvement] Added a component that enables direct integration with Ninja Combat.
[improvement] Added a function that can assume the container from an item in safe scenarios.
[bugfix] Fixed initial memories for Level and Quality fragments.
[bugfix] Fixed filters for Data Tables.
[bugfix] Fixed a crash while checking for empty Inventory Avatars.
[bugfix] Fixed a corner-case of adding items to the first position in a container, without a pre-set container and multiple stacks.
[bugfix] Fixed the helper function that checks the result of an item context and provides a path.
```

## 1.0.11 - 08/09/2024
```
[improvement] Added a default implementation to the Equipment Actor Interface so it can use the Equipment Receiver Component.
```

## 1.1.14 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
[improvement] Added the appropriate Editor Category for all Inventory Assets in the Content Browser.
[improvement] Improved the logic for the Inventory Animation Ability activation check.
[bugfix] Fixed the Equipment State Changed broadcast not being called.
```

## 1.3.17 - 30/12/2024
```
[added] Completed "Load" functionality.
[added] New Scene Selector (`EquipmentSceneComponentProvider`) based on an interface, for advanced logic.
[improvement] Added the source to pickup actors.
[improvement] Exposed consumable objects in the Consumable Ability.
[bugfix] Fixed `IsSuccessful` in the `FInventoryItemContext`.
```