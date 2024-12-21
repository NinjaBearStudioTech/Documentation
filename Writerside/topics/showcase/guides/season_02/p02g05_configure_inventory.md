# Configure the Inventory
<secondary-label ref="guide"/>

To create our **secondary weapon**, we should have **Ninja Inventory** configured. So this is our next task: perform the
setup, update the **Weapon Manager**, and convert our weapons into **Items** and **Equipment**.

<procedure title="Add the Inventory Attribute Set">
    <step>Create a <b>Data Table</b> for <b>Inventory Attributes</b>, using the base data from <a href="inv_attributes.md"/>.</step>
    <step>Change the initial <b>Backpack Attribute</b> to <code>20</code>, or any other value that you prefer.</step>
    <step>
        <p>Add the <b>Inventory Attribute Set</b> to the player, via the <b>Ability Definition</b>.</p>
        <img src="p02g05_inventory_attribute_set.png" alt="Inventory Attribute Set" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Configure the Equipment Manager Component" collapsible="true">
    <step>Add the <b>Equipment Manager Component</b> to the Player Character.</step>
    <step>
        <p>Implement the <b>Equipment Provider Interface</b> to the Player Character and implement the <code>GetEquipmentManager</code> function.</p>
        <img src="p02g05_implement_equipment_interface.png" alt="Equipment Provider Interface" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step> 
        <p>In the Equipment Manager, create two virtual slots for the weapon actors, one for the sword, one for the shield.</p>
        <p>These Slots will be identified by the Gameplay Tags <code>Equipment.Slot.Weapon.MainHand</code> and <code>Equipment.Slot.Weapon.OffHand</code>. In this example they are mapped to <code>sWeaponMainHand</code> and <code>sWeaponOffHand</code> sockets.</p>
        <img src="p02g05_actor_socket_slot_mapping.png" alt="Actor Socket/Slot Mapping" thumbnail="true" border-effect="line" width="600"/>
        <tip>
            <p><b>Slot/Socket Mapping</b></p>
            <p>Since our weapons are <b>Actors</b>, they are directly attached to the character. We need to map <b>Slots</b> to the <b>Sockets</b> previously created for the original <b>Weapon Manager</b>.</p>
            <p>For more information about the <b>Slot/Socket Mapping</b>, please check the <a href="inv_equipment.md#sockets">Equipment</a> page.</p>
        </tip>
    </step>
</procedure>

<procedure title="Replace the Default Weapon Manager" collapsible="true">
    <step>Replace your <b>Weapon Manager Component</b> with the <b>Equipment Adapter Component</b>.</step>
    <step>
        <p>Update the <code>GetWeaponManager</code> function, from the <b>Combat System Interface</b>, so it returns the new version of the Weapon Manager.</p>
        <img src="p02g05_replace_weapon_manager.png" alt="Equipment Weapon Manager" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Create Equipment Actors and Definition" collapsible="true">
    <step>Re-parent your base <b>Weapon Class or Blueprint</b> to <code>ANinjaCombatEquipmentWeaponActor</code>.</step>
    <step>Add the <code>EquipmentActorInterface</code> to the base class. You do not need to implement any methods from this interface.</step>
    <step>Create a new <b>Equipment Definition</b>, from the <b>Content Menu</b>, for the <b>Sword and Shield</b>. Be sure to create this Data Asset in the folder configured in the <b>Asset Manager</b>.</step>
    <step>Add a new <b>State Configuration</b> for the <code>Equipment.State.Activated</code> state. These instructions will be used when the Equipment is <b>Active</b></step>
    <step>Add an <b>Actor entry</b> setting the <b>Sword Actor</b> as the <b>Actor Class</b>, and the <code>Equipment.Slot.Weapon.MainHand</code> as the <b>Slot Tag</b>.</step>
    <step>Add an <b>Actor entry</b> setting the <b>Shield Actor</b> as the <b>Actor Class</b>, and the <code>Equipment.Slot.Weapon.OffHand</code> as the <b>Slot Tag</b>.</step>
    <img src="p02g05_equipment_definition.png" alt="Equipment Definition" thumbnail="true" border-effect="line" width="600"/>
    <tip>
        <p><b>Scene Component Selector</b></p>
        <p>For a regular character, you can use the <b>Character Mesh</b> selector, or even setting a Gameplay Tag to find another Scene Component.</p>
        <p>For more complex characters, using something like realtime IK Retargeting or multiple possible meshes from a Leader Pose Component, you might want to use the <b>Provider Interface</b> selector.</p>
        <p>More information about these selectors can be found in the <a href="inv_equipment.md#configuring-assets-for-states">Equipment</a> page.</p>
    </tip>
</procedure>

