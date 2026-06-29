# First Steps with Ninja Inventory
<primary-label ref="inventory"/>

This page guides you through the first steps for **Ninja Inventory**. Make sure to check the [**Inventory Setup**](inv_setup.md)
instructions before continuing.

This page assumes that your project has access to the **Gameplay Ability System**, but a full GAS implementation is not
required for this first inventory setup. If you are using [**Ninja G.A.S.**](gas_overview.md), the same concepts can
transfer to other G.A.S. setups.

The following steps aim to provide **an inventory owner with an initialized Inventory Manager**, a default container, and
a simple item stored in that container.

It is also recommended that your **Gameplay Debugger** is configured, so you can inspect the inventory state during gameplay.

## Inventory Attributes
<secondary-label ref="optional"/>

Ninja Inventory can use [**Gameplay Attributes**](inv_gameplay_attributes.md) for inventory-related gameplay values, 
such as **capacity**, **weight**, and **wealth**. 

For this first setup, inventory attributes are optional. You can skip this section if your project does not need
attribute-driven inventory behavior yet.

<procedure title="Add Inventory Attributes using Ninja G.A.S." collapsible="true" default-state="expanded">
    <step>Create a new <b>Data Table</b> for your Inventory Attributes, using <code>AttributeMetaData</code> as the table row structure.</step>
    <step>Download the <b><a href="inv_gameplay_attributes.md#initialization-data">Sample Initialization Data</a></b> and use it as the table data.</step>
    <step>
        <p>Create a new <b>G.A.S. Setup Data Asset</b> and add a new <b>Default Attribute Set</b> entry.</p> 
        <p>You can do so by right-clicking an empty area in the <b>Content Browser</b>, then navigating to <b>Ninja Bear Studio</b> &rarr; <b>Ninja G.A.S.</b> &rarr; <b>G.A.S. Setup</b>.</p>
    </step>
    <step>Add the <b>Ninja Inventory Attribute Set</b>, <code>NinjaInventoryAttributeSet</code>, and the data table as the <b>Attribute Table</b>.</step>
    <step>Set the new GAS Setup Data to the character's <b>Ability System Component</b>.</step>
</procedure>

## Default Container

Containers define where items can be stored. For this first setup, we will create a simple default container using the
**Simple Layout**, which is a position-based type of storage.

<procedure title="Create a Default Container" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new <b>Container Definition Data Asset</b> in the Containers folder configured in the Asset Manager.</p>
        <p>You can do so by right-clicking an empty area in the <b>Content Browser</b>, then navigating to <b>Ninja Bear Studio</b> &rarr; <b>Ninja Inventory</b> &rarr; <b>Container Definition</b>.</p>
    </step>
    <step>Name it <code>Container_Backpack</code>.</step>
    <step>Add <code>Inventory.Container.Trait.Default</code> and <code>Inventory.Container.Type.Backpack</code> as the <b>Gameplay Tags</b> that define and identify this container.</step>
    <step>Configure the <b>Layout</b> as a <b>Simple Layout</b> and set <b>Slots</b> to <code>12</code>.</step>
    <step>
        <p>Set the <b>Priority</b> to <code>10</code> so other high-priority containers can take precedence.</p>
        <img src="inv_container_backpack.png" alt="Backpack Container" border-effect="line"/>
    </step>
</procedure>

## Simple Item

Items are defined via **aggregation**, through **Item Fragments**. For this first setup, we will create a simple stackable 
item that can be stored in a container and displayed in the user interface.

> **Example Item**
>
> This page uses `Ammo_Rifle` as a simple stackable item, but you can create any item that makes sense for your project. 
> The important part is that it uses the **Container Storage**, **User Interface**, and **Stack** fragments.
{style="tip"}

<procedure title="Create a Simple Item" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new <b>Item Definition Data Asset</b> in the Items folder configured in the Asset Manager.</p>
        <p>You can do so by right-clicking an empty area in the <b>Content Browser</b>, then navigating to <b>Ninja Bear Studio</b> &rarr; <b>Ninja Inventory</b> &rarr; <b>Item Definition</b>.</p>
    </step>
    <step>Name it <code>Ammo_Rifle</code>, or another simple item name that fits your project.</step>
    <step>Add a <b>Container Storage</b> fragment so the item can be stored in inventory containers.</step>    
    <step>Add a <b>User Interface</b> fragment, set the <b>Display Name</b>, <b>Category</b>, <b>Description</b> and <b>Icon</b>.</step>    
    <step>
        <p>Add a <b>Stack</b> fragment, set the <b>Maximum Quantity</b> to <code>900</code> and the <b>Stack Limit</b> to <code>90</code>.</p>
        <img src="inv_item_ammo.png" alt="Simple Item" border-effect="line"/>
    </step>
