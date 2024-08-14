# Weapons
<primary-label ref="combat"/>

**Weapon** are a **core component** in the Combat System. They are **Actors** that can perform important combat tasks 
such as **Melee Scans** or **Launch a Projectile**.

## Weapon Interface

A Weapon is defined by the **Weapon Interface** (`CombatWeaponInterface`), a straightforward API that requires the weapon 
to identify itself using **Gameplay Tags**. This tagging system allows the **[Weapon Manager](cbt_weapon_manager.md)** 
to locate efficiently.

Gameplay Tags ensure that weapons can be easily categorized and accessed by the **Weapon Manager**, providing flexibility 
in how they are described, identifying **usage scenarios** or other **relevant traits**.

> **Melee and Ranged Weapons**
> 
> **Melee** or **Ranged** behaviors are introduced by other interfaces. This separation exists to allow such behaviors 
> to be added to **Weapons** and also **Combatants**.
> 
> For more information about these interfaces, please take a look at their dedicated pages.

## Default Weapon Actor

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

### Melee Hit Cosmetics

In the Damage Handling flow, you can have a **Damage Handler** to invoke **Combat Interfaces** on the **Damage Causer**,
which may likely be a **Weapon**. This triggers the `HandleMeleeDamageCosmetics` function, meant to play cosmetics like
**Sounds** and **Particles**.

The Default Weapon Actor will provide a preliminary structure to handle these assets, allowing you to set them in the 
weapon's **Details Tab**. They are stored as **soft references** load on-demand.

> **Niagara Parameters**
> 
> If you need to set parameters to the Niagara Component, override the `ModifyMeleeHitComponent` function. By default,
> this function will set: **Target**, **Hit Location** and **Hit Normal**.
{style="note"}

## Equipment Weapon Actor

**[Ninja Inventory](inv_overview.md)** provides an **Equipment Module** that represents **Items**, like **Weapons**, in
the world.

The Combat System is able to detect if you have the Inventory System in your project. If so, then the **Equipment Weapon 
Actor** will become available. It can be used as a base class to create **weapon equipment**.

An **Equipment Weapon Actor** (`ANinjaCombatEquipmentWeaponActor`) has the following characteristics:

- It is compatible with the **[Equipment Weapon Manager](cbt_weapon_manager.md)**.
- It is visible to the **[Equipment Manager](inv_equipment_manager.md)**, since it implements `IEquipmentActorInterface`.
- It will be used by the Equipment System as an **Effect Causer**, which is the Actor used as the **Cause** of an effect applied to target. 
- Can use the **[Item Level](inv_level_fragment.md)** as the Effect Level for Melee Hit Gameplay Effects.

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
