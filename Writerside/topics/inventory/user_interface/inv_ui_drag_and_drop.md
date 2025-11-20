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

## Dragging Item Widgets

Drag and Drop behavior is usually implemented in your **Item Widget**.

<procedure title="Creating a Drag and Drop Widget" collapsible="true" default-state="expanded">
    <step>
        <p>
        Create a widget based on <code>UNinjaInventoryItemCommonWidget</code> or <code>NinjaInventoryItemWidget</code>, 
        depending on whether you are using Common UI in your project or not.
        </p>
    </step>
    <step>
        <p>
        Design your widget as desired, adding any relevant components to represent your Inventory Item, including all
        relevant <a href="inv_ui_mvvm.md">Inventory ViewModels</a> needed to support the widget.
        </p>
    </step>
    <step>
        <p>
        In the widget's <b>root settings</b>, navigate to the <b>Inventory</b> category and under <b>settings</b>, set
        the <b>Drag Widget Class</b> which will represent the item while being dragged.
        </p>
        <note>
        To get started, you can simply use the same Item Widget. If your widget is based on the base Item Widget classes
        provided by the framework, all ViewModels will be automatically configured.
        </note>
    </step>
</procedure>

## World Drops

Dropping items in the world to generate **pickups** is automatically supported. The custom operation class will detect
a target widget that implements the expected interface, `InventoryDropZoneWidgetInterface`, so it's recognized as a 
viable **drop zone**.

The position provided by the interface is then send to the [**Drop Fragment**](inv_fragment_drop.md), along with the selected world 
location, to generate the pickup representation.

Ninja Inventory provides a base widget implementing this interface, `UNinjaInventoryDropZoneWidget`.
