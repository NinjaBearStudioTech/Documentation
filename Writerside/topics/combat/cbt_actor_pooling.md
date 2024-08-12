# Actor Pooling
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

<tldr>
    <ul>
        <li>Combat Pawns can activate their Actor Pool by declaring a <code>NinjaCombatActorPoolComponent</code>.</li>
        <li>Combat Pawns with a valid Actor Pool must implement <code>CombatPoolProviderInterface</code>.</li>
        <li>The Actor Pool supports any Actor, but they must implement <code>CombatPoolableActorInterface</code>.</li>
        <li>The <code>NinjaCombatPoolableActor</code> is a default implementation that supports replication.</li>
        <li>The pool is replicated and pooled actors behave as if they were placed in the map.</li>
    </ul>
</tldr>

It's very common for a combat system to require spawning and destroying multiple actors. Projectiles and Cast actors
are very common use cases where actors are frequently spawned and destructed in short intervals.

To mitigate the cost of constantly spawning/destroying actors during gameplay, an **Actor Pool** was introduced to the
Combat System, that can prepare a predefined amount of instances of actors frequently used by a combatant.

## The Actor Pool Component

Each combatant has its own Actor Pool, represented by the `NinjaCombatActorPoolComponent`. You can configure all
actors that will be pooled and how many instances will be available.

It's important that combatants using an Actor Pool implement the `CombatPoolProviderInterface`, providing the component,
so external functionalities can quickly retrieve and use the pool, such as the Projectile Request.

## Poolable Actors

Poolable Actors are primarily defined by the `CombatPoolableActorInterface`. This means that any actor implementing this
interface can be added to the Actor Pool Component.

If possible, and if you are building a multiplayer game, then it is recommended that, instead of implementing that interface,
you extend from `NinjaCombatPoolableActor`, which is the **default base class**. 

This base actor not only implements the Poolable Actor interface, but it's configured in a way that it supports 
networking and replication, as if the actor was originally placed in the map.

The Actor Pool Component and the base Poolable Actor can work together to reduce the initial network usage that would be
necessary to replicate many actors being spawned at the same time, when preparing the pool.

You can configure the Actor Pool in the **Actor Pool Component**, by setting the actor class and the amount of instances
that should be initialized.

![Actor Pool Setup](cbt_actor_pool_setup.png "Actor Pool Setup")

### Supported Actors

Right now, Projectiles and Cast actors are supported by default.