# Inventory Integration
<primary-label ref="combat"/>

Integrating **Ninja Combat** and **Ninja Inventory** allows you to use weapons obtained from the **Inventory Manager**,
instead of ones registered to the default **Weapon Manager**.

## Equipment Weapon Manager

1. **Remove** the original **Weapon Manager** (`NinjaCombatWeaponManagerComponent`) from your pawn or character, if you have it.
2. **Add** the integrated Weapon Manager (`NinjaCombatEquipmentAdapterComponent`) in Blueprint or C++. 
3. Implement the `GetWeaponManagerComponent` function, from `CombatSystemInterface`, so it returns the updated Weapon Manager.

## Weapon Class

- Modify your Weapon Actors, so they extend from **Equipment Weapon** (`NinjaCombatEquipmentWeaponActor`).
- Add the `EquipmentActorInterface` to your Weapon Actors. You don't need to implement any functions.

> **Base Weapon Actor**
> 
> It's highly recommended that you create your base Weapon Class or Blueprint so all your actual Weapon Actors can 
> extend from it.
{style=note}

## C++ Dependencies

If you plan on working with the C++ classes used in the integration, then you need to add yet another library to your
`Build.cs` file, related to the **Integration module**. 

Make sure to also add the appropriate Inventory libraries, as per the [Inventory Setup](inv_setup.md) page.

<tabs group="sample">
    <tab title="Build.cs">
        <code-block lang="c#" src="cbt_build_inventory.cs"/>
    </tab>
</tabs>