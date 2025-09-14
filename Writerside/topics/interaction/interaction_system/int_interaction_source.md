# Interaction Source
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li><b>Interaction Sources</b> (instigators) are usually pawns or characters that detect <b>Interaction Targets</b> and initiate interactions.</li>
        <li>The <b>Interaction Manager Component</b> is the backbone: it detects targets, tracks states, and executes interactions via <b>State Trees</b> and the <b>Ability System</b>.</li>
        <li>Detection relies on <b>Collision Components</b> (scan and focus colliders) which register/unregister targets and fire gameplay events to start or stop scanning.</li>
        <li>Two default <b>Interaction Abilities</b> are required: one to find the best candidate, and one to execute the interaction.</li>
        <li>Targets transition through <b>Focus States</b> (None, Eligible, Focused) and <b>Interaction States</b> (None, Started, Commited, Finished, Cancelled).</li>
    </ul>
</tldr>

An **Interaction Source** (also called an **Interaction Instigator**) is an actor, most often a pawn or character, that
detects an [**Interaction Target**](int_interaction_targets.md) and deliberately **initiates an interaction** with it.

Interaction Sources are powered by two Unreal Engine frameworks: **State Trees** and the **Gameplay Ability System**. At 
the center is the **Interaction Manager Component**, which ties these frameworks together, coordinating detection, validation, 
and execution, while exposing the functionality required by Ninja Interaction.

## Interaction Manager Component

The `UNinjaInteractionManagerComponent` is the core component that must be **added to any actor** intended to detect
interaction targets and initiate interactions. It serves as the backbone of the Interaction Source and has the following responsibilities:

1. Manage the list of **known interaction targets**, typically detected through dedicated collision components.
2. Perform **scans for eligible targets** using the Gameplay Ability System, allowing them to be focused and then interacted with.
3. **Track interaction states**, including when a target is registered, focused, or actively interacting.
4. Execute the interaction logic defined by the target through its assigned **State Tree** asset.

The component exposes several events you can bind to in order to track when interactable actors are detected, focused, 
or interacted with.

| Event                             | Description                                                                 |
|-----------------------------------|-----------------------------------------------------------------------------|
| `OnInteractableActorRegistered`   | Fired when an interactable actor is detected and registered.                |
| `OnInteractableActorUnregistered` | Fired when an interactable actor is no longer detected and is unregistered. |
| `OnFocusStateChanged`             | Fired when an the focus state changes for a registered target.              |
| `OnInteractionStateChanged`       | Fired when an the interaction state changes for a focused target.           |

The `UNinjaInteractionManagerComponent` also exposes several **Blueprint-accessible functions** used to query the actor's
awareness of interaction targets and to control the interaction flow.

| Function                                       | Description                                                                                                              |
|------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| `GetInteractionSummary`                        | Retrieves a summary of the current interaction, if any.                                                                  |
| `GetRegisteredInteractionTargets`              | Returns all interaction targets currently registered with this manager.                                                  |
| `GetEligibleInteractionTargets`                | Returns all interaction targets currently eligible to be focused.                                                        |
| `GetFocusedInteractionTargets`                 | Returns all interaction targets currently being focused.                                                                 |
| `HasInteractionTargetActor`                    | Checks if the given actor is registered as an interaction target.                                                        |
| `HasInteractionTargetComponent`                | Checks if the given component is registered as an interaction target.                                                    |
| `HasLineOfSightWithInteractionTargetComponent` | Checks if there is line-of-sight to the given interaction target component, even if it is not registered.                |
| `ApplyFocusToTarget`                           | Applies focus to a specific interaction target, setting the focus state from `eligible` to `focused`.                    |
| `RemoveFocusFromTarget`                        | Removes focus from a specific interaction target, setting the focus state to `none`.                                     |
| `StartInteraction`                             | Starts an interaction based on a given request. Returns the activation result.                                           |
| `CommitCurrentInteraction`                     | Commits the current interaction, if one is in progress.                                                                  |
| `TryCancelCurrentInteraction`                  | Attempts to cancel the current interaction, optionally providing a Gameplay Tag that represents the cancellation reason. |

