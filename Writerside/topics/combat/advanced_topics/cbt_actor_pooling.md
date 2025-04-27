# Actor Pooling
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

<tldr>
    <ul>
        <li>Combat Pawns can use the Actor Pool by declaring a <code>NinjaCombatActorPoolComponent</code>.</li>
        <li>Combat Pawns with a valid Actor Pool must implement <code>CombatPoolProviderInterface</code>.</li>
        <li>The Actor Pool supports any Actor implementing <code>CombatPoolableActorInterface</code>.</li>
        <li>The <code>NinjaCombatPoolableActor</code> is a default implementation that supports replication.</li>
        <li>The pool is replicated, and pooled actors behave as if they were placed in the map.</li>
    </ul>
</tldr>

It is common for combat systems to require frequent spawning and destroying of actors, such as projectiles or cast actors, 
in short intervals.

To mitigate the performance cost of constant actor spawning and destruction during gameplay, an **Actor Pool** was introduced
to the Combat System. This pool prepares a predefined number of instances of frequently used actors for each combatant.

## The Actor Pool Component

Each combatant has its own Actor Pool, represented by the `NinjaCombatActorPoolComponent`. You can configure all the 
actors that will be pooled and specify how many instances will be available.

Combatants using an Actor Pool must implement the `CombatPoolProviderInterface` to provide the component, allowing 
external functionalities, such as the Projectile Request, to quickly retrieve and use the pool.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <p>Add the <b>Actor Pool</b> component to your character.</p>
        <img src="cbt_actor_pool_component.png" alt="Actor Pool Component" thumbnail="true" border-effect="line"/>
        <br/>
        <p>Add the <b>Provider Interface</b> and return the component, from the appropriate function.</p>
        <img src="cbt_actor_pool_provider.png" alt="Actor Pool Provider" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="cbt_add_actor_pool_component.h"/>
        <br/>
        <code-block lang="c++" src="cbt_add_actor_pool_component.cpp"/>
    </tab>
</tabs>

## Poolable Actors

Poolable Actors are primarily defined by the `CombatPoolableActorInterface`. Any actor implementing this interface can 
be added to the Actor Pool Component.

It's generally recommended to extend from `NinjaCombatPoolableActor`, the **default base class**, rather than directly 
implementing the interface. This base actor not only implements the Poolable Actor interface but is also configured to 
support networking and replication, as if the actor was originally **placed in the map**.

The Actor Pool Component and the base Poolable Actor work together to reduce the initial network overhead that would 
otherwise occur when replicating many actors being spawned simultaneously to prepare the pool.

The Actor Pool can be configured in the **Actor Pool Component** by setting the actor class and the number of 
instances to initialize.

![Actor Pool Setup](cbt_actor_pool_setup.png "Actor Pool Setup")

> **Pools are Actor Specific**
>
> You are configuring an actor pool in the component assigned to each pool owner. This means that the pool size is
> specific to that actor.
> 
> Keep that in mind while defining your pool limits for all pool owners in the scene!

### Actor Lifecycle

When you use Poolable Actors, it is important to keep in mind how the Actor lifecycle changes.

Functions like **Begin Play** and **End Play** will be called when the Poolable Actor is created and destroyed by the 
pool, making them inadequate to handle events that should happen whenever the actor is actually added or removed from
the world.

Instead, Poolable Actors use methods defined by `CombatPoolableActorInterface`: 
 
- `Activate`: Invoked when a poolable actor is retrieved from the pool and placed in the world. 
- `Deactivate`: Invoked when the poolable actor is ready to be returned to the pool.

If you are using the default implementation, `NinjaCombatPoolableActor`, those methods are already implemented, and you
can simply hook any important events to their respective extension points, available to Blueprints and C++.

- `OnActivation`: Invoked when the actor is activated on the server and clients.
- `OnDeactivation`: Invoked when the actor is deactivated on the server and clients.

Here are some examples of functionalities that should be handled by these events:

1. Playing a **Particle Effect** from the start.
2. Playing a **Sound Effect** from the start.
3. Adding **velocity** to a projectile.

> **Call Parent/Super**
> 
> When extending `OnActivation` or `OnDeactivation`, make sure to call their parent/super implementations!
{style="note"}

### Supported Actors
Currently, the following actors are supported by default by the Actor Pool:

- **Projectiles** used by the [Attack Ability](cbt_ranged_attacks.md).
- **Cast Actors** and **Targeting Actors** used by the [Cast Ability](cbt_casts.md).
- **Marker Actors** used by the [Target Lock Ability](cbt_target_lock.md).

If you need to support new objects, you can do so by extending `NinjaCombatPoolableActor`, which is recommended, or by
implementing `CombatPoolableActorInterface`. 

## Retrieving Actors
To retrieve an actor from the pool, you can use the `TryGetActorFromPool` function, from the **Actor Pool Function Library**.
Supported actors listed before are already retrieved using this functionality and require no additional work.

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
> The Actor Pool Component will log messages when an actor is retrieved or when there were no instances available. To
> track these messages, set the output level of `LogNinjaCombat` to _Verbose_.
{style="note"}
