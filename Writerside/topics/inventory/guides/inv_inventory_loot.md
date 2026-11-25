# Open a Shared Loot Container
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

Build a supply chest that offers one bandage stack. The chest owns the original stack, the player chooses **Take**, and a later visitor sees the chest without it. Start with a [player inventory](inv_first_steps.md) with room for the reward.

<procedure title="Stock the chest">
    <step><p>Create a Blueprint based on <code>NinjaInventorySharedStorageActor</code>, add a mesh, and place it in the level. Its shared manager handles the world inventory. Give it an <b>Initial Containers</b> entry with Simple Layout and the default-container tag.</p></step>
    <step><p>Add a <b>Loot Fragment</b> to the <a href="inv_guide_inventory_items.md">bandage definition</a>. Leave <b>Only From Loot Containers</b> off for this example. Add one bandage stack to the chest's <b>Initial Items</b>. Keep it unbound so it can be offered as loot.</p></step>
    <step><p>On the chest's manager choose <b>Inventory Items Loot Selector</b>. Disable <b>Roll for Items</b> and <b>Consume Item Budget</b> for a guaranteed offer. Use <b>None</b> for <b>Loot Persistency Mode</b> to read the current contents each time. On the player's receiving manager, enable <b>Remove Looted Items From Source</b>.</p></step>
</procedure>

<procedure title="Offer the contents and take one entry">
    <step><p>When the player opens the chest, check your range or access condition on the server. Call <code>OpenSessionForActor</code> on the chest with the player actor. Check <code>IsActorAuthorized</code> before allowing access.</p></step>
    <step><p>Open a panel owned by the player. Give it an <b>Inventory Loot ViewModel</b> with <b>Inventory Resolver</b> and bind <b>Get Items</b> to the panel's item entries. Once the panel is listening, call <code>GenerateLoot</code> on the chest's manager with the player's manager. The resulting selection is sent to that player.</p></step>
    <step><p>On <b>Take</b>, pass the selected entry to the Loot ViewModel's <code>TransferLootEntryFromViewModel</code>. For a custom menu using manager functions, call <code>TransferLoot</code> on the player's manager with the original offered entry. It carries the identity of this chest and this reward.</p></step>
    <step><p>On close, call <code>DismissLoot</code> on the Loot ViewModel, or on the player's manager with the source manager. Close the chest's session with <code>CloseSessionForActor</code> on the server. Use the same cleanup when the player walks away.</p></step>
</procedure>

Use the player's `OnLootEvent` delegate for a custom reward notification. C++ listeners can bind `Native_OnLootEvent`. To change eligibility without rebuilding the panel, customize the [source's loot selector](inv_shared_inventories.md).

## Try It in Play

Open the chest, take the stack, and check the player's bag. Inspect the chest's inventory in the Gameplay Debugger and confirm that its original stack is gone. Close the panel and check that the chest no longer authorizes that player. Reopen it with a second player and check that the bandages are gone.
