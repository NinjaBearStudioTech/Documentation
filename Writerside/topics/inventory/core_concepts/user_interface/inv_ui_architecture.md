# UI Architecture
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: User Interface Architecture</b></p>
    <br/>
    <ul>
        <li>The UI system uses a layered MVVM approach: <b>Backend → View Models → Widgets</b>.</li>
        <li><b>Item View Models</b> expose data from item instances or views and notify <b>fragment View Models</b>.</li>
        <li><b>Container View Models</b> feed item data into dynamic widgets (e.g., grids, loot panels) via <b>ViewModel Extensions</b>.</li>        
        <li>Base widgets like <code>NinjaInventoryItemWidget</code> automate ViewModel propagation and reduce manual bindings.</li>
    </ul>
</tldr>

The Inventory UI system uses a layered and flexible binding strategy powered by View Models. It separates responsibilities 
between **backend data**, **logic**, and **presentation**. The system is organized into three main layers:

- **Backend**: Entities and events introduced by the Inventory Domain - containers, item instances, default item data, and fragment definitions.
- **View Models**: Act as intermediaries that normalize data and react to relevant backend events, so the data can be updated as needed.
- **Widgets**: The actual UI elements bound to View Models, which automatically update when data changes.

The diagram below shows how item data flows from the backend to the UI, how View Models are instantiated, and how updates 
propagate throughout the system.

<img src="inv_ui_mvvm_layers.png" alt="Inventory User Interface Architecture"/>

> **Inventory Scope**
>
> While the Inventory system provides the **full data flow from backend to View Models**, it intentionally avoids prescribing 
> how your widgets should be structured.
> 
> Widget layouts, styling, and interaction logic are left to the project level. To support this flexibility, the system 
> includes **optional base widget classes and utility helpers**, but the actual UI design is entirely up to you.

## Inventory Widget Overview

When designing your Inventory User Interface, we recommend a bottom-up approach: start with the smallest building blocks 
and work your way up to the full Inventory Window.

1. **Item Tooltip**: Displays detailed information about an item. Extends from `UNinjaInventoryItemCommonWidget` or `UNinjaInventoryItemWidget`.
2. **Item Drag**: Represents an item while it is being dragged (if drag-and-drop is supported). In many setups, you can skip this widget entirely and reuse the **Item widget** during dragging.
3. **Item**: Represents an item within a container. Receives configuration about which Tooltip and Drag widgets to use. Also extends from `UNinjaInventoryItemCommonWidget` or `UNinjaInventoryItemWidget`.
4. **Containers**: Represents each container (backpack, equipment slots, etc.). Uses a ViewModel extension that links each container to the Item ViewModel used in the Item widget. Extends from `UNinjaInventoryContainerCommonWidget` or `UNinjaInventoryContainerWidget`.
5. **Inventory Window**: The main window that aggregates all containers. You are free to use any base class for this, as Ninja Inventory does not provide one.

In the next pages, you will ll find more details about:
- All provided [**Base Widgets**](inv_ui_widgets.md).
- How to se the provided [**UMG ViewModels**](inv_ui_mvvm.md).
- Working with [**tooltips**](inv_ui_tooltips.md).
- Details and customizations for [**Drag and Drop**](inv_ui_drag_and_drop.md).