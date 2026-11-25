# Build a Spatial Grid Inventory
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

Build a three-column, two-row backpack. A small supply occupies one cell. A tool occupies two neighboring cells and can turn to fit vertically. Start with a working player Inventory Manager from [First Steps](inv_first_steps.md). You can use this layout as the player's first bag.

<procedure title="Define the backpack and its contents">
    <step><p>Create a Container Definition called <b>Container_FieldPack</b>. Add <code>Inventory.Container.Trait.Default</code> and choose <b>Spatial Layout</b>. Use <b>Property</b> for the slot count, set <b>Grid Width</b> to three and <b>Grid Height</b> to two, and use <b>Per Cell</b> placement. Set <b>Swap Policy</b> to <b>Blocked</b> for this test. Leave its item compatibility query empty.</p></step>
    <step><p>Assign the field pack as the only <b>Initial Containers</b> entry on the player's Inventory Manager. Clear the starting items for this test. Use a fresh inventory so the old bag does not receive pickups.</p></step>
    <step><p>Create two Item Definitions, <b>Item_Supply</b> and <b>Item_Tool</b>. Give both a <b>Container Placement Fragment</b>, a <b>User Interface Fragment</b> with distinct icons, and a <b>Dimensions Fragment</b>. Set the supply to one cell wide by one high and the tool to two wide by one high. Enable <b>Can Rotate</b> on the tool. Leave stacking off or set the stack limit to one.</p></step>
    <step><p>Set up individual <a href="inv_guide_inventory_items.md">pickups</a> for four supplies and one tool. For an irregular item, enable the Dimensions Fragment's <b>Occupancy Mask</b> and mark the cells the item actually covers. Leave the mask off for the rectangular tool.</p></step>
</procedure>

<procedure title="Draw cells and items in the same space">
    <step><p>Create a Widget Blueprint based on <code>NinjaInventorySpatialContainerWidget</code>. Assign <b>Container_FieldPack</b> as its <b>Container Data Asset</b>, enable <b>Fill Empty Entries</b>, and add an <b>Inventory Container ViewModel</b> using <b>Inventory Resolver</b>.</p></step>
    <step><p>In the Designer, add an Overlay named <code>GridOverlay</code>. Inside it, place a Uniform Grid Panel named <code>ReferenceGrid</code> first and a Grid Panel named <code>ItemGrid</code> above it. Give both panels the same bounds and let pointer hits pass through empty space in the top panel to its underlying cells (set the top panel to <b>Not Hit-Testable (Self Only)</b>). The bottom panel supplies one target per cell. The top panel draws each item once at its starting cell and spans its width and height.</p></step>
    <step><p>For <b>Reference Widget Class</b>, use a slot widget with a visible cell border and a consistent cell size. For <b>Item Widget Class</b>, use an item widget with the item's icon. Add a manual Inventory Item ViewModel to both. Bind the container and position on the cell widget and the item view on the icon widget as shown in <a href="inv_ui_mvvm.md#bindings-with-the-item-widget">Bindings with the Item Widget</a>. In the icon widget, use <b>On Item View Set</b> to get the source item and read <b>Get Dimensions</b> from its Dimensions Fragment. Multiply width and height by the cell size and apply them to the icon's Size Box. With 48-unit square cells, the tool should measure 96 by 48 or 48 by 96.</p></step>
    <step><p>Bind the container ViewModel's <b>Get Items</b> to the spatial widget's <b>Set Grid Entries</b>. Add the widget to the player's menu. Enable <a href="inv_ui_drag_and_drop.md">drag-and-drop</a> on the cells and items so you can rearrange the contents.</p></step>
</procedure>

For a **Rotate** action on a stored item, get its Dimensions Fragment and call `CanRotateItemInPlace`. If it fits, call `SetRotated` with the opposite of `IsRotated`. For a request through another authorized inventory, use `SetRotatedFromAuthorizedInventory` with the requesting manager.

To redraw immediately after a turn, bind the bag screen to the manager's `OnItemEvent`. When the tag is `Inventory.Event.Item.RotationChanged` and the item belongs to this bag, refresh its entries on the next tick. In Blueprint, keep the container reference, call **Set Container** on the container ViewModel with an empty reference, then set it back to the saved container. The **Get Items** binding rebuilds both layers so the old cells become available as drop targets. Unbind the screen when it closes.

A C++ layout subclass can override `TestWithCustomAlgorithm` and select the layout's **Custom** placement algorithm if your game uses different fit rules.

For an example with gaps, this L-shaped item can turn once the smaller item moves out of its way.

<img src="inv_layout_spatial.png" alt="A small item blocks an L-shaped item from turning" width="500"/>

<img src="inv_layout_spatial_rotated.png" alt="The L-shaped item rotated after the blocking cell was cleared" width="500"/>

## Try It in Play

1. Collect the four supplies. Arrange three across the bottom row and one in the top middle cell. Pick up the horizontal tool. Both top corners are free, but the tool needs two adjacent cells. It should stay in the world.
2. Move the top supply to the top-left corner. Pick up the tool again. It should occupy the top-middle and top-right cells, with one icon across both.
3. Try rotating it. The supply directly below its starting cell blocks the turn. Free that bottom-middle cell and rotate again. The tool should now cover the middle column and leave the top-right cell free.
