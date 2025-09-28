# UMG ViewModels
<primary-label ref="interaction"/>

## Introduction
The **ViewModel layer** is the bridge between **backend interaction data** and your **UMG widgets**.

In the Interaction System, ViewModels observe the live interaction state and expose it as **UI-friendly fields** so
prompts and HUD elements can update reactively without hard-wiring gameplay logic into widgets.

## Backend Data
The backend exposes the current **Interaction State**, which ViewModels present from two complementary **information perspectives**:

- **Interaction Source**: Represents the **instigator** (player or AI) and its relationship to nearby targets.
- **Interaction Target**: Represents data from the **target**, and the current state of its possible interactions. 

> **Perspectives are not Implementation**  
> 
> These perspectives are about **what viewpoint the data represents**.
> 
> They are **independent** from how or where you render the prompt. You can explore both perspectives, regardless if 
> your widget is added to the player HUD or attached to the interaction actor.
{style="note"}

## Actor Prompts

## HUD Prompts