# Set Up Ninja Interaction
<primary-label ref="interaction"/>

## Prerequisites

Start with a playable pawn and a working Unreal **Ability System Component** for that pawn. Ninja Interaction uses **Smart Objects** for slots, **Gameplay Abilities** to claim them, and **State Trees** to run the action. A Blueprint character using Enhanced Input can run the first walkthrough.

## Setup Checklist

| Step | When you need it | Where to go |
| --- | --- | --- |
| Enable Ninja Interaction and its engine plugin dependencies. | Every project | [Install plugins](installing_plugins.md) |
| Add `NinjaInteraction` to your module dependencies. | C++ classes using the Interaction Manager or target interfaces | [Work with plugin source](installing_plugins.md) |
| Configure the `InteractionObject` object channel and the `InteractionSource` and `InteractionTarget` presets. | Overlap detection | [Collision Settings](collision_settings.md) |
| Grant the find and execute abilities to the source pawn's ability system. | Focused interactions | [First Steps](int_first_steps.md) |
| Grant the play-animation ability and choose a montage. | Interactions that animate the source | [Animate an Interaction](int_adv_interaction_animations.md) |

## Find the Starting Assets

In the Content Browser, enable **Show Plugin Content**. Under **Ninja Interaction Content → Blueprints → Interactables**, find `SO_Interaction_Generic` and `ST_Interaction_Generic`. Duplicate assets into your game's Content folder before customizing them. When you copy both, open the copied Smart Object and point its slot's **Interaction Tree** at your copied tree.

[Build your first interaction](int_first_steps.md).
