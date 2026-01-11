# Team and Attitude Configuration
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

At this point, the Bot is perceiving the player as a **friendly target**, since no team or attitude resolution has been configured.

Ninja Bot separates team resolution logic through the use of [**Team Providers**](bot_advanced_ninja_factions.md). It natively
supports two options: Unreal Engine’s **Team Agent Interface** and [**Ninja Factions**](fct_overview.md).

Before starting, make sure you have completed the previous steps or have an equivalent setup.

<tabs group="team_mode">
<tab title="Team Agent Interface" group-key="agent_interface">

<!-- BEGIN: TEAM INTERFACE SETUP -->
<note>
    <p>Your environment must be configured to work with <b>C++</b>, including enabling the <a href="bot_setup_installation.md" alt="Bot Installation"><b>C++ modules used by Ninja Bot</b></a>.</p>
</note>

<procedure title="Implement the Team Agent Interface" collapsible="true" default-state="collapsed">
<step>
    <p>Create a new C++ class extending <code>APlayerController</code>. Add <code>IGenericTeamAgentInterface</code> to the class declaration, declare an override for <code>GetGenericTeamId</code>, and create a <code>uint8</code> property named <b>TeamId</b>.</p>
    <code-block lang="C++" src="bot_player_controller.h"/>
</step>
<step>
    <p>Switch to the implementation file and implement <code>GetGenericTeamId</code>, returning a <code>FGenericTeamId</code> constructed from the <b>TeamId</b> value.</p>
    <code-block lang="C++" src="bot_player_controller.cpp"/>
</step>
</procedure>

<procedure title="Set the Default Team Provider" collapsible="true" default-state="collapsed">
<step>
    <p>Navigate to Ninja Bot’s default properties: Edit &rarr; Project Settings &rarr; Ninja Bot.</p>
</step>
<step>
    <p>Set <code>NinjaBotTeamProvider</code> as the <b>Team Provider Class</b>.</p>
    <img src="bot_guide_team_default_provider.png" alt="Using Default Team Resolution" width="780" border-effect="line"/>
</step>
</procedure>
<!-- END: TEAM INTERFACE SETUP -->

</tab>
<tab title="Ninja Factions" group-key="ninja_factions">

<!-- BEGIN: NINJA FACTIONS SETUP -->
<note>
    <p>Make sure that <a href="fct_overview.md"><b>Ninja Factions</b></a> is added and configured in your project. Don’t forget to add the <b>Faction Component</b> to your base Character class.</p>
</note>

<procedure title="Create the Player Faction" collapsible="true" default-state="collapsed">
<step>
    <p>In your Faction Data folder, create a new <b>Faction</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Factions &rarr; Faction. Name this faction <b>Players</b>.</p>
</step>
<step>
    <p>Configure the Player Faction with an appropriate <b>Display Name</b>, <b>Faction Tag</b>, and set the <b>Team ID</b> to <code>1</code>. The default attitude settings are sufficient for this setup.</p>
    <img src="bot_guide_team_factions_player.png" alt="Player Faction" width="780" border-effect="line"/>
</step>
<step>
    <p>Add a new <b>membership</b> to the Player’s Faction Component and assign this faction as the <b>Main Faction</b>.</p>
</step>
</procedure>

<procedure title="Create the Enemy Faction" collapsible="true" default-state="collapsed">
<step>
    <p>In your Faction Data folder, create a new <b>Faction</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Factions &rarr; Faction. Name this faction <b>Enemies</b>.</p>
</step>
<step>
    <p>Configure the Enemy Faction with an appropriate <b>Display Name</b>, <b>Faction Tag</b>, and set the <b>Team ID</b> to <code>2</code>. Set the <b>Default Attitude Towards My Faction</b> to <code>Neutral</code> and the <b>Default Attitude Towards Other Factions</b> to <code>Hostile</code>.</p>
    <img src="bot_guide_team_factions_enemy.png" alt="Enemy Faction" width="780" border-effect="line"/>
</step>
<step>
    <p>Add a new <b>membership</b> to the Enemy’s Faction Component and assign this faction as the <b>Main Faction</b>.</p>
</step>
</procedure>

<procedure title="Set the Faction Team Provider" collapsible="true" default-state="collapsed">
<step>
    <p>Navigate to Ninja Bot’s default properties: Edit &rarr; Project Settings &rarr; Ninja Bot.</p>
</step>
<step>
    <p>Set <code>UTeamProvider_Factions</code> as the <b>Team Provider Class</b>.</p>
    <img src="bot_guide_team_factions_provider.png" alt="Using Faction Team Resolution" width="780" border-effect="line"/>
    <note>The <b>Factions Team Provider</b> is only visible if Ninja Factions is installed and enabled in your project.</note>
</step>
</procedure>
<!-- END: NINJA FACTIONS SETUP -->

</tab>
</tabs>

<procedure title="Review your Perception Profile" collapsible="true" default-state="collapsed">
<step>
    <p>Open your <b>Perception Sense Profile</b>.</p>
</step>
<step>
    <p>Modify the <b>Sight Configuration</b>, updating <b>Detection by Affiliation</b> so that only <b>Hostiles</b> are detected.</p>
    <img src="bot_guide_perception_sense_profile_hostile_only.png" alt="Revisited Sense Profile" width="780" border-effect="line"/>
</step>
</procedure>

Your Bot behavior should remain unchanged, but the AI now correctly identifies players as **hostile targets**. 
Furthermore, when using Ninja Factions, this behavior can change dynamically based on **reputation**.

