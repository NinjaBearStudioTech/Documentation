# Asset Manager and Data Assets
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary:Asset Manager and Data Assets</b></p>
    <br/>
    <ul>
        <li>Players will have their Inventory Manager in the <b>Player State</b>. Other pawns and actors will have it in their actual classes.</li>
        <li>All actors that having an Inventory Manager should implement the <b>Inventory System Interface</b>.</li>
    </ul>
</tldr>

Ninja Inventory provides multiple **Primary Data Assets** used to represent its data domain. These must be registered 
with the **Asset Manager**, so it can load them on demand, whenever necessary.

## Container Data Assets
Container Data Assets are the primary representation of a **Container**, which can be thought of as a _region_ or _area_
of an inventory. 

<procedure title="Registering Container Data Assets" collapsible="true" default-state="expanded">
    <step>Open the <b>Asset Manager Settings</b>, located in <b>Edit</b> &rarr; <b>Project Settings</b> &rarr; <b>Asset Manager</b>.</step>
    <step>Add a new entry to the <b>Primary Data Asset Type to Scan</b> list.</step>
    <step>Set <code>InventoryContainerData</code> as the <b>Primary Asset Type</b>.</step>
    <step>Set <code>NinjaInventoryContainerDataAsset</code> as the <b>Asset Base Class</b>.</step>
    <step>Select one or many folders in your project where you will store Container Data Assets.</step>
    <img src="inv_setup_asset_manager_containers.png" alt="Container Setup in the Asset Manager" thumbnail="true" border-effect="line"/>
</procedure>

## Item Data Assets
Item Data Assets are the primary representation of an **Item**, which are defined by **aggregation** using **Fragments**
and then added to an inventory.

<procedure title="Registering Item Data Assets" collapsible="true" default-state="expanded">
    <step>Open the <b>Asset Manager Settings</b>, located in <b>Edit</b> &rarr; <b>Project Settings</b> &rarr; <b>Asset Manager</b>.</step>
    <step>Add a new entry to the <b>Primary Data Asset Type to Scan</b> list.</step>
    <step>Set <code>InventoryItemData</code> as the <b>Primary Asset Type</b>.</step>
    <step>Set <code>NinjaInventoryItemDataAsset</code> as the <b>Asset Base Class</b>.</step>
    <step>Select one or many folders in your project where you will store Item Data Assets.</step>
    <img src="inv_setup_asset_manager_items.png" alt="Item Setup in the Asset Manager" thumbnail="true" border-effect="line"/>
</procedure>