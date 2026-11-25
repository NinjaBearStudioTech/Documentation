# Save and Restore an Inventory
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

Save a character with a partially used stack, move it, then load the save and check where it returns. The save contains the inventory's containers, items, and fragment memories, including stack counts and placement.

<procedure title="Save the player's current inventory">
    <step><p>After the Inventory Manager has initialized, create a <b>Save Game Object</b> using <code>NinjaInventorySaveGame</code>. Call <code>SaveInventory</code> on it with the manager that owns the player's items.</p></step>
    <step><p>Get <b>Save Game Slot Name</b> and <b>Save Game User Index</b> from that manager. Pass those values and the object to <b>Async Save Game to Slot</b>. Show the player a saved message only when the disk operation succeeds.</p></step>
</procedure>

<img src="inv_advanced_save.png" alt="Copying the manager's inventory into a Save Game object and writing it to a slot" width="650" border-effect="line"/>

<procedure title="Restore the same player">
    <step><p>For a manual load, read the same slot and user index with <b>Async Load Game from Slot</b>. Check the result and cast the returned object to <code>NinjaInventorySaveGame</code>. Call <code>LoadInventory</code> on it with the target manager. Restoring into a running inventory replaces its current contents.</p></step>
    <step><p>For automatic restoration at startup, enable <b>Automatically Load From Disk</b> on the manager and configure the same slot and user index. If no save exists, the manager uses its starting inventory. Use a separate test slot if you want to keep an existing playthrough.</p></step>
</procedure>

Override the manager's `GetSaveGameSlotName` or `GetSaveGameUserIndex` when each player or profile needs a different save. In multiplayer, run the normal save and restore flow for the authoritative inventory. Bind `OnInventoryInitializationSucceeded` to reopen the inventory UI after initialization and `OnInventoryInitializationFailed` to handle a failed initialization.

When a custom fragment needs to change how it saves a value, override `SerializeFragmentMemory` and read the result in `InitializeItemWithDefaultMemory`. For a rechargeable tool, save its remaining charge and verify that it survives a round trip.

## Try It in Play

Move a partial bandage stack to a known slot and save. Use one bandage and move the stack elsewhere. Load the save and check its original quantity and position. With a spatial backpack, save a rotated tool and check its footprint after loading. With equipment, save the lantern in its slot and check its attachment and state after the restore.
