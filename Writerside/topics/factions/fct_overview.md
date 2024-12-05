# Ninja Factions
<primary-label ref="factions"/>

![Ninja Factions](fct_feature.png "Ninja Factions")

The **Ninja Factions** plugin is designed to provide flexibility when establishing the relationship between your **AI Teams**.

It introduces the concept of **Factions**, **Memberships** and **Reputation**, creating a very dynamic way to determine
not only how your AI Agents react to perceived targets, but also how your world can react to players.

## Main Features

- **Data Driven**: Configuration for Factions and Reputation Tiers is done in Data Assets and Data Tables.
- **Flexible Databases**: The default Faction Database uses Data Assets registered in the Asset Manager implementation, but you can also create your databases.
- **Flexible Attitude Resolution**: Attitude Resolution Strategies are extensible, so you can use the provided ones (Simple Team Check and Reputation Tier Check), or create your own.
- **Designer-Friendly**: Built in C++ but can be configured and extended in Blueprints.
- **Extensible**: Everything is configurable, extensible or component/interface based. No specific class requirements, which makes it much easier to integrate this plugin with other systems.
- **Save System**: Factions can be saved and loaded so players can continue their progress between play sessions.
- **Integrated with the Editor**: Including a Settings Page, Data Asset Contextual Creation and a new Faction Category for the Gameplay Debugger.

## Design Pillars

- **Data and Gameplay Oriented**: Based on **Data Assets** and **Data Tables**. Dynamic Memberships and Reputation altered by Gameplay.
- **AI Foundation**: Created with the **AI Team Agent** and the **AI Perception** systems in mind. 

## Integrations

- Factions can be used by the **[Ninja Combat](cbt_overview.md)** to enable or disable **Friendly Fire**.
- Factions can be used by **Ninja Bot** to determine **Attitude** for the **Perception Layer**.