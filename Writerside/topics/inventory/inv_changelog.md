# Changelog
<primary-label ref="inventory"/>

## 2.2.21 - 19/09/2025
```
[added] ViewModel exposing Inventory Attributes, such as Encumbrance and Wealth.
[improvement] Modified Equipment Load callback to make it more robust for precompiled libraries plus deep hierarchies.
[fix] Send Inventory Event notify won't trigger ensure assertion on editor.
[fix] Added platform allowlist for the test module.
[fix] Ensured that dynamic magnitudes are always applied, regardless of a previous application that happened before.
[fix] Changed direct call to interface call in NinjaInventoryDropZoneWidget.
```

## 2.1.16 - 10/09/2025
```
[improvement] Marked container function GetTotalSlots as virtual.
[improvement] Added an option to still execute item actions, even when an ability animation is missing.
[improvement] The inventory Subsystem will support registering inventories using either the avatar or owner.
[improvement] Added a GetInventoryAnimInstance function in the Equipment Interface, to support realtime retargeting scenarios. 
[fix] Ensured that the equipment manager queries equipment instances, not items.
[fix] Reintroduced missing blueprint attributes for inventory item, equipment and components.
[fix] Corrected the logic to determine the attach socket for the equipment actor, so it correctly addresses optional overrides. 
```

## 2.1.9 - 01/09/2025
```
[added] Introduced a network proxy and authorized inventory checkers.
[improvement] Exposed dedicated transfer function for inventory items.
[improvement] Updated arrays with raw object pointers to use TObjectPtr instead.
[improvement] Simplified the ASC binding flow to remove the confusing "bShouldFailFromASC" flag.
[improvement] Modified fragment initialization signature to avoid unnecessary copying of the initial memory struct.
[improvement] Automatic server RPC management for item and container functions.
[improvement] Tag-based visibility for Equipment Actors.
[fix] Build issue from FInventoryItemContainerPlacementOperation.
[fix] Corrected the description to match the purpose of the Drag and Drop ViewModel.
[fix] Added missing call to "Super" in the Inventory View Model resolver.
```

## 2.0.0 - 22/08/2025
```
[major] Moved all inventory and fragment delegates to the Inventory Manager.
[major] Updated Blueprint APIs to use FInstancedStruct (replaces TInstancedStruct in select signatures).
[major] Converted mostly the entire UI to View Models + Inventory Resolver.
[major] Container Placement: memory-driven initialization with salvage; deterministic container/position selection.
[major] Container Placement: new PlacementInitialized event; refined ContainerChanged/PositionChanged gating.
[major] Container Placement: accurate payloads (previous/current container & position); swap-aware add/move.
[major] Linked Container: primary and linked mirroring (equipment single-slot semantics).
[major] Linked Container: redirect when placed in linked first; move owner to primary, then mirror.
[major] Nested Container: auto-create on activation; lifecycle tied to owner; auto-remove on owner removal.
[added] Allowed build platforms: Linux and Mac.
[added] Spatial layout: PerCell and BitSetRows fit algorithms; custom hook via TestWithCustomAlgorithm (C++).
[added] Occupancy Masks with rotation support and in-editor mask UI (paint/mirror/rotate/validate).
[added] Drag & Drop: UNinjaInventoryDropZoneWidget + UNinjaInventoryDragDropOperation integration for world/container drops.
[added] Automated test suite covering placement, events, swaps, nested/linked, eviction, container removal.
[improvement] Container Placement: single graceful retry path (TryPlaceWithRetry) for transient failures.
[improvement] Container Placement: ResolveById for authoritative container instance resolution.
[improvement] Linked Container: listens to item + container events; clears mirror on container removal/unequip.
[improvement] Consume ability: expanded logs/comments to clarify cancellation causes.
[improvement] Attribute Set: replaced ensure with check/warning for Equipment Managers.
[improvement] Test utilities consolidated into shared event listeners and helpers.
[fix] Crash when removing items without stacks fragments.
[fix] Consume from gameplay events condition corrected.
[fix] Equipment State ability now ends correctly when no animation is found.
[fix] Linked Container: prevented duplicate subscriptions and stale mirror memory on deactivate.
[fix] Nested Container: prevented duplicate creation on re-activation or load.
[fix] Crash when loading inventory with certain stack values.
```

## 1.3.17 - 30/12/2024
```
[added] Completed "Load" functionality.
[added] New Scene Selector (`EquipmentSceneComponentProvider`) based on an interface, for advanced logic.
[improvement] Added the source to pickup actors.
[improvement] Exposed consumable objects in the Consumable Ability.
[fix] Fixed `IsSuccessful` in the `FInventoryItemContext`.
```

## 1.1.14 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
[improvement] Added the appropriate Editor Category for all Inventory Assets in the Content Browser.
[improvement] Improved the logic for the Inventory Animation Ability activation check.
[fix] Fixed the Equipment State Changed broadcast not being called.
```

## 1.0.11 - 08/09/2024
```
[improvement] Added a default implementation to the Equipment Actor Interface so it can use the Equipment Receiver Component.
```

## 1.0.10 - 25/08/2024
```
[improvement] Organizing the code to eventually auto-generate Mesh Components for slots.
[improvement] Added a component that enables direct integration with Ninja Combat.
[improvement] Added a function that can assume the container from an item in safe scenarios.
[fix] Fixed initial memories for Level and Quality fragments.
[fix] Fixed filters for Data Tables.
[fix] Fixed a crash while checking for empty Inventory Avatars.
[fix] Fixed a corner-case of adding items to the first position in a container, without a pre-set container and multiple stacks.
[fix] Fixed the helper function that checks the result of an item context and provides a path.
```

## 1.0.0 - 12/08/2024
First release for Unreal Engine 5.3 and 5.4.
