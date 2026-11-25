# First Steps: Give a Character a Starting Item
<primary-label ref="inventory"/>

Give the player a backpack containing three bandages, then check the item before building a menu. Start with [registered asset folders](inv_setup.md) and a playable pawn.

<procedure title="Create a backpack and a bandage">
    <step><p>In the registered container folder, choose <b>Ninja Bear Studio → Ninja Inventory → Container Definition</b>. Name it <b>Container_Backpack</b>, give it the tag <code>Inventory.Container.Trait.Default</code>, and choose <b>Simple Layout</b>. Use <b>Property</b> for the slot count and set <b>Slots</b> to six.</p></step>
    <step><p>In the item folder, create an <b>Item Definition</b> named <b>Item_Bandage</b>. Add a <b>Container Placement Fragment</b> so each bandage stack can be placed in the backpack. Add a <b>Stack and Quantity Fragment</b> with a stack limit of five and a maximum quantity of at least ten. Add a <b>User Interface Fragment</b> with a display name and icon.</p></step>
</procedure>

<procedure title="Give the starting inventory to the player">
    <step><p>Add an <b>Inventory Manager Component</b> to the player pawn. For inventory that follows a player across pawn changes, put it on their Player State instead. Implement <b>Inventory System Interface</b> on that owner and return the component from <b>Get Inventory Manager</b>.</p></step>
    <step><p>On the manager, add <b>Container_Backpack</b> to <b>Initial Containers</b> and <b>Item_Bandage</b> to <b>Initial Items</b>. In the item's <b>Initial Fragment Data</b>, choose the stack fragment class, select <b>Stack Memory</b>, and set <b>Stack Size</b> to three.</p></step>
    <step><p>Test with a fresh inventory using initial data. A saved inventory loaded at startup can replace these defaults.</p></step>
</procedure>

<img src="inv_default_container_and_item.png" alt="Initial container, item, and stack memory on an Inventory Manager" width="700" border-effect="line"/>

## Try It in Play

Open the **Gameplay Debugger**, select the inventory owner, and enable the **Inventory** category. Look for an initialized manager, the expected owner and avatar, a six-slot backpack, and one stack of three. If the bag appears empty, check the Default tag, the item's placement fragment, and whether an earlier save was loaded.

Find the debugger key and category assignment in **Project Settings → Engine → Gameplay Debugger**.

<img src="inv_gameplay_debugger.png" alt="Inventory category showing the owner, containers, and current items" width="650" border-effect="line"/>

## Next Steps

[Display the six slots](inv_guide_simple_grid.md), or [set up a spatial backpack](inv_guide_spatial_grid.md) where bandages and larger tools occupy different amounts of space.
