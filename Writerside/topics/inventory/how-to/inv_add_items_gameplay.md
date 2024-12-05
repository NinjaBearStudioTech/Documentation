# Adding Items during Gameplay
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

This how-to will show you how to **add new items** to the inventory during **gameplay**, which is a common task for 
things like **pickups**, **quest rewards**, and more.

<procedure title="Create a Health Potion definition" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>item data</b> folder. If you are creating a new folder, it should match the configuration in your <b>Asset Manager</b>.</step>
    <step>Right-click in any empty area, select the <b>Inventory</b> category, and then <b>Item Definition</b>.</step>
    <step>Name your new container asset <code>Consumable_HealthPotion</code> and open it.</step>
    <step>In the <b>Gameplay Tags</b> property, add the <code>Inventory.Item.Potion.Health</code> Gameplay Tag to identify this item.</step>
    <step>Add the <b><a href="inv_user_interface_fragment.md">User Interface Fragment</a></b> to configure how this item is presented in the user interface. Set appropriate values for it.</step>
    <step>Add the <b><a href="inv_stack_fragment.md">Stack Fragment</a></b>. Set a <code>Stack Limit</code> of <code>10</code> and a <b>Maximum Limit</b> of <code>100</code>. Set it to <b>Automatically Merge New Items</b>.</step>.
    <step>
        <p>Add the <b><a href="inv_container_fragment.md">Container Fragment</a></b> and configure your <b>Preferred Container Query</b> to prioritize the backpack container.</p>
        <img src="inv_create_item_iron_query.png" alt="Iron Bar Preferred Container Query" border-effect="line"/>
    </step>
    <step>
        <p>When you are done, your <b>Health Potion</b> should look like this (except maybe for the User Interface details).</p>
        <img src="inv_activate_add_item_potion_data.png" alt="Health Potion Item Data Asset" border-effect="line"/>
    </step>
</procedure>

<procedure title="Add the Health Potion via Gameplay" collapsible="true">
    <step>
        Create an <code>Add Health Potion</code> event to retrieve the <b>Inventory Manager</b> and add the new <b>Health Potion</b> with a default <b>stack</b> of <code>5</code>.
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <p>In your <b>Character</b>, declare a <b>Custom Event</b> named <code>Add Health Potion</code>.</p>
                <img src="inv_add_item_health_potion.png" alt="Adding Health Potions" border-effect="line" thumbnail="true"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p>In your <b>Character</b>, declare a <b>Blueprint Callable Function</b> named <code>Add Health Potion</code>.</p>
                <code-block lang="c++" src="inv_add_item_health_potion.h" />
                <br/>
                <code-block lang="c++" src="inv_add_item_health_potion.cpp" />
            </tab>
        </tabs>
    </step>
    <step>
        <p>In your <b>Character</b>, create a Blueprint event from <code>Debug Key K</code>. Drag from the execution pin and call <code>Add Health Potion</code>.</p>
        <img src="inv_add_item_health_potion_debug_event.png" alt="Adding Health Potions" border-effect="line"/>
        <tip>Normally, the item would be added from other <b>Gameplay Systems</b>, but using a <b>Debug Key</b> is a quick way to test features.</tip>
    </step>
</procedure>

<procedure title="Check your Inventory in the Gameplay Debugger" collapsible="true">
    <step><p>Hit the <b>Play</b> button and press the <code>K</code> key to <b>add the potion</b>.</p></step>
    <step>
        <p>Open the <b>Gameplay Debugger</b> to confirm that the <b>Health Potion</b> has been added to the inventory.</p>
        <img src="inv_activate_add_item_potion_debugger.png" alt="Health Potion added to the Inventory" border-effect="line" thumbnail="true" />
    </step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="inv_inventory_manager.md" summary="Inventory Manager and Layout assignment.">Inventory Manager</a>
        <a href="inv_troubleshooting.md" summary="Using the Inventory Gameplay Debugger and accessing logs.">Debugger and Logs</a>
    </category>
</seealso>