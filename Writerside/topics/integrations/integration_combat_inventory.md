# Combat and Inventory
<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="inventory-sec"/>

[**Ninja Combat**](cbt_overview.md) can defer [**Weapon Management**](cbt_concept_weapon_management.md) and [**Ammo Management**](cbt_concept_firearms.md)
to [**Ninja Inventory**](inv_overview.md). You can also create **custom fragments** that define weapon behavior,
such as **weapon damage**, **critical hit chance and bonus**, **fire rate**, **ammo capacity**, and so on.

This integration is automatically enabled when both plugins are available and active in the project, regardless of whether
they are installed locally or in the engine. 

Once set up:

- Weapon spawning, attachment, features, and configuration are handled by the **Inventory system**.
- The Combat system **no longer directly manages weapons**. Instead, it requests the correct weapon actor for each equipment slot.
- You can define **weapon-specific behavior** through **item fragments**, such as gameplay elements, dynamic attributes, off-hand attachments, and so on.

## Weapon Manager

Ninja Combat uses a **Weapon Manager** to retrieve weapons available to a combatant. With Ninja Inventory, this responsibility
is assigned to the Inventory Manager, and the Weapon Manager simply forwards requests to it.

Instead of adding the usual `NinjaCombatWeaponManagerComponent`, use the equipment-aware variant,
`NinjaCombatEquipmentAdapterComponent`. This version implements `CombatWeaponManagerInterface`, as expected by Ninja Combat,
but forwards requests to an **Equipment Manager** that should also be present in the character.

Make sure to return the correct component from `GetWeaponManager`, in the **Combat System Interface**.

<procedure title="Configure the Equipment Weapon Manager" collapsible="true" default-state="expanded">
    <step>Add the <b>Equipment Manager</b>, <code>NinjaEquipmentManagerComponent</code>, to your character. Check the <a href="inv_equipment_management.md"><b>Equipment Management</b></a> documentation for additional details.</step>
    <step>
        <p>Add the <b>Equipment Weapon Adapter</b>, <code>NinjaCombatEquipmentAdapterComponent</code>, to your character. Check the <a href="cbt_concept_weapon_management.md"><b>Weapon Management</b></a> documentation for additional details.</p>
        <note>
            <p><b>Do Not Duplicate Weapon Managers</b></p>
            <p>If you are using the Equipment Adapter component, make sure that no other Weapon Manager component is active on your character.</p>
        </note>
    </step>
    <step>Return the new <b>Equipment Adapter Component</b> from <code>GetWeaponManager</code>, which is a function from <code>CombatSystemInterface</code>.</step> 
</procedure>

## Weapon Actor

Weapon Actors can also benefit from a closer integration with Ninja Inventory. Specifically, they can access the
**Equipment Instance** that contains relevant item data, such as the **Item Instance and its Fragments**. This is exposed
by the `NinjaEquipmentActorComponent`, which is added to each actor used as an **Equipment Presence**.

To leverage this, either use `ANinjaCombatEquipmentWeaponActor` as your base **Weapon Class**, or add
`NinjaEquipmentActorComponent` to your own Weapon Actor hierarchy. Keep in mind that the provided base class includes
additional features, such as using the **Item Level** as the **Weapon Level** when applying Gameplay Effects.

> **Weapon Tags**
>
> When using the default Weapon Manager and Weapon Actor, weapons are identified by tags set in the Weapon Actor itself.
>
> However, when weapons are managed by the Inventory, the identifying tags are set in the **Item Data Asset**, and tags
> added to the actor are no longer used.

<procedure title="Create Inventory Weapons" collapsible="true" default-state="expanded"> 
    <step>
        <p>For your weapon actors, use <code>NinjaCombatEquipmentWeaponActor</code> as your base class.</p>
        <note>
            <p><b>Different Class Hierarchies</b></p>
            <p>If you cannot use the provided base class in your hierarchy, add <code>NinjaEquipmentActorComponent</code> to your own base Weapon Actor class or Blueprint.</p>
        </note>
    </step>
    <step>Create a new <b>Item Definition</b> for your weapon. Check the <a href="inv_inventory_items.md"><b>Inventory Items</b></a> documentation for additional details.</step>
    <step>Add an <b>Equipment Fragment</b> to your Item Definition and configure the <b>Equipped State</b>, at minimum.</step>
    <step>
        <p>Set the <b>Equipment Type</b> to <b>Actor</b> and set the Weapon Actor as the <b>Actor Class</b>.</p>
        <note>
            <p><b>Weapons are always Equipment Instances</b></p>
            <p>Weapons are always implemented as <b>Equipment Actors</b>, as they represent items with <b>physical presence</b> and <b>dedicated in-world logic</b>.</p>
        </note>
    </step>
</procedure>

## Ammo Storage

Similar to the **Weapon Manager**, Ninja Combat uses an **Ammo Storage** component to manage ammunition for firearms
during reloads. When using Ninja Inventory, ammo can be managed using **Item Stacks**.

Instead of using the default `NinjaCombatAmmoStorageComponent`, use `NinjaCombatInventoryAmmoAdapterComponent` and set
its `AllAmmoTypesQuery` to a query that covers all items that represent ammo. For example, if your ammo items use
identification tags such as `Item.Type.Ammo.Rifle` and `Item.Type.Ammo.Shotgun`, set this query to find `Item.Type.Ammo`.

<procedure title="Configure the Ammo Storage" collapsible="true" default-state="expanded">
    <step>
        <p>Add the <b>Ammo Storage Adapter</b>, <code>NinjaCombatInventoryAmmoAdapterComponent</code>, to your character. Check the <a href="cbt_concept_firearms.md"><b>Firearms</b></a> documentation for additional details.</p>
        <note>
            <p><b>Do Not Duplicate Ammo Storages</b></p>
            <p>If you are using the Ammo Adapter component, make sure that no other Ammo Storage component is active on your character.</p>
        </note>
    </step>
    <step>Configure the Adapter's <code>AllAmmoTypesQuery</code> property to catch all ammo types in your Inventory.</step>
    <step>Create Inventory Items representing <b>Ammunition</b>, including a <b>Stack Fragment</b> set to be <b>observable</b>. This allows you to get a <b>global count</b> in addition to the per-stack count.</step>
    <step>Create Inventory Items representing <b>Firearms</b>, including a <b>Firearm Component</b>, which provides specialized ammo functions.</step>
</procedure>

## Item Fragments

Multiple Item Fragments can be used to enhance weapons in many ways.

| Fragment           | Description                                                                                                |
|--------------------|------------------------------------------------------------------------------------------------------------|
| Firearm            | Identifies a firearm and becomes aware of compatible ammo.                                                 |
| Equipment          | Configures an actor presence for a weapon, which can be used as the Weapon Actor.                          |
| Offhand Position   | Allows two-handed weapons to properly place the off-hand.                                                  |
| Dynamic Attributes | Can be used to set magnitudes for weapons, such as damage, critical hit chance, and critical damage bonus. |

When using **Dynamic Attributes** in your weapons, override `GetAdditionalCombatMagnitudes`, from `CombatMagnitudeProviderInterface`,
to expose your dynamic attributes, such as Damage and Critical Hit Chance, using the proper data tags.