# Create Containers and set up a Layout
<primary-label ref="inventory"/>
<secondary-label ref="how-to"/>

## Goal

In this how-to, you will learn how to create your first **Containers**, add them to a new **Inventory Layout** and then
assign this layout to an **Inventory Manager**.

## Pre-requisites

1. The initial [**setup**](inv_setup.md) was completed.
2. Primary Assets were registered to the **Asset Manager**
3. The [**Inventory Attribute Set**](inv_attributes.md) was **added** and **initialized** with proper data.
4. The **Gameplay Debugger** has been enabled in the project.

## Tasks

<procedure title="Create a Backpack Container" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Container Definition</b>.</step>
    <step>Name your new container asset <code>Container_Backpack</code> and open it.</step>
    <step>Type <code>Backpack</code> in the <b>Display Name</b> property, or select a value from a String Table.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Backpack</code> Gameplay Tag, to identify this container.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Default</code> Gameplay Tag, to mark this as the <b>default</b> container.</step>
    <step>Set the <b>priority</b> to <code>100</code>. This makes the default container to be selected last, prioritizing equipment slots.</step>
    <step>Set your <b>Slots Attribute</b> to <code>NinjaInventoryAttributeSet:BackpackSlots</code>.</step>
    <step>Configure your <b>Item Compatibility Query</b> to support any items, by adding <code>All Tags Match</code> as the <b>Root Expression</b> and then adding the <code>Inventory.Item</code> tag.</step>
</procedure>

<procedure title="Create a Primary Item Container" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Container Definition</b>.</step>
    <step>Name your new container asset <code>Container_Primary_Item_A</code> and open it.</step>
    <step>Type <code>Primary Weapon</code> in the <b>Display Name</b> property, or select a value from a String Table.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Primary.A</code> Gameplay Tag, to identify this container.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Equipment</code> Gameplay Tag, to mark this as an <b>equipment</b> container.</step>
    <step>Set the <b>Default State Tag</b> to <code>Equipment.State.Deactivated</code>, to determine the initial state of equipment instances added to this container.</step>
    <step>Configure your <b>Item Compatibility Query</b> to support any weapons, by adding <code>All Tags Match</code> as the <b>Root Expression</b> and then adding the <code>Inventory.Item.Weapon</code> tag.</step>
</procedure>

<procedure title="Create a Secondary Item Container" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Container Definition</b>.</step>
    <step>Name your new container asset <code>Container_Primary_Item_B</code> and open it.</step>
    <step>Type <code>Primary Weapon</code> in the <b>Display Name</b> property, or select a value from a String Table.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Primary.B</code> Gameplay Tag, to identify this container.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Equipment</code> Gameplay Tag, to mark this as an <b>equipment</b> container.</step>
    <step>Set the <b>Default State Tag</b> to <code>Equipment.State.Deactivated</code>, to determine the initial state of equipment instances added to this container.</step>
    <step>Set the <b>priority</b> to <code>2</code>. This gives the secondary slot a lower priority than the primary one.</step>
    <step>Configure your <b>Item Compatibility Query</b> to support any weapons, by adding <code>All Tags Match</code> as the <b>Root Expression</b> and then adding the <code>Inventory.Item.Weapon</code> tag.</step>
</procedure>

<procedure title="Create an Inventory Layout" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Inventory Layout</b>.</step>
    <step>Name your new container asset <code>Layout_Players</code> and open it.</step>
    <step>Type <code>Inventory</code> in the <b>Display Name</b> property, or select a value from a String Table.</step>
    <step>Add the <b>containers</b> created in the previous steps.</step>
</procedure>

<procedure title="Assign the Layout to the Inventory Manager" collapsible="true">
    <step>Open the <code>Pawn</code>, <code>Character</code> or <code>Player State</code> where your <code>Inventory Manager</code> is located.</step>
    <step>Navigate to the <code>Inventory Manager Component</code>, so you can see its <code>Default Values</code>.</step>
    <step>Under the <b>Inventory Manager</b> category, select the <b>layout</b> in the <b>Inventory Layout</b> property.</step>
</procedure>

<procedure title="Test the Results" collapsible="true">
    <step>Hit <b>Play</b>, open the <b>Gameplay Debugger</b> and activate the <b>Inventory</b> category.</step>
    <step>Make sure that you see all containers - <b>Backpack</b>, <b>Primary Item</b> and <b>Secondary Item</b> - assigned to the inventory.</step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_setup.md" summary = "Steps necessary to have the inventory up and running.">Inventory Setup</a>
        <a href="inv_container_and_layout.md" summary = "Containers, Inventory Layouts and how they are related.">Containers and Layouts</a>
        <a href="inv_inventory_manager.md" summary = "Inventory Manager and Layout assignment.">Inventory Manager</a>
        <a href="inv_debugger_and_logs.md" summary = "Using the Inventory Gameplay Debugger and accessing logs.">Debugger and Logs</a>
    </category>
</seealso>