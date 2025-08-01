# Linked Container Fragment
<primary-label ref="inventory"/>
<secondary-label ref="experimental"/>

The **Linked Container** fragment allows an item to **occupy multiple containers** simultaneously, typically to represent
equipment that spans multiple slots, such as **two-handed weapons** that require both a main-hand and off-hand slot.

It enables precise control over how such items are added, mirrored, and evicted from linked containers.

This fragment works in conjunction with a **primary container** (the one explicitly used by the player or system) and a
linked container, which is automatically updated based on the primary's state. For example, equipping a greatsword
into the main-hand slot will also reserve space in the off-hand slot.

## Fragment Tags

This fragment does not add additional gameplay tags by default, but your containers or layouts may define tags that
are used to resolve the **Primary Container Query** and **Linked Container Query**.

## Properties
This fragment has the following properties.

| Property                | Description                                                                                          |
|-------------------------|------------------------------------------------------------------------------------------------------|
| `PrimaryContainerQuery` | The container query used to identify the **main container** this item should occupy.                 |
| `LinkedContainerQuery`  | The container query used to identify the **secondary container** that will be automatically updated. |

## Operations
This fragment exposes the following operations.

| Function                  | Description                                                                                   |
|---------------------------|-----------------------------------------------------------------------------------------------|
| `GetLinkedContainer`      | Returns the linked container currently associated with the item, or `nullptr` if unavailable. |
| `MatchesPrimaryContainer` | Returns true if the given container matches the `PrimaryContainerQuery`.                      |
| `MatchesLinkedContainer`  | Returns true if the given container matches the `LinkedContainerQuery`.                       |

## Behavior

When an item with this fragment is placed into the primary container:

- The fragment will automatically place a **mirror of the item** into the **linked container**.
- If the linked container’s mirror position is **already occupied**, the current item in that slot will be **evicted to a default container**, if available.
- If no valid position can be found, the placement may fail silently.

When the item is **removed from the primary container**, the mirror in the linked container is also removed.

> **Reverse Placement**
> 
> Currently, placing the item directly into the linked container is not supported and will not trigger reverse placement.

## Memory
This fragment uses `FInventoryItemFragmentContainerMemory` to store the item’s **linked container reference** and position.
It does not interfere with the container memory from the primary ContainerPlacement fragment.

## Event Payload
The fragment does not broadcast custom events.

## Equipment System Integration

The Linked Container Fragment is designed to work seamlessly with the **Equipment Container** and **Equipment Layout**.
This allows for elegant support of items that require multiple equipment slots (e.g., two-handed weapons).

### Equipment Container
The `UNinjaInventoryEquipmentContainer` class is aware of this fragment and uses it to:

- Determine whether it is the primary or linked container for a given item.
- Forward item acceptance checks to the correct container based on the fragment's configuration.
- Expose helper functions to retrieve the current primary or linked container from the item.

When an item with this fragment is equipped, the container uses the fragment to manage both the primary and secondary occupancy.

### Equipment Layout
The `UNinjaInventoryContainerEquipmentLayout` does not directly manipulate the linked container,
but it should call TryPrepareToAddItem and check with the item's fragments (such as this one) to:

- Validate whether the item can be equipped.
- Evict or swap existing items in the equipment slot if needed.
- Ensure that the linked container will also accept the item or make room for it.

The layout system ensures that equipment containers behave consistently, while the fragment enforces the dual-slot logic.