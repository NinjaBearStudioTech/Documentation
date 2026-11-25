# Set Up Ninja G.A.S.
<primary-label ref="gas"/>

## Prerequisites

Start with an Unreal project and a test level. Ninja G.A.S. uses Unreal's Gameplay Ability System. For numeric values such as energy, supply an Attribute Set from your project or a plugin. You can give a character an ability without adding an Attribute Set.

## Setup Checklist

| Step | When you need it | Where to go |
| --- | --- | --- |
| Install and enable Ninja G.A.S. and its engine dependencies. | Every project | [Install plugins](installing_plugins.md) |
| Register the primary asset type for your ability bundles. | When creating G.A.S. Setup assets | [Asset Manager](asset_manager.md) |
| Add the modules your game references to its Build.cs file. | C++ classes using Ninja G.A.S. or Unreal ability types | See the example below. |

In **Project Settings → Asset Manager → Primary Asset Types to Scan**, add `AbilityBundleData` with base class `NinjaGASDataAsset`. Leave **Has Blueprint Classes** off. Add the folder where you will save your bundles, for example `/Game/Data/Abilities/Bundles`, and choose **Always Cook**. Save the settings and restart the editor.

<img src="gas_setup_data_asset.png" alt="Ability bundle scan settings in the Asset Manager" thumbnail="true" border-effect="line"/>

<code-block lang="c#" src="gas_setup_build.cs" collapsible="true" collapsed-title="Example C++ module dependencies"/>

## Ability System Initialization

The Ninja G.A.S. subsystem initializes Unreal's global ability data at startup. Each character still needs its own owner, avatar, and setup asset. Continue to [Give a Character an Ability System](gas_first_steps.md).
