# Ranged Combat
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The weapon or character must implement the <b>Ranged Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Ranged Attacks</b>. Once it activates, it will listen to the <b>Launch Projectile</b> Gameplay Event.</li>
        <li>A <b>projectile</b> is launched by the Attack Ability, from a <b>Gameplay Event</b>, and it can be obtained from the <b>Actor Pool</b>.</li>
        <li><b>Damage</b> is applied by the projectile, and it does not need its source to be available.</li>
    </ul>
</tldr>

The **Ranged Combat** functionality is designed to connect animations, launching projectiles and applying their damage
regardless of the owner's Ability System Component. This functionality is also related to the [Actor Pool](cbt_actor_pooling.md).

Here is a Sequence Diagram showing how all the participants in the **Ranged Combat** are related.

<code-block lang="mermaid">
sequenceDiagram
    ASC->>AttackAbility: activate
    activate AttackAbility
        AttackAbility->>AttackAbility: listen for events
        AttackAbility->>Animation: play
        activate Animation
            Animation->>LaunchProjectileNotify: begin
            activate LaunchProjectileNotify
                LaunchProjectileNotify->>ProjectileRequestInstance: initialize
                activate ProjectileRequestInstance
                    ProjectileRequestInstance-->>LaunchProjectileNotify: instance
                deactivate ProjectileRequestInstance
                LaunchProjectileNotify->>AttackAbility: gameplay event
                Animation->>LaunchProjectileNotify: end
            deactivate Animation
            deactivate LaunchProjectileNotify
            AttackAbility->>SpawnProjectileTask: initialize
            activate SpawnProjectileTask
                SpawnProjectileTask-->>AttackAbility: instance
            deactivate SpawnProjectileTask
            AttackAbility->>SpawnProjectileTask: activate
            activate SpawnProjectileTask
                SpawnProjectileTask->>ProjectileRequestInstance: spawn
                activate ProjectileRequestInstance
                    ProjectileRequestInstance->>Projectile: spawn
                    activate Projectile
                    ProjectileRequestInstance-->>SpawnProjectileTask: Projectile
                deactivate ProjectileRequestInstance
            SpawnProjectileTask-->>AttackAbility: Projectile
            deactivate SpawnProjectileTask
            AttackAbility->>Projectile: set GE Spec
            AttackAbility->>Projectile: launch
            deactivate Projectile
    deactivate AttackAbility
</code-block>

## Attack Ability

A Ranged Attack starts with the **Attack Ability**.

<img src="cbt_ranged_ability.png" alt="Ranged Ability" border-effect="line" thumbnail="true"/>

Within the **Ranged Attack** category, you can select the **Projectile Class** and the **Gameplay Effect** that will be
applied when a projectile hits a target.

