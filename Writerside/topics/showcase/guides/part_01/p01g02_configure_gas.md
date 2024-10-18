# Configure the Gameplay Ability System
<secondary-label ref="guide"/>

<video src="https://youtu.be/T_rtZjQz-9A" preview-src="sc_thumbnail_p01g02.png" width="800" />

Using **Ninja GAS**, you can configure the Gameplay Ability System in your project and prepare your Player Character,
so it can use the Combat Attribute Set provided by **Ninja Combat**.

<procedure title="Add Ninja GAS and Combat to your project" collapsible="true">
    <step>Follow the steps from the <b><a href="gas_setup.md">Ninja GAS setup page</a></b>.</step>
    <step>Follow the steps from the <b><a href="cbt_setup.md">Ninja Combat setup page</a></b>.</step>
</procedure>

<procedure title="Configure the Combat Attribute Data Table" collapsible="true">
    <step>Create a <b>Data Table</b> using <code>AttributeMetaData</code> as the <b>row type</b>.</step>
    <step>
        <p>Save the sample <b><a href="cbt_attributes.md#initialization-data">Json data</a></b> to your computer and <b>import it</b> in your Data Table, by pressing the <b>Reimport</b> button.</p>
        <img src="p01g02_player_attribute_table.png" alt="Player Attribute Table" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Create the Player Abilities Data Set" collapsible="true">
    <step>
        <p>Create a <b>GAS Setup</b>, either using the contextual menu or creating a data asset based on <code>NinjaGASDataAsset</code>.</p>
        <p>Make sure to create this Data Asset in the folder configured in the <b>Asset Manager</b>, during the <b>initial setup for Ninja G.A.S.</b>.</p>
        <img src="p01g02_create_gas_setup.png" alt="Create GAS Data Asset" thumbnail="true" border-effect="line"/>
    </step>
    <step>
        <p>Open the Data Asset, add a new entry to <b>Default Attribute Sets</b> and set <code>NinjaCombatAttributeSet</code> to <b>Attribute Set Class</b>. As for the <b>Attribute Table</b>, add the Data Table created on the previous step.</p>
        <p>Add a new entry to <b>Default Gameplay Effects</b> and set <code><a href="cbt_effects.md#vital-stats">CombatEffect_ReplenishStamina</a></code> to <b>Gameplay Effect Class</b>, this will be useful later!</p>
        <img src="p01g02_player_gas_data_asset.png" alt="Configure GAS Data Asset" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Create a GAS-compatible Player State" collapsible="true">
    <step>Create a new <b>Blueprint Class</b> selecting <code>NinjaGASPlayerState</code> as the base class.</step>
    <step>
        <p>Open the new <b>Player State</b>, select the <b>Ability System Component</b> and set the Data Asset that was created in the previous setup as the <b>Default Ability Setup</b>.</p>
        <img src="p01g02_player_state_asc_setup.png" alt="Player State and ASC Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>Set your new <b>Player State</b> to your <b>Game Mode</b>.</step>
</procedure>

<procedure title="Reparent the Player Character" collapsible="true">
    <step>Open your <b>Character Blueprint</b> and reparent it to <code>NinjaGASPlayerCharacter</code>.</step>
    <step>
        <p>In your player <b>Animation Blueprint</b>, add a <b>slot</b> for the Attack Abilities, such as <b>Default Slot</b> or <b>Full Body</b> for example.</p>
        <img src="p01g02_animation_blueprint.png" alt="Player State and ASC Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <tip>You can also create a new character if you prefer. If you do, then make sure to set the proper base class and configure it in your Game Mode!</tip>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press <b>play</b>, you should see your <b>Player Character</b>, as usual.</step>
    <step>Type the following command in your <b>Console</b>: <code>showdebug AbilitySystem</code></step>
    <step>
        <p>Back in your game, you should see lots of GAS-related information, including all attributes from <b>Ninja Combat</b>.</p>
        <img src="p01g02_gas_debug.png" alt="GAS Debug" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>
