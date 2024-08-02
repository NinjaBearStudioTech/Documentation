# Create Items and add them to the Inventory
<primary-label ref="inventory"/>
<secondary-label ref="how-to"/>

## Goals

In this how-to, you will learn how to create your first **Items** and add them to the Inventory Manager.

## Pre-requisites

1. The initial [**setup**](inv_setup.md) was completed.
2. Primary Assets were registered to the **Asset Manager**
3. Completed the [Containers and Layout](inv_create_containers.md) how-to, or have an equivalent setup.
4. The **Gameplay Debugger** has been enabled in the project.

## Tasks

<procedure title="Create a Sword" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>item data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Item Definition</b>.</step>
    <step>Name your new container asset <code>Weapon_Sword_Basic</code> and open it.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Item.Weapon.Sword</code> Gameplay Tag, to identify this item.</step>
    <step>Add the <b><a href="inv_user_interface_fragment.md">User Interface Fragment</a></b> and configure it.</step>
    <step>Add the <b><a href="inv_stack_fragment.md">Stack Fragment</a></b>.</step>
    <step>Add the  <b><a href="inv_container_fragment.md">Container Fragment</a></b>. For the <b>Preferred Container Query</b>, set <code>Any Tags Match</code> as the <b>Root Expression</b> and point to the <b>Primary Container</b> by adding the <code>Inventory.Container.Primary.A</code> Gameplay Tag.</step>
</procedure>

<procedure title="Create a Shield" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>item data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Item Definition</b>.</step>
    <step>Name your new container asset <code>Weapon_Sword_Basic</code> and open it.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Item.Weapon.Shield</code> Gameplay Tag, to identify this item.</step>
    <step>Add the <b><a href="inv_user_interface_fragment.md">User Interface Fragment</a></b>, and configure it.</step>
    <step>Add the <b><a href="inv_stack_fragment.md">Stack Fragment</a></b>.</step>
    <step>Add the  <b><a href="inv_container_fragment.md">Container Fragment</a></b>. For the <b>Preferred Container Query</b>, set <code>Any Tags Match</code> as the <b>Root Expression</b> and point to the <b>Secondary Container</b> by adding the <code>Inventory.Container.Primary.B</code> Gameplay Tag.</step>
</procedure>

<procedure title="Create Iron Bars" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>item data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Item Definition</b>.</step>
    <step>Name your new container asset <code>Crafting_Iron_Bar</code> and open it.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Item.Crafting.Iron</code> Gameplay Tag, to identify this item.</step>
    <step>Add the <b><a href="inv_user_interface_fragment.md">User Interface Fragment</a></b> and configure it.</step>
    <step>Add the <b><a href="inv_stack_fragment.md">Stack Fragment</a></b>. Set a <code>Stack Limit</code> of <code>20</code>, and a <b>Maximum Limit</b> of <code>100</code></step>.
    <step>Add the <b><a href="inv_container_fragment.md">Container Fragment</a></b>. For the <b>Preferred Container Query</b>, set <code>Any Tags Match</code> as the <b>Root Expression</b> and point to the <b>Backpack</b> by adding the <code>Inventory.Container.Backpack</code> Gameplay Tag.</step>
</procedure>

<procedure title="Add Default Items" collapsible="true">
    <step>Open the <code>Pawn</code>, <code>Character</code> or <code>Player State</code> where your <code>Inventory Manager</code> is located.</step>
    <step>Navigate to the <code>Inventory Manager Component</code>, so you can see its <code>Default Values</code>.</step>
    <step>Under the <b>Inventory Manager</b> category, add a new entry to the <b>Default Items</b> property, select <code>Weapon_Sword_Basic</code> as the <b>Item Data</b>, add a new <b>Fragment Memory</b>, select the <code>Container</code> fragment class and the <code>Container Memory</code>, select <code>Container_Backpack</code> as the <b>Default Container Data</b>.</step>
    <step>Add another entry to the <b>Default Items</b> property, select <code>Weapon_Shield_Basic</code> as the <b>Item Data</b>, add a new <b>Fragment Memory</b>, select the <code>Container</code> fragment class and the <code>Container Memory</code>, select <code>Container_Backpack</code> as the <b>Default Container Data</b>, set the <b>Position</b> to <code>1</code>.</step>
    <step>Add another entry to the <b>Default Items</b> property, select <code>Crafting_Iron_Bar</code> as the <b>Item Data</b>, add a new <b>Fragment Memory</b>, select the <code>Stack</code> fragment class and the <code>Stack Memory</code>, set the <b>Stack Size</b> to <code>50</code>.</step>
</procedure>

<procedure title="Test the Results" collapsible="true">
    <step>Hit <b>Play</b>, open the <b>Gameplay Debugger</b> and activate the <b>Inventory</b> category.</step>
    <step>Confirm that the <b>Sword</b> and <b>Shield</b> were assigned to the <b>Backpack</b> and not their preferred containers. They occupy positions <b>0</b> and <b>1</b>, respectively.</step>
    <step>Confirm that three stacks of <b>Iron Bars</b> were created: two stacks with a size of <b>20</b>, one stack with a size of <b>10</b>. They occupy positions <b>2</b>, <b>3</b> and <b>4</b> in the <b>Backpack</b>.</step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_setup.md" summary = "Steps necessary to have the inventory up and running.">Inventory Setup</a>
        <a href="inv_items_and_fragments.md" summary = "Item information and Fragment reference.">Items and Fragments</a>
        <a href="inv_inventory_manager.md" summary = "Inventory Manager and Layout assignment.">Inventory Manager</a>
        <a href="inv_debugger_and_logs.md" summary = "Using the Inventory Gameplay Debugger and accessing logs.">Debugger and Logs</a>
    </category>
</seealso>