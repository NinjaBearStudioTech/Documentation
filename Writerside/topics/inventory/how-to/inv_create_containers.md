# Create Containers and an Inventory Layout
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

This how-to will show you how to create your first **Containers** and create an **Inventory Layout**, which is a bundle
that can be added to an **Inventory Manager**.

<procedure title="Create a Backpack Container" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Container Definition</b>.</step>
    <step>Name your new container asset <code>Container_Backpack</code> and open it.</step>
    <step>Set the value <code>Backpack</code> to the <b>Display Name</b> property.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Backpack</code> Gameplay Tag, to identify this container.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Default</code> Gameplay Tag, to mark this as the <b>default</b> container.</step>
    <step>Set the <b>priority</b> to <code>100</code>. This makes the default container to be selected last, prioritizing equipment slots.</step>
    <step>Set your <b>Slots Attribute</b> to <code>NinjaInventoryAttributeSet:BackpackSlots</code>.</step>
    <step>
        <p>Set your <b><a href="inv_container_and_layout.md">Item Compatibility Query</a></b> to support <b>any items</b>.</p>
        <img src="inv_add_container_backpack_query.png" alt="Backpack Container Query" border-effect="line"/>
    </step>
    <step>
        <p>When you are done, your <b>Backpack Container</b> should look like this.</p>
        <img src="inv_add_container_backpack_data.png" alt="Backpack Container Data Asset" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create a Primary Item Container" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Container Definition</b>.</step>
    <step>Name your new container asset <code>Container_Primary_Item_A</code> and open it.</step>
    <step>Set the value <code>Primary Weapon</code> to the <b>Display Name</b> property.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Primary.A</code> Gameplay Tag, to identify this container.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Equipment</code> Gameplay Tag, to mark this as an <b>equipment</b> container.</step>
    <step>Set the <b>Default State Tag</b> to <code>Equipment.State.Deactivated</code>, to determine the initial state of equipment instances added to this container.</step>
    <step>
        <p>Set your <b><a href="inv_container_and_layout.md">Item Compatibility Query</a></b> to support <b>any weapons except for shields</b>.</p>
        <img src="inv_add_container_primary_a_query.png" alt="Primary Item A Container Query" border-effect="line"/>
    </step>
    <step>
        <p>When you are done, your <b>Primary Item A Container</b> should look like this.</p>
        <img src="inv_add_container_primary_a_data.png" alt="Primary Item A Data Asset" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create a Secondary Item Container" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Container Definition</b>.</step>
    <step>Name your new container asset <code>Container_Primary_Item_B</code> and open it.</step>
    <step>Set the value <code>Secondary Weapon</code> to the <b>Display Name</b> property.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Primary.B</code> Gameplay Tag, to identify this container.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Container.Equipment</code> Gameplay Tag, to mark this as an <b>equipment</b> container.</step>
    <step>Set the <b>Default State Tag</b> to <code>Equipment.State.Deactivated</code>, to determine the initial state of equipment instances added to this container.</step>
    <step>Set the <b>priority</b> to <code>2</code>. This gives the secondary slot a lower priority than the primary one.</step>
    <step>
        <p>Set your <b><a href="inv_container_and_layout.md">Item Compatibility Query</a></b> to support <b>off-hand weapons, including shields</b>.</p>
        <img src="inv_add_container_primary_b_query.png" alt="Primary Item B Container Query" border-effect="line"/>
    </step>
    <step>
        <p>When you are done, your <b>Primary Item B Container</b> should look like this.</p>
        <img src="inv_add_container_primary_b_data.png" alt="Primary Item B Data Asset" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create an Inventory Layout" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>container data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category and then <b>Inventory Layout</b>.</step>
    <step>Name your new container asset <code>Layout_Player</code> and open it.</step>
    <step>Type <code>Inventory</code> in the <b>Display Name</b> property, or select a value from a String Table.</step>
    <step>Notice the <b>Default Container Query</b>. It will look for Containers marked as <code>Default</code>.</step>
    <step>Add the <b>containers</b> created in the previous steps.</step>
    <step>
        <p>When you are done, your <b>Inventory Layout</b> should look like this.</p>
        <img src="inv_add_container_layout_data.png" alt="Inventory Layout with Backpack and Primary Items" border-effect="line"/>
    </step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_container_and_layout.md" summary = "Containers, Inventory Layouts and how they are related.">Containers and Layouts</a>
    </category>
</seealso>