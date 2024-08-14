# Weapon Manager
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Provides <b>active weapons</b> to the Combat System.</li>
        <li>Defined by <code>CombatWeaponManagerInterface</code>.</li>
        <li>The default implementation is <code>NinjaCombatWeaponManagerComponent</code>.</li>
        <li>The system also provides <code>NinjaCombatEquipmentWeaponManagerComponent</code> to integrate with <b>Ninja Inventory</b>.</li>
    </ul>
</tldr>

The **Weapon Manager** Component is responsible for providing all weapons currently **available** to a _Combatant_ Pawn
or Character.

The Combat System does not interact with this component directly. Instead, it will use the `CombatWeaponManagerInterface`, 
which is implemented by the base component provided by the framework. This interface allows the Combat System to identify
weapons based on its **Gameplay Tags**.

## Weapon Manager Interface

This interface is used by the Combat System to find the **Source Weapon** for weapon-based actions, such as **Melee 
Scans** or **Launching Projectiles**.

It provides a single function, `GetWeapon`, which will obtain a specific **Weapon Actor** from a **Gameplay Tag Query**.

You can create a custom Weapon Manager starting from a basic Actor Component, as long as the expected interface is  
properly implemented. The Combat System provides two implementations that you can use.

## Default Weapon Manager

The Combat System provides a **Default Weapon Manager**, which can be used for basic scenarios, such as Combatant with
fixed weapons. It will still allow you to change registered weapons, but might not scale well for complex scenarios
where the Combatant may have multiple dynamic weapons, as that would be the role of an **Inventory Manager**.

The Default Weapon Manager can **register weapons** in three different ways, which are **exclusive to it** and not part
of the Weapon Manager Interface.

To use the default Weapon Manager, add `NinjaCombatWeaponManagerComponent` to your Combatant Pawn or Character.

### Add Weapons By Class

Adding weapons by their classes is the most common way to register weapons, especially in a scenario where the Combatant
will not switch weapons frequently. They can be added in the component's **Details Tab**, in the **Default Weapon Classes**
array.

You can correlate Weapon Classes with specific **Sockets** on the owner's Skeletal Mesh. Once a Weapon Actor is spawned, 
it will be automatically attached to the socket that matches its class, in the Skeletal Mesh Component set as the 
**Combat Mesh**.

The following image shows how to add default weapons by their class.

<img src="cbt_weapon_manager_defaults.png" alt="Add Default Weapons By Class" border-effect="line"/>

### Automatic Detection

Weapon Actors that are deliberately spawn and attached to the Combatant can be detected and registered by the Weapon 
Manager. For that, you need to call the `FindAttachedWeapons`, after all your actors have been manually instantiated and
attached.

The following image shows how to automatically detect weapons attached to the Combatant.

<img src="cbt_weapon_manager_scan.png" alt="Automatic Weapon Detection" border-effect="line" thumbnail="true"/>

### Manual Registering

The Weapon Manager also allow weapons to be **added** and **removed** via the respective `AddWeapon` and `RemoveWeapon`
functions. This method is useful if you manage and create Weapon Actors outside the Weapon Manager. Weapons added using 
this method will also be matched with the **Socket Mapping** configuration.

The following image shows how to add weapons that are instantiated, but not already attached.

<img src="cbt_weapon_manager_add.png" alt="Adding external Weapon Actors" border-effect="line" thumbnail="true"/>

## Equipment Weapon Manager

**[Ninja Inventory](inv_overview.md)** supports complex item and equipment management, including asset loading and 
attachment. If your game allows multiple weapons to be equipped, then you can delegate all your weapon management to the 
Inventory System.

The Combat System is able to detect if you have the Inventory System in your project. If so, then the **Equipment Weapon 
Manager** will become available, and can be used to retrieve **Weapon Actors** from the **Inventory System**. 

Items must adhere to the following criteria:

- The **[Equipment Manager](inv_equipment_manager.md)** can find a match for the **Weapon Query**.
- The **Equipment Instance** has an actor marked as an **[Effect Causer](inv_equipment.md)**.

Add `NinjaCombatEquipmentWeaponManagerComponent` to your Combatant Pawn or Character to enable the integration.Make sure 
to remove the **Default Weapon Manager** if you added it before.
