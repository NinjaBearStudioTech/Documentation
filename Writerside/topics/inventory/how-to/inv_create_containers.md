# Create Containers and set up a Layout
<primary-label ref="inventory"/>
<secondary-label ref="how-to"/>

## Goals

In this how-to, you will learn how to create your first **Container**, assign it to a new **Inventory Layout** and then
assign this layout to an **Inventory Manager**.

## Pre-requisites

1. The initial [setup](inv_setup.md) was completed.
2. The [Inventory Attribute Set](inv_attributes.md) was added and initialized with proper data.

## Tasks

<procedure title="Create a Backpack Container" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Container Definition</b>.</step>
    <step>Name your new container asset <code>DA_Backpack</code>, and then open it.</step>
    <step>Type <code>Backpack</code> in the <b>Display Name</b> property, or select a value from a String Table key.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Backpack</code> Gameplay Tag, to identify this container.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Default</code> Gameplay Tag, to mark this as the <b>default</b> container.</step>
    <step>Set the <b>priority</b> to <code>100</code>. This makes the default container to be selected last, prioritizing equipment slots.</step>
    <step>Set your <b>Slots Attribute</b> to <code>NinjaInventoryAttributeSet:BackpackSlots</code>.</step>
    <step>Configure your <b>Item Compatibility Query</b> to support any items, by adding <code>All Tags Match</code> as the <b>Root Expression</b> and then adding the <code>Inventory.Item</code> tag.</step>
</procedure>

<procedure title="Create a Primary Item Container" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_SwordDamage</code>".</step>
    <step>Open your new Gameplay Effect Blueprint and, in the Class Defaults tab, add a new <b>Modifier</b>.</step>
    <step>Select the <b>Attribute</b> that you want to modify. For this example, we'll use the <code>BaseDamage</code> Attribute, from <a href = "cbt_overview.md">Ninja Combat</a>.</step>
    <step>In the <b>Modifier Magnitude</b> section, select <code>Set By Caller</code> as the value for <b>Magnitude Calculation Type</b>.</step>
    <step>Set the Data Tag that will be retrieved from the Item Fragment. For this example, we'll use <code>Combat.Data.Damage</code>.</step>
    <step>Set the <b>Duration Policy</b> to <code>Infinite</code>.</step>
    <step>Compile and save your Gameplay Effect Blueprint.</step>
</procedure>

<procedure title="Create a Secondary Item Container" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_SwordDamage</code>".</step>
    <step>Open your new Gameplay Effect Blueprint and, in the Class Defaults tab, add a new <b>Modifier</b>.</step>
    <step>Select the <b>Attribute</b> that you want to modify. For this example, we'll use the <code>BaseDamage</code> Attribute, from <a href = "cbt_overview.md">Ninja Combat</a>.</step>
    <step>In the <b>Modifier Magnitude</b> section, select <code>Set By Caller</code> as the value for <b>Magnitude Calculation Type</b>.</step>
    <step>Set the Data Tag that will be retrieved from the Item Fragment. For this example, we'll use <code>Combat.Data.Damage</code>.</step>
    <step>Set the <b>Duration Policy</b> to <code>Infinite</code>.</step>
    <step>Compile and save your Gameplay Effect Blueprint.</step>
</procedure>

<procedure title="Create an Inventory Layout" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_SwordDamage</code>".</step>
    <step>Open your new Gameplay Effect Blueprint and, in the Class Defaults tab, add a new <b>Modifier</b>.</step>
    <step>Select the <b>Attribute</b> that you want to modify. For this example, we'll use the <code>BaseDamage</code> Attribute, from <a href = "cbt_overview.md">Ninja Combat</a>.</step>
    <step>In the <b>Modifier Magnitude</b> section, select <code>Set By Caller</code> as the value for <b>Magnitude Calculation Type</b>.</step>
    <step>Set the Data Tag that will be retrieved from the Item Fragment. For this example, we'll use <code>Combat.Data.Damage</code>.</step>
    <step>Set the <b>Duration Policy</b> to <code>Infinite</code>.</step>
    <step>Compile and save your Gameplay Effect Blueprint.</step>
</procedure>

<procedure title="Assign the Layout to the Inventory Manager" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_SwordDamage</code>".</step>
    <step>Open your new Gameplay Effect Blueprint and, in the Class Defaults tab, add a new <b>Modifier</b>.</step>
    <step>Select the <b>Attribute</b> that you want to modify. For this example, we'll use the <code>BaseDamage</code> Attribute, from <a href = "cbt_overview.md">Ninja Combat</a>.</step>
    <step>In the <b>Modifier Magnitude</b> section, select <code>Set By Caller</code> as the value for <b>Magnitude Calculation Type</b>.</step>
    <step>Set the Data Tag that will be retrieved from the Item Fragment. For this example, we'll use <code>Combat.Data.Damage</code>.</step>
    <step>Set the <b>Duration Policy</b> to <code>Infinite</code>.</step>
    <step>Compile and save your Gameplay Effect Blueprint.</step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_container_and_layout.md" summary = "Containers, Inventory Layouts and how they are related.">Containers and Layouts</a>
        <a href="inv_inventory_manager.md" summary = "Inventory Manager and Layout assignment.">Inventory Manager</a>
    </category>
</seealso>