# Stack and Quantity
<primary-label ref="inventory"/>

The **Stack and Quantity** fragment determines how many items can be grouped into a **stack** and the **total number** of 
items of the same type allowed in an inventory. 

It handles **initialization**, **merging behavior**, **stack size** updates, and emits **events** when changes occur.

This fragment is essential for inventory systems where stackable items (such as potions, arrows, or crafting materials) 
must be handled efficiently. It supports automatic stack merging and split logic during activation.

## Fragment Tags
This fragment adds the `Inventory.Item.Trait.Stackable` tag to an item, which introduces the **Stackable** trait.

## Properties
This fragment has the following properties.

| Property          | Description                                                                  |
|-------------------|------------------------------------------------------------------------------|
| `MaximumQuantity` | The maximum number of items of this type allowed in the inventory.           |
| `StackLimit`      | The maximum number of items allowed in a single stack (1 means no stacking). |
| `AllowStackMerge` | Whether the item can merge into existing stacks of the same type.            |

## Operations
This fragment exposes the following operations.

| Function                     | Description                                                         |
|------------------------------|---------------------------------------------------------------------|
| `GetMaximumQuantity`         | Returns the maximum allowed quantity of the item in the inventory.  |
| `GetStackLimit`              | Returns the maximum number of items allowed in one stack.           |
| `GetStackSize`               | Returns the current stack size of a specific item.                  |
| `SetStackSize`               | Sets the stack size of a specific item (authority-only).            |
| `CountItemQuantity`          | Returns the total quantity of a specific item across the inventory. |
| `TryMergeIntoExistingStacks` | Attempts to merge the item's stack into existing incomplete stacks. |

## Memory
This fragment uses `InventoryItemFragmentStackMemory ` to store the current **stack size**.

## Event Payload
This fragment emits the following event, using `InventoryItemStackAndQuantityPayload` as the payload structure.

| Event                               | Description                                 |
|-------------------------------------|---------------------------------------------|
| `Inventory.Event.Item.StackChanged` | Emitted when the item's stack size changes. |