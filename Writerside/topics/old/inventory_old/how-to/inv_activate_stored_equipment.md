# Activate Equipment via Inventory Abilities
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

This how-to guide will expand on the **Equipment Definition** setup, enabling weapons to be activated.

## Part 1: Configuring the Equipment

In this first part, you will create **Actors** to represent the **Active Equipment** and update the previously created
Equipment Definitions to support the **Activated** state.

<procedure title="Create the Sword Actor" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>Blueprint</b> folder.</step>
    <step>Create a new <b>Blueprint</b> using <code>NinjaEquipmentActor</code> as the parent. Name it <code>BP_Weapon_Sword</code>.</step>
    <step>Add a new <b>Static Mesh Component</b> and set your Sword's mesh to it.</step>
    <step>Navigate to the component's <b>Collision</b> settings and set the <b>Collision Preset</b> to <code>No Collision</code>.</step>
    <tip>For <b>Melee Weapons</b>, you might want to use some sort of <b>scan</b> to detect hits. Please refer to <a href="cbt_overview.md">Ninja Combat</a> for more information.</tip>
</procedure>

<procedure title="Create the Shield Actor" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>Blueprint</b> folder.</step>
    <step>Create a new <b>Blueprint</b> using <code>NinjaEquipmentActor</code> as the parent. Name it <code>BP_Weapon_Shield</code>.</step>
    <step>Add a new <b>Static Mesh Component</b> and set your Shield's mesh to it.</step>
    <step>Navigate to the component's <b>Collision</b> settings and set the <b>Collision Preset</b> to <code>Custom</code>, ensuring it only <b>blocks</b> your <b>projectile channel</b>, if applicable.</step>
    <note>You may need to fine-tune your shield's collision settings, but as a general rule, set it to <b>ignore</b> most channels, <b>overlap</b> with melee channels, and <b>block</b> projectiles.</note>
</procedure>

<procedure title="Configure the Equipment for the Sword" collapsible="true">
    <step>Add a new <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Activated</code>.</step>
    <step>In the <b>Activated</b> State Configuration, add a new entry to the <b>Actors</b> array. Set <code>BP_Weapon_Sword</code> as the <b>Actor Class</b>.</step>
    <step>Set <code>Equipment.Slot.MainHand</code> as the <b>Slot Tag</b>.</step>
    <note>You can add more elements to the state, such as <b>Attack Abilities for the sword</b>, <b>relevant Gameplay Effects</b>, <b>Animation Layers</b>, and more.</note>
</procedure>

<procedure title="Configure the Equipment for the Shield" collapsible="true">
    <step>Add a new <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Activated</code>.</step>
    <step>In the <b>Activated</b> State Configuration, add a new entry to the <b>Actors</b> array. Set <code>BP_Weapon_Shield</code> as the <b>Actor Class</b>.</step>
    <step>Set <code>Equipment.Slot.OffHand</code> as the <b>Slot Tag</b>.</step>
    <note>You can add more elements to the state, such as <b>Attack Abilities for the shield</b>, <b>relevant Gameplay Effects</b>, <b>Animation Layers</b>, and more.</note>
</procedure>

<procedure title="Configure Virtual Slots in your Equipment Manager" collapsible="true">
    <step>Go to your character's <b>Equipment Manager</b> and configure the following <b>Virtual Slots</b>:</step>
    <step>Create a <b>Main Hand</b> Slot by mapping the Gameplay Tag <code>Equipment.Slot.MainHand</code> to the <code>sSword_RH</code> socket.</step>
    <step>Create an <b>Offhand</b> Slot by mapping the Gameplay Tag <code>Equipment.Slot.OffHand</code> to the <code>sShield_LH</code> socket.</step>
    <step>
        <p>When you are done, your Equipment Manager configuration should look like this:</p>
        <img src="inv_activate_equipment_virtual_sockets.png" alt="Virtual Sockets for Equipment" border-effect="line"/>
    </step>
</procedure>

## Part 2: Configuring the Gameplay

In this second part, you will configure the **Animations**, **Abilities**, and **Input** to enable equipment to be
**equipped** and **stored**.

<procedure title="Configure your Animation Montages" collapsible="true">
    <step>Select the <b>Animation Sequence</b> representing the <b>Activate</b> action. Create an <b>Animation Montage</b> from it and name it <code>M_WeaponAndShield_Equip</code>.</step>
    <step>Open your Animation Montage and add the <b>Send Equipment Event Animation Notify</b> to the frame where the <b>Sword</b> should be equipped.</step>
    <step>In the Notify, set the <b>Event Tag</b> to <code>Inventory.Event.Animation.Activate</code> and add <code>Inventory.Item.Weapon.Sword</code> to the <b>Equipment Tags</b>.</step>
    <step>Add another Notify to the frame where the <b>Shield</b> should be equipped.</step>
    <step>In the Notify, set the <b>Event Tag</b> to <code>Inventory.Event.Animation.Activate</code> and add <code>Inventory.Item.Weapon.Shield</code> to the <b>Equipment Tags</b>.</step>
    <step>Repeat these steps to create another <b>Animation Montage</b> named <code>M_WeaponAndShield_Store</code>, representing the <b>Deactivate</b> event. In the Animation Notify, set the <b>Event Tag</b> to <code>Inventory.Event.Animation.Deactivate</code>.</step>
    <note>If both weapons should be equipped or stored at the same frame, you can add a single <b>Animation Notify</b> with both tags in the <b>Equipment Tags</b> container.</note>
