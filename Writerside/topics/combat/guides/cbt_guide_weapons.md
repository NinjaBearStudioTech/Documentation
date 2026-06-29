# Creating Weapons
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

The Combat System uses **weapons** for melee scans, projectile launches, and firearms. Weapons are accessed through the
**Weapon Manager**, which makes them available to abilities and other combat systems through **Weapon Queries**.

This guide shows how to create common weapon actors and register them with a character.

For more information, check [**Weapon Management**](cbt_concept_weapon_management.md).

## Melee Weapon

Melee weapons are actors that implement `CombatMeleeInterface`, either directly or through a base class such as
`NinjaCombatWeaponActor`. They usually provide a mesh with a socket used as the source for **melee scans**.

<procedure title="Configure a Sword Mesh" collapsible="true" default-state="collapsed">
    <step>Open the <b>skeletal mesh</b> or <b>static mesh</b> that represents your melee weapon. In this example, we'll use a sword.</step>
    <step>
        <p>Add a socket at the center of the blade and name it <code>sScan</code>. This socket will be used by melee scans.</p>
        <img src="cbt_guide_weapon_melee_mesh.png" alt="Weapon Socket" border-effect="line" thumbnail="true"/>
    </step>
    <step>Make sure the mesh asset has <b>no collision</b>, since regular mesh collision can interfere with gameplay collision and scan results.</step>
</procedure>

<procedure title="Create the Sword Actor" collapsible="true" default-state="collapsed">
    <step>Create a new <b>Weapon Actor</b> based on <code>NinjaCombatWeaponActor</code>.</step>
    <step>Add a <b>Static Mesh Component</b> or <b>Skeletal Mesh Component</b>, depending on the mesh type used by the weapon.</step>
    <step>Implement <code>GetMeleeMesh</code>, returning the mesh component used by melee scans.</step>
    <step>Save this Blueprint as your base melee weapon.</step>
    <step>Create a <b>Child Blueprint</b> from the base melee weapon, and set the sword mesh configured earlier.</step>
    <step>
        <p>Add <code>Combat.Weapon.Sword</code>, or any other identifying tags, to the list of <b>Weapon Tags</b>.</p>
        <p>Make sure the tag collection <b>uniquely identifies</b> this specific weapon.</p>
    </step>
</procedure>

## Ranged Weapon

Ranged weapons are actors that implement `CombatRangedInterface`, either directly or through a base class such as
`NinjaCombatWeaponActor`. They usually provide a mesh with a socket used as the source for **projectile launches**.

<procedure title="Configure a Bow Mesh" collapsible="true" default-state="collapsed">
    <step>Open the <b>skeletal mesh</b> or <b>static mesh</b> that represents your ranged weapon. In this example, we'll use a bow.</step>
    <step>
        <p>Add a socket at the projectile launch point and name it <code>sProjectile</code>.</p>
        <img src="cbt_guide_weapon_ranged_mesh.png" alt="Weapon Socket" border-effect="line" thumbnail="true"/>
        <tip>
            <p><b>Socket Rotation</b></p>
            <p>Add a preview mesh, such as an arrow, and make sure the socket rotation points forward.</p>
        </tip>
    </step>
</procedure>

<procedure title="Create the Bow Actor" collapsible="true" default-state="collapsed">
    <step>Create a new <b>Weapon Actor</b> based on <code>NinjaCombatWeaponActor</code>.</step>
    <step>Add a <b>Static Mesh Component</b> or <b>Skeletal Mesh Component</b>, depending on the mesh type used by the weapon.</step>
    <step>Implement <code>GetProjectileSourceMesh</code>, returning the mesh component used to launch projectiles.</step>
    <step>Save this Blueprint as your base ranged weapon.</step>
    <step>Create a <b>Child Blueprint</b> from the base ranged weapon, and set the bow mesh configured earlier.</step>
    <step>
        <p>Add <code>Combat.Weapon.Bow</code>, or any other identifying tags, to the list of <b>Weapon Tags</b>.</p>
        <p>Make sure the tag collection <b>uniquely identifies</b> this specific weapon.</p>
    </step>
</procedure>

## Firearm

Firearms are weapon actors with a **Firearm Component** (`NinjaCombatFirearmComponent`). They usually provide at least one
socket used as the source for hitscan or projectile fire, and may also provide sockets for cosmetics such as muzzle flashes
and tracers.

<procedure title="Configure a Rifle Mesh" collapsible="true" default-state="collapsed">
    <step>Open the <b>skeletal mesh</b> or <b>static mesh</b> that represents your firearm. In this example, we'll use a rifle.</step>
    <step>
        <p>Add a socket just after the end of the barrel and name it <code>sProjectile</code>. This socket will be used as the fire source.</p>
        <img src="cbt_guide_weapon_firearm_mesh.png" alt="Weapon Socket" border-effect="line" thumbnail="true"/>
        <tip>
            <p><b>Socket Rotation</b></p>
            <p>Add a preview mesh and make sure the socket rotation points forward.</p>
        </tip>
    </step>
</procedure>

<procedure title="Create the Rifle Actor" collapsible="true" default-state="collapsed">
    <step>Create a new <b>Weapon Actor</b> based on <code>NinjaCombatWeaponActor</code>.</step>
    <step>Add a <b>Static Mesh Component</b> or <b>Skeletal Mesh Component</b>, depending on the mesh type used by the weapon.</step>
    <step>Add <code>NinjaCombatFirearmComponent</code> to the list of <b>Actor Components</b>.</step>
    <step>Save this Blueprint as your base firearm.</step>
    <step>Create a <b>Child Blueprint</b> from the base firearm, and set the rifle mesh configured earlier.</step>
    <step>
        <p>Add <code>Combat.Weapon.Rifle</code>, or any other identifying tags, to the list of <b>Weapon Tags</b>.</p>
        <p>Make sure the tag collection <b>uniquely identifies</b> this specific weapon.</p>
    </step>
</procedure>

> **Firearm Operation**
> 
> At this point, the firearm Blueprint is ready. You can now create **Firearm Data** assets to define how the firearm 
> operates, such as its fire mode, ammunition, spread, recoil, and other behavior.
> 
> For more information, check the [<b>Firearms Guide</b>](cbt_guide_firearms.md).

## Register Weapons

The default Weapon Manager manages the weapons available to an owner. These weapons are accessed through **Weapon Queries**,
which are matched against the **Weapon Tags** assigned to each weapon.

<procedure title="Add the Weapon Manager Component" collapsible="true" default-state="collapsed">
    <step>In your Character Blueprint or base class, add <code>NinjaCombatWeaponManagerComponent</code>.</step>
    <step>Implement <code>GetWeaponManagerComponent</code> from <code>CombatSystemInterface</code>, returning your <b>Weapon Manager Component</b>.</step>
    <step>Add your weapon Blueprints to the list of <b>Default Weapon Classes</b>. These weapons will be available to Weapon Queries.</step>
</procedure>

You can also use [**Ninja Inventory**](inv_overview.md) to define weapons through **Inventory Items**. In that setup,
weapons are provided to the Combat System through the [**Combat and Inventory Integration**](integration_combat_inventory.md).