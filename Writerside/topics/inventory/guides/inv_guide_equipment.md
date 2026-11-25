# Equip an Item and Change Its Appearance
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

Give the player a lantern that appears in their hand when equipped and on their belt when stored. Start with the character and backpack from [First Steps](inv_first_steps.md).

<procedure title="Add a lantern slot to the character">
    <step><p>Add a <b>Ninja Equipment Manager Component</b> to the character that will wear the lantern. The Inventory Manager can stay on the character or Player State. On a character with a custom mesh setup, implement the <b>Equipment System Interface</b> and use <b>Get Inventory Mesh</b> to supply the mesh that owns the sockets. Select the inventory-interface attach finder on the Equipment Manager for that setup.</p></step>
    <step><p>Add a hand socket and a belt socket to that mesh's skeleton. Create a Container Definition called <b>Container_LanternSlot</b> with <b>Equipment Layout</b>. Set <b>Default State Tag</b> to <code>Inventory.Equipment.State.Equipped</code>. Enter your socket names in <b>Default Equip Socket Name</b> and <b>Default Stored Socket Name</b>.</p></step>
    <step><p>Create a project item tag such as <code>Item.Gear.Lantern</code>. Require it in the slot's <b>Item Compatibility Query</b>. Add the slot to the player's <b>Initial Containers</b> alongside the default bag.</p></step>
</procedure>

<procedure title="Define the lantern's two appearances">
    <step><p>Create <b>Item_Lantern</b> and add the lantern tag. Give it <b>Container Placement</b>, <b>User Interface</b>, and <b>Equipment</b> fragments. Give it dimensions too if the player uses a spatial bag.</p></step>
    <step><p>In the Equipment Fragment, add an <b>Equipment States</b> entry tagged <code>Inventory.Equipment.State.Equipped</code>. Choose <b>Actor</b> and assign a lantern actor Blueprint with a visible mesh and light. Add a second entry tagged <code>Inventory.Equipment.State.Stored</code>. Choose a static mesh for the unlit lantern. Let both states use the layout's sockets.</p></step>
    <step><p>Give the player the item in the default backpack, using a pickup or starting item. If the lantern should start in the backpack, set its placement preference to the default-container tag. Display the lantern slot with a container widget bound to <b>Container_LanternSlot</b>. <a href="inv_ui_drag_and_drop.md">Drag the lantern</a> from the bag into that slot, or call the placement fragment's <code>SetContainerAndPosition</code> with the slot container and its single position.</p></step>
</procedure>

For a **Stow** button, call the Equipment Fragment's `SetEquipmentState` on the server with the lantern item and the Stored tag. Pass the Equipped tag to draw it again. If drawing requires a skill, put the prerequisite on the Equipped state and call `EvaluatePrerequisitesForState` to explain availability in the menu. The [ability guide](inv_gameplay_abilities.md) shows how to trigger the change from a selected entry.

## Try It in Play

Move the lantern into its slot. Its light should appear at the hand socket. Stow it and check for the unlit mesh on the belt. Draw it again, then move it back into the backpack. Both worn appearances should now be gone and the bag should still contain the lantern. If it attaches at the character's origin, check the chosen parent mesh and the spelling of its sockets.
