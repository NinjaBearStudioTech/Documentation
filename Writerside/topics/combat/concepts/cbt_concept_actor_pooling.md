# Actor Pooling
<primary-label ref="combat"/>

Combat systems often need to **spawn short-lived actors**, such as projectiles, cast actors, targeting actors, and marker 
actors. Creating and destroying these actors repeatedly during combat can become expensive, especially when many combatants 
are active at the same time.

The **Actor Pool** reduces that cost by preparing **reusable actor instances** ahead of time. Instead of spawning a new 
actor every time one is needed, the Combat System can retrieve an inactive actor from the pool, activate it, and return 
it to the pool when it is no longer needed.

Actor Pooling is optional, but it is recommended for actors that are spawned frequently during combat.

## Actor Pool Component

Each combatant can have its own Actor Pool, represented by the `NinjaCombatActorPoolComponent`. The component defines
which actor classes are pooled and how many instances of each class should be initialized.

Combatants using an Actor Pool should also implement `CombatPoolProviderInterface`. This allows other systems, such as
projectile requests, cast abilities, and targeting logic, to retrieve the pool without depending on a specific character
class.

<procedure title="Add the Actor Pool Component" collapsible="true" default-state="expanded">
    <tabs group="sample">
        <tab title="Blueprint" group-key="bp">
            <img src="cbt_actor_pool_component.png" alt="Actor Pool Component" thumbnail="true" border-effect="line"/>
            <p><br/></p>
            <img src="cbt_actor_pool_provider.png" alt="Actor Pool Provider Interface" thumbnail="true" border-effect="line"/>
        </tab>
        <tab title="C++" group-key="c++">
            <code-block lang="c++" src="cbt_add_actor_pool_component.h"/>
            <p><br/></p>
            <code-block lang="c++" src="cbt_add_actor_pool_component.cpp"/>
        </tab>
    </tabs>
    <step>
        <p>Add the <b>Actor Pool</b> component to your character.</p>
    </step>
    <step>
        <p>Implement <code>CombatPoolProviderInterface</code> and return the Actor Pool component from the appropriate function.</p>
    </step>
</procedure>

## Pool Configuration

The Actor Pool is configured directly in the **Actor Pool Component**. Each entry defines an actor class and the number
of instances that should be initialized for that class.

<img src="cbt_actor_pool_setup.png" alt="Actor Pool Setup" border-effect="line" thumbnail="true"/>

> **Actor-Based and Global Pools**
>
> By default, each Actor Pool is managed by the component assigned to its **owning actor**. This means each combatant can 
> have its own pool configuration and limits.
>
> If you prefer to use a **central Actor Pool**, override the base Pool Component's `GetActorFromPool` function and route
> requests to your global pool instead.
{style="tip"}

## Poolable Actors

Poolable actors are defined by `CombatPoolableActorInterface`. Any actor implementing this interface can be added to the
Actor Pool Component.

For most cases, it is recommended to extend `NinjaCombatPoolableActor` instead of implementing the interface directly.
This base class already implements the poolable actor contract and is configured to support networking and replication,
so pooled actors can behave as if they were placed in the map.

The Actor Pool Component and `NinjaCombatPoolableActor` work together to reduce the initial network overhead that could
otherwise happen when many replicated actors are spawned at the same time.

## Actor Lifecycle

Poolable actors have a different lifecycle from regular spawned actors.

Functions such as **Begin Play** and **End Play** are called when the pooled actor is created or destroyed by the pool.
They are not called every time the actor is retrieved from the pool or returned to it.

For per-use behavior, use the lifecycle functions provided by `CombatPoolableActorInterface`.

| Function     | Description                                                                      |
|--------------|----------------------------------------------------------------------------------|
| `Activate`   | Called when a poolable actor is retrieved from the pool and placed in the world. |
| `Deactivate` | Called when a poolable actor is ready to return to the pool.                     |

If you are using `NinjaCombatPoolableActor`, these functions are already implemented. You can use the extension points
provided by the base class instead.

| Extension Point  | Description                                                     |
|------------------|-----------------------------------------------------------------|
| `OnActivation`   | Called when the actor is activated on the server and clients.   |
| `OnDeactivation` | Called when the actor is deactivated on the server and clients. |

These events are appropriate for behavior that should happen every time the actor is reused, such as:

- Playing a particle effect from the start.
- Playing a sound effect from the start.
- Applying velocity to a projectile.
- Resetting visual state or gameplay state from a previous activation.

> **Call Parent/Super**
>
> When overriding `OnActivation` or `OnDeactivation`, make sure to call the parent/super implementation, since they 
> have important synchronization code to execute.
{style="note"}

## Supported Actors

The following actor types are supported by the Actor Pool by default.

| Actor Type           | Description                                                                                             |
|----------------------|---------------------------------------------------------------------------------------------------------|
| **Projectiles**      | Spawned by [**Ranged Attacks**](cbt_concept_ranged_attacks.md).                                         |
| **Cast Actors**      | Spawned by certain [**Cast Flows**](cbt_concept_cast_flows.md).                                         |
| **Targeting Actors** | Spawned by abilities that use Targeting Actors, like the [**Cast Ability**](cbt_concept_cast_flows.md). |
| **Marker Actors**    | Spawned by the [**Target Lock Ability**](cbt_concept_target_locking.md)                                 |

You can support additional actors by extending `NinjaCombatPoolableActor`, or by implementing
`CombatPoolableActorInterface` directly.

## Retrieving Actors

To retrieve an actor from the pool, use `TryGetActorFromPool` from the **Actor Pool Function Library**.

The actor types listed above already use this functionality internally, so no additional retrieval code is required when
using the default Combat features.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="cbt_actor_pool_retrieval.png" alt="Actor Pool Retrieval" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="cbt_retrieve_actor_from_pool.cpp"/>
    </tab>
</tabs>

> **Logging Pool Behavior**
>
> The Actor Pool Component logs messages when an actor is retrieved or when no instances are available. To track these
> messages, set the output level of `LogNinjaCombat` to `Verbose`.
{style="tip"}