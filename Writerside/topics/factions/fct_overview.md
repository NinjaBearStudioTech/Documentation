# Ninja Factions
<primary-label ref="factions"/>

![Ninja Factions](fct_feature.png "Ninja Factions")

**Ninja Factions** is a team and reputation framework for Unreal Engine. It helps define how AI agents, players, and 
world systems relate to each other through factions, memberships, attitudes, and reputation.

The plugin is designed to work with Unreal Engine's AI Team Agent and AI Perception systems, while remaining flexible 
enough to support simple team checks, reputation-driven worlds, friendly fire rules, and project-specific attitude logic.

## What It Does

- Provides a reusable framework for **factions**, **memberships**, **reputation**, and **attitude resolution**.
- Allows AI agents to determine how they should react to perceived targets.
- Supports dynamic reputation changes that can affect how the world responds to players.
- Provides data-driven configuration through **Data Assets** and **Data Tables**.
- Integrates with AI Perception, Combat friendly fire rules, and Bot perception logic.
- Includes editor and debugging support for faster configuration and testing.

## Main Features

- **Faction Definitions**: Define factions as data assets that can be registered and reused across the project.
- **Membership System**: Assign actors to factions and expose their team identity to gameplay and AI systems.
- **Reputation Tiers**: Use data-driven reputation values and tiers to represent changing relationships.
- **Flexible Attitude Resolution**: Resolve friendly, neutral, or hostile attitudes through built-in or custom strategies.
- **AI Perception Support**: Works with Unreal's AI Team Agent flow so perceived actors can be evaluated through faction logic.
- **Save Support**: Faction and reputation data can be saved and loaded between play sessions.
- **Editor Integration**: Includes project settings, contextual asset creation, and Gameplay Debugger support.
- **Extension Points**: Provides component, interface, Blueprint, and C++ hooks for project-specific faction rules.

## Architecture Overview

Ninja Factions is organized around the relationship between faction data, actor membership, reputation state, and attitude 
resolution.

Faction assets define the available groups in the project. Actors can become members of these factions (gain Membership) 
through components or interfaces, allowing gameplay systems to query their faction identity without requiring a specific 
actor class. Reputation can then modify how one faction or actor relates to another over time.

When an attitude is requested, the plugin uses an attitude resolution strategy to decide whether the target should be 
considered friendly, neutral, or hostile. The default strategies support simple team checks and reputation-tier checks, 
but projects can provide their own logic for more specific rules.

This makes Ninja Factions useful as a foundation for AI perception, combat filtering, social systems, world reactions, 
and any gameplay feature that needs consistent relationship data between team members.

## Integrations

- **[Ninja Combat](cbt_overview.md)** can use factions to enable, disable, or customize friendly fire behavior.
- **[Ninja Bot](bot_overview.md)** can use factions to determine perceived target attitude in the perception layer.