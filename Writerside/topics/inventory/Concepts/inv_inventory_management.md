# Inventory Operations and Events
<primary-label ref="inventory"/>

Use the Inventory Manager when a player receives, finds, or loses an item. Give it an item definition and any starting fragment memory. The manager checks what it can accept, fills eligible stacks, and looks for room in compatible containers. For a move, the destination must accept the existing item at the requested position.

## Respond to the Result

| When your game needs to act | Hook to use | Example |
| --- | --- | --- |
| The starting bag is ready | `OnInventoryInitializationSucceeded` or `OnInventoryInitializationFailed` | Enable the menu when the inventory is ready. Check asset registration if initialization fails. |
| An item is being granted | `AddItemWithCallback` or `AddItemWithAcceptanceCallback` | In Blueprint, use the lifecycle callback to follow a grant. In C++, use the acceptance callback to approve or reject the item before it enters the inventory. The ID returned by `AddItem` tracks the request. |
| A stack, position, or equipment state changes | `OnItemEvent` | Filter by the event tag and read the affected item. For `Inventory.Event.Item.StackChanged`, update a pickup counter. |
| The owner gains or loses a container | `OnContainerEvent` | Add or remove the bag's tab when gear grants a new container. |

The item and container delegates are available in Blueprint. C++ listeners can bind to `Native_OnItemEvent` and `Native_OnContainerEvent`. Both receive the affected object, the event tag, and its payload. An inventory widget can use the [built-in ViewModels](inv_ui_mvvm.md) to handle these updates.

## When an Item Has Nowhere to Go

A pickup can grant part of a stack. Use the [pickup result](inv_guide_inventory_items.md) to decide how much stays in the world. A different problem occurs when an item the player already owns loses its home, for example when gear that grants a pouch is removed. The manager runs its **Stranded Item Handlers** in order. The supplied handlers try another container or try dropping the item. If no handler succeeds, the item can be removed.

For a quest item that must be preserved, add a handler before the fallback. Override `HandleStrandedItem`, move the item into a suitable recovery container, and report success once it has a home. Test the rule with every ordinary bag full.
