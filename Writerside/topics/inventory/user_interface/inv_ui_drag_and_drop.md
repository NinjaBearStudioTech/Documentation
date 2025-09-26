# Drag and Drop
<primary-label ref="inventory"/>

Inventory Items can automatically handle **drag-and-drop** when using the provided Item Widget (both UMG and Common UI variants).

Whenever a drag begins, the widget spawns a new **Drag & Drop operation object**. This object detects the type of 
operation (container drop, world drop, or other) and ensures it's processed correctly when the drop happens.

The class behind this is `UNinjaInventoryDragDropOperation`, which can be extended if you want to introduce new behaviors. 
It provides the following methods for this, and by overriding them, you can customize what happens when items interact. 

| Method                        | Purpose                                                       |
|-------------------------------|---------------------------------------------------------------|
| `EvaluateOperation`           | Evaluates a drag/drop operation between two generic contexts. |
| `EvaluateTargetItemOperation` | Evaluates an operation specifically between two items.        |
| `PerformOperation`            | Executes the chosen operation once validated.                 |

Once an operation is evaluated, the possible outcomes are determined, from the following scenarios:

| Operation Outcome       | Condition / Description                                                                                                                                         |
|-------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Invalid**             | Missing required data (invalid item/container), operation not permitted, item cannot be placed/swapped, or fails other conditions.                              |
| **NoChange**            | Source container and target container are the same, and the source position equals the target position. Basically a "sanity check".                             |
| **DropToWorld**         | Source item is not *Bound* and the target widget is a recognized “Drop Zone Widget.”                                                                            |
| **MergeStacks**         | Source and target items are of the same type, have a valid `UItemFragment_StackAndQuantity`, and `CanMergeStacks()` returns true.                               |
| **CombineItems**        | Source item's `CanCombineItem(TargetItem)` returns true.                                                                                                        |
| **SwapItems**           | Both items are valid, not mergeable/combining, so default fallback when dragging onto another item.                                                             |
| **MoveWithinContainer** | Source and target are the same container, target item is invalid, and `TargetContainer->CanAcceptItemAtPosition(SourceItem, TargetPosition)` is true.           |
| **MoveToContainer**     | Source and target containers belong to the same inventory, target accepts item at position, and no item-specific interaction applies.                           |
| **TransferToInventory** | Source and target containers belong to different inventories, item not bound *or* the source inventory authorizes the target inventory, and placement is valid. |

## World Drops

Dropping items in the world to generate **pickups** is automatically supported. The custom operation class will detect
a target widget that implements the expected interface, `InventoryDropZoneWidgetInterface`, so it's recognized as a 
viable **drop zone**.

The position provided by the interface is then send to the [**Drop Fragment**](inv_fragment_drop.md), along with the
selected world location, to generate the pickup representation.

Ninja Inventory provides a base widget implementing this interface, `UNinjaInventoryDropZoneWidget`.
