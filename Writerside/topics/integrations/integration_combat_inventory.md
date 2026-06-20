# Combat and Inventory

<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="inventory-sec"/>

[**Ninja Combat**](cbt_overview.md) can defer [**Weapon Management**](cbt_concept_weapon_management.md) and [**Ammo Management**](cbt_concept_firearms.md)
to [**Ninja Inventory**](inv_overview.md). Additionally, you can create **custom fragments** that define weapon behavior,
such as **weapon damage**, **critical hit chance and bonus**, **fire rate**, **ammo capacity**, and so on.

## Weapon Manager

Ninja Combat uses a **Weapon Manager** to retrieve weapons available to a combatant. With Ninja Inventory, this responsibility
is then assigned to the Inventory Manager, and the Weapon Manager should simply forward requests to it.

Instead of adding the usual `NinjaCombatWeaponManagerComponent`, use the equipment-aware variant, `NinjaCombatEquipmentAdapterComponent`,
instead. This version implements `CombatWeaponManagerInterface`, as expected by Ninja Combat, but forwards requests to
an **Equipment Manager** that should also be present in the character.

Make sure to return the correct component from `GetWeaponManager`, in the **Combat System Interface**.

## Weapon Actor

Weapon Actors can also benefit from a closer integration with Ninja Inventory. Specifically, they can access the
**Equipment Instance** that contains relevant item data, such as the **Item Instance and its Fragments**, which is
exposed by the `NinjaEquipmentActorComponent`, added to each actor that is used as an **Equipment Presence**.

To leverage this, make sure to either use `ANinjaCombatEquipmentWeaponActor` as your base **Weapon Class**, or add
`NinjaEquipmentActorComponent` to your own Weapon Actor hierarchy. Keep in mind that the former provides additional features,
such as using the **Item Level** as the **Weapon Level** when applying Gameplay Effects.

## Ammo Storage

Similar to the **Weapon Manager**, Ninja Combat uses an **Ammo Storage** component to manage ammunition for firearms
during reloads. When using Ninja Inventory, ammo can be managed using **Item Stacks**.

Instead of using the default `NinjaCombatAmmoStorageComponent`, use `NinjaCombatInventoryAmmoAdapterComponent` and set
its `AllAmmoTypesQuery` to a query that covers all items that represent ammo. For example, if your ammo items use
identification tags like `Item.Type.Ammo.Rifle` and `Item.Type.Ammo.Shotgun`, set this query to find `Item.Type.Ammo`.

## Item Fragments

Multiple Item Fragments can be used to enhance weapons in many ways.

| Fragment           | Description                                                                                                |
|--------------------|------------------------------------------------------------------------------------------------------------|
| Firearm            | Identifies a firearm and becomes aware of compatible ammo.                                                 |
| Equipment          | Configures an actor presence for a weapon, which can be used as the Weapon Actor.                          |
| Offhand Position   | Allows two-handed weapons to properly place the off-hand.                                                  |
| Dynamic Attributes | Can be used to set magnitudes for weapons, such as damage, critical hit chance, and critical damage bonus. |

When using **Dynamic Attributes** in your weapons, override `GetAdditionalCombatMagnitudes`, from `CombatMagnitudeProviderInterface`,
to expose your dynamic attributes, such as Damage and Critical Hit Chance, using the proper data tags.