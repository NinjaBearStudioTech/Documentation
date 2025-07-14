# Inventory Integration
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Use <code>NinjaCombatEquipmentWeaponActor</code> (or a subclass) to represent weapons as inventory equipment.</li>
        <li>Add <code>NinjaCombatEquipmentAdapterComponent</code> to your character to bridge inventory and combat systems.</li>
        <li>Replace the <b>default Weapon Manager</b> to ensure equipped items are used correctly in combat.</li>
    </ul>
</tldr>

Combat and Inventory can be integrated through the **Weapon Manager** and **Weapon Actors**. This integration is provided 
by Ninja Combat and is automatically enabled when Ninja Inventory is present in one of the following ways:

1. Both plugins are installed in the engine (default behavior when using the **Epic Launcher**).
2. Both plugins are installed in the project under `[Project]/Plugins/NinjaBearStudio`.

## Weapons and Equipment

Weapons are defined by Ninja Combat but can be seamlessly integrated with Ninja Inventory as **Equipment Actors**.

The Inventory System does not impose a hierarchy requirement on **Equipment Actors**. However, it expects the actor to 
include an **Actor Component** that implements the `EquipmentActorInterface`. This allows the actor to receive and store 
information about its **backing equipment instance**.

To simplify this integration, Ninja Combat includes a base actor class: `NinjaCombatEquipmentWeaponActor`. This class 
extends the default **Combat Weapon** and includes an **Equipment Receiver** component that handles equipment data.

You can create your own weapon actors by subclassing this base class (or your own variant) and using them as the actor 
representation for **equipped** equipment instances.

Here are some specific aspects of the provided **Equipment Weapon Actor**:

- Supports using an **Item Level Fragment** to determine the Equipment Level, which is used by Combat Hit Effects.
- Uses the **Inventory Avatar** as the **Weapon Owner**, ensuring proper integration with owner-dependent systems like Gameplay Effects or Targeting.

> **Custom Weapon Class**
>
> It's recommended to create your own subclass of `NinjaCombatEquipmentWeaponActor` to keep a clean separation between 
> plugin logic and game-specific behavior. This also gives you room to add features unique to your weapon system.
{style="tip"}

## Weapon Manager

The integration also provides a custom **Weapon Manager Component**, `NinjaCombatEquipmentAdapterComponent`, which 
implements the `CombatWeaponManagerInterface`.

This component **replaces** the default Weapon Manager. It should be added to the character that owns the inventory and 
returned through the `CombatSystemInterface`.

<procedure title="Using the Equipment Weapon Manager" collapsible="true">
    <step>Add the component to your character. Search for <b>Equipment Adapter</b> and add it. In this example, we'll name it <b>Equipment Weapon Manager</b>.</step>
    <step>Update your <b>Combat System Interface</b> implementation to return this new component as the Weapon Manager.</step>
    <tabs group="sample">
        <tab title="Blueprint" group-key="bp">
            <p>Adding the Equipment Weapon Manager:</p>
            <img src="cbt_integration_inventory_weapon_manager_add.png" alt="Add Weapon Manager" thumbnail="true"/>
            <p>Updating the Combat System Interface:</p>
            <img src="cbt_integration_inventory_weapon_manager_interface.png" alt="Combat System Interface" thumbnail="true"/>
        </tab>
        <tab title="C++" group-key="cpp">
            <code-block lang="c++" src="cbt_integration_inventory_weapon_manager.h"/>
            <br/>
            <code-block lang="c++" src="cbt_integration_inventory_weapon_manager.cpp"/>
        </tab>
    </tabs>
</procedure>

> **Avoid Weapon Manager Duplicates**  
> If you're using the Equipment Weapon Manager, make sure to **remove** the default Weapon Manager to prevent conflicts.
{style="note"}
