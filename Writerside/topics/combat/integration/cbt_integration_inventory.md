# Inventory Integration
<primary-label ref="combat"/>

Integrating **Ninja Combat** and **Ninja Inventory** allows you to use weapons obtained from the **Inventory Manager**,
instead of ones registered to the default **Weapon Manager**.

## Equipment Weapon Manager

1. **Replace or remove** the original **Weapon Manager** (`NinjaCombatWeaponManagerComponent`) from your pawn or character.
2. Implement the `GetWeaponManagerComponent` function, from `CombatSystemInterface`, so it returns the updated Weapon Manager.

## Weapon Class

- Modify your Weapon Actors, so they extend from **Equipment Weapon** (`NinjaCombatEquipmentWeaponActor`).
- Add the `EquipmentActorInterface` to your Weapon Actors. You don't need to implement any functions.

> **Base Weapon Actor**
> 
> It's highly recommended that you create your base Weapon Class or Blueprint so all your actual Weapon Actors can 
> extend from it.
{style=note}