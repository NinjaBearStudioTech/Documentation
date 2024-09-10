# Actor Pooling
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

<tldr>
    <ul>
      <li>Combat Pawns can activate their Actor Pool by declaring a <code>NinjaCombatActorPoolComponent</code>.</li>
      <li>Combat Pawns with a valid Actor Pool must implement <code>CombatPoolProviderInterface</code>.</li>
      <li>The Actor Pool supports any Actor, but they must implement <code>CombatPoolableActorInterface</code>.</li>
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

### Supported Actors

Currently, **Projectiles** and **Cast** actors are supported by default.
