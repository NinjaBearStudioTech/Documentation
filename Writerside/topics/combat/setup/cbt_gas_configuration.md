# G.A.S. Configuration
<primary-label ref="combat"/>

<tldr>
    <p><b>Summary: Configuring G.A.S. for Ninja Combat</b></p>
    <br/>
    <ul>
        <li>Set <b>Ability System Globals</b> via Project Settings or in <code>DefaultGame.ini</code>.</li>
        <li>Use a Ninja GAS <b>base character class</b> or any other ASC-ready class from your project.</li>
        <li>Create and assign the <b>Combat Attributes Set</b> and <b>Attribute Data Table</b>.</li>
        <li>Create and assign the <b>GAS Setup</b> Data Asset to your character's <b>Ability System Component</b>.</li>
    </ul>
</tldr>

This page will walk you through the necessary steps to prepare the **Gameplay Ability System** for **Ninja Combat**.
Make sure that you have a basic G.A.S. setup done. If you are using **[](gas_overview.md)**, then make sure to configure it first.

## Ability System Globals
The Gameplay Ability System must be configured to use the **Global Class** and the **Cue Manager** provided by the plugin.
If you have dedicated versions of these classes in your project, you will need to **reparent** them, so they inherit from
the plugin classes.

| Class                  | Base Implementation                |
|------------------------|------------------------------------|
| Ability System Globals | `UNinjaCombatAbilitySystemGlobals` |
| GameplayCueManager     | `UNinjaCombatGameplayCueManager`   |

<procedure title="Option 1: Setting GAS classes via Project Settings" collapsible="true" default-state="expanded">
    <tip>The <b>Gameplay Ability Settings</b> page is only available in Unreal Engine 5.5 and above.</tip>
    <step>In your project, navigate to <b>Edit</b> &rarr; <b>Project Settings</b>.</step>
    <step>In the <b>Settings Window</b>, select the <b>Gameplay Ability Settings</b> category.</step>
    <step>
        <p>Add the correct Ninja Combat classes, as shown in the image:</p>
        <p><img src="cbt_setup_gas.png" alt="GAS Settings Page" thumbnail="true" border-effect="line" width="600"/></p>
    </step>
</procedure>

<procedure title="Option 2: Setting GAS classes via INI files" collapsible="true" default-state="expanded">
    <step>Open your <code>DefaultGame.ini</code> file, located in the <b>Config</b> folder in your project.</step>
    <step>
        <p>Add the following contents to the <code>[AbilitySystemGlobals]</code> section:</p>
        <code-block lang="ini" src="cbt_gas_global_settings.ini"/>
    </step>
</procedure>

## Combat Attributes
Any **Pawn** or **Character** participating in combat must have a **Combat Attribute Set** assigned. The easiest way to
do that is using **[](gas_overview.md)**, but you can use any other GAS setup that you are comfortable with.

<procedure title="Configuring Combat Attributes with Ninja G.A.S." collapsible="true" default-state="expanded">
    <step>
        <p>
            Set your character's <b>base class</b> either to <code>NinjaGASCharacter</code> or <code>NinjaGASPlayerCharacter</code> depending on whether
            you want the Ability System Component to reside in the <b>Character</b> (recommended for single-player or NPCs) or the <b>Player State</b> (commonly used for multiplayer characters).
        </p>
    </step>
    <step>Create a <b>Data Table</b> for your Combat Attributes, using the <code>AttributeMetaData</code> row structure.</step>
    <step>Download the <b><a href="cbt_gameplay_attributes.md#initialization-data">Sample Initialization Data</a></b> and use it as the table data.</step>
    <step>Create a new <b>G.A.S. Setup Data Asset</b> and add a new <b>Default Attribute Set</b> entry.</step>
    <step>Add the <code>Ninja Combat Attribute Set</code> class and the data table as the <b>Attribute Table</b>.</step>
    <step>Set the new GAS Setup Data to your player character's Ability System Component.</step>
</procedure>
