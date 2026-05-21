# Ninja Interaction
<primary-label ref="interaction"/>

![Ninja Interaction](int_feature.png "Ninja Interaction")

**Ninja Interaction** is an interaction framework for Unreal Engine that helps define, evaluate, and execute interactions 
between actors.

It orchestrates core engine systems such as the **Gameplay Ability System**, **Smart Objects**, **Gameplay Behaviors**, 
and **State Trees**, allowing interaction logic to remain modular, reusable, and multiplayer-ready.

## What It Does

- Provides a structured framework for defining interactable actors and interaction flows.
- Supports simple and complex interactions through **State Trees** and gameplay logic.
- Uses **Smart Objects** and **Gameplay Behaviors** to standardize interactions for players and AI agents.
- Triggers interactions through **Gameplay Abilities**, making them compatible with other ability-driven systems.
- Tracks focus, availability, progress, and interaction state through reusable systems.
- Provides UI support through widgets and **ViewModels**.
- Exposes extension points for systems such as **Ninja Inventory**.

## Main Features

- **Interaction Targets**: Actors can expose one or more interaction options that are evaluated at runtime.
- **Target Detection and Focus**: Registered targets are scanned, evaluated, and selected based on configurable focus rules.
- **State Tree Interaction Flows**: Interaction behavior can be authored as simple or complex State Tree-driven flows.
- **Smart Object Support**: Interactions can use Smart Objects and Gameplay Behaviors to support both players and AI agents.
- **GAS Integration**: Interactions are triggered through Gameplay Abilities, allowing costs, conditions, gameplay events, and ability logic to participate.
- **UI Presentation**: ViewModels and widgets can present interaction prompts, progress, and state to the player.
- **Extension Points**: Blueprint and C++ hooks allow projects to customize target evaluation, interaction outcomes, and external system integration.

## Architecture Overview

Ninja Interaction is organized around a clear flow: targets are registered, candidates are evaluated, focus is resolved, 
and the selected interaction can be activated.

Interaction targets define what can be done with an actor. Scanner tasks and focus logic determine which target is 
currently relevant to an instigator. Once activated, the interaction can execute gameplay behavior through State Trees, Gameplay Abilities, Smart Objects, Blueprint logic, or C++ extension points.

This separation keeps interaction detection, interaction selection, and interaction execution independent of each other. 
Designers can author interaction flows using assets and Blueprints, while programmers can extend the framework for 
project-specific requirements.

The result is a reusable interaction layer that can support simple prompts, pickups, inspections, conversations, Smart 
Object usage, AI interactions, or more complex gameplay sequences.

## Integrations

- **[Ninja G.A.S.](gas_overview.md)** can provide the Ability System setup used by interaction abilities.
- **[Ninja Inventory][1]** can use interactions for pickups, containers, inspection flows, or item-driven outcomes.
- **[Ninja Input](ipt_overview.md)** can trigger interaction abilities through input handlers.
- **[Ninja Bot](bot_overview.md)** can use interaction flows for AI agents through Smart Objects and behavior logic.

[1]: inv_overview.md