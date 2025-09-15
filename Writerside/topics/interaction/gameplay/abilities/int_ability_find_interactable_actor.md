# Find Interactable Actor
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li>Determines the "best" interaction target using a configured strategy and <b>waits for the player's Interaction input</b>.</li>
        <li>Meant to be <b>granted to the Interaction Source</b> (e.g., player) by default, so it's ready whenever targets appear.</li>
        <li>Supports pluggable selection tasks (e.g., <code>FindClosest</code> or <code>TraceFromCamera</code>); you can add your own by extending <code>UNinjaInteractionSearchAbilityTask</code>.</li>
        <li>Ends automatically when there are <b>no registered targets</b>, and cleanly interrupts the ongoing selection task.</li>
    </ul>
</tldr>

Determines the best available interaction target for the current **Interaction Source** and holds that selection while it
**waits for an Interaction input** (e.g., button press routed via Ninja Input). This ability is typically **granted by
default** to the player, so it's always listening as targets come and go.

## Properties

This ability exposes the following properties that can modify its base behavior.

| Property               | Description                                                             |
|------------------------|-------------------------------------------------------------------------|
| `ClaimPriority`        | Claim priority applied when starting interactions from this ability.    |
| `InteractionTaskClass` | The gameplay task that discovers/chooses interactable actors. (NoClear) |
| `bInDebugMode`         | Enables debug visuals/logs for applicable tasks.                        |

## Functions

You can customize this ability's behavior end-to-end by overriding its core functions in **Blueprint** or **C++**. 

| Function                           | Description                                                                      | 
|------------------------------------|----------------------------------------------------------------------------------|
| `InitializeInteractionAbilityTask` | Create & initialize the **search/selection task**.                               |      
| `GetClaimPriority`                 | Provide the **Smart Object claim priority** for this context.                    | 
| `InitializeGameplayEventTask`      | Create the **Wait Gameplay Event** task for confirm/cancel input.                |
| `InitializeInteractionRequest`     | Build the **interaction request** added to the payload.                          | 
| `HandleInteractionTargetFound`     | React to a newly **found/focused** target.                                       | 
| `HandleInteractionTargetLost`      | React to a **lost/invalid** target.                                              | 
| `HandleInteractionActorDestroyed`  | Clean up when the **current actor is destroyed**.                                | 
| `HandleGameplayEventReceived`      | Process **confirm/cancel** gameplay events.                                      | 
| `SendStartInteractionEvent`        | Prepare payload and **emit start event** (usually triggers Execute Interaction). |

## Built-in Selection Tasks

- **`FindClosestInteractionTarget`**  
  Collects all targets registered by the **Far Collision Component**, marks those colliding with the **Near Collision Component** as **eligible**, then chooses the **closest** one to the instigator as the focused actor.

- **`TraceInteractionTarget`**  
  Collects all targets registered by the **Far Collision Component**, marks those colliding with the **Near Collision Component** as **eligible**, then focuses the target **hit by a camera-centered trace**. Configure **MaxDistance** and **LoS** channel in **Ninja Interaction Settings**.

> **Extend the Strategy** 
> 
> You can create custom selection logic by subclassing **`UNinjaInteractionSearchAbilityTask`**.
{style="note"}
