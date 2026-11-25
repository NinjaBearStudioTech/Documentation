# Inventory Widgets and ViewModels
<primary-label ref="inventory"/>

A bag screen needs to know which slots exist, which item occupies each one, and what to show for that item. Ninja Inventory provides a ViewModel for each of those jobs. Connect them in the Widget Blueprint's **View Bindings** panel so quantities and positions update as the inventory changes.

| Part of the screen | ViewModel | Example |
| --- | --- | --- |
| Bag or equipment panel | Inventory Container | Sends the panel a list of entries, optionally including empty positions. |
| Slot or loot entry | Inventory Item | Supplies an item view to the entry. A live item has a source instance. A preview or loot offer can still supply display data. |
| Icon, label, or quantity | Fragment ViewModels | Use **User Interface** for the icon and name, and **Stack** for quantity. |
| Character capacity or received loot | Attribute or Loot ViewModels | Display the owner's carried weight, or populate a panel when loot arrives. |

## Bindings with the Item Widget

1. Create an entry based on `NinjaInventoryItemWidget` or its Common UI counterpart. Add an **Inventory Item ViewModel** with **Manual** creation. The parent panel supplies this instance when it creates the entry.
2. In View Bindings, connect the Item ViewModel's `GetItemView` to the widget's `SetItemView`. Bind `GetContainer` to `SetOwningContainer` and `GetPositionInContainer` to `SetPositionInContainer` when the entry is assigned. These last two bindings give an empty slot an address for drops.
3. Add the User Interface and Stack fragment ViewModels using **Resolver** and **Inventory Resolver**. The base widget passes its item view to them. Bind **Get Icon Brush** to the image brush and **Get Stack Size** to the quantity text. Hide those visuals for an empty entry and keep the slot target visible.

If you already have a live item in Blueprint, the base widget also accepts `SetItemInstance`. For a tooltip or loot preview, pass the existing item view so the widget can also display entries that have no live instance.

For the tool in a spatial backpack, use the widget's `OnItemViewSet` hook to size the icon from the live tool's Dimensions Fragment. The [spatial guide](inv_guide_spatial_grid.md) includes the binding and rotation refresh. For a worn tool, the **Durability** ViewModel can drive a condition bar from the same item view.

## Connect the Container

Use `NinjaInventoryContainerWidget` with an **Inventory Container ViewModel**, the **Inventory Resolver**, and the bag's **Container Data Asset**. For a custom container screen, set the container ViewModel's `SetContainer` to the runtime container you want to display. This matters for a chest panel, where the bag belongs to an actor other than the player.

A [standard bag](inv_guide_simple_grid.md) sends **Get Items** to a panel extension's **Set Items**. A [spatial bag](inv_guide_spatial_grid.md) sends the same list to **Set Grid Entries**, which builds the cells and places each item across its footprint. [Tooltips and drag-and-drop](inv_ui_drag_and_drop.md) use the same entry data.
