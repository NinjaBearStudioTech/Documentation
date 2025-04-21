# Ranged Attacks
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The <b>weapon</b> or <b>character</b> performing the attack must implement the <b>Ranged Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Ranged Attacks</b>. Once it activates, it will listen to many <b>Launch Projectile Events</b>.</li>
        <li>The <b>Launch Projectile</b> event is usually sent using the <b>Launch Projectile Notify</b>, but it's a <b>Gameplay Event</b> that can be triggered from other sources.</li>
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

| Function                      | Description                                                                                                                                                  |
|-------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `GetSpeed`                    | Provides the projectile speed. Can be obtained from a **Projectile Movement Component** or other means.                                                      |
| `PrepareLaunch`               | Prepares any initial data before the projectile is launched.                                                                                                 |
| `Launch`                      | Effectively launches the projectile.                                                                                                                         |
| `GetImpactEffectClass`        | Provides a **Gameplay Effect** applied when this actor **collides** with a target. Overrides the Gameplay Effect specified in the Ability if one is present. |
| `GetImpactEffectLevel`        | Level used when instantiating the **Damage Gameplay Effect**.                                                                                                |
| `SetImpactEffectHandle`       | Sets the pre-configured **Gameplay Effect Handle** used by the projectile.                                                                                   |
| `GetDamage`                   | Optionally provides a **damage** value magnitude set to the Gameplay Effect using `combat.data.damage` as the **data tag**.                                  |
| `GetPoiseConsumption`         | Optionally provides a **poise** value magnitude set to the Gameplay Effect using `combat.data.poise` as the **data tag**.                                    |
| `GetActorsHit`                | Provides all actors that were hit by this projectile.                                                                                                        |
| `GetProjectileImpactStrength` | Defines a strength applied when **physical reactions** are enabled.                                                                                          |
| `HandleImpactCosmetics`       | Invoked by the Damage System to render **cosmetics** from a registered impact, via the **Gameplay Cue** system.                                              |

> **Gameplay Effect Priority**
>
> You can define a Gameplay Effect in three places: **Attack Ability**, **Projectile Interface**, and **Launch Request**.
>
> If multiple Gameplay Effects are defined, the system selects the one in the following order: **Launch Request > Projectile Interface > Attack Ability**.
{style="note"}

## Projectile Actor
The Projectile Actor (`NinjaCombatProjectileActor`) is an **abstract class** that can be used as a base for all your projectiles.
It fully implements the **Projectile Interface**, with built-in logic and exposed properties for easy configuration.

This implementation is based on the **Projectile Movement Component** implementation. It does not assume any specific 
type of visuals, so you can add a **Static Mesh Component**, **Skeletal Mesh Component**, **Particle Effects** and so on.

<procedure title="Configure a Projectile Actor" collapsible="true" default-state="expanded">
    <step>Create a new <b>Blueprint</b> based on <code>NinjaCombatProjectileActor</code>.</step>
    <step>Add a <b>projectile mesh</b>, it can be a <b>Static or Skeletal Mesh Component</b>, depending on your weapon requirements.</step>
    <step>In the <b>Projectile Movement Component</b>, adjust the <b>speed</b> to your liking, but <code>3000</code> should be a good starting point.</step>
    <step>Configure any <b>cosmetics</b> in their appropriate slots.</step>
</procedure>

The Default Projectile Actor has the following **properties** that can be used to adjust its behavior.

| Property         | Description                                                         |
|------------------|---------------------------------------------------------------------|
| `AimingMode`     | Determines how the projectile aims for targets when launched.       |
| `MaxBounces`     | Max bounces allowed for the projectile. Zero means "_no bouncing_". |
| `TraceChannel`   | The channel used to trace for target between frames.                |
| `ImpactStrength` | Strength applied when a physical animation system is in use.        |

The **Aiming Mode** supports the following options:
- **Forward**: The projectile is launched forward, from its origin socket.
- **Targeting System**: The projectile is launched towards a target collecting via a **targeting preset**, from the Gameplay Targeting System.
- **Location**: The projectile is launched towards the location set by `SetInitialLocation`, most likely called calculated and called in `PrepareLaunch`.

> **Camera Aiming**
> 
> You can implement **Camera Aiming** using the **Location Aiming Mode** performing the calculations in the `PrepareLaunch`
> function, and setting the desired final location via `SetInitialLocation`.  

<procedure title="Prepare the Weapon for Projectiles" collapsible="true" default-state="expanded">
    <step>Open the <b>Static or Skeletal Meshes</b> used to represent your ranged weapons.</step>
    <step>
        <p>Place a socket where the <b>projectile is positioned on launch</b>. Make sure that this socket is rotated <b>forward</b>.</p>
        <img src="cbt_wpatk_ranged_weapon_sockets.png" alt="Weapon Sockets" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

