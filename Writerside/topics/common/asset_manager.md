# Asset Manager

Unreal Engine's **Asset Manager** provides a centralized way to identify, discover, load, and manage important game assets.

Some Ninja Bear Studio plugins use **Primary Data Assets** to define core gameplay data such as ability bundles, inventory 
items, inventory containers, bot setup data, and faction setup data. These assets are often referenced softly, loaded on 
demand, or queried as part of a runtime database.

Registering these assets with the Asset Manager allows the plugins to discover and load them reliably **without requiring 
hard references** everywhere in the project. This helps reduce **unnecessary memory usage**, keeps systems **data-driven**, 
and allows larger gameplay databases to remain **scalable**.

## Adding Primary Assets
To add primary assets, register each required asset type in Unreal Engine's Asset Manager by defining its Primary Asset 
Type, Asset Base Class, scan directories, and cook rule.

Use the table below to add the required entries for each Ninja Bear Studio plugin enabled in your project.

<procedure title="Adding Primary Assets to the Asset Manager" collapsible="true" default-state="expanded">
    <step>In the editor, open <b>Edit</b> &rarr; <b>Project Settings</b>.</step>
    <step>Navigate to <b>Game</b> &rarr; <b>Asset Manager</b>.</step>
    <step>Find the <b>Primary Asset Types to Scan</b> list.</step>
    <step>Add a new entry for each asset type required by the plugins you are using.</step>
    <step>Set the <b>Primary Asset Type</b> and the <b>Asset Base Class</b> using the values listed in the table below, under <b>Asset Name</b> and <b>Base Class</b> columns.</step>
    <step>Select one or more <b>Directories</b> where assets of that type will be stored. Consider the suggested folder structure below, or adjust it to your needs.</step>
    <step>Set the <b>Cook Rule</b> to <b>Always Cook</b>.</step>
    <step>Save the project settings and restart the editor.</step>
</procedure>

Use the following entries based on the plugins enabled in your project.

| Plugin          | Asset Name               | Base Class                         | Purpose                                                                                   | Recommended Folder           |
|-----------------|--------------------------|------------------------------------|-------------------------------------------------------------------------------------------|------------------------------|
| Ninja Bot       | `BotSetupData`           | `NinjaBotSetupDataAsset`           | Defines perception, awareness, and related setup data used by AI agents.                  | `/Game/Data/Bots`            |
| Ninja Combat    | `FirearmData`            | `NinjaCombatFirearmDataAsset`      | Defines features related to firearms in the combat system.                                | `/Game/Data/Firearms`        |
| Ninja G.A.S.    | `AbilityBundleData`      | `NinjaGASDataAsset`                | Bundles Attribute Sets, Gameplay Effects, and Gameplay Abilities to be granted.           | `/Game/Data/Ability/Bundles` |
| Ninja Factions  | `FactionSetup`           | `NinjaFactionDataAsset`            | Defines faction data used for memberships, reputation, and attitude resolution.           | `/Game/Data/Factions`        |
| Ninja Inventory | `InventoryContainerData` | `NinjaInventoryContainerDataAsset` | Defines inventory containers, which represent regions or areas where items can be stored. | `/Game/Data/Containers`      |
| Ninja Inventory | `InventoryItemData`      | `NinjaInventoryItemDataAsset`      | Defines inventory items through fragments and reusable item data.                         | `/Game/Data/Items`           |

<tip>
    <p>You don't need to follow the folder structure above, but it's recommended to keep Primary Gameplay Data Assets grouped under a <code>Data</code> folder, then separated by <b>plugin</b> or <b>purpose</b>.</p>
</tip>

## Modifying DefaultGame.ini
<secondary-label ref="advanced"/>
Alternatively, you can add the following entries to your <code>DefaultGame.ini</code> file.

If you decide to configure the Asset Manager this way, make sure to keep any existing entries already present under `AssetManagerSettings`, 
either before or after the entries below. **Add only the entries required by the plugins enabled in your project**. 

```ini
[/Script/Engine.AssetManagerSettings]
+PrimaryAssetTypesToScan=(PrimaryAssetType="AbilityBundleData",AssetBaseClass="/Script/NinjaGAS.NinjaGASDataAsset",bHasBlueprintClasses=False,bIsEditorOnly=False,Directories=((Path="/Game/Data/Abilities/Bundles")),SpecificAssets=,Rules=(Priority=-1,ChunkId=-1,bApplyRecursively=True,CookRule=AlwaysCook))
+PrimaryAssetTypesToScan=(PrimaryAssetType="InventoryContainerData",AssetBaseClass="/Script/NinjaInventory.NinjaInventoryContainerDataAsset",bHasBlueprintClasses=False,bIsEditorOnly=False,Directories=((Path="/Game/Data/Containers")),SpecificAssets=,Rules=(Priority=-1,ChunkId=-1,bApplyRecursively=True,CookRule=AlwaysCook))
+PrimaryAssetTypesToScan=(PrimaryAssetType="InventoryItemData",AssetBaseClass="/Script/NinjaInventory.NinjaInventoryItemDataAsset",bHasBlueprintClasses=False,bIsEditorOnly=False,Directories=((Path="/Game/Data/Items")),SpecificAssets=,Rules=(Priority=-1,ChunkId=-1,bApplyRecursively=True,CookRule=AlwaysCook))
+PrimaryAssetTypesToScan=(PrimaryAssetType="FirearmData",AssetBaseClass="/Script/NinjaCombatFirearm.NinjaCombatFirearmDataAsset",bHasBlueprintClasses=False,bIsEditorOnly=False,Directories=((Path="/Game/Data/Firearms")),SpecificAssets=,Rules=(Priority=-1,ChunkId=-1,bApplyRecursively=True,CookRule=AlwaysCook))
+PrimaryAssetTypesToScan=(PrimaryAssetType="FactionSetup",AssetBaseClass="/Script/NinjaFactions.NinjaFactionDataAsset",bHasBlueprintClasses=False,bIsEditorOnly=False,Directories=((Path="/Game/Data/Factions")),SpecificAssets=,Rules=(Priority=-1,ChunkId=-1,bApplyRecursively=True,CookRule=AlwaysCook))
+PrimaryAssetTypesToScan=(PrimaryAssetType="BotSetupData",AssetBaseClass="/Script/NinjaBot.NinjaBotSetupDataAsset",bHasBlueprintClasses=False,bIsEditorOnly=False,Directories=((Path="/Game/Data/Bots")),SpecificAssets=,Rules=(Priority=-1,ChunkId=-1,bApplyRecursively=True,CookRule=AlwaysCook))
```