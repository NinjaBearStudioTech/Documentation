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
When an item with Linked Container is placed in the primary equipment container:

- The fragment creates a **mirror** (not a duplicate) of the item in the linked container Since equipment uses single-slot semantics the position is always defined as `single`.
- If the linked slot is already occupied, the occupant is evicted to a default container (e.g., Backpack) when possible. If no default container can accept it, the mirror is not created and the original placement in the primary remains; a verbose log is emitted (no extra events).
- If the item is placed directly into the linked container first, the fragment redirects it to the primary container (evicting the primary's occupant to a default container if needed), then establishes the mirror in the linked container.
- When the item leaves the primary (unequipped/moved/removed), the linked mirror is cleared.
- When the linked container is removed, the fragment clears the mirror and the system unequips the item (it is moved to a default container), keeping state consistent.

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