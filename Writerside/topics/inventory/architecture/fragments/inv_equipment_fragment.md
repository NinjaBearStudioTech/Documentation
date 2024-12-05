# Equipment
<primary-label ref="inventory"/>

Grants the backing item the **equipment** trait, connects the Item Definition to an **Equipment definition** and 
provides the **Activate** and **Deactivate** operations.

Equipment items are tagged as `Inventory.Item.Trait.Equipment`.

## Equipment Tracking

The Equipment Fragment is a bridge between the [Inventory Manager](inv_inventory_manager.md) and the [Equipment Manager](inv_equipment_manager.md).

It will keep track of the item's current container, and whenever it is added to, or removed from an **Equipment Slot**, 
it will trigger the **Activate** or **Deactivate**, respectively.  

Internally, these flows will broadcast a **Gameplay Event** to activate a **Equipment State Gameplay Ability**, providing
the [**Equipment Definition**](inv_equipment.md#equipment-definition) in the payload. 

## Equipment Definition

The [**Equipment Definition**](inv_equipment.md#equipment-definition) contains information about the equipment that represents the item in the game world.
Make sure to check the [**Equipment page**](inv_equipment.md) for more information!

## Gameplay Abilities

There are two Gameplay Abilities that can handle Activating and Deactivating equipment instances:

- `UInventoryAbility_ActivateEquipment`: Watches for Gameplay Events to **activate** equipment instances.
- `UInventoryAbility_DeactivateEquipment`: Watches for Gameplay Events to **deactivate** equipment instances.

They are connected to the [**Equipment Manager**](inv_equipment_manager.md) and will initialize and modify equipment
states based on the incoming payload.

You can find more information about these abilities in the [Gameplay Abilities](inv_abilities.md)

> The abilities should always be granted as **default** abilities to your character, as they should be available when
> the appropriate Gameplay Events are triggered.
{style="note"}

## Animation Notify

In conjunction with the **Gameplay Abilities**, you can use the **Send Equipment Event** Animation Notify, to trigger
certain gameplay events, such as effectively changing an item's state.