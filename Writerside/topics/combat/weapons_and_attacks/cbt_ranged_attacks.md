# Ranged Attacks
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The <b>weapon</b> or <b>character</b> performing the attack must implement the <b>Ranged Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Ranged Attacks</b>. Once it activates, it will listen to many <b>Launch Projectile Events</b>.</li>
        <li><b>Launch Projectile</b> events are sent usually using the <b>Launch Projectile Notify</b> start and stop the scan, executed each frame while active.</li>
        <li>The <b>Projectile Actor</b> represents a projectile in the game and applies a <b>Gameplay Effect</b> on collision.</li>
    </ul>
</tldr>

**Ranged Attacks** are one of the _core features_ of Ninja Combat. They are usually implemented using a combination of
**Animation Montages**, **Gameplay Abilities** and **Projectile Actors**, applying specified **Damage Effects** on collision.

## Ranged Weapon Interface
Any object, such as **Pawns** or **Weapons**, meant to execute **ranged attacks** must implement `CombatRangedInterface`.
It defines the source mesh, from which a **projectile** will be launched. 

This interface is designed in a way to support projectiles being launched from different source meshes, based on the 
**socket** that is being used.

| Function                     | Description                                                                |
|------------------------------|----------------------------------------------------------------------------|
| `GetProjectileSourceMesh`    | Provides the mesh used to launch a **projectile** from a given **socket**. |

## Projectile Interface
**Projectiles** are the main participants in the **ranged combat**. They are launched by the Attack Gameplay Ability, or
any other ability designed to do so, and carry a pre-generated version of the **Gameplay Effect** that should be applied
when they **collide with targets**.

| Function                      | Description                                                                                                                 |
|-------------------------------|-----------------------------------------------------------------------------------------------------------------------------|
| `GetSpeed`                    | Provides the projectile speed. Can be obtained from a **Projectile Movement Component** or other means.                     |
| `PrepareLaunch`               | Prepares any initial data before the projectile is launched.                                                                |
| `Launch`                      | Effectively launches the projectile.                                                                                        |
| `GetImpactEffectClass`        | Provides a **Gameplay Effect** applied when this actor **collides** with a target. Overrides the Ability Hit Effect.        |
| `GetImpactEffectLevel`        | Level used when instantiating the **Damage Gameplay Effect**.                                                               |
| `SetImpactEffectHandle`       | Sets the pre-configured **Gameplay Effect Handle** used by the projectile.                                                  |
| `GetDamage`                   | Optionally provides a **damage** value magnitude set to the Gameplay Effect using `combat.data.damage` as the **data tag**. |
| `GetPoiseConsumption`         | Optionally provides a **poise** value magnitude set to the Gameplay Effect using `combat.data.poise` as the **data tag**.   |
| `GetActorsHit`                | Provides all actors that were hit by this projectile.                                                                       |
| `GetProjectileImpactStrength` | Defines a strength applied when **physical reactions** are enabled.                                                         |
| `HandleImpactCosmetics`       | Invoked by the Damage System to render **cosmetics** from a registered impact, via the **Gameplay Cue** system.             |

> **Gameplay Effect Priority**
>
> You can define a Gameplay Effect in three places: **Attack Ability**, **Projectile Interface**, and **Launch Request**.
>
> If a Gameplay Effect is present in one or more of these slots, the selection order is **Launch Request > Projectile Interface > Attack Ability**.
{style="note"}

## Projectile Actor
The Projectile Actor (`NinjaCombatProjectileActor`) is an **abstract class** that can be used as a base for all your projectiles. 
It properly implements the **Projectile Interface**, executing the expected logic and exposing properties for adjustment.

This implementation is based on the **Projectile Movement Component** implementation. It does not assume any specific 
type of visuals, so you can add a **Static Mesh Component**, **Skeletal Mesh Component**, **Particle Effects** and so on.

<procedure title="Configure a Projectile Actor" collapsible="true" default-state="expanded">
    <step>Create a new <b>Blueprint</b> based on <code>NinjaCombatProjectileActor</code>.</step>
    <step>Add a <b>projectile mesh</b>, it can be a <b>Static or Skeletal Mesh Component</b>, depending on your weapon requirements.</step>
    <step>In the <b>Projectile Movement Component</b>, adjust the <b>speed</b> to your liking, but <code>3000</code> should be a good starting point.</step>
    <step>Configure any <b>cosmetics</b> the appropriate slots.</step>
</procedure>

The Default Projectile Actor has the following **properties** that can be used to adjust its behavior.

| Property       | Description                                                         |
|----------------|---------------------------------------------------------------------|
| `AimingMode`   | Determines how the projectile aims for targets when launched.       |
| `MaxBounces`   | Max bounces allowed for the projectile. Zero means "_no bouncing_". |
| `TraceChannel` | The channel used to trace for target between frames.                |

<procedure title="Prepare the Weapon for Projectiles" collapsible="true" default-state="expanded">
    <step>Open the <b>Static or Skeletal Meshes</b> used to represent your ranged weapons.</step>
    <step>
        <p>Place a socket where the projectile should start its trajectory. This will be used when the projectile is launched.</p>
        <img src="cbt_wpatk_melee_weapon_sockets.png" alt="Weapon Sockets" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

<procedure title="Configure a Ranged Weapon" collapsible="true" default-state="expanded">
    <step>Open the <b>Rifle Weapon Actor</b>, created in the <b><a href="cbt_weapon_actors.md">Weapon Actors page</a></b>.</step>
    <step>
        <p>Implement the <code>GetProjectileSourceMesh</code> function, returning the <b>Static or Skeletal Mesh</b> that will be used when <b>launching projectiles</b>.</p>
        <img src="cbt_wpatk_melee_get_mesh_implementation.png" alt="Weapon Setup" border-effect="line" thumbnail="true"/>
    </step>
    <step>Set the <b>Projectile Class</b> in the <b>Ranged</b> category.</step>
</procedure>

## Projectile Requests
Projectile Requests are used to **launch projectiles** during an attack. They are usually driven by animation, but the
backing Gameplay Ability is ultimately responsible for launching the projectile. 

<procedure title="Configuring a Melee Scan" collapsible="true" default-state="expanded">
    <step>Create or open an <b>Animation Montage</b> that represents the <b>ranged attack</b>.</step>
</procedure>

### Projectile Request Class

## Attack Ability
The **Attack Ability** is responsible for **Melee** and **Ranged** attacks. To get started with Ranged Attacks, all you
need to do is setting the **Default Animation Montage** and make sure to assign this Gameplay Ability to your character.

## Actor Pooling
Projectiles are a common candidate for **Actor Pooling**. This reduces the cost of **spawning** and **garbage collecting**
projectile actors constantly used in the game.

Ninja Combat has an **[Actor Pool](cbt_actor_pooling.md) and the default **Projectile Actor** is also a **Poolable Actor**. 
The default spawn logic in the Attack Gameplay Ability will take that into consideration and will try to retrieve an 
actor from the pool, before spawning a new one in the world.

Check the **[Actor Pool page](cbt_actor_pooling.md)** for more information about enabling the Actor Pool and registering 
the projectile actor to it.

