# Changelog
<primary-label ref="inventory"/>

## 2.0.0 - 22/08/2025
<secondary-label ref="wip"/>
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
[bugfix] Crash when removing items without stacks fragments.
[bugfix] Consume from gameplay events condition corrected.
[bugfix] Equipment State ability now ends correctly when no animation is found.
[bugfix] Linked Container: prevented duplicate subscriptions and stale mirror memory on deactivate.
[bugfix] Nested Container: prevented duplicate creation on re-activation or load.
[bugfix] Crash when loading inventory with certain stack values.
```

## 1.3.17 - 30/12/2024
```
[added] Completed "Load" functionality.
[added] New Scene Selector (`EquipmentSceneComponentProvider`) based on an interface, for advanced logic.
[improvement] Added the source to pickup actors.
[improvement] Exposed consumable objects in the Consumable Ability.
[bugfix] Fixed `IsSuccessful` in the `FInventoryItemContext`.
```

## 1.1.14 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
[improvement] Added the appropriate Editor Category for all Inventory Assets in the Content Browser.
[improvement] Improved the logic for the Inventory Animation Ability activation check.
[bugfix] Fixed the Equipment State Changed broadcast not being called.
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
[bugfix] Fixed initial memories for Level and Quality fragments.
[bugfix] Fixed filters for Data Tables.
[bugfix] Fixed a crash while checking for empty Inventory Avatars.
[bugfix] Fixed a corner-case of adding items to the first position in a container, without a pre-set container and multiple stacks.
[bugfix] Fixed the helper function that checks the result of an item context and provides a path.
```

## 1.0.0 - 12/08/2024
First release for Unreal Engine 5.3 and 5.4.
