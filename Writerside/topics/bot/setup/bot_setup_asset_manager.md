# Asset Manager and Data Assets
<primary-label ref="bot"/>

<tldr>
    <p><b>Summary: Asset Manager and Data Assets</b></p>
    <br/>
    <ul>
        <li>Ninja Bot relies on a single primary data asset to configure AI behavior.</li>
        <li>This asset defines how bots evaluate perception and awareness.</li>
        <li>The asset must be registered with the Asset Manager to be loaded on demand.</li>
    </ul>
</tldr>

**Ninja Bot** uses a Primary Data Asset to represent the configuration required by AI controllers and perception components.
This asset must be registered with the **Asset Manager** so it can be discovered and loaded reliably at runtime.

## Bot Setup Data Asset
The Bot Setup Data Asset represents the high-level configuration for Ninja Bot. It defines how **perception, awareness, 
and related systems are initialized** for AI agents. 

<procedure title="Registering the Bot Setup Data Asset" collapsible="true" default-state="expanded">
    <step>Open the <b>Asset Manager Settings</b>, located in <b>Edit</b> &rarr; <b>Project Settings</b> &rarr; <b>Asset Manager</b>.</step>
    <step>Add a new entry to the <b>Primary Data Asset Type to Scan</b> list.</step>
    <step>Set <code>BotSetupData</code> as the <b>Primary Asset Type</b>.</step>
    <step>Set <code>NinjaBotSetupDataAsset</code> as the <b>Asset Base Class</b>.</step>
    <step>Select one or many folders in your project where you will store Bot Setup Data Assets.</step>
    <img src="bot_setup_asset_manager_bot_data.png" alt="Bot Setup in the Asset Manager" thumbnail="true" border-effect="line"/>
</procedure>