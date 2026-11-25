# Ninja Interaction
<primary-label ref="interaction"/>

![Ninja Interaction](int_feature.png "Ninja Interaction")

Use Ninja Interaction to give world objects actions a player or AI can perform. A door can offer **Open**, a terminal can take time to search, and a coin can be collected as the player walks past.

## What It Does

The character's **Interaction Manager** discovers targets in range. Each target offers actions through **Smart Object slots**. A slot pairs an interaction type, such as `Interaction.Type.Open`, with the **State Tree** that runs when someone uses it.

## Main Features

| What should the player do? | Setup |
| --- | --- |
| Press once and wait while the character searches. | [Time the interaction in the State Tree](int_adv_interaction_duration.md). |
| Hold a button to confirm the action. | [Time the hold with an Input Action](int_guide_hold_input.md). The slot stays free until the hold succeeds. |
| Press once and use a switch immediately. | [Run an immediate interaction in a State Tree](int_guide_immediate.md). |
| Walk over a pickup or use a nearby tagged object while looking elsewhere. | [Interact without focus](int_guide_without_focus.md). |

## How an Interaction Works

When the player presses Open, the source requests the door's Open slot. The execution ability claims it, and the State Tree triggers the door's behavior. The door changes state and the slot becomes available again. You can also [show a prompt](int_ui_mvvm.md), [play a montage](int_adv_interaction_animations.md), or [require a key](int_adv_openable_actor.md).

Start with [Set Up Ninja Interaction](int_setup.md), then [interact with a nearby object](int_first_steps.md).

## Integrations

[Connect Ninja Input to Interaction](int_adv_integration_input.md) to route an input handler to the current pawn. [Connect Interaction to Ninja Inventory](integration_interaction_inventory.md) to put collected items into a player's inventory.
