# Create the Inventory UI
<secondary-label ref="guide"/>

Let's create the first part of the Inventory UI, so it can display the weapon slots and the backpack. These will be 
built using the base Inventory Widgets and UMG Viewmodels.

## Main Interface Elements

First, we need to create all **main widgets** that represent our current Inventory Layout: Primary and Secondary weapons,
the backpack for all other items, and the Inventory Window itself.

<procedure title="Create the Item Widget" collapsible="true">
    <step>Create a new <b>Widget Blueprint</b> based on <code>NinjaInventoryItemWidget</code>.</step>
    <step>
        <p>Design the widget, making sure that you have a valid <b>Image Component</b> for the icon and a <b>Text Component</b> for the quantity. Mark these component as a <b>variables</b>.</p>
        <img src="p02g06_item_widget_icon.png" alt="Item Widget Icon" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Go to the <b>Graph</b> and, in the <code>PreConstruct</code> event, hiding components that are not shown by default, marking them as <b>collapsed</b>.</p>
        <img src="p02g06_item_widget_pre_construct.png" alt="Item Widget Pre-Construct" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a new Blueprint Function, <code>SetIcon</code>, to receive the <b>Icon</b> and set the texture to the correct component. This function will receive a <code>Texture2D</code> object.</p>
        <img src="p02g06_item_widget_set_icon.png" alt="Item Widget Set Icon Function" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a new Blueprint Function, <code>SetStack</code>, to receive the <b>Quantity</b> and set the value to the correct component. This function will receive an <code>Integer</code> value.</p>
        <img src="p02g06_item_widget_set_stack.png" alt="Item Widget Set Stack Function" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>Back to the <b>Widget Designer</b>, add the <b>Item User Interface</b> and <b>Item Stack</b> viewmodels. Configure their <b>Creation Type</b> to <b>Create Instance</b>.</step>
    <step>
        <p>Add two <b>View Bindings</b>, mapping the <code>Icon</code> property from the User Interface Viewmodel to the <code>SetIcon</code> function, and <b>Stack Size</b> property from the Item Stack Viewmodel to the <code>SetStack</code> function.</p>
        <img src="p02g06_item_widget_viewmodel.png" alt="Item Widget Viewmodel" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Create the widget for the primary weapon" collapsible="true">
    <step>Create a new <b>Widget Blueprint</b> based on <code>NinjaInventoryContainerWidget</code>.</step>
    <step>
        <p>Click the <b>root element</b> in the widget and set the <b>Container Data</b> to the <b>Primary Container</b> and set the <b>Item Widget Class</b> as the <b>Item Widget</b> created in the previous step.</p>
        <img src="p02g06_weapon_widget_settings.png" alt="Primary Weapon Settings" thumbnail="true" border-effect="line" width="600"/>        
    </step>
    <step>
        <p>Design the widget as you like, making sure that you have a valid <b>Named Slot</b> labeled <code>ContainerViewSlot</code>. In this Named Slot, add an <b>Inventory Container Border</b>, and finally, inside the Container Border, add the <b>Item Widget</b> created in the previous step.</p>
        <img src="p02g06_weapon_named_slot.png" alt="Primary Weapon Slot Setup" thumbnail="true" border-effect="line" width="600"/>
        <note>
            <p><b>Container Border</b></p>
            <p>A Container Border is a good component choice, when you only want to represent a single item. Usually the case for <b>Equipment Slots</b>.</p>
        </note>
    </step>
    <step>
        <p>Add the <b>Inventory Items View Model</b>, set it to be instantiated when the widget is created, and bind it to the <code>RefreshItems</code> function.</p>
        <img src="p02g06_weapon_widget_binding.png" alt="Primary Weapon Binding" thumbnail="true" border-effect="line" width="600"/>  
        <note>
            <p><b>Refresh Items Function</b></p>
            <p>This function is provided by the base <b>Container Widget</b> and will refresh items as needed. You can also create your own function and call <code>RefreshItems</code> in there, if you need additional logic.</p>
        </note>
    </step>
