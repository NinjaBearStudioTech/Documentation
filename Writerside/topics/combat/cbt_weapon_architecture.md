# Weapon Architecture
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Weapons are represented by <b>Actors</b> implementing <code>CombatWeaponInterface</code>.</li>
        <li>Can become <b>Melee</b> and <b>Ranged</b> weapons via the appropriate interfaces.</li>
        <li>Weapons are assigned to the <b>Weapon Manager</b>, used by the Combat System to query for them via <b>Gameplay Tag Queries</b>.</li>
        <li>The <b>Weapon Manager</b> is an <b>Actor Component</b> implementing <code>NinjaCombatWeaponManagerComponent</code>.</li>
        <li>The Combat System provides base classes for Weapons and the Weapon Manager. It also provides versions compatible with <b>Ninja Inventory</b>.</li>
    </ul>
</tldr>

## Weapon Actor

**Weapon** are a **core component** in the Combat System. They are **Actors** that can perform important combat tasks
such as **Melee Scans** or **Launch a Projectile**.

### Weapon Interface

A Weapon is defined by the **Weapon Interface** (`CombatWeaponInterface`), a straightforward API that requires the weapon 
to identify itself using **Gameplay Tags**. This tagging system allows the **Weapon Manager** to locate weapons efficiently.

Gameplay Tags ensure that weapons can be easily categorized and accessed by the **Weapon Manager**, providing flexibility 
in how they are described, identifying **usage scenarios** or other **relevant traits**.

> **Melee and Ranged Weapons**
> 
> **Melee** or **Ranged** behaviors are introduced by other interfaces. This separation exists to allow such behaviors 
> to be added to **Weapons** and also **Combatants**.
> 
> For more information about these interfaces, please take a look at their dedicated pages.

### Default Weapon Actor

You can start implementing your weapons using the provided **Weapon Actor** (`ANinjaCombatWeaponActor`). It implements
the required **Weapon Interface**, exposing the **Gameplay Tag Container** so it can be easily configured in the **Details
Tab**, and it also provides the following features:

- It is compatible with the **[Actor Pool](cbt_actor_pooling.md)**.
- Can be immediately used as a **Melee Weapon**, a **Ranged Weapon** or **both**.
- Has a **Scene Component** as **Root**, but has no other component structure.

While using this actor, you will most likely set a **Static or Skeletal Mesh Component** that represents the weapon.
This actor can **automatically** identify the Mesh Component as the **Melee** or **Projectile** source if the component
is tagged:

- For a **Melee Source**, the Mesh Component should be tagged with `Combat.Component.MeleeScanSource`.
- For a **Projectile Source**, the Mesh Component should be tagged with `Combat.Component.ProjectileSource`.

Alternatively, if you need more **flexibility**, you can override the following functions instead, and provide any Mesh
Component that you need.

- `GetMeleeMesh` is used when a Mesh Component is required for **Melee Scans**.
- `GetProjectileSourceMesh` is used when a Mesh Component is required as a **Projectile source point**.

> **Component Tags or Function Overrides?**
> 
> The Component Tag Lookup happens on **Begin Play** and caches the Mesh Components, so they won't be accessed on every
> request. 
> 
> You only need to override these functions if you need to provide a Mesh Component based on **dynamic conditions**,
> specific for certain weapon types.

### Equipment Weapon Actor

**[Ninja Inventory](inv_overview.md)** provides an **Equipment Module** that represents **Items**, like **Weapons**, in
the world.

The Combat System is able to detect if you have the Inventory System in your project. If so, then the **Equipment Weapon 
Actor** will become available. It can be used as a base class to create **weapon equipment**.

An **Equipment Weapon Actor** (`ANinjaCombatEquipmentWeaponActor`) has the following characteristics:

- It is compatible with the **Equipment Weapon Manager**.
- It is visible to the **[Equipment Manager](inv_equipment_manager.md)**, since it implements `IEquipmentActorInterface`.
- It will be used by the Equipment System as an **Effect Causer**, which is the Actor used as the **Cause** of an effect applied to target. 
- Can use the **[Item Level](inv_level_fragment.md)** as the Effect Level for Melee Hit Gameplay Effects.

The **Weapon Manager** Component is responsible for providing all weapons currently **available** to a _Combatant_ Pawn
or Character.

The Combat System does not interact with this component directly. Instead, it will use the `CombatWeaponManagerInterface`,
which is implemented by the base component provided by the framework. This interface allows the Combat System to identify
weapons based on its **Gameplay Tags**.

