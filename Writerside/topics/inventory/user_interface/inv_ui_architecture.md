# User Interface Architecture
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

## Backend

The backend provides several inventory-related data types that are consumed by the ViewModel layer:

- **Container**: Represents a section of the inventory capable of holding items.
- **Item Instance**: A live, managed item currently stored within a container.
- **Item View**: A detached representation of an item, commonly used for previews, loot drops, vendor displays, etc.
- **Fragments**: Modular data blocks that define specific aspects of an item, such as stack size, quality, or durability.

These types are **not used directly by UI widgets**. Instead, they serve to **transfer structured data** into the ViewModel 
layer, where UI-safe representations are created and maintained.

## View Models

The ViewModel layer acts as a **bridge** between backend data and UI widgets. In the context of the Inventory System,
the responsibility of all ViewModels is to translate backend Containers and Items into UI data-types.

### Item View Model

The **Inventory Item View Model** exposes **Item Instances** and **Item Views** to the user interface. 

- It accepts either an **Item Instance** or an **Item View**.
- Normalizes access to **shared information** between both data types.
- Can be directly connected to all **Fragment View Models**, such as Stack and Quality.
- Uses the **Inventory View Model Resolver** for its **Creation Type**.

<procedure title="Preparing the Item Widget" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new Item Widget, extending from <code>UserWidget</code>.</p>
        <note>Ninja Inventory provides a base <b>Item Widget</b>, but right now, we want to create everything from scratch, so the concept can be fully explained.</note>
    </step>
    <step>
        <p>Add the <b>Inventory Item View Model</b> to the widget. Set its <b>Creation Type</b> to <code>Resolver</code>, and choose <code>Inventory View Model Resolver</code> as the resolver class.</p>
        <img src="inv_ui_mvvm_creation_details.png" alt="Item View Model Creation" border-effect="line"/>
    </step>
    <step>
        <p>
            Add other item-related fragment View Models you might need, such as <b>Stack</b>, <b>Quality</b>, or <b>User Interface</b>. 
            Set each of them to use <b>Creation Type</b> <code>Resolver</code>, and assign the <code>Inventory View Model Resolver</code> to ensure they are correctly initialized.
        </p>
    </step>
    <step><b>Compile and save</b> your widget, so all View Model entries will be available in the <b>View Bindings</b> panel.</step>
    <step>
        <p>In the <b>View Bindings</b> panel, configure the bindings, setting the <b>Item Instance</b> and <b>Item View</b> from the <b>Item View Model</b> to each <b>Fragment View Model</b>.</p>
        <img src="inv_ui_mvvm_data_pipeline.png" alt="Data Pipeline" width="800" border-effect="line"/>
        <note>The base <b>Item Widget</b> provided by the framework can do that automatically for you. Later we will look into replacing this step.</note>
    </step>
    <step>
        <p>Now bind the values from each <b>Fragment View Model</b> to the appropriate UI elements. This includes setting widget <b>properties</b> or calling <b>functions</b> that use those values at runtime.</p>
        <img src="inv_ui_mvvm_item_bindings.png" alt="Item Bindings" width="800" border-effect="line"/>
        <note>Binding View Model values to Widget <b>Functions</b> enables advanced UI behavior. For example, modifying visuals based on quality, or formatting tooltips dynamically.</note>
    </step>
</procedure>

As shown in the steps above, binding the Item View Model directly to every Fragment View Model can become repetitive and 
error-prone, especially as your UI grows.

To simplify this, the Inventory System provides a built-in **Base Item Widget** (`NinjaInventoryItemWidget`) that automatically 
propagates item data to all child View Models.

<procedure title="Using the Base Item Widget" collapsible="true" default-state="expanded">
    <step>Reparent your Item Widget to <code>NinjaInventoryItemWidget</code>.</step>
    <step>
         <p>Update your ViewModel bindings so that the <b>Item View Model</b> updates the functions <code>SetItemInstance</code> and <code>SetItemView</code>, which are provided by the base class.</p>
        <img src="inv_ui_mvvm_data_pipeline_base_widget.png" alt="Data Pipeline with Base Widget" width="800" border-effect="line"/>
    </step>
</procedure>

### Container View Model



## Widgets

The first part of the hierarchy is the **Item Widget**.

- Root widget that owns the Item View Model (data entry-point).
- Child view models (e.g., stack, rarity) bind to the entry-point.
- It's self-contained, when given an Item View Model, all Fragment View Models are automatically updated.

Then the next part is the **Container Widget** (like grids, panels, loot lists).

- Hosts multiple Item Widgets.
- Uses a **Container View Model**, which outputs multiple **Item View Models**.
- If using a **ViewModel Extension**, bindings from the container to entries are automatic.
