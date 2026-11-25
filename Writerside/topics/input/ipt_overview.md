# Ninja Input
<primary-label ref="input"/>

![Ninja Input](ipt_feature.png "Ninja Input")

Ninja Input connects Unreal Enhanced Input actions to reusable Blueprint or C++ handlers. A character, a vehicle, and a mounted player can share camera controls while each responds differently to the same movement keys.

## What It Does

A mapping context turns a key or stick movement into an **Input Action**. An **Input Setup** pairs that context with handlers. The **Input Manager** activates the setup for the local player and passes the action to the handlers that accept its trigger event.

## Main Features

- Put shared controls on the Player Controller and let each possessed pawn supply its own setup.
- Use the provided movement, camera, HUD, and ability handlers or write your own.
- Remember a press during an animation and release it when the character can act.
- Let players rebind keys, invert axes, and adjust mouse and gamepad sensitivity.

## First Steps

[Set up Ninja Input](ipt_setup.md), then [move a template character](ipt_first_steps.md). For an existing project, migrate one set of controls at a time.

## Integrations

Use [Input and G.A.S.](ipt_gas_handlers.md) to activate a granted ability, [Combat and Input](integration_combat_input.md) to drive combos and targeting, or [Input and Interaction](int_adv_integration_input.md) to start and cancel an interaction.
