# First Steps with Ninja Factions
<primary-label ref="factions"/>

This page guides you through the first steps for **Ninja Factions**. Make sure to check the [**Factions Setup**](fct_setup.md)
instructions before continuing.

This page has no plugin assumptions, but it can also support projects using [**Ninja Bot**](bot_overview.md), since both
systems can integrate through Unreal Engine's AI and Team framework.

The following steps aim to provide **an initial setup with two factions**: one representing the player and another
representing enemies. These factions will be assigned to controllers so they can participate in team and attitude
resolution.

## Faction Assets

The most important faction-related asset introduced by Ninja Factions is the **Faction Data Asset**. It defines
how factions are supposed to react to each other, including special exception cases established by an **Attitude Matrix**.

Most importantly, each faction is defined by a unique **identifying Gameplay Tag** and a **Team ID** used by Unreal 
Engine's Team and Attitude framework.

<procedure title="Create the Faction Assets" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new <b>Faction Data Asset</b> named <b>Players</b> in the Factions folder configured in the Asset Manager.</p> 
        <p>You can do so by right-clicking an empty area in the <b>Content Browser</b>, then navigating to <b>Ninja Bear Studio</b> &rarr; <b>Ninja Factions</b> &rarr; <b>Faction</b>.</p>
    </step>
    <step>
        <p>Set <code>Factions.ID.Players</code> as the <b>Faction Tag</b> and <code>1</code> as the <b>Team ID</b>.</p>
        <p>Notice that <b>Team Attitude Towards My Faction</b> is <b>Friendly</b> and <b>Team Attitude Towards Other Factions</b> is <b>Neutral</b>.</p>
        <img src="fct_faction_players.png" alt="Players Faction" border-effect="line"/>
    </step> 
    <step>
        <p>Create another <b>Faction Data Asset</b> named <b>Zombies</b>, or another relevant enemy type.</p>
    </step>
    <step>
        <p>Set <code>Factions.ID.Enemies.Zombies</code> as the <b>Faction Tag</b> and <code>10</code> as the <b>Team ID</b>.</p>
        <p>Set <b>Team Attitude Towards My Faction</b> to <b>Neutral</b> and <b>Team Attitude Towards Other Factions</b> to <b>Hostile</b>.</p>
        <img src="fct_faction_zombies.png" alt="Zombies Faction" border-effect="line"/>
    </step>  
</procedure>

## Faction Members

Faction Members are possessed Pawns or Characters that own a **Faction Component** (`NinjaFactionComponent`). This component
is responsible for managing **memberships** and **reputations** (if applicable).

<procedure title="Add the Faction Component and Membership" collapsible="true" default-state="expanded">
    <step>Add the <b>Faction Component</b>, <code>NinjaFactionComponent</code>, to your base Pawn or Character (Blueprint or C++).</step>
    <step>Add the <b>Faction Member Interface</b>, <code>FactionMemberInterface</code>, as well.</step>
    <step>
        <p>Implement/override the interface function, <code>GetFactionComponent</code>, so it returns the <b>Faction Component</b>.</p>
        <tabs group="sample">
             <tab title="Blueprint" group-key="bp">
                <img src="fct_setup_component.png" alt="Faction Component Assignment" thumbnail="true" border-effect="line"/>
                <br/>
                <img src="fct_member_interface.png" alt="Faction Member Interface" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="C++" src="fct_setup_faction_component.h"/>
                <br/>
                <code-block lang="C++" src="fct_setup_faction_component.cpp"/>
            </tab>
        </tabs>        
    </step>
    <step>
        <p>In your <b>Player Subclass</b>, navigate to the Faction Component and, in <b>Default Factions</b>, add a new entry for <b>Player Faction</b> data asset.</p>
        <p>Mark this as the <b>Main Faction</b> and optionally, set the <b>Reputation</b> to a high value, such as <code>9999</code> (you can adjust this later if you introduce reputations).</p>
    </step>
    <step>
        <p>In your <b>Enemy Subclass</b>, navigate to the Faction Component and, in <b>Default Factions</b>, add a new entry for <b>Zombie Faction</b> data asset.</p>
        <p>Mark this as the <b>Main Faction</b> and optionally, set the <b>Reputation</b> to a high value, such as <code>9999</code> (you can adjust this later if you introduce reputations).</p>
    </step>
</procedure>

## Controllers

Unreal Engine's **Team and Attitude Framework** is controller-centric, so your AI and Player Controllers must be able
to provide the **Faction's Team ID**, from their possessed pawn's **Main Faction**. The AI Module expects this through 
the `GenericTeamAgentInterface`.

### AI Controller

The AI Controller already implements `GenericTeamAgentInterface`, so all that is left is to extend the implementation,
so it retrieves the Faction from the Pawn's **Faction Component**. You have two options here, depending on whether you
are using [**Ninja Bot**](bot_overview.md) or not.

#### Standalone

When not using Ninja Bot, the Faction System provides a base **AI Controller**, `NinjaFactionAIController`, that can be
used as your base AI Controller. This class is able to retrieve the Faction Component from its possessed Pawn and, by using 
the system's **Attitude Provider**, determine the correct attitude between the agent and its sensed targets. 

#### Ninja Bot

If you are using Ninja Bot, then you can ignore the AI Controller provided by Ninja Factions and continue to use the one
provided by Ninja Bot instead. All you need to do to connect both systems is to select the correct **Team Provider Class**,
in the Ninja Bot's settings.

For more information, check the [**Bot and Factions Integration Page**](bot_ninja_factions.md).

### Player Controller

The base Player Controller provided by Unreal Engine does not implement the expected `GenericTeamAgentInterface`, and 
this interface is not implementable in Blueprints.

The Faction System provides a base **Player Controller**, `NinjaFactionPlayerController`, that is able to retrieve the
Faction Component from its possessed Pawn, and use it to determine the **Team ID** for the **AI System**. Alternatively,
you can use your own variation, as long as you replicate the same behavior.

## Next Steps

At this point, you have an initial faction setup with a **Player** faction and an **Enemy** faction assigned to faction 
members, with controllers able to expose team information to Unreal Engine's AI system.

From here, you can:

- Create [**Reputation Tiers**](fct_reputation_tiers.md) to support more dynamic faction relationships.
- Integrate [**Ninja Factions with Ninja Combat**](itg_combat_factions.md) to disable or customize Friendly Fire.
- Learn more about [**Factions and Memberships**](fct_factions_memberships.md).