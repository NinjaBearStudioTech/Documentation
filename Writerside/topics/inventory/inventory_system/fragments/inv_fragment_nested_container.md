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

## Memory
This fragment uses `InventoryItemFragmentNestedContainerMemory` to store the current **nested container key**.

## Event Payload
The fragment does not broadcast custom events. However, you can listen for the following container-related events to 
respond to changes:

- `Inventory.Event.Container.AddedToInventory`
- `Inventory.Event.Container.RemovedFromInventory`

These are broadcast from the **Inventory Manager** when the nested container is added or removed, and can be used to 
trigger UI updates or gameplay reactions.