## Weapon Manager

The **Weapon Manager** Component is responsible for providing all weapons currently **available** to a _Combatant_ Pawn
or Character.

### Weapon Manager Interface

This interface is used by the Combat System to find the **Source Weapon** for weapon-based actions, such as **Melee
Scans** or **Launching Projectiles**.

It provides a single function, `GetWeapon`, which will obtain a specific **Weapon Actor** from a **Gameplay Tag Query**.

You can create a custom Weapon Manager starting from a basic Actor Component, as long as the expected interface is  
properly implemented. The Combat System provides two implementations that you can use.

### Default Weapon Manager

The Combat System provides a **Default Weapon Manager**, which can be used for basic scenarios, such as Combatant with
fixed weapons. It will still allow you to change registered weapons, but might not scale well for complex scenarios
where the Combatant may have multiple dynamic weapons, as that would be the role of an **Inventory Manager**.

The Default Weapon Manager can **register weapons** in three different ways, which are **exclusive to it** and not part
of the Weapon Manager Interface.

To use the default Weapon Manager, add `NinjaCombatWeaponManagerComponent` to your Combatant Pawn or Character.

#### Add Weapons By Class

Adding weapons by their classes is the most common way to register weapons, especially in a scenario where the Combatant
will not switch weapons frequently. They can be added in the component's **Details Tab**, in the **Default Weapon Classes**
array.

You can correlate Weapon Classes with specific **Sockets** on the owner's Skeletal Mesh. Once a Weapon Actor is spawned,
it will be automatically attached to the socket that matches its class, in the Skeletal Mesh Component set as the
**Combat Mesh**.

The following image shows how to add default weapons by their class.

<img src="cbt_weapon_manager_defaults.png" alt="Add Default Weapons By Class" border-effect="line"/>

#### Automatic Detection

Weapon Actors that are deliberately spawn and attached to the Combatant can be detected and registered by the Weapon
Manager. For that, you need to call the `FindAttachedWeapons`, after all your actors have been manually instantiated and
attached.

The following image shows how to automatically detect weapons attached to the Combatant.

<img src="cbt_weapon_manager_scan.png" alt="Automatic Weapon Detection" border-effect="line" thumbnail="true"/>

#### Manual Registering

The Weapon Manager also allow weapons to be **added** and **removed** via the respective `AddWeapon` and `RemoveWeapon`
functions. This method is useful if you manage and create Weapon Actors outside the Weapon Manager. Weapons added using
this method will also be matched with the **Socket Mapping** configuration.

The following image shows how to add weapons that are instantiated, but not already attached.

<img src="cbt_weapon_manager_add.png" alt="Adding external Weapon Actors" border-effect="line" thumbnail="true"/>

### Equipment Weapon Manager

**[Ninja Inventory](inv_overview.md)** supports complex item and equipment management, including asset loading and
attachment. If your game allows multiple weapons to be equipped, then you can delegate all your weapon management to the
Inventory System.

The Combat System is able to detect if you have the Inventory System in your project. If so, then the **Equipment Adapter
Component** will become available, and can be used to retrieve **Weapon Actors** from the **Inventory System**. 

Items must adhere to the following criteria:

- The **[Equipment Manager](inv_equipment_manager.md)** can find a match for the **Weapon Query**.
- The **Equipment Instance** has an actor marked as an **[Effect Causer](inv_equipment.md)**.

Add `UNinjaCombatEquipmentAdapterComponent` to your Combatant Pawn or Character to enable the integration. Make sure
to remove the **Default Weapon Manager** if you added it before, since this adapter is a **replacement for it**.

## Weapon Cosmetics Component

This additional Component is responsible for handling usual cosmetics for Weapons, such as **Particles**, **Sounds** 
and **Camera Shakes**. It is added by default to all **Weapons**.

<seealso style="cards">
    <category ref="related">
        <a href="cbt_melee_combat.md" summary="Melee weapons and Melee Scans.">Melee Combat</a>
        <a href="cbt_ranged_combat.md" summary="Ranged weapons and Projectiles.">Ranged Combat</a>
    </category>
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine" summary="Official documentation for Gameplay Ability System.">Gameplay Ability System</a>
        <a href="https://github.com/tranek/GASDocumentation" summary="Dan Tranek's excellent documentation on G.A.S.">Dan Tranek's GAS Documentation</a>
    </category>
</seealso>
