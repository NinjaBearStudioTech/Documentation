# UMG ViewModels
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: UMG ViewModels</b></p>
    <br/>
    <ul>
        <li>The UI system follows a layered MVVM structure: <b>Backend → ViewModels → Widgets</b>.</li>
        <li><b>Item ViewModels</b> (set to <code>Manual</code>) expose item data and distribute it to <b>fragment ViewModels</b> (set to <code>Resolver</code>).</li>
        <li><b>Container ViewModels</b> (set to <code>Resolver</code>) manage container data and broadcast item lists via <b>ViewModel Extensions</b>.</li>        
        <li>Base widgets like <code>NinjaInventoryItemWidget</code> and <code>NinjaInventoryContainerWidget</code> automate data propagation and reduce manual setup.</li>
    </ul>
</tldr>

The ViewModel layer acts as a **bridge** between backend data and UI widgets. In the context of the Inventory System,
the responsibility of all ViewModels is to translate backend Containers and Items into UI data-types.

## Backend Data

The backend provides several inventory-related data types that are consumed by the ViewModel layer:

- **Container**: Represents a section of the inventory capable of holding items.
- **Item Instance**: A live, managed item currently stored within a container.
- **Item View**: A detached representation of an item, commonly used for previews, loot drops, vendor displays, etc.
- **Fragments**: Modular data blocks that define specific aspects of an item, such as stack size, quality, or durability.

These types are **not used directly by UI widgets**. Instead, they serve to **transfer structured data** into the ViewModel
layer, where UI-safe representations are created and maintained.

## Item ViewModel

The **Inventory Item ViewModel** exposes **Item Instances** and **Item Views** to the user interface.

- It accepts either an **Item Instance** or an **Item View**.
- Normalizes access to **shared information** between both data types.
- Can be directly connected to all **Fragment ViewModels**, such as Stack and Quality.
- Uses the **Inventory Resolver** for its **Creation Type**.

<procedure title="Preparing the Item Widget" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new Item Widget, extending from <code>UserWidget</code>.</p>
        <note>Ninja Inventory provides a base <b>Item Widget</b>, but right now, we want to create everything from scratch, so the concept can be fully explained.</note>
    </step>
    <step>
        <p>Add the <b>Inventory Item ViewModel</b> to the widget. Set its <b>Creation Type</b> to <code>Manual</code>, since it will be provided later on by a ViewModel extension.</p>
        <img src="inv_ui_mvvm_item_creation_details.png" alt="Item ViewModel Creation" border-effect="line"/>
    </step>
    <step>
        <p>
            Add other item-related fragment ViewModels you might need, such as <b>Stack</b>, <b>Quality</b>, or <b>User Interface</b>. 
            Set each of them to use <b>Creation Type</b> <code>Resolver</code>, and assign the <code>Inventory Resolver</code> to ensure they are correctly initialized.
        </p>
    </step>
    <step><b>Compile and save</b> your widget, so all ViewModel entries will be available in the <b>View Bindings</b> panel.</step>
    <step>
        <p>In the <b>View Bindings</b> panel, configure the bindings, setting the <b>Item Instance</b> and <b>Item View</b> from the <b>Item ViewModel</b> to each <b>Fragment ViewModel</b>.</p>
        <img src="inv_ui_mvvm_item_data_pipeline.png" alt="Data Pipeline" width="800" border-effect="line"/>
        <note>The base <b>Item Widget</b> provided by the framework can do that automatically for you. Later we will look into replacing this step.</note>
    </step>
    <step>
        <p>Now bind the values from each <b>Fragment ViewModel</b> to the appropriate UI elements. This includes setting widget <b>properties</b> or calling <b>functions</b> that use those values at runtime.</p>
        <img src="inv_ui_mvvm_item_bindings.png" alt="Item Bindings" width="800" border-effect="line"/>
        <note>Binding ViewModel values to Widget <b>Functions</b> enables advanced UI behavior. For example, modifying visuals based on quality, or formatting tooltips dynamically.</note>
    </step>
</procedure>

To recap, we have two important ViewModel responsibilities in this widget:

- **Data Entry Point**:
    - The Item ViewModel receives data from external sources (e.g., the **container**) and broadcasts an **Item Instance or View** to **Data Processors**.
    - Since a **ViewModel Extension** will provide a valid instance, the **Creation Type** should be set to `Manual`.
- **Data Processor**:
    - Fragment ViewModels will receive data from the **Entry Point** and perform their own data collection and processing.
    - Since these instances are not created externally, their **Creation Type** should use the provided **Resolver**, the `Inventory Resolver`.

However, as shown in the steps above, binding the Item ViewModel directly to every Fragment ViewModel can become repetitive
and error-prone, especially as your UI becomes more complex.

To simplify this, the Inventory System provides a built-in **Base Item Widget** (`NinjaInventoryItemWidget`) that automatically
propagates item data to all child ViewModels.

<procedure title="Using the Base Item Widget" collapsible="true" default-state="expanded">
    <step>Reparent your Item Widget to <code>NinjaInventoryItemWidget</code>.</step>
    <step>
         <p>Update your <b>ViewModel bindings</b> in the <b>View Bindings panel</b> so that the Item ViewModel calls the functions <code>SetItemInstance</code> and <code>SetItemView</code>, which are provided by the base class.</p>
        <img src="inv_ui_mvvm_item_data_pipeline_base_widget.png" alt="Data Pipeline with Base Widget" width="800" border-effect="line"/>
    </step>
