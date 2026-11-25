# Factions and Memberships
<primary-label ref="factions"/>

**Town Watch** is a faction. The fact that a particular character belongs to the Watch is a **membership**. Create one faction asset for the whole town, then give each member its own starting reputation and main faction.

## What Belongs on the Asset?

Give the faction a unique **Faction Tag** under `Factions.ID` and a **Team ID** for Unreal's team system. Use different team IDs for teams Unreal should tell apart. **Display Name** and **Color** are useful in a faction menu. Additional **Tags** let you group factions, for example when listing every guild in a region.

The asset also says how this faction sees its own members and other factions. A faction can make exceptions for particular neighbors. See [Reputation and Attitude](fct_reputation_tiers.md).

## What Belongs on the Character?

The **Faction Component** holds the character's memberships. A player can represent **Players** and also have a reputation with the **Town Watch**. Mark exactly one starting membership as **Main Faction**. That membership supplies the character's team ID and represents the character when it judges another actor. A secondary membership lets the Watch track the player's standing while the player still represents Players.

Use **Default Factions** for memberships an actor starts with. To grant membership through recruitment, a quest, or an active Game Feature, see [Assign and Change Memberships](fct_manage_memberships.md).

## How Controllers Find the Faction

**Get Faction Component** checks the actor you pass in. If it can't find the component there, it checks the pawn's controller or the controller's possessed pawn. Keeping one component on the character lets both use the same memberships. If teams should follow the controller across possessions, you can put the component there instead.

If your actor implements **Faction Member Interface** (`IFactionMemberInterface`), return its component from **Get Faction Component** (`GetFactionComponent`). This gives the lookup a direct route. For actors without the interface, it searches for an attached component.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="fct_setup_component.png" alt="Faction Component on a character Blueprint" width="780" border-effect="line"/>
        <img src="fct_member_interface.png" alt="Get Faction Component returns the character's component" width="780" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="C++" src="fct_setup_faction_component.h"/>
        <code-block lang="C++" src="fct_setup_faction_component.cpp"/>
    </tab>
</tabs>

For your own C++ controller, implement Unreal's `IGenericTeamAgentInterface`. Return the member's main team ID from `GetGenericTeamId`. On an AI controller, use the faction attitude from the possessed pawn toward the other actor in `GetTeamAttitudeTowards`. The [first steps](fct_first_steps.md) use controllers that already do this.

## Choose Where Factions Come From

The built-in database finds faction assets in the folders registered in the [Asset Manager](fct_setup.md). To supply your own list, create a Blueprint or C++ subclass of `NinjaFactionDatabase`, override **Get Factions** (`GetFactions`) to return your assets, and select it as **Faction Database Class**. The inherited **Get Faction** can then find an entry in that list by its exact faction tag.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp"><img src="fct_database_example.png" alt="A custom database returning a list of faction assets" width="780" border-effect="line"/></tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="C++" src="fct_list_database.h"/>
        <code-block lang="C++" src="fct_list_database.cpp"/>
    </tab>
</tabs>
