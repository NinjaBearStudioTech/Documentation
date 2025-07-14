# Container Placement
<primary-label ref="inventory"/>

The **Container Placement** fragment determines where an item is stored in the inventory. It handles the selection of a 
container and position, and stores the result in a fragment memory.

This fragment is essential for jigsaw inventory, equipment slots, or any system where items must be physically or 
logically placed.

It works in conjunction with container layouts and can define preferred containers using a tag query. If no preferred 
container is available, the system selects the most appropriate option based on layout, compatibility, and priority.

## Fragment Tags
This fragment does not add any traits to the item, but it relies on container tags and layout compatibility to work correctly.

## Properties
This fragment has the following property.

| Property                  | Description                                                                  |
|---------------------------|------------------------------------------------------------------------------|
| `PreferredContainerQuery` | Gameplay Tag Query used to filter/select preferred containers for this item. |

## Operations
This fragment exposes the following operations.

| Function                            | Description                                                                  |
|-------------------------------------|------------------------------------------------------------------------------|
| `GetDefaultContainer`               | Returns the default container for the item based on the fragment memory.     |
| `GetContainer`                      | Returns the container where the item is currently placed.                    |
| `GetPosition`                       | Returns the position of the item in its current container.                   |
| `SetContainerAndPosition`           | Manually sets the item's container and position.                             |
| `GetOrSelectContainerForItem`       | Tries to use memory/default/preferred container, or selects one dynamically. |
| `SelectContainerForItem`            | Finds the best container for the item using the provided criteria.           |
| `SelectPositionForItem`             | Returns a valid position for the item in its current container.              |
| `SelectPositionForItemInContainer`  | Returns a valid position for the item in the provided container.             |
| `FindPreferredContainers`           | Finds containers matching the preferred tag query.                           |

## Memory
This fragment uses `InventoryItemFragmentContainerMemory` to store the current **container** and **position**.

## Event Payload
This fragment emits the following events, using `InventoryItemContainerPlacementPayload` as the payload structure.

| Event                                   | Description                                                   |
|-----------------------------------------|---------------------------------------------------------------|
| `Inventory.Event.Item.ContainerChanged` | The container storing the item has been changed.              |
| `Inventory.Event.Item.PositionChanged`  | The position of the item, in the container, has been changed. |
