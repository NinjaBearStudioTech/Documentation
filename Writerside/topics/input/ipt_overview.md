# Ninja Input
<primary-label ref="input"/>

![Ninja Input](ipt_feature.png "Ninja Input")

**Ninja Input** is a focused layer built on top of Unreal Engine's **[Enhanced Input System][1]**. It keeps input handling 
out of Character and Pawn classes while providing a reusable path for dispatching input through Blueprints or C++.

It includes an Input Manager, reusable Input Handlers, Gameplay Ability System integration, animation-aware input buffering, 
input remapping, and player-facing input settings.

## What It Does

- Separates input orchestration from Pawns, Characters and Controller code.
- Provides reusable **Input Handlers** for common input patterns.
- Routes player input into **Gameplay Abilities** and gameplay events.
- Supports animation-aware input buffering for smoother action timing.
- Provides a remapping workflow with UI, ViewModels, save, and apply support.
- Adds input-related user settings such as sensitivity and axis inversion.

## Main Features

- **Enhanced Input Integration**: Works directly with Epic's actions, triggers, modifiers, and mapping contexts.
- **Input Manager Component**: Centralizes mapping context setup, handler dispatch, and input lifecycle management.
- **Input Handlers**: Provides ready-made handlers for pressed, held, repeated, axis-based, toggle, and gameplay-event input flows.
- **GAS Integration**: Activates abilities, cancels abilities, and sends gameplay events through the Gameplay Ability System.
- **Animation Input Buffer**: Allows input windows to be aligned with montages and animation notifies, reducing dropped inputs during transitions.
- **Input Remapping Pipeline**: Supports a full remapping flow using UI, ViewModels, persistence, and runtime application.
- **User Settings and Modifiers**: Includes settings for mouse and gamepad sensitivity, axis inversion, and matching input modifiers.
- **Editor Integration**: Provides contextual asset menus and Project Settings support for faster configuration.

## Architecture Overview

Ninja Input is designed around the idea that input should be handled by dedicated objects instead of being hardcoded into 
Pawn/Character or Controller classes.

The Input Manager component owns the runtime input flow. It installs mapping contexts, receives Enhanced Input actions, 
and dispatches them to Input Handlers. Each handler is responsible for one focused behavior, such as activating an ability, 
forwarding an axis value, sending a gameplay event, or managing a buffered input window.

This keeps player input modular and easy to extend. Designers can configure common behavior through assets and Blueprints, 
while programmers can create custom handlers for project-specific input flows.

Because the plugin is built on Enhanced Input, it does not replace the engine input stack. Instead, it adds a reusable 
gameplay layer on top of it, making it easier to connect input to GAS, combat, inventory, UI, and other gameplay systems.

## Integrations

- **[Ninja G.A.S.][3]** can provide the Ability System foundation used by input-driven abilities.
- **[Ninja Combat][4]** can use input handlers to trigger attacks, combos, and combat abilities.
- **[Ninja Inventory][5]** can use input handlers to trigger inventory-driven abilities or equipment behavior.

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input-in-unreal-engine
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
[3]: gas_overview.md
[4]: cbt_overview.md
[5]: inv_overview.md