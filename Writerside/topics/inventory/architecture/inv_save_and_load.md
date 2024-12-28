# Save and Load
<primary-label ref="inventory"/>

## Saving the Inventory
To save the Inventory, you need to use the `NinjaInventorySaveGame` class, which is able to serialize the Inventory 
Manager's properties, along with all Containers, Items and their Fragment Memories.

It's important to call the `SaveInventory` function, providing the Inventory Manager that you want to save. This is
the function responsible for obtaining the serialized inventory data and adding it to the save file.

Here is an example of how to perform a save operation.

<img src="inv_save.png" alt="Saving the Player Inventory" thumbnail="true" border-effect="line" width="600"/>

## Loading the Inventory
To load the Inventory, once again you need to use the `NinjaInventorySaveGame` class, which is able to deserialize the
Inventory Manager's properties, along with all Containers, Items and their Fragment Memories.

Here is an example of how to perform a load operation.

<img src="inv_load.png" alt="Loading the Player Inventory" thumbnail="true" border-effect="line" width="600"/>

## Data Serialization
<secondary-label ref="advanced"/>

The following image shows what a serialized and saved inventory looks like, from a data structure perspective.

<img src="inv_save_output.png" alt="Serialized Inventory" thumbnail="true" border-effect="line" width="600"/>

> The data view for the serialized inventory structure was obtained using the **Save File Editor** plugin, by Hubber
> Studios. For more information, please check the links below.

As you can see, it contains all containers, items and their memories from the provided Inventory Manager. They can be 
used to restore the inventory to that exact state.

The Serialization and Deserialization processes are separate from the actual Save and Load. This allows you to use
the serialized structure for any purposes you might need, and even replace the entire saving mechanism with your own.

You can obtain the Serialization structure by calling the `GetInventoryRecordForSerialization` function, available in 
the Inventory Manager. It will provide a `FInventoryManagerRecord` struct, containing all the data displayed in the 
example above.

You can also load an Inventory Manager Record back into the inventory, by calling the `LoadInventory`, which resets
the inventory data and loads the one provided by the incoming `FInventoryManagerRecord`.

<seealso style="cards">
   <category ref="external" >
    <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/saving-and-loading-your-game-in-unreal-engine">Official documentation</a>
    <a href="https://www.tomlooman.com/unreal-engine-cpp-save-system/">Save System article by Tom Looman</a>
    <a href="https://www.unrealengine.com/marketplace/en-US/product/save-file-editor">Save File Editor in the UE Marketplace</a>
   </category>
</seealso>