</procedure>

<procedure title="Create the widget for the secondary weapon" collapsible="true">
    <step>Create a new <b>Widget Blueprint</b> based on <code>NinjaInventoryContainerWidget</code>.</step>
    <step>Repeat the same tasks from the previous step, but set the <b>Container Data</b> to the <b>Secondary Container</b>.</step>
</procedure>

<procedure title="Create the Backpack Widget" collapsible="true">
    <step>Create a new <b>Widget Blueprint</b> based on <code>NinjaInventoryContainerWidget</code>.</step>
    <step>
        <p>Click the <b>root element</b> in the widget and set the <b>Container Data</b> to the <b>Backpack Container</b> and set the <b>Item Widget Class</b> as the <b>Item Widget</b> created in the previous step.</p>
        <img src="p02g06_backpack_widget_settings.png" alt="Backpack Settings" thumbnail="true" border-effect="line" width="600"/>        
    </step>
    <step>
        <p>Design the widget as you like, making sure that you have a valid <b>Named Slot</b> labeled <code>ContainerViewSlot</code>. In this Named Slot, add an <b>Inventory Container Box</b>. Enable <b>Fill Empty Slots</b>. Depending on your design, you might want to also set <b>Wrap Size</b> and <b>Explicit Wrap Size</b>.</p>
        <img src="p02g06_backpack_named_slot.png" alt="Backpack Slot Setup" thumbnail="true" border-effect="line" width="600"/>
        <note>
            <p><b>Container Box</b></p>
            <p>A Container Box is a good component choice, when you want to represent items in a <b>grid</b>.</p>
        </note>
    </step>
    <step>Add the <b>Inventory Items View Model</b>, set it to be instantiated when the widget is created, and bind it to the <code>RefreshItems</code> function.</step>
</procedure>

<procedure title="Create the Inventory Window Widget" collapsible="true">
    <step>Create a new <b>Widget Blueprint</b> based on <code>NinjaInventoryWindowWidget</code>.</step>
    <step>
        <p>Design the widget as you like, making sure that you incorporate all widgets previously created: <b>Primary Weapon</b>, <b>Secondary Weapon</b> and <b>Backpack</b>. Also add a <b>Text Component</b> for the <b>title</b> that will be obtained from the <b>Layout Data Asset</b>.</p>
        <img src="p02g06_inventory_window_designer.png" alt="Inventory Window Designer" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Add the <b>Inventory Layout View Model</b>, set it to be instantiated when the widget is created, and bind the <b>Display Name</b> property to the <code>Title Text</code>.</p>
        <img src="p02g06_inventory_window_title_binding.png" alt="Inventory Window Title Binding" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>In the <b>Blueprint Graph</b>, create a <b>Show Inventory</b> event that will set the <b>Input Mode</b> to <b>Menu</b> and <b>show the mouse cursor</b>. For now, this will always be called during the <b>Construct</b> event. The <b>Hide Inventory</b> function reverts that setting.</p>
        <img src="p02g06_inventory_window_graph.png" alt="Inventory Window Graph" thumbnail="true" border-effect="line" width="600"/>
        <note>
            <p><b>Handling Input Mode</b></p>
            <p>For now, the Inventory Widget will be constantly shown and the mouse will be captured in the <b>Menu</b> mode, so it won't be received by the gameplay.</p>
            <p>In the following sections, we'll continue to work on the Inventory Interface, until we configure the inputs to be better integrated with the game.</p>
        </note>
    </step>
</procedure>

