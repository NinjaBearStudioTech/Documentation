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
