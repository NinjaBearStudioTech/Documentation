# Set Up Ninja Factions
<primary-label ref="factions"/>

## Prerequisites

Start with an Unreal project and a level where you can play as one character and place an enemy. Ninja Factions supplies the components and controllers needed for the first walkthrough.

## Setup Checklist

| Step | When you need it | Where to go |
| --- | --- | --- |
| Enable Ninja Factions. | Every project | [Install plugins](installing_plugins.md) |
| Add the `NinjaFactions` module to your project dependencies. | C++ classes that use the plugin | [Work with plugin source](installing_plugins.md) |
| Register the folder that contains your faction assets. | Projects using the built-in asset database | [Asset Manager](asset_manager.md) |
| Choose how one actor judges another. | Keep the default for fixed teams, or select reputation for changing relationships. | [Reputation and Attitude](fct_reputation_tiers.md) |

<procedure title="Register your faction folder">
    <step><p>In the Content Browser, create a folder for faction assets, for example <b>Content/Data/Factions</b>.</p></step>
    <step><p>Open <b>Edit → Project Settings → Asset Manager → Primary Asset Types to Scan</b>. Add or update the entry for <code>FactionSetup</code>. Set <b>Asset Base Class</b> to <code>NinjaFactionDataAsset</code>.</p></step>
    <step><p>Add your folder under <b>Directories</b>, for example <code>/Game/Data/Factions</code>. Leave <b>Has Blueprint Classes</b> and <b>Is Editor Only</b> off. Use <b>Always Cook</b> to include these factions in packaged builds. Save the settings and restart the editor.</p></step>
</procedure>

<img src="fct_setup_asset_manager.png" alt="FactionSetup entry in Unreal's Asset Manager" width="780" border-effect="line"/>

The shared [Asset Manager guide](asset_manager.md) includes the matching configuration entry.

## Choose the Relationship Rules

Open **Project Settings → Ninja Factions**. For a first game with fixed teams, keep **Faction Database Class** on **Faction Database: Data Assets** and **Faction Solver Class** on **Faction Attitude Solver: Simple Attitude Check**. The plugin uses **Default Team** (initially No Team) and **Default Attitude** (initially Neutral) as fallbacks when it cannot resolve a team or attitude.

For a game where quests change how a faction sees the player, choose **Target Reputation** and assign a **Reputation Table**. You can make that change after the first team test. See [Reputation and Attitude](fct_reputation_tiers.md).

## First Steps

[Give two actors opposing factions](fct_first_steps.md) to check your setup in play.
