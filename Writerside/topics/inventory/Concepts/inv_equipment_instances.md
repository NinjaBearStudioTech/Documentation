# Equipment and Appearance
<primary-label ref="inventory"/>

A lantern can hang from a belt, appear in a character's hand, or disappear into a backpack. The lantern remains the same inventory item. Its **Equipment Fragment** defines what the player sees in each state, and the **Equipment Manager** attaches the matching actor or mesh to the avatar.

## Choose the Appearance for Each State

| State | Example | Where to set it |
| --- | --- | --- |
| Equipped | A lantern in the character's hand | Give the Equipped state an actor or mesh. Set the hand socket in the Equipment Layout. |
| Stored | The same lantern hanging from a belt | Configure the Stored state and the layout's stored socket. The lantern can stay in its equipment slot while stored. |
| Inactive | The lantern is packed away | Move it to an ordinary bag. Its equipment appearance is removed. |

A static mesh works for a simple prop. Choose an actor for gear with behavior of its own, such as a lantern with a light component. A skeletal mesh can follow the avatar's pose for fitted armor. If the character needs a different stance while holding the item, set **Equipment Anim Layer Class** on that state and expose the avatar's animation instance through `GetInventoryAnimInstance`.

## Customize Attachment and Visibility

The default attach finder uses the character mesh. With a different avatar, implement the **Equipment System Interface** to provide `GetEquipmentManager` and `GetInventoryMesh`, then choose the inventory-interface attach finder. For an attachment that depends on the item, subclass `NinjaEquipmentAttachParentFinder` and implement `FindAttachParent`. A state can override the default finder or socket.

For an equipment actor that should only be visible at certain times, add a **Ninja Equipment Actor Component** and set its **Visibility Tag**. Grant that tag on the owner's Ability System Component to show the actor and remove it to hide it. This lets you hide a lantern during a cutscene without moving the item or changing its equipment state.

For gear that occupies two slots, use a **Linked Container Placement Fragment** in place of ordinary placement. For example, link the off-hand slot to a two-handed tool placed in the main hand. A state can also grant a container, such as a pouch, or apply a Gameplay Effect for as long as that state is active.

## React to a Gear Change

Use the Equipment Manager's `OnBoundToInventory` when your gear screen needs a ready manager. Use the Inventory Manager's `OnItemEvent` with `Inventory.Event.Item.EquipmentStateChanged` when the screen needs to know which item changed. C++ can bind `Native_OnBoundToInventory` or `Native_OnItemEvent`. [Equip a lantern and switch its appearance](inv_guide_equipment.md) to try both states.
