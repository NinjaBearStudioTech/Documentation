# Create Equipment for Inventory Items
<primary-label ref="inventory"/>
<secondary-label ref="how-to"/>

## Goal

In this how-to, you will learn how to define **Equipment** that represents **Items** in the game world, and change their 
states between **activate** and **deactivated**, using **Inventory Abilities**.

This is a long hot-to, since the first time configuring equipment in the system requires some additional setup. To make
these parts clearer, this topic is separated in two parts: **Setup Tasks** and **Equipment Tasks**. 

## Pre-requisites

1. The initial [**setup**](inv_setup.md) was completed.
2. Primary Assets were registered to the **Asset Manager**
3. You [created and assigned your first **items**](inv_create_item.md).
4. The Gameplay Ability System was configured, and you are ready to add abilities to characters.
5. The **Gameplay Debugger** has been enabled in the project.
6. Animations for equipping and storing weapons.

## Setup Tasks

<procedure title="Configure your Character for Equipment Slots" collapsible="true">
    <step>Open your character's <b>Skeleton Asset</b>.</step>
    <step>Add a <b>socket</b> named <code>sShield_LH</code> to the <b>Left Hand</b> bone. Adjust the location and rotation as you like.</step>    
    <step>Add a <b>socket</b> named <code>sSword_RH</code> to the <b>Right Hand</b> bone. Adjust the location and rotation as you like.</step>  
    <step>Add two <b>sockets</b> to the <b>Spine 03</b> bone: <code>sStoredWeaponA_Right</code> and <code>sStoredWeaponA_Left</code>. Adjust their location and rotation as you like.</step>
    <step>Open your character's <b>Blueprint</b>.</step>
    <step>Add a <b>Static Mesh Component</b> parented to the character's <b>Mesh</b>, set the <b>Parent Socket</b> to <code>sStoredWeaponA_Left</code>, and add <code>Equipment.Slot.Back.Weapon.A.Left</code> to the list of <b>Component Tags</b>.</step>    
    <step>Add a <b>Static Mesh Component</b> parented to the character's <b>Mesh</b>, set the <b>Parent Socket</b> to <code>sStoredWeaponA_Right</code>, and add <code>Equipment.Slot.Back.Weapon.A.Right</code> to the list of <b>Component Tags</b>.</step>
</procedure>

<procedure title="Configuring your Animation Montages" collapsible="true">
    <step>Select an <b>Animation Sequence</b> to represent your Sword and Shield being <b>equipped</b>. Right-click the asset and create an <b>Animation Montage</b>. Name it <code>M_WeaponAndShield_Equip</code>.</step>
    <step>Open your Animation Montage, scrub to the frame where the <b>Shield</b> should be equipped and add an <b>Animation Notify</b>, select <b>Send Equipment Event</b>.</step>
    <step>Click on the new Animation Notify, set the <b>Event Tag</b> to <code>Inventory.Event.Animation.Activate</code> and set the <b>Equipment Query</b> root to <code>All Tags Match</code>, with the <code>Inventory.Item.Weapon.Shield</code> tag.</step>
    <step>Add another <b>Animation Notify</b> to the frame where the <b>Sword</b> should be equipped. Configure it as the previous notify, but this time using <code>Inventory.Item.Weapon.Sword</code> tag.</step>
    <step>Perform the same steps for another <b>Animation Sequence</b> to represent your Sword and Shield being <b>Stored</b>, name it Name it <code>M_WeaponAndShield_Store</code>. This time, set <b>Event Tag</b> in the <b>Animation Notifies</b> to <code>Inventory.Event.Animation.Deactivate</code>.</step>
    <tip>If your Sword and Shield should be equipped and/or stored at the same frame, then you can add a single <b>Animation Notify</b>, with an <code>Any Tags Match</code> root, and both item tags in it.</tip>
</procedure>

<procedure title="Configure the Animation Table" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>data folder</b> and create a new <b>Data Table</b>, select the <code>InventoryAnimationTableRow</code> as the <b>Row Structure</b> and name it <code>TB_Inventory_Animations</code>.</step>
    <step>Open your new Data Table and <b>add a new row</b>, set the <b>Montage To Play</b> to <code>M_WeaponAndShield_Equip</code>.</step>
    <step>Set the <b>Montage Query</b> as the following image.</step>
    <img src="inv_create_equipment_query_anim_equip.png" alt="Equip Weapon Montage Query"/>
    <step>Add another <b>row</b>, set the <b>Montage To Play</b> to <code>M_WeaponAndShield_Store</code> and the <b>Montage Query</b> as the following image.</step>
    <img src="inv_create_equipment_query_anim_store.png" alt="Store Weapon Montage Query"/>
    <step>Set the <b>Montage Query</b> as the following image. This will give you the flexibility to use the same <b>Animation Montage</b> for any combination of <b>one-handed weapon</b> and a <b>shield</b>.</step>
    <tip>These queries will give you the flexibility to use the same <b>Animation Montage</b> for any combination of <b>one-handed weapons</b> with a <b>shield</b>.</tip>
