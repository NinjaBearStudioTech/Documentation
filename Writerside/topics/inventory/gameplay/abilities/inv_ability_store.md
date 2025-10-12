# Store Ability
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Transitions one or more items to their <b>Stored</b> state.</li>
        <li>Requires an <b>Equipment Fragment</b> to define behavior and current state.</li>
        <li>Supports equipping <b>specific items</b> from a payload or query-based searches triggered by <b>input bindings</b>.</li>
    </ul>
</tldr>

The **Store Ability** transitions valid equipment items to the **Stored** state, typically placing them on the
character's body, backpack, or holster, depending on your **equipment state setup**.

This ability is a direct sibling to the [<b>Equip Ability</b>](inv_ability_equip.md), and shares all of its core behavior,
infrastructure, and activation methods. It inherits from the same `ChangeEquipmentState` base class.
