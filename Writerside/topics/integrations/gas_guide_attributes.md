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

<code-block lang="json" src="cbt_attributes.json" collapsible="true" collapsed-title="Combat starting values"/>

## Give a Backpack Its Capacity

<procedure title="Initialize the Inventory Attribute Set">
    <step><p>With Ninja Inventory enabled, copy the JSON below into <code>DT_InventoryAttributes.json</code>. Import it as a Data Table with row structure <b>AttributeMetaData</b>. It starts <b>BackpackSlots</b> at 12, <b>WeightLimit</b> at 100, and <b>Wealth</b> at zero.</p></step>
    <step><p>In the inventory owner's G.A.S. Setup asset, add <code>NinjaInventoryAttributeSet</code> to <b>Default Attribute Sets</b> and assign the inventory table. Assign the bundle to the owner. If the same character uses Combat, add both sets with their respective tables to the same bundle.</p></step>
    <step><p>On the backpack container, choose <b>Gameplay Attribute</b> as the slot count type and select <b>BackpackSlots</b>. In play, inspect the owner's attribute and open the backpack. Both should show a capacity of 12. See <a href="inv_guide_simple_grid.md">Build a Standard Slot-Based Inventory</a> for the container setup.</p></step>
</procedure>

<code-block lang="json" src="inv_attributes.json" collapsible="true" collapsed-title="Inventory starting values"/>
