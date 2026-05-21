# Weapon Actors
<primary-label ref="combat"/>

<tldr>
    <p><b>Summary: Creating Weapon Actors</b></p>
    <br/>
    <ul>
        <li>Weapon Actors are actors implementing <code>CombatWeaponInterface</code>.</li>
        <li>You can have <b>melee weapons</b>, <b>ranged weapons</b> and also <b>hybrid weapons</b>.</li>
        <li>You can also have a game without any weapon actors (i.e. hand-to-hand combat or weapons modeled with character meshes).</li>
        <li>Weapons are always used in conjunction with the <b>Weapon Manager</b>.</li>
    </ul>
</tldr>

This page provides information about **Weapon Actors**, which are used to apply or defend damage, in conjunction with
the **Weapon Manager** and **Gameplay Abilities**.

## Class Hierarchy
Weapons are the primary Actor introduced by Ninja Combat, so they are designed to be flexible and extensible.

### Weapon Interface
Ninja Combat recognizes weapons via the `CombatWeaponInterface`. This interface has relevant functions used to identify
the **weapon** and its **owner**.

| Function         | Description                                                               |
|------------------|---------------------------------------------------------------------------|
| `GetWeaponOwner` | Returns the **Actor** that owns this weapon.                              |
| `GetWeaponTags`  | Returns a **container of Gameplay Tags** that uniquely identify a weapon. |

> **Identifying Weapons**
> 
> The Gameplay Tags used to identify a weapon are not expected to do so globally. Instead, they are expected to uniquely
> identify a weapon in the current character's context, considering things like the **weapon type**, **current slot**,
> **equipment state**, and so on. 
{style=note}

### Default Weapon Actor
You can create your own actors implementing the **Weapon Interface**, or use the provided **Default Weapon Actor**
(`NinjaCombatWeaponActor`), which is a valid implementation for both **melee** and **ranged** weapons.

You may want to create your own base Weapon Blueprint or C++ class, extending the Default Weapon Actor, including some 
of your own defaults, such as the **mesh type** being used in your project and any other common logic that should be 
shared between all weapon actors.

<procedure title="Creating a melee weapon: the Sword" collapsible="true" default-state="expanded">
    <step>Create a new <b>Blueprint</b> based on <code>NinjaCombatWeaponActor</code> (or your base Weapon class).</step>
    <step>Add a <b>weapon mesh</b>, it can be a <b>Static or Skeletal Mesh Component</b>, depending on your weapon requirements.</step>
    <step><b>Disable the collisions</b> from the weapon mesh (or have that done in your base Weapon class).</step>
    <step>In the <b>Class Defaults</b> panel, add a Gameplay Tag that defines this weapon, such as <code>Inventory.Item.Type.Sword</code>.</step>
</procedure>

<procedure title="Creating a defensive weapon: the Shield" collapsible="true" default-state="expanded">
    <step>Create a new <b>Blueprint</b> based on <code>NinjaCombatWeaponActor</code> (or your base Weapon class).</step>
    <step>Add a <b>weapon mesh</b>, it can be a <b>Static or Skeletal Mesh Component</b>, depending on your weapon requirements.</step>
    <step><b>Disable the collisions</b> from the weapon mesh (or have that done in your base Weapon class).</step>
    <step>In the <b>Class Defaults</b> panel, add a Gameplay Tag that defines this weapon, such as <code>Inventory.Item.Type.Shield</code>.</step>
</procedure>

<procedure title="Creating a ranged weapon: the Rifle" collapsible="true" default-state="expanded">
    <step>Create a new <b>Blueprint</b> based on <code>NinjaCombatWeaponActor</code> (or your base Weapon class).</step>
    <step>Add a <b>weapon mesh</b>, it can be a <b>Static or Skeletal Mesh Component</b>, depending on your weapon requirements.</step>
    <step><b>Disable the collisions</b> from the weapon mesh (or have that done in your base Weapon class).</step>
    <step>In the <b>Class Defaults</b> panel, add a Gameplay Tag that defines this weapon, such as <code>Inventory.Item.Type.Rifle</code>.</step>
</procedure>

> **Base Weapon Class**
>
> It's highly recommended creating a **base weapon class or blueprint** containing any additional components, properties and logic.
> You can use `NinjaCombatWeaponActor` as a base class or, if you have a different class hierarchy, implement the appropriate interfaces.
{style="note"}

> **Melee and Ranged Weapons**
> 
> In this chapter we are introducing the basic **weapon concepts**. Once we are ready to use these weapons, by configuring
> the **[](cbt_weapon_manager.md)**, we will then fully configure the **melee** and **ranged** aspects of these weapons.
{style=note}

## Weapon Cosmetics
Weapon and Projectile impacts are internally handled via **Gameplay Cues**. 

### Cosmetics Data Table
Weapons and Projectiles have default cosmetics - **sounds**, **particles** and **camera shakes** set directly to them. 
However, you may want to trigger different effects, based on the **Physical Material** set to the colliding target.

For that, you can set a Data Table, based on `CombatImpactCosmeticsTableRow`. This structure has the following columns:

| Column         | Description                                                          |
|----------------|----------------------------------------------------------------------|
| `Row Name`     | Should match the **Physical Material asset name** (i.e. `PA_Flesh`). |
| `Particles`    | Particle effects played for the given surface.                       |
| `Sound`        | Sound effects played for the given surface.                          |
| `Camera Shake` | Camera shake played for the given surface.                           |

### Cosmetics Component
The **Combat Cosmetics Component**, included in the base **Weapon Actor**, handles **audio effects**, **particle effects** 
and **camera shakes**. This component is also integrated with the **Asset Manager**, supporting **soft references** and 
loading on demand, when applicable.

> **Combatant Pawns and Characters**
>
> Pawns and/or Characters that can perform melee attacks can also benefit from this component. You can add it to your
> base classes and use its methods to handle cosmetics.
{style="note"}

> **Niagara Parameters**
>
> If you need to set values to parameters in the Niagara Component, override the `ModifyMeleeHitComponent` function.
> By default, this function will set: `user.Target`, `user.HitLocation` and `user.HitNormal` in the **Impact VFX**.
{style="note"}

## Inventory Integration
To integrate weapons with an Inventory Manager, they must be converted into **Equipment Actors**. To learn how to 
integrate with **[](inv_overview.md)**, see the **[](itg_combat_inventory.md)** guide. 