# User Interface
<primary-label ref="interaction"/>

The Interaction System displays information to players, conveying the status of available or active interactions. This
is done via interaction-specific **Widget Components**, **Widgets** and **UMG Viewmodels**.

## Interaction Widget

The `NinjaInteractionBaseWidget` class serves as a base for two common interaction scenarios:

1. **Central Interaction Prompt**: In a UI with a centralized Interaction Prompt, not related to any interaction actor.
2. **Per-Actor Interaction Prompt**: In a game where each Interactable Target has its own Interaction Prompt widget.

This widget implements `InteractionActorAwareInterface`, which allows the **Interaction Widget Component** to set its
owner to the widget, when hosting it for an Interactable Target. If no target is set, then the owning Player Pawn is
considered the Interaction Actor.

When an Interaction Actor is set to this widget, it will automatically be set on any Interaction Viewmodel too.

## Interaction Widget Component

This component is meant to be used with Interaction Actors that have their own **Interaction Prompt**. By using this 
component, in conjunction with the **Interaction Widget**, all Interaction Viewmodels are correctly set, pointing to the
correct **Interaction Components**.

## Interaction UMG Viewmodel

