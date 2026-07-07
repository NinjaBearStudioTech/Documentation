# Store Ability
<primary-label ref="inventory"/>

The **Store Ability** transitions valid equipment items to the **Stored** state, typically placing them on the
character's body, backpack, or holster, depending on your **equipment state setup**.

This ability is a direct sibling to the [**Equip Ability**](inv_ability_equip.md), and shares all of its core behavior,
infrastructure, and activation methods. It inherits from the same `ChangeEquipmentState` base class.
