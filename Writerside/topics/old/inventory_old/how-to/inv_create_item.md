# Create Item Definitions using Item Fragments
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

This how-to will show you how to create your first few **Inventory Items**. 

<procedure title="Create a Sword definition" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>item data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Item Definition</b>.</step>
    <step>Name your new container asset <code>Weapon_Sword</code> and open it.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Item.Weapon.Sword</code> Gameplay Tag, to identify this item.</step>
    <step>Add the <b><a href="inv_user_interface_fragment.md">User Interface Fragment</a></b> to configure how this item is presented in the user interface. Set appropriate values to it.</step>
    <step>Add the <b><a href="inv_stack_fragment.md">Stack Fragment</a></b>, set the <b>Stack Limit</b> to <code>1</code> so this item cannot be stacked, and the <b>Maximum Limit</b> to <code>10</code>, so we can allow a maximum of 10 swords in the inventory.</step>
    <step>
        <p>Add the <b><a href="inv_container_fragment.md">Container Fragment</a></b> and configure your <b>Preferred Container Query</b> to prioritize equipment containers.</p>
        <img src="inv_create_item_sword_query.png" alt="Sword Preferred Container Query" border-effect="line"/>
    </step>
    <step>
        <p>When you are done, your <b>Sword Item</b> should look like this (except maybe for the User Interface details).</p>
        <img src="inv_create_item_sword_data.png" alt="Sword Item Data Asset" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create a Shield definition" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>item data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Item Definition</b>.</step>
    <step>Name your new container asset <code>Weapon_Shield</code> and open it.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Item.Weapon.Shield</code> Gameplay Tag, to identify this item.</step>
    <step>Add the <b><a href="inv_user_interface_fragment.md">User Interface Fragment</a></b>, and configure it.</step>
    <step>Add the <b><a href="inv_stack_fragment.md">Stack Fragment</a></b>, set the <b>Stack Limit</b> to <code>1</code> so this item cannot be stacked, and the <b>Maximum Limit</b> to <code>10</code>, so we can allow a maximum of 10 shields in the inventory.</step>
    <step>
        <p>Add the <b><a href="inv_container_fragment.md">Container Fragment</a></b> and configure your <b>Preferred Container Query</b> to prioritize the off-hand container.</p>
        <img src="inv_create_item_shield_query.png" alt="Shield Preferred Container Query" border-effect="line"/>
    </step>
    <step>
        <p>When you are done, your <b>Shield Item</b> should look like this (except maybe for the User Interface details).</p>
        <img src="inv_create_item_shield_data.png" alt="Shield Item Data Asset" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create an Iron Bar definition" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>item data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Item Definition</b>.</step>
    <step>Name your new container asset <code>Resource_IronBar</code> and open it.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Item.Crafting.Iron</code> Gameplay Tag, to identify this item.</step>
    <step>Add the <b><a href="inv_user_interface_fragment.md">User Interface Fragment</a></b> and configure it.</step>
    <step>Add the <b><a href="inv_stack_fragment.md">Stack Fragment</a></b>. Set a <code>Stack Limit</code> of <code>20</code>, and a <b>Maximum Limit</b> of <code>100</code>. Set it to <b>Automatically Merge New Items</b>.</step>.
    <step>
        <p>Add the <b><a href="inv_container_fragment.md">Container Fragment</a></b> and configure your <b>Preferred Container Query</b> to prioritize the backpack container.</p>
        <img src="inv_create_item_iron_query.png" alt="Iron Bar Preferred Container Query" border-effect="line"/>
    </step>
    <step>
        <p>When you are done, your <b>Iron Bar Item</b> should look like this (except maybe for the User Interface details).</p>
        <img src="inv_create_item_iron_data.png" alt="Iron Bar Item Data Asset" border-effect="line"/>
    </step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_items_and_fragments.md" summary = "Item information and Fragment reference.">Items and Fragments</a>
    </category>
</seealso>