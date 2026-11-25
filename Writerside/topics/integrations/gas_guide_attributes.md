# G.A.S. with Combat and Inventory: Initialize Plugin Attributes
<primary-label ref="integrations"/>
<secondary-label ref="gas-sec"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="inventory-sec"/>

Use an ability bundle to give a combatant starting health or an inventory owner a backpack capacity. Each example works independently. Begin with an actor that [has an initialized Ninja Ability System Component](gas_first_steps.md) and a G.A.S. Setup asset in a [registered bundle folder](asset_manager.md).

## Give a Combatant Starting Health

<procedure title="Initialize the Combat Attribute Set">
    <step><p>With Ninja Combat enabled, copy the JSON below into a file named <code>DT_CombatAttributes.json</code>. Import it into the Content Browser as a Data Table with row structure <b>AttributeMetaData</b>. The sample sets <b>Health</b> and <b>MaxHealth</b> to 100 and <b>BaseDamage</b> to 10.</p></step>
    <step><p>Open the combatant's G.A.S. Setup asset. In <b>Default Attribute Sets</b>, add <code>NinjaCombatAttributeSet</code> and select the imported table as its <b>Attribute Table</b>. Assign the bundle to <b>Default Ability Setup</b> on the character or its owning component.</p></step>
    <step><p>In play, inspect this combatant with <code>showdebug abilitysystem</code>. Check that health starts at 100 and base damage at 10. To use the values in an attack, continue with <a href="cbt_first_steps.md">Set Up a Combatant</a>.</p></step>
</procedure>

For a health bar on a newly possessed pawn, use the Blueprint node **Wait For Ability System** before reading Health. In C++, read the starting value from that component and subscribe to `GetGameplayAttributeValueChangeDelegate` for Health to update the bar when Combat applies damage. Remove the binding when switching components.

<code-block lang="json" src="cbt_attributes.json" collapsible="true" collapsed-title="Combat starting values"/>

## Give a Backpack Its Capacity

<procedure title="Initialize the Inventory Attribute Set">
    <step><p>With Ninja Inventory enabled, copy the JSON below into <code>DT_InventoryAttributes.json</code>. Import it as a Data Table with row structure <b>AttributeMetaData</b>. It starts <b>BackpackSlots</b> at 12, <b>WeightLimit</b> at 100, and <b>Wealth</b> at zero.</p></step>
    <step><p>In the inventory owner's G.A.S. Setup asset, add <code>NinjaInventoryAttributeSet</code> to <b>Default Attribute Sets</b> and assign the inventory table. Assign the bundle to the owner. If the same character uses Combat, add both sets with their respective tables to the same bundle.</p></step>
    <step><p>On the backpack container, choose <b>Gameplay Attribute</b> as the slot count type and select <b>BackpackSlots</b>. In play, inspect the owner's attribute and open the backpack. Both should show a capacity of 12. See <a href="inv_guide_simple_grid.md">Build a Standard Slot-Based Inventory</a> for the container setup.</p></step>
</procedure>

For a pawn with its own backpack size, assign its bundle through **Default Ability Setup** on the avatar Blueprint. A custom C++ avatar can implement `IAbilitySystemDefaultsInterface::GetAbilityData` to return that bundle. If the Player State already grants the Inventory Attribute Set, configure the shared capacity there. The component skips duplicate entries for the same set class.

<code-block lang="json" src="inv_attributes.json" collapsible="true" collapsed-title="Inventory starting values"/>

## Try It in Play

For Combat, take a hit and check that current Health falls while MaxHealth stays at 100. For Inventory, change the table's BackpackSlots base value to eight and start with a fresh inventory. The bag should show eight slots. If the attribute reads eight but the bag still has 12, check that the container uses the attribute for its slot count.
