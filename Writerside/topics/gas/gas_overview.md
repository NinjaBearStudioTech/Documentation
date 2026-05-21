# Ninja G.A.S.
<primary-label ref="gas"/>

![Ninja G.A.S.](gas_feature.png "Ninja G.A.S.")

**Ninja G.A.S.** is a foundation plugin that helps projects get started with Unreal Engine's **[Gameplay Ability System][1]** with less boilerplate and a clearer setup path.

It provides reusable building blocks for Ability System Components, Attribute Sets, Gameplay Effects, Gameplay Abilities, initialization flows, and common runtime patterns for both players and AI.

## What It Does

- Helps you configure the **Gameplay Ability System** faster and with fewer project-specific assumptions.
- Supports common ASC ownership models, including **Pawn-based** and **Player State-based** setups.
- Provides data-driven setup for **Attribute Sets**, **Gameplay Effects**, and **Gameplay Abilities**.
- Extends GAS usage into **Behavior Trees** and **State Trees** for AI-driven ability logic.
- Serves as the recommended foundation for plugins such as **Ninja Input**, **Ninja Inventory**, and **Ninja Combat**.

## Main Features

- **Fast GAS Setup**: Reduces the boilerplate needed to start using the Gameplay Ability System in a project.
- **Common ASC Patterns**: Supports common Ability System Component ownership, initialization, and ability-granting flows.
- **Data-Driven Configuration**: Startup Attribute Sets, Gameplay Effects, and Gameplay Abilities can be configured through reusable data assets.
- **Passive Abilities**: Provides support for abilities that are automatically granted and activated as part of an actor's setup.
- **Batch Activation**: Allows groups of abilities to be activated together when a specific gameplay flow requires it.
- **Lazy ASC Loading**: Provides utilities for resolving Ability System Components when they may not be immediately available.
- **AI Integration**: Exposes GAS functionality to Behavior Trees and State Trees so AI agents can use the same ability foundation as players.
- **Framework Foundation**: Provides the base layer used by other Ninja Bear Studio plugins that depend on abilities, effects, attributes, or gameplay events.

## Architecture Overview

Ninja G.A.S. is designed to provide a reusable setup layer around Unreal Engine's Gameplay Ability System.

At its core, the plugin helps define how an actor receives and initializes its Ability System Component, how startup 
attributes and effects are applied, and how initial abilities are granted. This setup can be configured through data assets, 
making it easier to reuse the same gameplay foundation across multiple characters, pawns, enemies, or project templates.

The plugin also extends GAS into AI workflows by exposing ability-related functionality to Behavior Trees and State Trees. 
This allows AI agents to activate abilities using the same underlying system as player-controlled characters.

By keeping the setup focused and reusable, Ninja G.A.S. acts as the foundation for other systems that depend on abilities, 
effects, attributes, or gameplay events and expands the Ability System Component, introducing additional features such
as Passive Abilities, Lazy Loading and Batch Activation.

## Integrations

- **[Ninja Input][5]** can route Enhanced Input actions into GAS abilities and gameplay events.
- **[Ninja Combat][3]** builds its combat abilities, effects, and attributes on top of GAS.
- **[Ninja Inventory][4]** uses GAS for inventory abilities, equipment effects, and attribute-driven behavior.

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input-in-unreal-engine
[3]: cbt_overview.md
[4]: inv_overview.md
[5]: ipt_overview.md