</procedure>

<procedure title="Create the Equipment Abilities" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>ability folder</b> and create a new <b>Gameplay Ability</b>, using <code>InventoryAbility_ActivateEquipment</code> as the parent. Name it <code>GA_EquipPrimaryItems</code>.</step>
    <step>Open your new ability and set the <b>Equipment Query</b> as the following image.</step>
    <img src="inv_create_equipment_query_ability_equip.png" alt="Equip Weapon Ability Query"/>
    <step>Set <code>TB_Inventory_Animations</code> as the <b>Montage Table</b> and <code>Wait For Gameplay Event</code> as the <b>Animation Strategy</b>.</step>
    <step>Add <code>Ability.Equipment.Primary.Activate</code> to the <b>Ability Tags</b>.</step>
    <step>Back in your <b>Content Browser</b>, navigate to your <b>ability folder</b> and create a new <b>Gameplay Ability</b>, using <code>InventoryAbility_DeactivateEquipment</code> as the parent. Name it <code>GA_StorePrimaryItems</code>.</step>
    <step>Open your new ability and set the <b>Equipment Query</b> as the following image.</step>
    <img src="inv_create_equipment_query_ability_store.png" alt="Store Weapon Ability Query"/>
    <step>Set <code>TB_Inventory_Animations</code> as the <b>Montage Table</b> and <code>Wait For Gameplay Event</code> as the <b>Animation Strategy</b>.</step>
    <step>Add <code>Ability.Equipment.Primary.Deactivate</code> to the <b>Ability Tags</b>.</step>
    <step>Set <code>TB_Inventory_Animations</code> as the <b>Montage Table</b> and <code>Wait For Gameplay Event</code> as the <b>Animation Strategy</b>.</step>
    <step>Add both Abilities to your Character's <b>Ability System Component</b>.</step>
    <step>In your <b>Input Manager</b>, configure a key or gamepad button to activate both Abilities by their <b>Gameplay Tags</b>: <code>Ability.Equipment.Primary.Activate</code> and <code>Ability.Equipment.Primary.Deactivate</code>.</step>
    <tip>You can activate both abilities, and the Inventory System will evaluate which one is actually viable, so your items will be properly <b>equipped</b> and <b>stored</b>.</tip>
</procedure>

## Equipment Tasks

<procedure title="Create the Sword Actor" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>blueprint</b> folder.</step>
    <step>Create a new <b>Blueprint</b> using <code>NinjaEquipmentActor</code> as the parent. Name it <code>BP_Weapon_Sword</code></step>
    <step>Add a new <b>Static Mesh Component</b> and set your Sword's mesh to it.</step>
    <step>Navigate to the component's <b>Collision</b> and set the <b>Collision Preset</b> to <code>No Collision</code>.</step>
    <tip>For your <b>Melee Weapons</b> you probably want to use some sort of <b>scan</b> to detect hits. Please take check <a href = "cbt_overview.md">Ninja Combat</a>, as it can help you with that!</tip>
</procedure>

<procedure title="Configure the Equipment for the Sword" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>equipment data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Equipment Definition</b>.</step>
    <step>Name your new container asset <code>Equipment_Sword_Common</code> and open it.</step>
    <step>Add a new <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Activated</code>.</step>
    <step>In the <b>Activated</b> State Configuration, add a new entry to the <b>Actors</b> array. Set <code>BP_Weapon_Sword</code> to the <b>Actor Class</b>.</step>
    <step>Set <code>Equipment.Slot.MainHand</code> to the <b>Slot Tag</b>.</step>
    <step>Add another <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Deactivated</code>.</step>
    <step>In the <b>Deactivated</b> State Configuration, add a new entry to the <b>Static Meshes</b> array. Set the Static Mesh that represents your sword to the <b>Mesh</b>.</step>
    <step>Set <code>Equipment.Slot.Back.Weapon.A.Right</code> to the <b>Slot Tag</b> and <code>sStoredWeaponA_Right</code> to the <b>SocketName</b></step>
</procedure>

