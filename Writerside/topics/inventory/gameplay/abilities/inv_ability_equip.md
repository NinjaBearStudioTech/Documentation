# Equip Ability
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Transitions one or more items to their <b>Equipped</b> state, including support for <b>pre-requisite items</b> (e.g., an item that must be stored first).</li>
        <li>Requires an <b>Equipment Fragment</b> to define behavior and current state.</li>
        <li>Supports equipping <b>specific items</b> from a payload or query-based searches triggered by <b>input bindings</b>.</li>
    </ul>
</tldr>

The **Equip Ability** transitions valid equipment items to the **Equipped** state, typically placing them on the
character's hand, depending on your **equipment state setup**.

This ability is a specialization of the abstract [`ChangeEquipmentState`](inv_gameplay_abilities.md) ability class, 
which provides shared logic for resolving equipment items, validating prerequisites, and applying state changes.

## Item Requirement

Only items that include a [**Equipment Fragment**](inv_fragment_equipment.md) are eligible to be equipped. The fragment
defines the current state of the equipment and provides utility methods to update or query its status.

## Usage Options

You can select items through an Item Query or provide them directly as an optional object in the ability's trigger payload.
These options give you flexibility to support a wide range of gameplay scenarios, such as:

1. **Interactive selection**: Activate the ability and allow the player (or AI) to choose which item to equip. This covers cases like "_equip the item in the primary hand_" or "_select a weapon from the wheel_".
2. **Direct activation**: Provide a specific item in the payload when the target item is already known. Common examples include "_press 1 to equip the shotgun_" or "select the equip option for an item in the UI_".