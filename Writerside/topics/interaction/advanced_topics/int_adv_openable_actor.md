# Openable Actor
<primary-label ref="interaction"/>
<secondary-label ref="advanced"/>

The **Openable Actor** provides a standardized way to create interactive objects such as doors, chests, containers, and 
panels. It supports the following interaction types:

| Interaction Type          | Description                                                                                             |
|---------------------------|---------------------------------------------------------------------------------------------------------|
| `Interaction.Type.Open`   | Opens the actor, triggering its associated cosmetic behavior.                                           |
| `Interaction.Type.Close`  | Closes the actor, restoring its closed cosmetic state.                                                  |
| `Interaction.Type.Unlock` | Attempts to unlock the actor by resolving a key through a configurable and flexible key resolver class. |

This system is fully replicated, extensible, and decoupled from any inventory implementation.

## Internal States
The `ANinjaInteractionOpenableActor` maintains two replicated states: **Locked** / **Unlocked** and **Open** / **Closed**.
These states have the corresponding **cosmetic blueprint events** defined below:

| Function             | Description                                         |
|----------------------|-----------------------------------------------------|
| `ApplyLockedState`   | Indicates that the actor is currently **locked**.   |
| `ApplyUnlockedState` | Indicates that the actor is currently **unlocked**. |
| `ApplyOpenState`     | Indicates that the actor is currently **open**.     |
| `ApplyClosedState`   | Indicates that the actor is currently **closed**.   |

Additionally, to ensure proper communication of these states, this actor will:

- Use **multicast RPCs** for live cosmetic events (e.g., door opening animation).
- Use **replication** for late joiners to snap into the correct final state.

The Openable Actor also optionally supports **auto-unlocking** when triggering an Open action, if a matching key exists.
Key resolution is delegated to a separate, interchangeable **Key Resolver** object, so there are no direct dependencies
with any **inventory backend**.

## Gameplay Behavior
You can introduce your own gameplay behaviors, related to the **open** or **close** events, by extending these functions,
in Blueprints or C++. When doing so, **make sure to call their parent/super** versions to keep the original behavior.

These events are only invoked in the **authoritative version** and should not be used for cosmetics. However, you might
want to trigger **client RPCs** to execute things such as opening user interface windows (e.g. inventory items).

| Function | Description                                                           |
|----------|-----------------------------------------------------------------------|
| `Open`   | The actor has been open on the server and the state will replicate.   |
| `Close`  | The actor has been closed on the server and the state will replicate. |

> **Call Parent/Super**
> 
> When extending these behaviors, **make sure to call parent or super implementations** in Blueprint or C++, as the
> base behavior must be kept, along with your extensions.
{style="note"}

## Properties
The following properties will adjust this actor's behavior, related to its **internal states**:

| Property                      | Description                                                                                                   |
|-------------------------------|---------------------------------------------------------------------------------------------------------------|
| `StartsLocked`                | Determines if the actor begins in a locked state.                                                             |
| `OpenCanAutoUnlock`           | If enabled, attempting to *Open* will automatically try to unlock the actor using a key.                      |
| `CanBeClosedViaInteraction`   | Allows or disallows "Close" interactions.                                                                     |
| `CanToggleOpenAndCloseStates` | Establishes a **toggle behavior**, allowing interactions to **alternate** between "open" and "closed" states. |

And the following properties will adjust this actor's behavior, related to the **key resolution**:

| Property           | Description                                                                                                                                                             |
|--------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `KeyItemQuery`     | A Gameplay Tag Query used to find a matching key in the instigator's inventory.                                                                                         |
| `KeyResolverClass` | A class that implements the logic for resolving keys. Defaults to a reflection-based resolver for Ninja Inventory, but can be overridden by project-specific resolvers. |

## Key Resolver
A **Key Resolver** is any class derived from `UNinjaInteractionKeyResolver`. It contains a single function that receives 
three parameters: Instigator controller, Unlockable actor and Key Query. It returns true if unlocking succeeds.

The default implementation is integrated with **Ninja Inventory** and will attempt to use an Inventory Item configured
as a [**key**](inv_fragment_key.md).