<procedure title="Update your Sword Item" collapsible="true">
    <step>Open the <b>Sword Item</b> that was created <a href="inv_create_item.md">earlier</a>, and add an <b><a href="inv_equipment_fragment.md">Equipment Fragment</a></b></step>
    <step>Set the <code>Equipment_Sword_Common</code> to the <b>Equipment Data</b>.</step>
</procedure>

<procedure title="Create the Shield Actor" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>blueprint</b> folder.</step>
    <step>Create a new <b>Blueprint</b> using <code>NinjaEquipmentActor</code> as the parent. Name it <code>BP_Weapon_Shield</code></step>
    <step>Add a new <b>Static Mesh Component</b> and set your Shield's mesh to it.</step>
    <step>Navigate to the component's <b>Collision</b> and set the <b>Collision Preset</b> to <code>Custom</code>, making sure it only <b>blocks</b> your <b>projectile channel</b>, if any.</step>
    <tip>You might need to fine-tune your shield's collision settings, but as a general rule of thumb, you want it to <b>ignore</b> everything, <b>overlap</b> with any melee channels and <b>block</b> projectiles.</tip>
</procedure>

<procedure title="Configure the Equipment for the Shield" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>equipment data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Equipment Definition</b>.</step>
    <step>Name your new container asset <code>Equipment_Shield_Common</code> and open it.</step>
    <step>Add a new <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Activated</code>.</step>
    <step>In the <b>Activated</b> State Configuration, add a new entry to the <b>Actors</b> array. Set <code>BP_Weapon_Shield</code> to the <b>Actor Class</b>.</step>
    <step>Set <code>Equipment.Slot.OffHand</code> to the <b>Slot Tag</b>.</step>
    <step>Add another <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Deactivated</code>.</step>
    <step>In the <b>Deactivated</b> State Configuration, add a new entry to the <b>Static Meshes</b> array. Set the Static Mesh that represents your shield to the <b>Mesh</b>.</step>
    <step>Set <code>Equipment.Slot.Back.Weapon.A.Left</code> to the <b>Slot Tag</b> and <code>sStoredWeaponA_Left</code> to the <b>SocketName</b></step>
</procedure>

<procedure title="Update your Shield Item" collapsible="true">
    <step>Open the <b>Shield Item</b> that was created <a href="inv_create_item.md">earlier</a>, and add an <b><a href="inv_equipment_fragment.md">Equipment Fragment</a></b></step>
    <step>Set the <code>Equipment_Shield_Common</code> to the <b>Equipment Data</b>.</step>
</procedure>

<procedure title="Update your Default Configuration" collapsible="true">
    <step>Open the <code>Pawn</code>, <code>Character</code> or <code>Player State</code> where your <code>Inventory Manager</code> is located.</step>
    <step>Navigate to the <code>Inventory Manager Component</code>, so you can see its <code>Default Values</code>.</step>
    <step>Remove the <b>Container Memory</b> that was added for both the <b>Sword</b> and the <b>Shield</b>. This will automatically place them in their preferred slots.</step>
</procedure>

<procedure title="Test the Results" collapsible="true">
    <step>Hit <b>Play</b>, open the <b>Gameplay Debugger</b>, activate the <b>Inventory</b> category and confirm that your Sword and Shield were assigned to their preferred containers.</step>
    <step>Also confirm that your Iron Bars were assigned to your <b>backpack</b>, and now they are in positions <b>0</b>, <b>1</b> and <b>2</b>.</step>
    <step>Confirm that the Equipment column shows <b>Deactivated</b> for your Sword and Shield and <b>N/A</b> for the Iron Bars.</step>
    <step>Press the key that was assigned to activate your abilities and the correct <b>Equip Animation Montage</b> should play. The Equipment column for the weapons should eventually show <b>Activated</b>.</step>
    <step>Press the key again and the correct <b>Store Animation Montage</b> should play. The Equipment column for the weapons should eventually show <b>Deactivated</b>.</step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_equipment.md" summary = "More details about objects related to the equipment.">Equipment, States and Actors</a>
        <a href="inv_equipment_manager.md" summary = "Equipment Manager and its functionalities.">Equipment Manager</a>
        <a href="inv_debugger_and_logs.md" summary = "Using the Inventory Gameplay Debugger and accessing logs.">Debugger and Logs</a>
        <a href="ipt_overview.md" summary = "Using the Ninja Input to trigger abilities.">Ninja Input</a>
        <a href="cbt_overview.md" summary = "Using the Ninja Combat to handle Melee Scans.">Ninja Combat</a>
    </category>
</seealso>
