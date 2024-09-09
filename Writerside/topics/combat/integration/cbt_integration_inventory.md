# Inventory Integration
<primary-label ref="combat"/>

Integrating **Ninja Combat** and **Ninja Inventory** allows you to use weapons obtained from the **Inventory Manager**,
instead of ones registered to the default **Weapon Manager**.

## Equipment Weapon Manager

In your character class, instead of using the default Weapon Manager, use the **Weapon Equipment Adapter** component 
(`NinjaCombatEquipmentAdapterComponent`) instead.

1. Replace or remove the original Weapon Manager from your pawn or character.
2. Return the Weapon Equipment Adapter in the `GetWeaponManagerComponent` function, from `CombatSystemInterface`.

## Weapon Class

Normally, weapons in the Combat System extend from `NinjaCombatWeaponActor`. To integrate with the Inventory System, 
you need to change that class hierarchy.

1. Extend from the `NinjaCombatEquipmentWeaponActor` class instead.
2. Add the `EquipmentActorInterface` to them. 

> **Interface Implementation**
> 
> You do not need to implement this interface yourself, unless you want to adjust or optimize its functionality.
{style=note}