</procedure>

## Container ViewModel

With an **Item Widget** ready, the next natural step is to prepare a **Container Widget** that represents an **Inventory
Container** in the UI, such as a _Backpack_ or _Equipment Panel_.

The steps below will guide you through setting up a fully reactive container using the **Inventory Container ViewModel**
and the **ViewModel Extension** workflow.

<procedure title="Preparing the Backpack Container Widget" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new Container Widget by extending from <code>UserWidget</code>.</p>
        <note>Ninja Inventory provides a base <b>Container Widget</b>, but for this example, we’ll build it from scratch to better understand the concepts involved.</note>
    </step>
    <step>
        <p>Add the <b>Inventory Container ViewModel</b> to the widget. Set its <b>Creation Type</b> to <code>Resolver</code>, and select <code>Inventory Resolver</code> as the resolver class.</p>
        <img src="inv_ui_mvvm_container_creation_details.png" alt="Container ViewModel Creation" border-effect="line"/>
    </step>
    <step>
        <p>In your <b>Widget Graph</b>, initialize the Container ViewModel by retrieving the desired <b>Container Instance</b> from the <b>Inventory Manager</b> and passing it to the ViewModel.</p>
        <img src="inv_ui_mvvm_container_initialization.png" alt="Container Initialization" width="800" border-effect="line"/>
    </step>
    <step>
        <p>Design your Container Widget layout using a <b>WrapBox</b> to display items. Adjust its size, spacing, and style as needed. Once the layout is complete, click <b>Add ViewModel Extension</b>.</p>
    </step>
    <step>
        <p>In the ViewModel Extension panel, set the <b>Entry Widget Class</b> to your <b>Item Widget</b>, and assign the <b>Inventory Item ViewModel</b> as the <b>Entry ViewModel</b>.</p>
        <img src="inv_ui_mvvm_container_mvvm_extension.png" alt="Container ViewModel Extension" width="800" border-effect="line"/>
    </step>
    <step>
        <p><b>Compile and save</b> your widget to ensure the new ViewModel Extension is registered and accessible in the <b>View Bindings</b> panel.</p>
    </step>
    <step>
        <p>In the <b>View Bindings</b> panel, connect the <code>GetItems</code> function from the <b>Container ViewModel</b> to the <code>SetItems</code> function provided by the <b>ViewModel Extension</b>.</p>
        <img src="inv_ui_mvvm_container_bindings.png" alt="Container List Binding" width="800" border-effect="line"/>
        <note>
            <p><b>Representing Empty Slots</b></p>
            <p>Grid-based UIs (e.g., a Backpack) may benefit from displaying empty slots, while list-style containers (e.g., Loot Lists) typically should not.</p>
            <p>This behavior is controlled by the <code>bFillEmptyEntries</code> setting in the <b>Container ViewModel</b>.</p>
        </note>
    </step>
    <step>
        <p>Still in the <b>View Bindings</b> panel, you can optionally connect the <code>GetContainerName</code> function from the <b>Container ViewModel</b> to a <b>Text Block</b> in your widget.</p>
        <img src="inv_ui_mvvm_container_bindings_cont.png" alt="Container Name Binding" width="800" border-effect="line"/>
    </step>
</procedure>

To simplify the setup, the Inventory System provides a built-in **Base Container Widget** (`NinjaInventoryContainerWidget`)
that automatically manages the **target container** and its ViewModel lifecycle.

This removes the need to set up the container manually during `OnConstruct`, and exposes a `ContainerDataAsset` property
that can be set directly in the Designer.

<procedure title="Using the Base Container Widget" collapsible="true" default-state="expanded">
    <step>Reparent your Container Widget to <code>NinjaInventoryContainerWidget</code>.</step>
    <step>
        <p>Open the widget’s <b>Designer</b> tab and select the root widget. In the <b>Details</b> panel, locate the <b>Container Data Asset</b> property and assign the appropriate container definition.</p>
        <img src="inv_ui_mvvm_container_data_pipeline_base_widget.png" alt="Container Binding with Base Widget" width="800" border-effect="line"/>
    </step>
    <step>
        <p>Remove any manual logic from your <b>OnConstruct</b> or <b>Widget Graph</b> that was used to initialize the container manually. The base widget will now handle initialization and ViewModel binding automatically.</p>
    </step>
</procedure>

## ViewModel Library

Ninja Inventory provides a modular **library of ViewModels** that you can use to build flexible, data-driven user interfaces.

All concepts introduced in this chapter apply across the entire ViewModel library, which is organized into the following 
categories:

- **Attributes**: Exposes **Gameplay Attribute** values from the Inventory Manager.
- **Containers**: Represents containers owned by the Inventory Manager, automatically updating when **items are added, removed, or repositioned**.
- **Item Data Entry**: Acts as the **entry point** for each Item Widget. Usually paired with a **ViewModel Extension** to distribute data to processors.
- **Item Data Processor**: Handles a specific **Item Fragment** (e.g., Stack, Quality, UI data).
- **Loot**: Displays loot **recently received** by the Inventory Manager, designed for temporary UI panels or pickup logs.

You can explore each category in detail using the following pages.