<procedure title="Create the Weapon Item Definition" collapsible="true">
    <step>Create a new <b>Item Definition</b>, from the <b>Content Menu</b>, for the <b>Sword and Shield</b>.</step>
    <step>Set a Gameplay Tag that identifies this item - <code>Inventory.Item.Weapon.SwordAndShield</code>.</step>
    <step>Add the <b>User Interface Fragment</b>, set the <b>Display Name</b> ("<i>Sword and Shield</i>"), <b>Display Type</b> (<i>Weapon</i>) and an Icon.</step>
    <step>Add the <b>Stack Fragment</b>, set the <b>Stack Limit</b> as <b>1</b> and <b>Maximum Limit</b> as 1.</step>
    <step>
        <p>Add the <b>Container Fragment</b>, set the <b>Preferred Container Query</b> to indicate the <b>Weapon Container</b>.</p>
        <img src="p02g05_item_container_query.png" alt="Preferred Container Query" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>Add the <b>Equipment Fragment</b>, set the Equipment Definition defined in the previous step as the <b>Equipment Data</b>.</step>
    <img src="p02g05_item_definition.png" alt="Item Definition" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Create the Backpack container" collapsible="true">
    <step>Create a new <b>Container Definition</b>, from the <b>Content Menu</b>, for the <b>Backpack</b> container.</step>
    <step>
        <p>Set the <b>Display Name</b> as <b>Backpack</b>, and add <code>Inventory.Container.Backpack</code> and <code>Inventory.Container.Default</code> Gameplay Tags.</p>
        <tip>
            <p><b>Default Container</b></p>
            <p>The <code>Inventory.Container.Default</code> is provided by the system and indicates a default container, used when no better option is available.</p>
        </tip>
    </step>
    <step>Set the <b>Priority</b> to <code>100</code>, so this container will have low priority in comparison with other compatible containers.</step>
    <step>
        <p>Set the <code>NinjaInventoryAttributeSet.BackpackSlots</code> as the <b>Slots Attribute</b>.</p>
        <tip>
            <p><b>Backpack Attribute Value</b></p>
            <p>This attribute is part of the <b>Ninja Inventory Attribute Set</b>, and it was previously initialized in this guide.</p>
        </tip>
    </step>
    <img src="p02g05_backpack_definition.png" alt="Backpack Definition" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Create the Primary Weapon slot" collapsible="true">
    <step>Create a new <b>Container Definition</b>, from the <b>Content Menu</b>, for the <b>Primary Weapon</b>.</step>
    <step>
        <p>Set the <b>Display Name</b> as <b>Primary Weapon</b>, and add <code>Inventory.Container.Equipment</code> and <code>Inventory.Container.Weapon.Main</code> Gameplay Tags.</p>
        <tip>
            <p><b>Equipment Container</b></p>
            <p>The <code>Inventory.Container.Equipment</code> is provided by the system and indicates an equipment slot, used to store equipment instances.</p>
            <p>Containers configured as <b>Equipment Slots</b> will default their size to <b>1</b>.</p>
        </tip>
    </step>
    <step>Set <code>Equipment.State.Activated</code> as the <b>Default State Tag</b>, defining the initial state of equipment instances added to this slot.</step>
    <step>
        <p>Set the <b>Item Compatibility Query</b> so it filters items tagged as <b>Weapons</b>.</p>
        <img src="p02g05_weapon_slot_query.png" alt="Weapon Slot Query" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <img src="p02g05_primary_weapon_definition.png" alt="Primary Weapon Definition" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Create the Secondary Weapon slot" collapsible="true">
    <step>Create a new <b>Container Definition</b>, from the <b>Content Menu</b>, for the <b>Secondary Weapon</b>.</step>
    <step>Repeat the steps above, defining the <b>Secondary Weapon</b> slot.</step>
    <step>Set the <b>Priority</b> to <code>2</code> to prioritize the <b>Primary Weapon</b> equipment slot.</step>
    <img src="p02g05_secondary_weapon_definition.png" alt="Secondary Weapon Definition" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the Inventory Layout" collapsible="true">
    <step>Create a new <b>Inventory Layout</b>, from the <b>Context Menu</b>.</step>
    <step>Add all <b>Container Definitions</b> created in the previous step to the list of <b>Container Definitions</b>.</step>
    <img src="p02g05_inventory_layout.png" alt="Inventory Layout" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the Inventory Manager Component" collapsible="true">
    <step>Make sure that Ninja Inventory is added to your project and your <b>Asset Manager</b> was configured, as instructed by the <a href="inv_setup.md"/> page.</step>    
    <step>
        <p>Create a <b>Player State</b> using <code>NinjaGASPlayerState</code> as the base class (or a subclass of it). Set it to your <b>Game Mode</b></p>
        <tip>You probably have a Player State already configured, from the <a href="p01g02_configure_gas.md">GAS setup guide</a>.</tip>
    </step>
    <step>Add the <b>Inventory Manager Component</b> to the Player State.</step>
    <step>
        <p>Add the <b>Inventory Provider Interface</b> to the Player State and implement the <code>GetInventoryManager</code> function.</p>
        <img src="p02g05_implement_inventory_interface.png" alt="Inventory Provider Interface" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Add default items" collapsible="true">
    <step>In the <b>Inventory Manager Component</b>, set the <b>Inventory Layout</b> that was just created.</step>
    <step>
        <p>Add an entry for <b>Default Items</b> and add the <b>Sword and Shield</b> as the <b>Item Data</b>.</p>
        <tip>
            <p><b>Automatic Slot Placement</b></p>
            <p>The <b>Weapon Slot</b> and <b>Weapon Item</b> are configured so this item will be automatically placed in the correct equipment slot.</p>
        </tip>
    </step>
    <img src="p02g05_default_items.png" alt="Add Default Items" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press <b>Play</b> and check the sword and shield added to the correct slots and sockets.</step>
    <step>Open your <b>Gameplay Debugger</b>, by pressing the pre-defined key. You can access the Gameplay Debugger Configuration in the <b>Project Settings</b>, <b>Gameplay Debugger</b> page.</step>
    <step>Expand the <b>Inventory Category</b> and notice that both <b>Containers</b> were added and the <b>Weapon Item</b> is set to the correct slot.</step>
    <img src="p02g05_results.png" alt="Test the Setup" thumbnail="true" border-effect="line" width="600"/>
</procedure>