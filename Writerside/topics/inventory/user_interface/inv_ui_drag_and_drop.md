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

## World Drops

Dropping items in the world to generate **pickups** is automatically supported. The custom operation class will detect
a target widget that implements the expected interface, `InventoryDropZoneWidgetInterface`, so it's recognized as a 
viable **drop zone**.

The position provided by the interface is then send to the [**Drop Fragment**](inv_fragment_drop.md), along with the
selected world location, to generate the pickup representation.

Ninja Inventory provides a base widget implementing this interface, `UNinjaInventoryDropZoneWidget`.