> **System Backbone** 
> 
> These functions can be called directly when needed, but in most cases they are invoked automatically by the interaction
> system itself. The manager component acts as the **backbone**, coordinating scans and interaction flow, rather than a 
> front-facing tool for frequent manual use.
{style="note"}

## Collision Components

On initialization, the **Interaction Manager Component** will search the owning actor for specific collider components
(`UShapeComponent`) that act as the entry point for detecting [**Interaction Targets**](int_interaction_targets.md).

Two types of colliders can be configured:

1. **Interactable Scan Collider (required)**  
   - A shape component (commonly a box or sphere) used to **register interaction targets** so they can later be focused and interacted with.  
   - This collider must be identified by the Component Tag: `Interaction.Component.InteractableScan`.  

2. **Interactable Focus Collider (optional)**
   - A smaller shape component used when interaction targets should become eligible for focus purely by **proximity**.  
   - This allows targets to be detected based on the source being within range.  
   - This collider must be identified by the Component Tag: `Interaction.Component.InteractableFocus`.  

> **Initialization and Binding**
> 
> The **Interaction Manager Component** will automatically find and cache these colliders during **Begin Play**.
{style="note"}

Once the first interactable actor is detected by the **Interactable Scan Collider** and registered, a **Gameplay Event**
is fired. This event triggers the **Find Interactable Actor** ability (and its variations), which performs the actual
scanning and processing of all available targets through the accompanying **Interaction Search Task**.

Similarly, when all registered targets are removed, another **Gameplay Event** is fired to interrupt the ability (and task)
execution, ensuring the system halts when no interactable targets are present.

## Interaction Abilities

The interaction system provides two **Gameplay Abilities** that must be granted by default to any actor serving as an
Interaction Source (Instigator). These abilities are responsible for detecting, selecting, and executing interactions.

- `UInteractionAbility_FindInteractableActor`: Scans the list of registered targets and, based on the **provided Task class**, selects the best candidate for focus or interaction.
- `UInteractionAbility_ExecuteInteraction`: Executes the selected interaction by bridging communication between the source and the target components.

The dedicated ability pages will cover these in detail, including how to customize or extend their behavior. For now, 
ensure that both abilities are added to your actor's **Ability System Component** by default, so they are always available 
when the **Interaction Manager** triggers its events.

## Interaction Target States

From the Interaction Manager's perspective, a **registered Interaction Target** can exist in a few possible **Focus States**,
and once focused, transition into a series of **Interaction States**.

### Focus States

| State        | Description                                                                                                                                               |
|--------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
| **None**     | The target is registered, but no focus is applied to the target.                                                                                          |
| **Eligible** | The target passed a pre-requisite criteria (e.g. it's colliding with the proximity box) and is ready to receive focus by a "focus event".                 |
| **Focused**  | The target received a focus event from the Inventor Manager (e.g. closest to the player, or aimed at by the player camera) and can accept an interaction. |

### Interaction States

When a target reaches the **Focused** state, it becomes eligible for interaction. At that point, the following states may apply:

| State         | Description                                                                                                                              |
|---------------|------------------------------------------------------------------------------------------------------------------------------------------|
| **None**      | No interaction is in progress.                                                                                                           |
| **Started**   | An interaction has been started. Immediate interactions will often skip this state.                                                      |
| **Commited**  | The target has received the outcome of the interaction, but the manager may still be executing it (e.g., an animation is still playing). |
| **Finished**  | The interaction has completed successfully.                                                                                              |
| **Cancelled** | The interaction was cancelled before completion.                                                                                         |

## Configuring an Interaction Source

To set up an **Interaction Source** (instigator), you'll need to combine collision, abilities, and the interaction manager
into a working flow. At a high level, this involves three main tasks:

1. Add the **Interaction Manager Component** to your pawn or character, making it the backbone for detecting and managing interaction targets.
2. Configure the **Collision Components** (scan and optional focus colliders) so the manager can register and track interaction targets in the world.
3. Ensure the actor's **Ability System Component** receives the required **Interaction Abilities**, so it can scan for targets and execute interactions.


