# Save and Load
<primary-label ref="inventory"/>
<secondary-label ref="advanced"/>

<tldr>
    <ul>
        <li>The Inventory System supports <b>saving</b> and <b>loading</b> operations using the Unreal Engine framework.</li>
        <li>An inventory can optionally be <b>automatically loaded</b> from a save slot during its initialization.</li>
        <li>All <b>serialization</b> and <b>deserialization</b> occurs in functions that can be extended in <b>Blueprint</b> or <b>C++</b>.</li>
    </ul>
</tldr>

## Saving the Inventory
To save an inventory, use the `NinjaInventorySaveGame` class. This class can serialize the Inventory Manager's properties, 
along with its Containers, Items, and their Fragment Memories.

Call the `SaveInventory` function (defined in the `NinjaInventorySaveGame` object) and pass the Inventory Manager you want 
to save. This function gathers the current inventory state and stores it in the Save Game Object, which can then be saved 
using Unreal Engine's standard save flow.

The following example will walk you through these general steps. It's done using a **debug key** in the **Player Character** 
blueprint, but you can perform the save operation wherever it is appropriate for your game.

<procedure title="Saving the Inventory" collapsible="true" default-state="expanded">
    <img src="inv_advanced_save.png" alt="Saving the Player Inventory" thumbnail="true" border-effect="line" width="600"/>
    <step>
        <p>Retrieve and validate the Inventory Manager Component from your actor using <code>GetInventoryManager</code>, available in the Inventory Blueprint Library.</p>
        <note>
            <p><b>This is a smart function!</b></p>
            <p><code>GetInventoryManager</code> can find the Inventory Manager across related classes. For example, you can call it from your Character or Pawn even if the Inventory Manager is in the Player State—and vice versa.</p>
        </note>
    </step>
    <step>Create a <b>Save Game Object</b> using <code>NinjaInventorySaveGame</code> as the <b>Save Game Class</b>.</step>
    <step>Call <code>SaveInventory</code> on the Save Game Object, passing in the <b>Inventory Manager</b> to be serialized.</step>
    <step>
        <p>Perform an <b>asynchronous save operation</b>, providing the desired <b>slot</b> and <b>user index</b>.</p>
        <note>
            <p><b>Synchronize the slot and index</b></p>
            <p>Make sure to use the same <b>slot</b> and <b>index</b> set in the Inventory Manager. This ensures it can automatically load the correct data later.</p>
        </note>
    </step>
    <step>Optionally track the result (e.g., print a message or update UI elements).</step>
</procedure>

You can verify the generated save file using any tool, such as the **[Save File Editor](https://www.fab.com/listings/8feaccda-c2fb-4319-a8e2-da770bdb97c2)**,
available on Fab. 

Next, we'll look into the **loading** operation, which can be executed either **automatically** or **manually**.

## Loading the Inventory
Once a saved inventory file exists, it can be loaded back into the Inventory Manager using the same base classes and 
functions used during saving.

The loading process can be performed either **manually** (e.g., triggered by the player or game logic) or **automatically** 
(during initialization). The example below demonstrates a manual approach using a debug key in the Player Character blueprint.

To load the data, you need to call the `LoadInventory` function from a `NinjaInventorySaveGame` object after successfully 
loading it from disk.

<procedure title="Loading the Inventory" collapsible="true" default-state="expanded">
    <img src="inv_advanced_load.png" alt="Loading the Player Inventory" thumbnail="true" border-effect="line" width="600"/>
    <step>Use <code>GetInventoryManager</code> to retrieve the Inventory Manager for the actor that should receive the inventory state.</step>
    <step>Validate the returned reference with <code>Is Valid</code>. If it is not valid, skip the rest of the logic.</step>
    <step>Obtain the <b>slot name</b> and <b>user index</b> from the Inventory Manager using <code>Get Save Game Slot Name</code> and <code>Get Save Game User Index</code>.</step>
    <step>Call <code>Async Load Game from Slot</code>, passing in the slot name and user index retrieved above.</step>
    <step>Check the success of the operation, and cast the returned object to <code>NinjaInventorySaveGame</code>.</step>
    <step>Call <code>LoadInventory</code> on the Save Game object, providing the Inventory Manager reference. This will apply the saved Containers, Items, and Fragment Memories to the manager.</step>
    <step>Optionally track the result (e.g., print a message or update UI elements).</step>
</procedure>

### Automatic Loading
The Inventory System also supports **automatic loading** of saved data, which can occur during the initialization of 
the Inventory Manager, without requiring any manual logic.

This behavior is controlled by the following Inventory Manager settings:

| Property                     | Description                                                                                                                                    |
|------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------|
| `bAutomaticallyLoadFromDisk` | If enabled, the Inventory Manager will automatically attempt to load inventory data from disk when it is initialized.                          |
| `SaveGameSlotName`           | The name of the slot to load from. This value is also used during save operations. You can retrieve it at runtime using `GetSaveGameSlotName`. |
| `SaveGameUserIndex`          | The user index to load from. You can override `GetSaveGameUserIndex` to implement dynamic logic if needed.                                     |

If a save file is present for the specified slot and index, the inventory will be automatically restored—no extra calls 
are needed. If the file is missing, the initialization happens normally, potentially loading default items as needed.

This setup is ideal for player inventories that should persist across sessions or respawns, without requiring explicit 
save/load Blueprint logic during gameplay.
