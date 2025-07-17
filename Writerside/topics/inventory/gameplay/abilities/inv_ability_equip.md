# Equip Ability
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Equip Ability</b></p>
    <br/>
    <ul>
        <li>Transitions one or more items to their <b>Equipped</b> state.</li>
        <li>Requires an <b>Equipment Fragment</b> to define behavior and current state.</li>
        <li>Supports equipping <b>specific items</b> or triggering actions via <b>generic input bindings</b>.</li>
    </ul>
</tldr>

The **Equip Ability** transitions valid equipment items to the **Equipped** state, typically placing them on the
character's hand, depending on your **equipment state setup**.

This ability is a specialization of the internal `ChangeEquipmentState` base ability class, which provides shared logic 
for resolving equipment items, validating prerequisites, and applying state changes.

## Item Requirement

Only items that include a [**Equipment Fragment**](inv_fragment_equipment.md) are eligible to be equipped. The fragment
defines the current state of the equipment and provides utility methods to update or query its status.

## Configurable Properties

The Equip Ability inherits all behavior from its base class, allowing control over the state transitions and prerequisites.

| Property                     | Description                                                                                           |
|------------------------------|-------------------------------------------------------------------------------------------------------|
| `NewEquipmentState`          | State tag to apply to selected items. For Equip, this is set to `inventory.equipment.state.equipped`. |
| `PrerequisiteQuery`          | Optional query used to find equipment that must change state before the new item can be equipped.     |
| `PrerequisiteEquipmentState` | Target state for items resolved by the prerequisite query. For Equip, this is usually `stored`.       |

These values can be configured per ability or exposed through Blueprint variants if needed.

## Usage Options

This ability can be triggered in two main ways:

### Per-Item Activation

Equip Abilities can be granted directly to individual items. This allows the item itself to define how it is equipped,
including animation overrides, timing, and prerequisite logic.

### Generic Activation by Slot

Alternatively, the Equip Ability can be granted once to the character or controller and activated via a key press or
gameplay event. In this case, the ability will attempt to resolve the relevant item dynamically based on an internal
**Item Query**, often using a tag to match the slot or weapon type.

This model is ideal for setups like "_Press 1 to equip primary weapon_", "_Equip whatever is in the main-hand slot_" and
"_weapon wheels_".
