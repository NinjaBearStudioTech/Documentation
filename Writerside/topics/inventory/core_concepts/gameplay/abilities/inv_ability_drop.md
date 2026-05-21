# Drop Ability
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Drop Ability</b></p>
    <br/>
    <ul>
        <li>Drops one or more items from the inventory into the world.</li>
        <li>Requires the item to include a <b>Drop Fragment</b> that defines how it should be instantiated or spawned.</li>
        <li>This ability is typically triggered via <b>payload activation</b> from user interfaces or game logic.</li>
    </ul>
</tldr>

The **Drop Ability** executes a **drop action** on one or more selected items, removing them from the inventory and
spawning them into the world. This is commonly used when players manually discard items via menus or drag-and-drop interfaces.

The Drop Ability is generally granted to characters by default and is triggered using <b>payload activation</b>:

- From user interface widgets (e.g., inventory menus).
- From other abilities or systems that wish to drop an item programmatically.

Since it relies on **context from the activation payload**, this ability is rarely activated manually by the player via 
hotkeys or direct bindings.

## Item Requirement

Only items that include a [**Drop Fragment**](inv_fragment_drop.md) are eligible to be dropped by this ability.

The fragment determines how the item will behave once dropped—such as the actor class to spawn, position logic, or whether
physics simulation should be applied.
