# Build Tooltips and Drag-and-Drop
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

Let the player inspect an item and drag it to a new position using the same entry that displays its icon. Start with the item widget from the [slot-based](inv_guide_simple_grid.md) or [spatial](inv_guide_spatial_grid.md) setup guide.

<procedure title="Show the selected item's details">
    <step><p>Create a tooltip based on the inventory item widget. Add a manual <b>Inventory Item ViewModel</b> and the fragment ViewModels for the values you want, such as the display name and stack size. Apply the same <a href="inv_ui_mvvm.md#bindings-with-the-item-widget">item-view bindings</a> as the entry widget.</p></step>
    <step><p>When an occupied entry receives pointer or keyboard focus, create the tooltip for the owning player. Use <b>Get View from User Widget</b> on the tooltip and <b>Set ViewModel by Class</b> to pass it the entry's existing Inventory Item ViewModel. Show it as a tooltip or in a details panel.</p></step>
    <step><p>On mouse leave or focus loss, hide the tooltip. If you created a floating widget, remove it from its parent and clear the reference. When navigating with a controller, use <b>On Added to Focus Path</b> to show details for the newly focused entry.</p></step>
</procedure>

<img src="inv_ui_tooltip_create_widget.png" alt="Assigning the selected entry's ViewModel to a tooltip" width="650" border-effect="line"/>

<procedure title="Move an item between slots">
    <step><p>In the base item widget's Inventory settings, set <b>Drag Widget Class</b> to the widget that should follow the pointer. Your existing item widget works as a first visual. Leave <b>Drag Drop Operation Class</b> set to <code>NinjaInventoryDragDropOperation</code>.</p></step>
    <step><p>Give every destination slot its owning container and position, including empty slots. In a spatial backpack, use the reference cells for these targets. The operation can then check the destination, move the item, merge compatible stacks, or apply the layout's swap rules.</p></step>
    <step><p>For a world drop area, use <code>NinjaInventoryDropZoneWidget</code> or implement <b>Inventory Drop Zone Widget Interface</b> on your own widget and return the intended world position from <code>GetDropLocationInWorldSpace</code>. Configure the item's <a href="inv_gameplay_abilities.md">Drop Fragment and pickup class</a> so an accepted drop creates the right pickup.</p></step>
</procedure>

To add a custom combination, subclass `NinjaInventoryDragDropOperation` and select it in the item's **Drag Drop Operation Class**. Override `EvaluateTargetItemOperation` to recognize the pair. Use `EvaluateOperation` for a rule involving the destination widget, and `PerformOperation` for the accepted action. Delegate ordinary moves to the parent implementation so the same widget still handles regular slots.

## Try It in Play

Hover over a bandage stack, then select it with a controller. Both should show the same quantity. Drag the stack to a free slot and then onto another partial bandage stack. Try dropping it on a lantern-only equipment slot. The bag should keep the bandages and their count when the destination rejects them.
