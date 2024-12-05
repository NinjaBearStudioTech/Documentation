# Configure Equipment for Stored Items
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

This how-to will show how to configure **Equipment** for Items that were previously created. Specifically, the **Sword**
and the **Shield**.

Currently, these items are **automatically assigned** to their preferred **Containers**. These Containers are configured 
to set the default **Equipment State** to **Deactivated**. Therefore, an **Equipment Definition** should be introduced 
to properly represent these Items.

In this topic, you will see a **Static Mesh** being used to represent the stored weapons, so make sure to have those
ready before getting started.

<procedure title="Configure Equipment Slots in the Character" collapsible="true" id="character_slots">
    <step>Open your character's <b>Skeleton Asset</b>.</step>
    <step>Add a <b>socket</b> named <code>sSword_RH</code> to the <b>Right Hand</b> bone. Adjust the location and rotation as necessary.</step>  
    <step>Add a <b>socket</b> named <code>sShield_LH</code> to the <b>Left Hand</b> bone. Adjust the location and rotation as necessary.</step>    
    <step>Add two <b>sockets</b> to the <b>Spine 03</b> bone: <code>sSword_Stored</code> and <code>sShield_Stored</code>. Adjust their location and rotation as necessary.</step>
    <step>Open your character's <b>Blueprint</b>.</step>
    <step>Add a <b>Static Mesh Component</b>, child of the character's <b>Mesh</b>, set the <b>Parent Socket</b> to <code>sSword_Stored</code>, and add <code>Equipment.Slot.Back.Weapon.A.Right</code> to the list of <b>Component Tags</b>.</step>    
    <step>Add a <b>Static Mesh Component</b>, child of the character's <b>Mesh</b>, set the <b>Parent Socket</b> to <code>sShield_Stored</code>, and add <code>Equipment.Slot.Back.Weapon.A.Left</code> to the list of <b>Component Tags</b>.</step>
</procedure>

<procedure title="Add the Equipment Manager to the Character" collapsible="true">
    <step>
        <p>Add the <b>Equipment Manager</b> component to your <b>Character</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <p>In <b>Blueprints</b>, go to your <b>Components</b>, search for <code>Equipment</code> and add <b>Ninja Equipment Manager Component</b>.</p>
                <br/>
                <img src="inv_setup_equipment_component.png" alt="Add the Equipment Manager Component" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p>Create a variable for the of <code>UNinjaEquipmentManagerComponent</code> in your class.</p>
                <br/>
                <code-block lang="c++" src="inv_setup_equipment_component.h" />
                <br/>
                <p>Create an instance of <code>UNinjaEquipmentManagerComponent</code> in your <b>constructor</b>.</p>
                <br/>
                <code-block lang="c++" src="inv_setup_equipment_component.cpp" />
            </tab>
        </tabs>
    </step>
    <step>
        <p>Add the <b>Equipment Manager Provider Interface</b> to your <b>Character</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <p>Open your <b>Class Settings</b>, navigate to the list of <b>Implemented Interfaces</b> and add the interface.</p>
                <br/>
                <img src="inv_setup_equipment_interface.png" alt="Add the Equipment Manager Component" border-effect="line"/>
                <br/>
                <p>In the <b>My Blueprint</b> panel, under <b>Interfaces</b>, expand <b>Equipment Manager Provider</b> and double-click <b>Get Equipment Manager</b>.</p>
                <p>In the <b>Blueprint Graph</b>, drag your <b>Equipment Manager</b> into the <b>Return Value</b>.</p>
                <br/>
                <img src="inv_setup_equipment_implementation.png" alt="Add the Equipment Manager Component" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p>Add <code>IEquipmentManagerProviderInterface</code> to your <b>class declaration</b>, and <b>override</b> <code>GetEquipmentManager</code>.</p>
                <br/>
                <code-block lang="c++" src="inv_setup_equipment_interface.h" />
                <br/>
                <p>Implement <code>GetEquipmentManager</code>, so it returns the <b>Equipment Manager</b>.</p>
                <br/>
                <code-block lang="c++" src="inv_setup_equipment_interface.cpp" />
            </tab>
        </tabs>
    </step>
</procedure>

