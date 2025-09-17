# Container Fragment
<primary-label ref="inventory"/>

The **Container Placement** fragment determines where an item is stored in the inventory. It handles the selection of a 
container and position, and stores the result in a fragment memory.

This fragment is essential for jigsaw inventory, equipment slots, or any system where items must be physically or 
logically placed.

It works in conjunction with container layouts and can define preferred containers using a tag query. If no preferred 
container is available, the system selects the most appropriate option based on layout, compatibility, and priority.

> **Required Fragment**
> 
> All layouts provided by the framework rely on this fragment to store item positions. If you are using these layouts, 
> always add this fragment to your items.
{style="note"}

## Fragment Tags
This fragment does not add any traits to the item, but it relies on container tags and layout compatibility to work correctly.

## Properties
This fragment has the following property.

| Property                  | Description                                                                  |
|---------------------------|------------------------------------------------------------------------------|
| `PreferredContainerQuery` | Gameplay Tag Query used to filter/select preferred containers for this item. |

## Operations
This fragment exposes the following operations.

| Function                           | Description                                                                  |
|------------------------------------|------------------------------------------------------------------------------|
| `GetDefaultContainer`              | Returns the default container for the item based on the fragment memory.     |
| `GetContainer`                     | Returns the container where the item is currently placed.                    |
| `GetPosition`                      | Returns the position of the item in its current container.                   |
| `SetContainerAndPosition`          | Manually sets the item's container and position.                             |
| `GetOrSelectContainerForItem`      | Tries to use memory/default/preferred container, or selects one dynamically. |
| `SelectContainerForItem`           | Finds the best container for the item using the provided criteria.           |
| `SelectPositionForItem`            | Returns a valid position for the item in its current container.              |
| `SelectPositionForItemInContainer` | Returns a valid position for the item in the provided container.             |
| `TryAddItem`                       | Adds an item to a container, in the provided position.                       |
| `TryMoveItem`                      | Moves an item to a new position. Swap items if needed.                       |
| `TrySwapItems`                     | Swaps two items in the container.                                            |

## Memory
This fragment uses `InventoryItemFragmentContainerMemory` to store the current **container** and **position**.

## Event Payload
This fragment emits the following events, using `InventoryItemContainerPlacementPayload` as the payload structure.

| Event                                       | Description                                                   |
|---------------------------------------------|---------------------------------------------------------------|
| `Inventory.Event.Item.PlacementInitialized` | The fragment is active and the placement was initialized.     |
| `Inventory.Event.Item.ContainerChanged`     | The container storing the item has been changed.              |
| `Inventory.Event.Item.PositionChanged`      | The position of the item, in the container, has been changed. |

### Placement vs. Change events
`PlacementInitialized` fires **once** when the fragment creates the initial container/position for the item, whether that 
comes from a fresh selection or a valid default memory.

`ContainerChanged` and `PositionChanged` fire only when the resolved container/position **differ from the previous ones**. 
On first initialization, these may also fire if the provided default memory had to be corrected (e.g., invalid container 
or out-of-range position). 

In that case, the payload's PreviousContainer/PreviousPosition reflect the defaults and Container/Position reflect the 
final placement. If the defaults are already viable, you'll get PlacementInitialized and no change events.