</procedure>

<procedure title="Configure the Animation Table" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>data folder</b> and create a new <b>Data Table</b> using <code>InventoryAnimationTableRow</code> as the <b>Row Structure</b>. Name it <code>TB_Inventory_Animations</code>.</step>
    <step>Open your new Data Table and add a new row. Set the <b>Montage To Play</b> to <code>M_WeaponAndShield_Equip</code>.</step>
    <step>
        <p>Set the <b>Montage Query</b> to be compatible with an <b>Activation</b> event involving a <b>shield</b> and other <b>one-handed weapons</b>.</p>
        <img src="inv_create_equipment_query_anim_equip.png" alt="Equip Weapon Montage Query" border-effect="line"/>
    </step>
    <step>Add another row and set the <b>Montage To Play</b> to <code>M_WeaponAndShield_Store</code>.</step>
    <step>
        <p>Set the <b>Montage Query</b> to be compatible with a <b>Deactivation</b> event involving a <b>shield</b> and other <b>one-handed weapons</b>.</p>
        <img src="inv_create_equipment_query_anim_store.png" alt="Store Weapon Montage Query" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create the Activate Equipment Ability" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>ability folder</b> and create a new <b>Gameplay Ability</b> using <code>InventoryAbility_ActivateEquipment</code> as the parent. Name it <code>GA_Equip_PrimaryItems</code>.</step>
    <step>
        <p>Open your new ability and configure the <b>Equipment Query</b> as shown below:</p>
        <img src="inv_create_equipment_query_ability_equip_query.png" alt="Equip Weapon Ability Query" border-effect="line"/>
    </step>
    <step>Set <code>TB_Inventory_Animations</code> as the <b>Montage Table</b> and choose <code>Wait For Gameplay Event</code> as the <b>Animation Strategy</b>.</step>
    <step>Add <code>Ability.Equipment.Primary.Activate</code> to the <b>Ability Tags</b>.</step>
    <step>
        <p>When you are done, your Ability should look like this:</p>
        <img src="inv_create_equipment_query_ability_equip.png" alt="Equip Weapon Ability" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create the Deactivate Equipment Ability" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>ability folder</b> and create a new <b>Gameplay Ability</b> using <code>InventoryAbility_DeactivateEquipment</code> as the parent. Name it <code>GA_Store_PrimaryItems</code>.</step>
    <step>
        <p>Open your new ability and configure the <b>Equipment Query</b> as shown below:</p>
        <img src="inv_create_equipment_query_ability_store_query.png" alt="Store Weapon Ability Query" border-effect="line"/>
    </step>
    <step>Set <code>TB_Inventory_Animations</code> as the <b>Montage Table</b> and choose <code>Wait For Gameplay Event</code> as the <b>Animation Strategy</b>.</step>
    <step>Add <code>Ability.Equipment.Primary.Deactivate</code> to the <b>Ability Tags</b>.</step>
    <step>
        <p>When you are done, your Ability should look like this:</p>
        <img src="inv_create_equipment_query_ability_store.png" alt="Store Weapon Ability" border-effect="line"/>
    </step>
</procedure>

<procedure title="Map your Inputs to Activate Abilities" collapsible="true">
    <step>Create an <b>Input Action</b> to <b>activate the Equipment</b>.</step>
    <step>Add the action to an <b>Input Mapping Context</b> assigned to the <b>Player Character</b> and map it to an appropriate key.</step>
    <step>
        <p>Create the Input Handling logic to activate the Equipment. For simplicity, it will attempt to activate both abilities, but the one with an invalid query result won't activate.</p>
        <img src="inv_activate_equipment_input_default.png" alt="Default input for activating equipment" border-effect="line"/>
    </step>
</procedure>

<procedure title="Test your Results and Check the Gameplay Debugger" collapsible="true">
    <step>
        <p>Hit the <b>Play</b> button and press the key you set to <b>activate the equipment</b>. Your animation should play, and the sword and shield should be <b>equipped</b>. Press the key again, and they should be <b>stored</b>.</p>
        <img src="inv_activate_equipment_results.gif" alt="Equip and Store weapons" border-effect="line"/>
    </step>
    <step>As you <b>equip and store</b> the weapons, notice that the <b>Equipment</b> column in the <b>Gameplay Debugger</b> will alternate between states.</step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_equipment.md" summary="More details about objects related to the equipment.">Equipment, States and Actors</a>
        <a href="inv_equipment_manager.md" summary="Equipment Manager and its functionalities.">Equipment Manager</a>
        <a href="inv_abilities.md" summary="Using the Gameplay Ability System with the Inventory.">Inventory Abilities</a>
    </category>
</seealso>