</procedure>

## Inventory Manager Component

The **Inventory Manager Component** owns the runtime inventory state. It should be added to the actor that represents
the inventory owner. For players, this usually means one of these options:

- **Player State**: The inventory should persist across pawn changes, respawns, or possession changes.
- **Player Pawn**: The inventory belongs to the current pawn and can reset when the pawn changes.

<procedure title="Add the Inventory Manager Component" collapsible="true" default-state="expanded">
    <step>Open the Player State or Player Pawn that should own the inventory.</step>
    <step>
        <p>Add the <b>Inventory Manager Component</b>, <code>NinjaInventoryManagerComponent</code>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="inv_setup_inventory_manager.png" alt="Add the Inventory Manager Component" width="600" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p><b>Header</b></p>
                <code-block lang="c++" src="inv_setup_inventory_manager_component.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="inv_setup_inventory_manager_component.cpp"/>
            </tab>
        </tabs>
    </step>
    <step>Navigate to the <b>Inventory Manager</b> category in the <b>Inventory Manager Component</b>.</step>
    <step>Add the <code>Container_Backpack</code> asset to the list of <b>Initial Containers</b>.</step>
    <step>Add the <code>Ammo_Rifle</code> asset to the list of <b>Initial Items</b>.</step>
    <step>Add a new entry to the item's <b>Initial Fragment Data</b>.</step>
    <step>Select <b>ItemFragment_StackAndQuantity</b> as the <b>Fragment Class</b>.</step>
    <step>
        <p>Select <b>Stack Memory</b> as the <b>Memory</b> and set the <b>Stack Size</b> to <code>30</code>.</p>
        <img src="inv_default_container_and_item.png" alt="Default Container and Item" border-effect="line" width="600"/>
    </step>
</procedure>

### Inventory System Interface
<secondary-label ref="optional"/>
<secondary-label ref="recommended"/>

To avoid repeated component lookups, you can optionally have the Actor or Player State implement `InventorySystemInterface`,
which is recommended. 

<procedure title="Add the Inventory System Interface" collapsible="true" default-state="expanded">
    <step>In your <b>inventory owner</b> (Actor or Player State), add the <code>InventorySystemInterface</code>.</step>
    <step>
        Implement the <code>GetInventoryManager</code> function so it returns the <b>Inventory Manager Component</b>.
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="inv_setup_inventory_interface.png" alt="Add the Inventory System Interface" width="800" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p><b>Header</b></p>
                <code-block lang="c++" src="inv_setup_inventory_system_interface.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="inv_setup_inventory_system_interface.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

## Evaluating the Inventory State
<secondary-label ref="optional"/>
<secondary-label ref="recommended"/>

After starting the game, you can use the **Gameplay Debugger** to confirm that the inventory was initialized correctly.

<procedure title="Inspect the Inventory with the Gameplay Debugger" collapsible="true" default-state="expanded">
    <step>Start the game in Play-in-Editor.</step>
    <step>Open the <b>Gameplay Debugger</b> and expand the <b>Inventory Category</b>.</step>
    <step>Select the actor that owns the <b>Inventory Manager Component</b>, if not selected by default.</step>
    <step>Check that the <b>Initialization State</b> displays <b>Initialized</b>.</step>
    <step>Check that the <b>Owner</b> and <b>Avatar</b> correctly match your Blueprints.</step>
    <step>Check that the <b>Data Source</b> displays <b>Initial Data</b>.</step>
    <step>Check that the <b>Backpack Container</b> is correctly shown, with the proper amount of <b>slots</b>.</step>
    <step>
        <p>Check that the <b>simple item</b> was properly stored in the container and has the correct stack size.</p>
        <img src="inv_gameplay_debugger.png" alt="Inventory Debugger" border-effect="line" width="600"/>
    </step>
</procedure>

## Next Steps

At this point, you have an inventory owner with an initialized **Inventory Manager**, a default container, and a simple
item stored in that container.

From here, you can:

- Learn more about [**Item Fragments**](inv_inventory_items.md).
- Configure [**Equipment**](inv_equipment_system.md).
- Learn about [**Save and Load**](inv_save_and_load.md) functionality.
- Integrate [**Ninja Inventory with Ninja Combat**](integration_combat_inventory.md).