<procedure title ="Update the Gameplay Widget" collapsible="true">
    <step>
        <p>Open the Gameplay Widget previously created for the <b><a href="p02g03_player_attributes.md">Player Attributes</a></b> and add the Inventory Widget, organizing it whenever you see fit.</p>
        <img src="p02g06_gameplay_widget.png" alt="Gameplay Widget" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press <b>Play</b> and your Inventory Window should be displayed.</step>
    <step>Your <b>Primary Weapon Slot</b> should display the icon from the <b>Sword and Shield</b> item.</step>
    <step>The <b>Secondary Weapon Slot</b> should be empty.</step>
    <step>The <b>Backpack</b> should be empty, but it should display all empty positions as the pre-defined item widget.</step>
    <img src="p02g06_results_01.png" alt="Test the Setup" thumbnail="true" border-effect="line" width="600"/>
</procedure>

## Inventory Window Visibility

<procedure title="Configure Input Actions and Input Handlers" collapsible="true">
    <step>
        <p>Create an <b>Input Action</b> for the Inventory Window and add a <b>Pressed</b> trigger to it.</p>
        <img src="p02g06_inventory_input_action.png" alt="Inventory Input Action" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Add the Input Action to the <b>Input Mapping Context</b>, mapping it to appropriate keys such as <b>I</b> and <b>Gamepad Special Right</b>.</p>
        <img src="p02g06_input_mapping_context.png" alt="Input Mapping Context" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Add a new entry to the <b>Input Setup</b>, with a <b>HUD: Send UI Event</b> handler. Set the correct Input Action and the <code>UI.Action.Inventory</code> Gameplay Tag.</p>
        <img src="p02g06_input_setup.png" alt="Input Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Handle interface events in the HUD" collapsible="true">
    <step>Add <code>HUDEventDispatcherInterface</code> to your <b>Gameplay HUD</b>.</step>
    <step>Convert your <b>Gameplay Widget instance</b>, in the Gameplay HUD, to a <b>variable</b>.</step>
    <step>Implement the <code>HandleInputEvent</code> function, so it invokes the same function (interface message call) in the <b>Gameplay Widget Instance</b>.</step>
</procedure>

<procedure title="Handle interface events in the Widget" collapsible="true">
    <step>Add <code>HUDEventDispatcherInterface</code> to your <b>Gameplay Widget</b>.</step>
    <step>
        <p>In your <b>Construct</b> event, set the <b>Inventory Window visibility</b> to be <b>collapsed</b>.</p>
        <img src="p02g06_construct_event.png" alt="Construct Event" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a new <b>function</b>, <code>ToggleInventoryWindow</code> that will adjust the <b>Inventory Window visibility</b> and set the correct <b>Input Mode</b>.</p>
        <img src="p02g06_toggle_inventory_window.png" alt="Toggle Inventory Window" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Implement the <code>HandleInputEvent</code> function from the new interface, routing the <b>Inventory Event</b> to the new function.</p>
        <img src="p02g06_inventory_event.png" alt="Inventory Event" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>Open your <b>Inventory Window Widget</b> and remove all <b>visibility-related features</b> created in this guide.</step>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press <b>Play</b> and your Inventory Window should be hidden.</step>
    <step>Press your <b>Inventory Key</b> and your Inventory Window should appear. Your mouse cursor should appear as well.</step>
    <step>Press your <b>Inventory Key</b> again and your Inventory Window should disappear, along with the mouse cursor.</step>
</procedure>

## Drag and Drop and Tooltips

With the main Inventory UI being shown, it's time to add special features, such as dragging stored items to perform 
operations and adding a tooltip for additional item details.

<procedure title="Create the Arrow Item" collapsible="true">
</procedure>

<procedure title="Configure the quality table" collapsible="true">
</procedure>

<procedure title="Add the Quality Fragment to items" collapsible="true">
</procedure>

<procedure title="Create the Drag and Drop Widget" collapsible="true">
</procedure>

<procedure title="Create the Tooltip Widget" collapsible="true">
</procedure>

<procedure title="Update the Item Widget" collapsible="true">
</procedure>

<procedure title="Test everything" collapsible="true">
</procedure>