<procedure title="Create the Sword Equipment Definition" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>equipment data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Equipment Definition</b>.</step>
    <step>Name your new container asset <code>Equipment_Sword</code> and open it.</step>
    <step>Add a new <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Deactivated</code>.</step>
    <step>In the <b>Deactivated</b> State Configuration, add a new entry to the <b>Static Meshes</b> array. Set the Static Mesh that represents your sword to the <b>Mesh</b>.</step>
    <step>
        <p>Set <code>Equipment.Slot.Back.Weapon.A.Right</code> to the <b>Slot Tag</b> and <code>sSword_Stored</code> to the <b>SocketName</b>.</p>
        <tip>This is the same Tag set to your Mesh Component, during the <a href="#character_slots">first part</a>.</tip>
    </step>
    <step>
        <p>When you are done, your <b>Sword Equipment Definition</b> should be similar to this.</p>
        <img src="inv_configure_stored_equipment_sword.png" alt="Sword Equipment Definition with the Deactivated state" border-effect="line" thumbnail="true" />
    </step>
</procedure>

<procedure title="Update the Sword Item Definition" collapsible="true">
    <step>Open the <b><a href="inv_create_item.md">Sword Item Definition</a></b> and add an <b><a href="inv_equipment_fragment.md">Equipment Fragment</a></b></step>
    <step>
        <p>Set the <code>Equipment_Sword</code> to the <b>Equipment Data</b>.</p>
        <img src="inv_configure_stored_equipment_sword_item.png" alt="Sword Item Definition with the Equipment Fragment" border-effect="line" thumbnail="true" />
    </step>
</procedure>

<procedure title="Create the Shield Equipment Definition" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>equipment data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Equipment Definition</b>.</step>
    <step>Name your new container asset <code>Equipment_Shield</code> and open it.</step>
    <step>Add a new <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Deactivated</code>.</step>
    <step>In the <b>Deactivated</b> State Configuration, add a new entry to the <b>Static Meshes</b> array. Set the Static Mesh that represents your shield to the <b>Mesh</b>.</step>
    <step>
        <p>Set <code>Equipment.Slot.Back.Weapon.A.Left</code> to the <b>Slot Tag</b> and <code>sShield_Stored</code> to the <b>SocketName</b>.</p>
        <tip>The Gameplay Tag matches the one set in the <b><a href="inv_create_containers.md">Off-Hand Container Definition</a></b>.</tip>
    </step>
    <step>
        <p>When you are done, your <b>Shield Equipment Definition</b> should be similar to this.</p>
        <img src="inv_configure_stored_equipment_shield.png" alt="Shield Equipment Definition with the Deactivated state" border-effect="line" thumbnail="true" />
    </step>
</procedure>

<procedure title="Update the Shield Item Definition" collapsible="true">
    <step>Open the <b><a href="inv_create_item.md">shield Item Definition</a></b> and add an <b><a href="inv_equipment_fragment.md">Equipment Fragment</a></b></step>
    <step>
        <p>Set the <code>Equipment_Shield</code> to the <b>Equipment Data</b>.</p>
        <img src="inv_configure_stored_equipment_shield_item.png" alt="Shield Item Definition with the Equipment Fragment" border-effect="line" thumbnail="true" />
    </step>
</procedure>

<procedure title="Check your Inventory in the Gameplay Debugger" collapsible="true">
    <step>Hit <b>Play</b>, open the <b>Gameplay Debugger</b> and activate the <b>Inventory</b> category.</step>
    <step>
        <p>Confirm that the <b>Sword</b> and <b>Shield</b> now show <b>Deactivated</b> in the <b>Equipment</b> column, meaning that an <b>Equipment Instance</b> is present.</p>
        <p>Your <b>Sword</b> and <b>Shield</b> meshes should be properly attached to your character.</p>
        <img src="inv_setup_equipment_debugger.png" alt="Equipment in the Gameplay Debugger" border-effect="line" thumbnail="true" />
    </step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_equipment.md" summary = "More details about objects related to the equipment.">Equipment, States and Actors</a>
        <a href="inv_equipment_manager.md" summary = "Equipment Manager and its functionalities.">Equipment Manager</a>
    </category>
</seealso>
