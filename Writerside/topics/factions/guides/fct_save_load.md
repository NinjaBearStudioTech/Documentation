# Save and Restore Faction Progress
<primary-label ref="factions"/>
<secondary-label ref="guide"/>

Save the player's team and standing so a guard remembers them the next time they play. This example saves one player's Faction Component in one slot. Start with **Players** as the main faction and a **Town Watch** membership whose score you can change. See [Change Reputation Through Gameplay](fct_add_reputation.md).

<procedure title="Write the player's memberships to a slot">
    <step><p>Call <b>Create Save Game Object</b> and choose <code>NinjaFactionSaveGame</code> as the class. On the returned faction save object, call <b>Save Factions</b> (<code>SaveFactions</code>) and pass the player's Faction Component.</p></step>
    <step><p>Pass that object to <b>Save Game to Slot</b>. For this test, use the slot name <code>FactionTest</code> and user index <code>0</code>. Check the success result before ending the session.</p></step>
</procedure>

<img src="fct_save_memberships.png" alt="Copying the player's faction memberships into a save game" width="780" border-effect="line"/>

<procedure title="Restore the memberships on the new player">
    <step><p>Once the player has spawned and its Faction Component is ready, check <b>Does Save Game Exist</b> for the same slot and user index. On a first run, keep the player's default memberships.</p></step>
    <step><p>Call <b>Load Game from Slot</b>, cast the result to <code>NinjaFactionSaveGame</code>, and call <b>Load Factions</b> (<code>LoadFactions</code>) with the new player's component. In multiplayer, restore memberships on the server.</p></step>
    <step><p>Loading replaces the current list and loads the saved faction assets asynchronously. For an open faction menu, bind <code>OnFactionRemoved</code> and <code>OnFactionAdded</code> before loading. Remove old rows and add each restored membership as it arrives.</p></step>
</procedure>

<img src="fct_load_memberships.png" alt="Applying the loaded save game to the player's Faction Component" width="780" border-effect="line"/>

## Use Your Existing Save System

Call **Get Faction Record for Serialization** (`GetFactionRecordForSerialization`) on each component you want to save. Store that record against the player or NPC's persistent identity. It includes each faction's asset path, reputation, and main-faction flag. Pass the matching record to **Load Faction Memberships** (`LoadFactionMemberships`) on the restored actor.

For a save system that handles individual entries, **Get Membership Records for Serialization** returns the list. **Add Faction From Membership** accepts a reconstructed membership, a source, and an event tag. If you override faction assignment rules, allow `Factions.Event.SaveGame` for restores you trust.

## Try It in Play

With the example tier table, give the player **12** Watch reputation and save. End play, start a fresh session, then load. After the Watch membership is added, check that **Players** is still the main faction and the Watch membership reads **12 / Trusted**. A Watch guard using **Target Reputation** should see the player as **Friendly** again. If you only see the defaults, check the slot name and user index, then inspect the component when its added events arrive.
