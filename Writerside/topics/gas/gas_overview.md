# Ninja G.A.S.
<primary-label ref="gas"/>

![Ninja G.A.S.](gas_feature.png "Ninja G.A.S.")

Use Ninja G.A.S. to give a character starting abilities and attributes through a single setup asset. A guard can own its abilities for its lifetime. A player can keep a shared set of abilities when they respawn and gain different moves when they possess a new pawn.

## What It Does

A **G.A.S. Setup** asset lists the attributes, effects, and abilities an actor starts with. The **Ability System Component** applies that setup. You choose whether the character owns the component or borrows it from the Player State.

## Main Features

| What you want to build | Start here |
| --- | --- |
| A character with starting energy and an ability that restores it | [Grant starting attributes and abilities](gas_guide_starting_abilities.md) |
| A charge effect that only the aiming player sees | [Play a local Gameplay Cue](gas_local_gameplay_cues.md) |
| An AI that recovers when its energy runs low | [Have an AI recover when energy runs low](gas_artificial_intelligence.md) |

## How a Guard Gets Its Recovery Move

The guard's setup asset grants Energy and a Recover ability. Its AI can read Energy, activate Recover when the value drops, and return to patrol once the ability ends. Another guard can use the same move with different starting values by changing the setup asset.

[Set up Ninja G.A.S.](gas_setup.md), then [give a character an ability system](gas_first_steps.md).

## Integrations

[Input and G.A.S.](ipt_gas_handlers.md) connects an input action to a granted ability. [Initialize plugin attributes](gas_guide_attributes.md) walks through starting health for Ninja Combat and backpack capacity for Ninja Inventory.
