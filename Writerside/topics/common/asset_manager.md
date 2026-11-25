# Register Assets with the Asset Manager

Register the folders where your plugin looks for gameplay data. For example, the default Ninja Factions database scans for faction definitions. A saved faction can appear in the Content Browser and still be outside the folder the database searches.

## Adding Primary Assets

<procedure title="Register a folder for faction definitions">
    <step><p>In the Content Browser, create <b>Content/Data/Factions</b>. Unreal calls the project's Content folder <code>/Game</code>, so this folder's asset path is <code>/Game/Data/Factions</code>.</p></step>
    <step><p>Open <b>Edit → Project Settings → Game → Asset Manager → Primary Asset Types to Scan</b>. Add an entry for <code>FactionSetup</code>, or edit the existing entry for that type. Select <code>NinjaFactionDataAsset</code> as the <b>Asset Base Class</b>.</p></step>
    <step><p>Add <code>/Game/Data/Factions</code> under <b>Directories</b>. Leave <b>Has Blueprint Classes</b> and <b>Is Editor Only</b> off for these data assets. Set <b>Cook Rule</b> to <b>Always Cook</b> to include the scanned assets in packaged games. Save the settings and restart the editor.</p></step>
</procedure>

<img src="fct_setup_asset_manager.png" alt="FactionSetup asset type, base class, and scan directory in Project Settings" width="780" border-effect="line"/>

## Choose the Entries Your Plugin Uses

Use your own content folders if you already keep these assets elsewhere. Input bindings and the first Interaction switch can go straight to their plugin walkthroughs. [Move a template character](ipt_first_steps.md) or [interact with a nearby object](int_first_steps.md).

| When you need it | Primary Asset Type | Asset Base Class | Example directory |
| --- | --- | --- | --- |
| [Bot setups](bot_first_steps.md) | `BotSetupData` | `NinjaBotSetupDataAsset` | `/Game/Data/Bots` |
| [Combat firearm definitions](cbt_guide_firearms.md) | `FirearmData` | `NinjaCombatFirearmDataAsset` | `/Game/Data/Firearms` |
| [Factions in the asset database](fct_first_steps.md) | `FactionSetup` | `NinjaFactionDataAsset` | `/Game/Data/Factions` |
| [G.A.S. ability bundles](gas_first_steps.md) | `AbilityBundleData` | `NinjaGASDataAsset` | `/Game/Data/Abilities/Bundles` |
| [Inventory containers](inv_first_steps.md) | `InventoryContainerData` | `NinjaInventoryContainerDataAsset` | `/Game/Data/Containers` |
| [Inventory items](inv_first_steps.md) | `InventoryItemData` | `NinjaInventoryItemDataAsset` | `/Game/Data/Items` |

## Modifying DefaultGame.ini

If you manage settings in source control, the faction example corresponds to this entry in `Config/DefaultGame.ini`. Edit the existing scan entry if you already added it in Project Settings.

```ini
[/Script/Engine.AssetManagerSettings]
+PrimaryAssetTypesToScan=(PrimaryAssetType="FactionSetup",AssetBaseClass="/Script/NinjaFactions.NinjaFactionDataAsset",bHasBlueprintClasses=False,bIsEditorOnly=False,Directories=((Path="/Game/Data/Factions")),Rules=(CookRule=AlwaysCook))
```

## Check That Unreal Found the Asset

Create and save a faction in the registered folder as described in [Give Two Actors Opposing Factions](fct_first_steps.md). In the editor's Output Log, run `AssetManager.DumpTypeSummary`. Find `FactionSetup` and check that its asset count includes your new faction and its scan path matches the folder. If the count is zero, compare the asset's class and location with the entry above. Use the same check with the type name for your own plugin.
