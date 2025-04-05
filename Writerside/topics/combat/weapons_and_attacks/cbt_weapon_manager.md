# Weapon Manager
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Actor Component that manages weapons available to a combatant.</li>
        <li>Should be added to any character that can hold a weapon at any moment.</li>
        <li>Has an extensible class hierarchy to support specific project needs.</li>
        <li>Bridge used for the Combat/Inventory integration.</li>
    </ul>
</tldr>

This page provides information about the **Weapon Manager**, the most important combat component, after the **Combat
Manager**. 

## Class Hierarchy
The **Weapon Manager** is a common extension target, so it is built with a class hierarchy designed to accommodate this 
requirement. 

### Weapon Manager Interface
The Weapon Manager is defined by the **Weapon Manager Interface** (`CombatWeaponManagerInterface`). It defines a single
function, `GetWeapon`, used by other classes to obtain a weapon using a **Gameplay Tag Query**. Any **Actor Component** 
implementing this interface is considered a **valid Weapon Manager** in the system.

### Base Weapon Manager Component
This **abstract class** can be used as a base class for Blueprint or C++ implementations. It is useful to define a character
hierarchy that requires different weapon managers for different character types. A common example is:

- An **abstract character class** defining the Weapon Manager using this base class.
- An **AI subclass** using a simpler version of the Weapon Manager, such as the **Default Weapon Manager**.
- A **player subclass** using a more complex version of the Weapon Manager, such as the **Equipment Weapon Manager**, to integrate with an Inventory System.  

### Default Weapon Manager Component
This **concrete implementation** is the main version provided by the framework that can be used for common combat 
requirements or as a base for more complex weapon management requirements.

## Setup
To configure the **Default Weapon Manager**, you need to create the weapon sockets in your character mesh, add the
component to your character and configure the weapon class/socket mapping.

<procedure title="Configuring Weapon Sockets" collapsible="true" default-state="expanded">
    <step>
        <p>Open the <b>Skeletal Mesh</b> used by the <b>Combat Mesh</b> in your character Blueprint.</p>
        <tip>In <b>Runtime Retargeting</b> scenarios, make sure to select the <b>Combat Mesh</b> (visible mesh).</tip>
    </step>
    <step>Navigate to the bones where your weapons should be attached, such as the <b>hand bones</b>.</step>
    <step>Create all necessary sockets, such as <code>sSword</code>, <code>sShield</code> and so on, adjusting their locations and rotations.</step>
</procedure>

<procedure title="Configuring the Weapon Manager" collapsible="true" default-state="expanded">
    <step>
        <p>In your <b>combatant Blueprint</b>, add a new <b>Default Weapon Manager Component</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="cbt_wpatk_weapon_manager_component.png" alt="Adding the Weapon Manager Component" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p><b>Header</b></p>
                <code-block lang="c++" src="cbt_setup_weapon_manager_component.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="cbt_setup_weapon_manager_component.cpp"/>
            </tab>
        </tabs>
    </step>
    <step>Implement the <code>GetWeaponManager</code> function, from the <code>Combat System Interface</code>, returning this component.</step>
    <step>
        <p>Navigate to the component's <b>Defaults Panel</b> and map all weapon classes to their sockets.</p>
        <img src="cbt_wpatk_weapon_manager_defaults.png" alt="Add Default Weapons" border-effect="line"/>
    </step>
    <step>Optionally, add any default <b>Weapon Classes</b> that should be added to the character by default.</step>
</procedure>

## Managing Weapons
The **Weapon Manager Interface** and the **Default Weapon Manager Component** provide functions that you can use to 
retrieve and manage weapons. 

### Get Weapon
The `GetWeapon` function, provided by the `CombatWeaponManagerInterface` is available to any valid implementation and
can be used to retrieve any weapons by the matching **Weapon Tags**, from the **[Weapon Interface](cbt_weapon_actors.md)**.

### Default Weapons 
You can add default weapon classes that will be instantiated when the Weapon Manager initializes. These weapon classes 
will be automatically attached to the sockets they are mapped to.

### Automatic Detection
Weapon Actors that are deliberately spawned and attached to the combatant can be detected and registered by the Weapon
Manager. For that, you need to call `FindAttachedWeapons`.

<img src="cbt_wpatk_weapon_manager_scan.png" alt="Automatic Weapon Detection" border-effect="line" thumbnail="true"/>

### Add and Remove Weapons
You can **add** and **remove** weapons using the Default Weapon Manager, using the following functions.

| Function              | Purpose                                                                          |
|-----------------------|----------------------------------------------------------------------------------|
| `AddWeapon`           | Adds a new **weapon instance** and attaches it to the pre-defined class socket.  |
| `AddWeaponClass`      | Instantiates a **weapon class** and attaches it to the pre-defined class socket. |
| `RemoveWeapon`        | Removes a **weapon instance** from the weapon collection.                        |
| `RemoveWeaponByQuery` | Removes a **weapon instance** returned by the `GetWeapon` function.              |

## Inventory Integration
The **Weapon Manager** is the perfect bridge to integrate the Combat System with an Inventory Manager. To learn how to 
integrate with **[](inv_overview.md)**, see the **[](cbt_integration_inventory.md)** guide. 