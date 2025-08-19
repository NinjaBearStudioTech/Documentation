# Nested Container Fragment
<primary-label ref="inventory"/>

The **Nested Container** fragment grants an item its own internal inventory container when it is added to an inventory.  
This enables support for **nested inventories**, a common feature in survival and crafting games — such as bags, pots, 
boxes, or crates that can store other items.

The container is automatically created when the item is added to an inventory, and removed when the item is removed.  
Internally, it uses a memory struct to track the container's lifecycle and ensure ownership is correctly linked to the item.

## Fragment Tags
This fragment adds the `Inventory.Item.Trait.Storage` tag to an item, which introduces the **Storage** trait.

## Properties
This fragment has the following properties.

| Property        | Description                                                                  |
|-----------------|------------------------------------------------------------------------------|
| `ContainerData` | The container data asset to use when creating the nested container instance. |

## Operations
This fragment exposes the following operations.

| Function             | Description                                                                  |
|----------------------|------------------------------------------------------------------------------|
| `GetNestedContainer` | Returns the nested container owned by the item, or `nullptr` if unavailable. |

## Behavior
When an item with **Nested Container** is activated/equipped:

- The fragment creates one nested container for that item (server/authority only) if one does not already exist (e.g., after load). Its ID is stored in the fragment’s memory.
- The Inventory Manager broadcasts Container Added for the nested container. 

While the **nested container exists**:
- The owning item cannot be placed inside its own nested container. Attempts to move/equip the owner into it are rejected by the layout/acceptance rules.
- Other items may be placed into the nested container normally (subject to its layout/capacity rules).
- The nested container cannot be explicitly removed via the Inventory Manager. Removal is only allowed as part of removing/unequipping the owning item.

When the **owning item is removed/deactivated**:
- The fragment looks up the nested container by the stored ID and removes it.
- The Inventory Manager repositions (e.g., moves to Backpack/default containers) any contents from the nested container according to your default placement rules.
- The fragment's nested-container memory is cleared.
- The Inventory Manager broadcasts Container Removed for the nested container.

## Memory
This fragment uses `InventoryItemFragmentNestedContainerMemory` to store the current **nested container key**.

## Event Payload
The fragment does not broadcast custom events. However, you can listen for the following container-related events to 
respond to changes:

- `Inventory.Event.Container.AddedToInventory`
- `Inventory.Event.Container.RemovedFromInventory`

These are broadcast from the **Inventory Manager** when the nested container is added or removed, and can be used to 
trigger UI updates or gameplay reactions.
