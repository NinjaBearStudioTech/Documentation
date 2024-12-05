# Setup
<primary-label ref="factions"/>

<tldr>
    <ul>
        <li><b>Download</b> and <b>install</b> the plugin.</li>
        <li>If your project uses <b>C++</b> make sure to add the correct <b>modules</b> to your `Build.cs` file.</li>
        <li>Add the <b>Faction Data Asset</b> to the <b>Asset Manager</b>.</li>
        <li>Add the necessary <b>components</b> and <b>interfaces</b> to your character and player controllers.</li>
    </ul>
</tldr>

This page will walk you through the **pre-requisites** and **steps** necessary to enable the **Ninja Factions** plugin.

## Installing the Plugin

Once acquired, you can install the plugin via the **Epic Games Launcher**. Like any **code plugin**, it can be installed
to any compatible engine version.

Once installed, create or open your project and navigate to **Edit** and then **Plugins**. In the search bar, type _Factions_
and the **Ninja Factions** plugin should appear. Tick the checkbox and restart the engine.

## C++ Modules

If you're working with C++ and using classes from the Factions System, ensure you add the following modules to your `Build.cs` file:

<tabs group="sample">
    <tab title="Build.cs">
        <code-block lang="c#" src="fct_build.cs"/>
    </tab>
</tabs>

## Asset Manager

Add the **Faction Data Asset** to the **Asset Manager**, ensuring that the correct **name** and **folder** are added.

<img src="fct_setup_asset_manager.png" alt="Faction Data Asset in the Asset Manager" thumbnail="true" border-effect="line"/>

Here's a summary of changes in the new entry:

| Setting            | Description                                                                               |
|--------------------|-------------------------------------------------------------------------------------------|
| Primary Asset Type | Unique name used to identify this asset. The name defined in the class is `FactionSetup`. |
| Asset Base Class   | Base class that represents this these assets. In our case, `NinjaFactionDataAsset`.       |
| Directories        | All content folders where assets of this type can be found. Adjust this as necessary.     |
| Cook Rule          | Always cook.                                                                              |

## Faction Component

The Faction Component must be present on each actor that belongs to a Faction. The most common examples are certainly the
**Player or AI characters**, but other actors such as _vehicles_ and _buildings_ can have factions too.

Optionally, each **Faction Member** can implement the **Faction Manager Interface** (`FactionMemberInterface`). This
allows the system to quickly retrieve the Faction Manager, without the need to iterate over actor components.

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

## Controllers

If you are planning to use Factions to determine the **AI Attitude** between AI Agents and actors detected by their
**Perception**, then you also need to configure both the AI and Player Controllers.

The Unreal Engine's Perception System will use the `GenericTeamAgentInterface`, implemented by Controllers, to determine
the **attitude** between members of certain **teams**. 

Factions are designed to provide a predefined **Team ID**, and if you are also using **Reputation**, it can be used to
define the attitude.

### AI Controller

The AI Controller already implements `GenericTeamAgentInterface`, so all that is left is to extend the implementation, 
so it uses the **Faction Manager** for attitude checks.

The Faction System provides a base **AI Controller**, `ANinjaFactionAIController`, that is able to retrieve the Faction
Manager from its possessed Pawn and, by using the system's **Attitude Provider**, determine the correct attitude between
the agent and its sensed targets.

> **This AI Controller is optional**
>
> If you already have your own hierarchy for the AI Controller, using the one provided by the framework is optional.
> But you need to make sure that the `GetTeamAttitudeTowards` function uses the Faction Manager.

### Player Controller

The Player Controller does not implement the `GenericTeamAgentInterface` used by the AI System to determine the attitude
between AI and Player Controllers. Furthermore, this interface is not implementable in Blueprints.

The Faction System provides a base **Player Controller**, `NinjaFactionPlayerController`, that is able to retrieve the
Faction Manager from its possessed Pawn, and use it to determine the **Team ID** for the **AI System**.

> **This Player Controller is optional**
>
> If you already have your own hierarchy for the Player Controller, using the one provided by the framework is optional.
> But you need to make sure that the interface is correctly implemented, retrieving the Team from the **Faction Manager**.