<procedure title="Configure a Ranged Weapon" collapsible="true" default-state="expanded">
    <step>Open the <b>Rifle Weapon Actor</b>, created in the <b><a href="cbt_weapon_actors.md">Weapon Actors page</a></b>.</step>
    <step>
        <p>Implement the <code>GetProjectileSourceMesh</code> function, returning the <b>Static or Skeletal Mesh</b> that will be used when <b>launching projectiles</b>.</p>
        <img src="cbt_wpatk_ranged_get_mesh_implementation.png" alt="Weapon Setup" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Make sure that your <b>Ranged Weapon</b> has a <b>weapon tag</b>, such as <code>Inventory.Item.Type.Rifle</code></p>
        <img src="cbt_wpatk_ranged_weapon_tags.png" alt="Weapon Tags" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

The Projectile Actor can be **extended** for other specific behaviors such as "Homing Projectiles", "Damage on Path", etc.

## Projectile Requests
Projectile Requests are used to **launch projectiles** during an attack. While animation triggers the launch event, the 
projectile is ultimately spawned by the Gameplay Ability.

<procedure title="Configuring a Projectile Launch" collapsible="true" default-state="expanded">
    <step>Create or open an <b>Animation Montage</b> that represents the <b>ranged attack</b>.</step>
    <step>Find the frame where the launch should happen and add a <b>Launch Projectile</b> Animation Notify.</step>
    <step>
        <p>Configure the Animation Notify to launch the projectile from a <b>weapon</b>, retrieved dynamically from the <b>Weapon Manager</b>, using the <b>weapon query</b> to match with the desired weapon (e.g. <code>Inventory.Item.Type.Rifle</code>).</p>
        <img src="cbt_wpatk_launch_projectile_notify.png" alt="Weapon Tags" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

### Projectile Request Class
This object is used to transfer launch data between all the framework layers: **Animation**, **Ability**, and **Task**.
It contains the logic to **spawn a projectile actor**, including the option to retrieve it from the **Actor Pool**.

The **Launch Projectile Anim Notify** creates an instance of this class which will be used by the **Attack Ability** to 
ultimately spawn a projectile actor, when the **gameplay event** is received.

> **Modifying the Projectile Actor**
>
> You can modify the projectile actor after it is spawned by the system, via the `ModifyProjectileActor`. This function 
> can be extended in Blueprints or C++.
{style=note}

### Projectile Launch and Hit Flow
We can summarize the **projectile lifecycle** with the following events:

1. The Ranged Attack Ability is triggered and plays the Animation Montage.
2. The Animation Montage plays the Launch Projectile Animation Notify.
3. The Animation Notify sends a Gameplay Event to the current Attack Ability.
4. The Attack Ability retrieves the Projectile Request from the event payload and spawns the projectile.
5. On hit, the projectile applies the Gameplay Effect on the target.

## Attack Ability
The **Attack Ability** is responsible for **Melee** and **Ranged** attacks. To get started with Ranged Attacks, all you
need to do is setting the **Default Animation Montage** and make sure to assign this Gameplay Ability to your character.

<procedure title="Configuring the Ranged Attack" collapsible="true" default-state="expanded">
    <step>Create a <b>Gameplay Ability</b> based on <code>CombatAbility_Attack</code>.</step>
    <step>
        <p>In the <b>Ranged Attack</b> category, set the <b>Projectile Class</b> that will be used by this attack.</p>
        <note>
            <p><b>Projectile Class Priority</b></p>
            <p>You can set the <b>Projectile Class</b> in the <b>Projectile Launch Notify</b>, <b>Gameplay Ability</b> and <b>Weapon Actor</b>.</p>
            <p>The projectile used by the ability is selected in that order. So you can use these locations to set <b>projectile overrides</b>.</p>
        </note>
    </step>
    <step>Configure the <b>Animation Montage</b> previously configured, with the <b>Launch Projectile Animation Notify</b>.</step>
    <step>
        <p>When you are done, your <b>Ranged Attack</b> should be similar to this.</p>
        <img src="cbt_wpatk_attack_ability_ranged.png" alt="Ranged Attack" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

## Actor Pooling
Projectiles are a common candidate for **Actor Pooling**. This reduces the cost of **spawning** and **garbage collecting**
projectile actors constantly used in the game.

Ninja Combat has an **[Actor Pool](cbt_actor_pooling.md)** and the default **Projectile Actor** is also a **Poolable Actor**. 
The default spawn logic in the Attack Gameplay Ability will take that into consideration and will try to retrieve an 
actor from the pool, before spawning a new one in the world.

Check the **[Actor Pool page](cbt_actor_pooling.md)** for more information about enabling the Actor Pool and registering 
the projectile actor to it.
