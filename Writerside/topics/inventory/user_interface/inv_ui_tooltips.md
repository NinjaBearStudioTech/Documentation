# Item Tooltips
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Item Tooltips</b></p>
    <br/>
    <ul>
        <li>Tooltips can be displayed in multiple ways, such as using the integrated tooltip widget, a static panel, or integrated into the cursor.</li>
        <li>Each tooltip reuses the <b>Item ViewModel</b> from the source widget for consistent data display.</li>
        <li>The <b>Item ViewModel</b> in the tooltip must be set to <code>Manual</code> creation mode.</li>
        <li>Tooltip display is typically triggered by <b>Mouse Over</b> or <b>Focus Events</b> from the Item Widget.</li>
        <li>ViewModel transfer ensures shared access to <b>item data and fragment ViewModels</b>.</li>
    </ul>
</tldr>

The Inventory System supports flexible tooltip implementations by allowing any widget to display item information using 
the same **Item ViewModel**. This approach ensures that tooltips reflect the same live data used by item widgets, with 
no additional binding work.

## Tooltip Options

You can implement item tooltips in a few different ways, depending on your design:

- **Native Tooltips**: Using the `Set Tool Tip` widget property available in Unreal.
- **Floating Tooltip Widget**: A dynamically spawned widget that follows the cursor or appears near the hovered item.
- **Static Panel**: A fixed section of the screen (e.g., side panel or status box) that updates based on hover/focus state.
- **Mouse Cursor Override**: Embedding the tooltip inside a custom mouse cursor or UI element.

No matter the strategy, the key is transferring the **Item ViewModel** from the hovered item to the tooltip widget.

## ViewModel Binding

When creating your Tooltip Widget:

- Add an **Inventory Item ViewModel**.
- Set its **Creation Type** to `Manual`, since the instance will be passed in externally.
- Add additional **fragment ViewModels** (e.g. Stack, Quality) using `Resolver` and the `Inventory Resolver` class.

This matches the setup of a standard item widget, except that the primary data is injected from the outside.

## Showing the Tooltip

In most cases, the tooltip should be shown when the item widget **receives focus**, which commonly happens when the user 
**hovers** over or navigates between widgets using the pre-defined **navigation**.

<procedure title="Handling Focus and Mouse Events" collapsible="true" default-state="expanded">
    <step>
        <p>In your Item Widget's Event Graph, handle <b>On Mouse Enter</b> and <b>On Mouse Leave</b> to control focus.</p>
        <img src="inv_ui_tooltip_event_graph.png" alt="Tooltip Event Graph" border-effect="line"/>
    </step>
    <step>
        <p>Use <code>On Added to Focus Path</code> and <code>On Focus Lost</code> to show and hide the tooltip respectively.</p>
        <note>This enables both mouse and keyboard/gamepad navigation.</note>
    </step>
</procedure>

<procedure title="Creating the Tooltip Widget" collapsible="true" default-state="expanded">
    <step>
        <p>Use <code>Create Widget</code> to spawn your tooltip. Assign the class and owning player.</p>
    </step>
    <step>
        <p>Retrieve the <b>MVVM View</b> from the created widget using <code>Get View from User Widget</code>.</p>
    </step>
    <step>
        <p>Use <code>Set ViewModel by Class</code> to assign the <b>Item ViewModel</b> from your current item to the tooltip.</p>
        <img src="inv_ui_tooltip_create_widget.png" alt="Tooltip Widget Creation" border-effect="line"/>
    </step>
</procedure>

## Hiding the Tooltip

To remove the tooltip when focus is lost:

<procedure title="Removing the Tooltip Widget" collapsible="true" default-state="expanded">
    <step>
        <p>Check if the Tooltip Widget is valid. If so, call <code>Remove from Parent</code>.</p>
    </step>
    <step>
        <p>Clear the reference to avoid holding stale widget pointers.</p>
        <img src="inv_ui_tooltip_remove_widget.png" alt="Tooltip Widget Removal" border-effect="line"/>
    </step>
</procedure>

## Summary

Tooltips are an extension of the same data flow used by item widgets. By reusing the **Item ViewModel**, you guarantee 
that tooltip content remains in sync with the live state of the item.

The MVVM setup makes it easy to:

- Maintain a single data source across UI elements.
- Build reusable tooltip widgets that automatically respond to bound values.
- Support all input types using the same focus and hover event logic.

You can combine this approach with UMG or CommonUI, and the tooltip will behave consistently as long as the ViewModel 
flow is respected.
