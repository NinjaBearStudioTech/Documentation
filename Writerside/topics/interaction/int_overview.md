# Ninja Interaction
<primary-label ref="interaction"/>

![Ninja Interaction](int_feature.png "Ninja Interaction")

The **Ninja Interaction** plugin streamlines the definition and execution of interactions by orchestrating core gameplay 
systems in the engine, including the **Gameplay Ability System**, **Smart Objects**, **Gameplay Behaviors**, and **State Trees**.

## Main Features

- Use **state machines** to design simple and complex interaction flows for each interactable actor.
- **Smart Objects** and **Gameplay Behaviors** define how each interaction works, including multiple interactions per target.
- Built on Smart Objects, allowing standardized interactions for both **players** and **AI agents**.
- Interactions are triggered via **Gameplay Abilities**, making them compatible with other systems.
- Bind the provided **ViewModels** to your UI to track interaction progress.
- Provides **extension points** to other systems, such as [**Ninja Inventory**][1].

## Architecture Overview

Ninja Interaction is organized around a clear separation of responsibilities between **detecting targets, evaluating
candidates, managing focus, triggering interactions and executing their outcomes**. Each layer is well-defined and separated, 
providing **relevant hooks and extension points**.

At a high level, the data flow follows this sequence:

<img src="int_overview_architecture.png" alt="Interaction Architecture Overview" width="800"/>

- **Triggers**: Gameplay events or elements that may initiate an interaction, by registering an interaction target.
- **Interaction Definition**: Candidates are evaluated based on their definition, which should reply if the target is viable for a given instigator. 
- **Ninja Interaction**: Registered targets are continuously evaluated for focus, which is determined by any of the provided (or custom) Scanner Tasks.
- **Interaction Outcome**: Focused targets can be activated, leading to a gameplay outcome defined by State Trees, and any specific game logic.
- **UI Presentation**: The entire interaction flow can be tracked per target, using the provided UI widgets and ViewModels.

This flow allows developers and designers to create both simple and complex interactions by simply **defining the State Tree
and additional relevant logic in Blueprints (or C++**). These are executed on top of a robust, multiplayer-ready, framework 
that will handle complexities. 

However, if needed, programmers can leverage **extension points and hooks** to modify the framework itself, and further 
accomodate any extra requirements presented by the project.

[1]: inv_overview.md