Then, the [**Animation Provider**](cbt_character_animation.md#animation-providers) determines which animation should be 
played during the attack. The default animation provider uses a single animation montage and section name.

> **Melee and Ranged**
> 
> Melee and Ranged attacks use the same base Ability. This design allows you to have an ability that acts as both, such
> as a "sword attack that also launches a shockwave projectile", without the need to create and activate two abilities.
> 
> Of course, if you still want to use the two abilities to accomplish something like the example above, because you have
> different costs or cooldowns, for example, you are of course free to do so.

## Projectiles

Projectiles are defined using the `CombatProjectileInterface`. Once configured in an Attack Ability, they will be 
launched when the appropriate **Gameplay Event** is received: `Combat.Event.Projectile.Launch`.

Projectiles carry their own **Gameplay Effect Spec Handle**, and don't require the original Gameplay Ability to apply 
their Gameplay Effects when they hit their targets.

> **Gameplay Effect Priority**
>
> You can define a Gameplay Effect in two places: Attack Ability and Projectile.
>
> If a Gameplay Effect is present in more than one place, the order of preference is **Projectile > Attack Ability**.
{style="note"}

### Launch Projectile Notify

Projectiles are launched by the Attack Ability when the `Combat.Event.Projectile.Launch` event is received. This event
can be triggered by any class in your project. By default, the Combat System offers the **Launch Projectile** Animation 
Notify.

<img src="cbt_ranged_anim_notify.png" alt="Ranged Animation Notify" border-effect="line" thumbnail="true"/>

Similar to its **Melee Scan** counterpart, this Animation Notify requires the **source** for the projectile, which could
be either the **owner** or a **weapon** defined by a Gameplay Tag Query.

You can also select a different Projectile Class in this Animation Notify, allowing you to have multiple projectiles
launched by the same animation, from left and right hands, for example.

This Animation Notify will also prepare the object that is expected to be provided by **Gameplay Event Payload**, as
one of its **Optional Objects**: the **Projectile Request**.

### Projectile Request Instance

This object is used to transfer data from the animation and the correct mesh, to the Attack Ability and its internal 
Launch Projectile Task. It also contains the logic to spawn the Projectile Actor, from the correct source location.

If you need to **modify the Actor Spawn logic**, this is the place to look into. You can set a Projectile Request Class 
to each Launch Projectile Animation Notify or **globally**, in the **Project Settings** for Ninja Combat.

> **Modifying the Projectile Request**
>
> You can modify the Spawn Actor logic executed by the Projectile Request Class in the `SpawnProjectile` function. This 
> function can be modified in Blueprints or C++.

### Projectile Actor

Any **Actor** implementing `CombatProjectileInterface` can be a valid projectile, but Ninja Combat provides a default
class that can be used as a **starting point** or at least as a **reference**.

The `NinjaCombatProjectileActor` class is an implementation based on the **Projectile Movement Component**. It provides
the following features:

1. Configuration of the **Impact Strength** for **Physics Reactions**.
2. Maximum amount of **bounces** for the Projectile Movement.
3. A configuration option to override the Impact **Gameplay Effect**.
4. **Impact cosmetics** played when the projectile hits a target.
5. The **Collision Channel** used to detect projectile impacts.
6. An optional **Targeting System Preset** that can be used to **aim** projectiles for their **first** target and then for each target after a **bounce**.

> **Targeting System**
> 
> You can also add variations to your Targeting System Preset, to avoid your projectiles to be too precise. If no targets
> are found, then the projectile just launches to the original velocity, or uses the velocity before a bounce.

The Projectile Actor is also a **Poolable Actor**. The default actor spawn logic will consider the [Actor Pool](cbt_actor_pooling.md)
first, before actually spawning a new projectile.

Projectiles supports a few different types of **Launch Direction** settings, that will determine the initial launch
trajectory. They are defined by the **Aiming Mode** setting.

| Aiming Mode      | Description                                                |
|------------------|------------------------------------------------------------|
| Forward          | Launches the projectile forward, from the origin socket.   |
| Targeting System | Uses the targeting preset to determine an Actor to aim at. |
| Location         | A location set via the `SetInitialLocation` function       | 

> **Pre-launch conditions**
> 
> You can also perform other calculations for the initial location in the `PrepareLaunch` function.

## Ranged Weapon Interface

When launching a projectile from an **owner** or from a **weapon**, the **Projectile Request** must know the **Mesh 
Component** containing the **socket** from which the projectile will be spawned.

The simplest way to provide this **Mesh Component** is by adding `Combat.Component.ProjectileSource` as a **Component Tag**.
Then, the first mesh - Static or Skeletal - tagged will be used.

However, if you want to avoid iterating over components due to potential performance costs, or if you want the flexibility 
to pick different Meshes depending on the **socket** that is being used, then you can do so by implementing the `RangedWeaponInterface`.

| Function                     | Description                                            |
|------------------------------|--------------------------------------------------------|
| `GetProjectileSourceMesh`    | Provides a Skeletal or Static Mesh for a given socket. |

### Weapon Actor

The Weapon Actor (`NinjaCombatWeaponActor`) is an **abstract class** that can be used as a base for all your weapons. It
properly implements the **Ranged Weapon Interface**.