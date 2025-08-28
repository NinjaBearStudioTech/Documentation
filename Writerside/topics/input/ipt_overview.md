# Ninja Input
<primary-label ref="input"/>

![Ninja Input](ipt_feature.png "Ninja Input")

**Ninja Input** is a focused layer on top of Unreal Engine's **[Enhanced Input System][1]**. It cleanly separates input
handling from your Character and Pawn code, while giving you a fast, extensible path in Blueprints or C++.

Out of the box, it includes a robust **Input Manager**, a library of **Input Handlers**, **GAS** hooks, an **animation-aware 
input buffer**, **input remapping**, and support for player **user settings**.

## Main Features

- **Enhanced Input integration**  
  Works directly with Epic's actions, triggers, modifiers, and mapping contexts. Keep using your existing EI assets.

- **Input Manager component**  
  Centralizes mapping context install/uninstall, handler dispatch, and lifecycle hooks to cut boilerplate.

- **Handler collection**  
  Ready-made handlers for common patterns (pressed/held/repeat, axis driving, toggles, gameplay events), extendable in BP/C++.

- **GAS integration**  
  Activate/cancel abilities and fire gameplay events with minimal glue. Plays nicely with **[Ninja GAS][3]** and **[Ninja Combat][4]**.

- **Animation-based input buffer**  
  Buffer windows aligned with montages/notify windows to avoid dropped inputs during transitions.

- **User settings & modifiers**  
  Built-in settings for invert XY and sensitivity (mouse X/Y, gamepad), with matching Input Modifiers that read from the settings object.

- **Input remapping pipeline**  
  End-to-end remapping workflow (UI → ViewModels → save/apply) on top of Enhanced Input. See the [remapping setup](ipt_remapping_setup.md).

- **Editor integration**  
  Contextual asset menus and a Project Settings page for quick configuration.

## Design Pillars

- **Separation of concerns**  
  Keep input orchestration out of Character classes.

- **Fast iteration**  
  Prototype quickly with ready-made handlers and clean extension points.

- **GAS-first gameplay**  
  A straightforward path from user input to abilities and gameplay events.

## Integrations

- Configure the Gameplay Ability System with **[Ninja GAS][3]**.
- Drive combo inputs and send events to **[Ninja Combat][4]**.
- Trigger Inventory-driven abilities via **[Ninja Inventory][5]**.

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input-in-unreal-engine
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
[3]: gas_overview.md
[4]: cbt_overview.md
[5]: inv_overview.md
