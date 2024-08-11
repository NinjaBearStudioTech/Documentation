# Activate Equipment via Inventory Abilities
<primary-label ref="inventory"/>
<secondary-label ref="how-to"/>

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

<procedure title="Create the Sword Actor" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>blueprint</b> folder.</step>
    <step>Create a new <b>Blueprint</b> using <code>NinjaEquipmentActor</code> as the parent. Name it <code>BP_Weapon_Sword</code></step>
    <step>Add a new <b>Static Mesh Component</b> and set your Sword's mesh to it.</step>
    <step>Navigate to the component's <b>Collision</b> and set the <b>Collision Preset</b> to <code>No Collision</code>.</step>
    <tip>For your <b>Melee Weapons</b> you probably want to use some sort of <b>scan</b> to detect hits. Please take check <a href = "cbt_overview.md">Ninja Combat</a>, as it can help you with that!</tip>
</procedure>

<procedure title="Configure the Equipment for the Sword" collapsible="true">
    <step>Add a new <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Activated</code>.</step>
    <step>In the <b>Activated</b> State Configuration, add a new entry to the <b>Actors</b> array. Set <code>BP_Weapon_Sword</code> to the <b>Actor Class</b>.</step>
    <step>Set <code>Equipment.Slot.MainHand</code> to the <b>Slot Tag</b>.</step>
</procedure>

<procedure title="Create the Shield Actor" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>blueprint</b> folder.</step>
    <step>Create a new <b>Blueprint</b> using <code>NinjaEquipmentActor</code> as the parent. Name it <code>BP_Weapon_Shield</code></step>
    <step>Add a new <b>Static Mesh Component</b> and set your Shield's mesh to it.</step>
    <step>Navigate to the component's <b>Collision</b> and set the <b>Collision Preset</b> to <code>Custom</code>, making sure it only <b>blocks</b> your <b>projectile channel</b>, if any.</step>
    <tip>You might need to fine-tune your shield's collision settings, but as a general rule of thumb, you want it to <b>ignore</b> everything, <b>overlap</b> with any melee channels and <b>block</b> projectiles.</tip>
</procedure>

<procedure title="Configure the Equipment for the Shield" collapsible="true">
    <step>Add a new <b>State Configuration</b> and set the <b>State Tag</b> to <code>Equipment.State.Activated</code>.</step>
    <step>In the <b>Activated</b> State Configuration, add a new entry to the <b>Actors</b> array. Set <code>BP_Weapon_Shield</code> to the <b>Actor Class</b>.</step>
    <step>Set <code>Equipment.Slot.OffHand</code> to the <b>Slot Tag</b>.</step>
</procedure>