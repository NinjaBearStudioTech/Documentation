# Casts
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Casts are abilities that will apply damage or effects to targets collected using <b>various criteria</b> and <b>applying different kinds of effects</b>.</li>
        <li>They can collect targets using <b>external Actors</b>, the <b>Gameplay Targeting System</b> or the <b>Ability Targeting System</b>.</li>
        <li>The <b>Cast</b> event is usually triggered using the <b>Cast Notify</b>, but it's a <b>Gameplay Event</b> that can be triggered from other sources.</li>
    </ul>
</tldr>

The term "Cast" comes from the traditional RPG expression, _spellcasting_. However, this Gameplay Ability can also be 
used as a base for other abilities that require **complex target selection** (friendly or hostile), **optional target 
confirmation** and diverse options regarding how to **apply gameplay effects** to these targets.

## Cast Ability
The Cast Ability can be configured in many ways to support different design goals. Below is a **property summary**, 
followed by details on supported **triggers**, **targeting options**, and **commit timings**.

| Property               | Usage                   | Description                                                                                                                       |
|------------------------|-------------------------|-----------------------------------------------------------------------------------------------------------------------------------|
| Cast Trigger           | Any                     | Defines **when** the cast will actually happen. See the **Cast Triggers** table below.                                            |
| Targeting              | Any                     | Defines **how** the ability collects targets. See the **Targeting** table below.                                                  |
| Commit Time            | Any                     | Defines **when** the ability commits its cost and cooldown. See the **Commit Time** table below.                                  |
| Cast Effect Class      | Any                     | The **Gameplay Effect class** applied to all acquired targets.                                                                    |
| Cast Effect Level      | Any                     | The **level** used when applying the Gameplay Effect.                                                                             |
| Cast Actor Class       | Spawn Actor             | The Actor to spawn when using **Spawn Actor** or **Wait for Confirmation and Spawn Actor**. Must implement `CombatCastInterface`. |
| Targeting Preset       | Targeting System        | Targeting Preset used when using the **Targeting System** option.                                                                 |
| Targeting Actor Class  | Confirmation            | Actor used to confirm and collect targets (e.g., ability target reticle).                                                         |        
| Section When Confirmed | Confirmation            | Montage section to play when the target is confirmed.                                                                             |
| Section When Cancelled | Confirmation            | Montage section to play when the target is cancelled.                                                                             |
| Confirmation Type      | Confirmation (no Actor) | Confirmation type used by the **Gameplay Ability System** when confirming targets without a custom actor.                         |

### Cast Triggers
| Cast Trigger       | Description                                                                                                 |
|--------------------|-------------------------------------------------------------------------------------------------------------|
| Ability Activation | The cast is triggered as soon as the ability **activates**.                                                 |
| Gameplay Event     | The cast is triggered when a **Gameplay Event** is received, typically from a **Cast Animation Notify**.    |

### Targeting Options
| Targeting                             | Description                                                                                                                   |
|---------------------------------------|-------------------------------------------------------------------------------------------------------------------------------|
| Targeting System                      | Uses a **Targeting Preset** from the Targeting System to collect targets.                                                     |
| Spawn Actor                           | Spawns an Actor implementing `CombatCastInterface` to collect targets (typically using collision).                            |
| Wait for Confirmation                 | Uses the **Gameplay Ability System** to allow the player to confirm a target or location.                                     |
| Wait for Confirmation and Spawn Actor | First confirms the **target location**, then spawns an Actor to collect targets at that location.                             |

### Commit Time Options
| Commit Time       | Description                                                  |
|-------------------|--------------------------------------------------------------|
| Ability Activates | Commits cost and cooldown as soon as the ability activates.  |
| Cast Starts       | Commits as soon as the cast is triggered.                    |
| Targets Acquired  | Commits only if at least one target is acquired.             |
| Ability Ends      | Commits at the end of the ability, regardless of outcome.    |

## Cast Requests
Similar to the Combat Ability, that uses [](cbt_melee_attacks.md#melee-scans) and [](cbt_ranged_attacks.md#projectile-requests)
as **data transfer objects**, the Cast Ability uses **Cast Requests** for the same purpose.

Cast Requests are usually sent by the **Cast Notify** and are received by the ability as the **payload** in the Gameplay
Event identified by `Combat.Event.Cast`.

<procedure title="Configuring a Cast" collapsible="true" default-state="expanded">
    <step>Create or open an <b>Animation Montage</b> that represents the <b>cast</b>.</step>
    <step>Find the frame where the cast should occur and add a <b>Cast</b> Animation Notify.</step>
</procedure>

### Cast Request Class
This object is used to transfer cast data between all the framework layers: **Animation**, **Ability**, and **Task**.
It contains the logic to **spawn a cast actor**, including the option to retrieve it from the **Actor Pool**.

The **Cast Anim Notify** creates an instance of this class which will be used by the **Cast Ability** to ultimately 
spawn a cast actor, when the **gameplay event** is received.

> **Modifying the Cast Actor**
>
> You can modify the cast actor after it is spawned by the system, via the `ModifyCastActor`. This function can be 
> extended in Blueprints or C++.
> {style=note}

## Executing a Targeting Preset to Apply Damage
Let's begin exploring usage scenarios for the Cast Ability, starting with the most straightforward one:
**collecting targets using a preset and applying damage**. This is usually enough for abilities such as **buffs** and 
**debuffs**.

<procedure title="Configure the Targeting Preset" collapsible="true" default-state="expanded">
    <step>Create a new <b>Data Asset</b> based on <code>TargetingPreset</code>.</step>
    <step>Add a <b>Targeting Task</b> to select actors in an area, using a <b>capsule shape</b> with a radius of <code>500</code>. Use the <b>CombatObject</b> collision channel.</step>
    <step>Add a <b>Filter Task</b> to exclude actors that do not match your base actor class or type.</step>
    <step>Add another <b>Filter Task</b> to remove actors that are already <b>dead</b>.</step>
    <img src="cbt_wpatk_cast_targeting_preset.png" alt="Cast Targeting Preset" border-effect="line" thumbnail="true"/>
</procedure>

<procedure title="Create the Damage Effect" collapsible="true" default-state="expanded">
    <step>Create a <b>Gameplay Effect</b> extending from <code>GameplayEffect</code>.</step>
    <step>Add a <b>Modifier</b> that increases the <b>Pending Damage</b> attribute.</step>
    <step>
        <p>Add <code>CombatExecution_Damage</code> to the list of <b>Executions</b>.</p>
        <tip>
            <p><b>Combat Attributes</b></p>
            <p>To use this Execution Class, make sure the <b>Combat Attribute Set</b> is initialized for your character, including a valid value for <code>BaseDamage</code>.</p>
        </tip>
    </step>
    <step>In the <b>Execution</b> section, add a <b>Modifier</b> that multiplies the <code>Base Damage</code> by <code>2.0</code>, or any value you prefer.</step>
    <img src="cbt_wpatk_cast_damage_effect.png" alt="Cast Gameplay Effect" border-effect="line" thumbnail="true"/>
</procedure>

<procedure title="Create the Cast Ability" collapsible="true" default-state="expanded">
    <step>Create a <b>Gameplay Ability</b> extending from <code>CombatAbility_Cast</code>.</step>
    <step>Set the <b>Cast Trigger</b> to <b>Gameplay Event</b>.</step>
    <step>Assign the Gameplay Effect you created as the <b>Cast Effect Class</b>.</step>
    <step>Set <b>Targeting</b> to <b>Targeting System</b>, and assign the Targeting Preset created earlier.</step>
    <step>Assign the Animation Montage that includes the <b>Cast Notify</b> as the <b>Default Animation</b>.</step>
    <img src="cbt_wpatk_cast_ability_01.png" alt="Cast Gameplay Ability" border-effect="line" thumbnail="true"/>
</procedure>

If you execute this ability in-game, it should apply the configured Gameplay Effect to all valid targets around the 
player, based on the criteria defined in your Targeting Preset.

> **Cosmetics on Hit**
> 
> You can apply **visual or sound effects** to affected targets by configuring Gameplay Cues in the **Gameplay Effect** 
> set in the Cast Ability.
> {style=note}

## Spawning a Cast Actor to Apply Damage
The next usage scenario covers spawning a **Cast Actor** that uses its physical presence in the world to **collect targets**
and apply a **Gameplay Effect**. This is useful for abilities where damage is applied by a spawned actor, such as a
"Black Hole", "Tornado", or similar effect.

Actors used by the Cast Ability must implement the `CombatCastInterface`. Ninja Combat provides a base implementation,
`NinjaCombatCastActor`, which you can extend to create your own Cast Actors.

<procedure title="Create the Cast Actor" collapsible="true" default-state="expanded">
    <step>Create an <b>Actor</b> extending from <code>NinjaCombatCastActor</code>.</step>
    <step>Add any visuals you like, such as a <b>Static Mesh</b>, <b>Niagara Effects</b>, or <b>Audio Components</b>.</step>
    <step>Adjust the size of the built-in <b>Sphere Collision</b> and configure it to act as a <b>Combat Collider</b>.</step>
    <img src="cbt_wpatk_cast_actor_not_pooled.png" alt="Cast Actor" border-effect="line" thumbnail="true"/>
</procedure>

<procedure title="Create the Cast Ability" collapsible="true" default-state="expanded">
    <step>Open the <b>Cast Ability</b> previously created (or a duplicate of it), and set <b>Targeting</b> to <b>Spawn Actor</b>.</step>
    <step>Assign your Cast Actor to the <b>Cast Actor Class</b>.</step>
    <img src="cbt_wpatk_cast_ability_02.png" alt="Cast Gameplay Ability" border-effect="line" thumbnail="true"/>
</procedure>

If you execute this ability in-game, it should spawn your Cast Actor and apply the configured Gameplay Effect to all
valid targets detected by the actor’s collision settings.

## Selecting the Spawn Location for the Cast Actor
Now let’s take the Cast setup one step further by introducing a **Gameplay Ability Target Actor**.  
The **Gameplay Ability System** uses actors based on `GameplayAbilityTargetActor` to handle **targeting** logic.

The result of this targeting process can be either a **group of actors** or a **location**, depending on the
**Targeting Mode** set on the **Cast Ability**.

- When set to **Wait for Confirmation**, the Target Actor provides a **list of targets**.
- When set to **Wait for Confirmation and Spawn Actor**, the Target Actor provides a **location**, which is used to spawn the Cast Actor.

<procedure title="Create the Cast Ability" collapsible="true" default-state="expanded">
    <step>Open the <b>Cast Ability</b> previously created (or a duplicate of it), and set <b>Targeting</b> to <b>Wait for Confirmation and Spawn Actor</b>.</step>
    <step>In the <b>Targeting Actor Class</b>, select the <b>Ability System Targeting Actor</b> you want to use.</step>
    <step>
        <p>Configure your input system to call <code>LocalInputConfirm</code> on the owner's Ability System Component when confirming the target.</p>
        <note>
            <p><b>Ninja Input Handlers</b></p>
            <p><a href="ipt_overview.md">Ninja Input</a> provides <b>confirmation</b> and <b>cancellation</b> input handlers that can be used for this.</p>
        </note>
    </step>
    <img src="cbt_wpatk_cast_ability_03.png" alt="Cast Gameplay Ability" border-effect="line" thumbnail="true"/>
</procedure>

> **Modifying the Target Actor**
> 
> If you need to **perform per-ability execution modifications on the Target Actor**, you can extend the `ModifyActor`
> function in the **Cast Ability**, in Blueprint or C++. 
{style=note}

If you execute this ability in-game, it will spawn your Targeting Actor according to your configuration. 

Once the target location is confirmed, the ability will spawn your Cast Actor and apply the configured Gameplay Effect 
to all valid targets detected through its collision settings.

## Cast Interface
Any actor meant to be used with **casting** must implement `CombatCastInterface`. It defines the **source** responsible
for spawning the actor (e.g. the _combatant_), the **Gameplay Effect Handle** applied and the main execution function.

| Function                  | Description                                                                                                   |
|---------------------------|---------------------------------------------------------------------------------------------------------------|
| `GetCastOwner`            | Provides the actor that "owns" this Cast Actor.                                                               |
| `SetCastOwner`            | Sets the actor that "owns" this Cast Actor. Usually invoked by the Gameplay Ability, when spawning the actor. |
| `SetGameplayEffectHandle` | Sets the Gameplay Effect Handle applied to targets.                                                           |
| `StartCast`               | Starts the cast, performing its logic, target collection, etc.                                                |

## Cast Actor

**Cast Actors** are commonly used during **casting**. They are created by the Cast Gameplay Ability (or another ability) and contain a pre-generated **Gameplay Effect** that is applied to targets they collect—typically via **collision**.

The base **Cast Actor** includes the following properties:

| Property                | Description                                                             |
|-------------------------|-------------------------------------------------------------------------|
| Should Ignore Source    | If true, automatically ignores the cast source during collision checks. |
| Try to Align with Floor | If true, attempts to align the actor with the ground surface.           |
| Floor Trace Channel     | Trace channel used to detect the ground surface.                        |
| Floor Offset            | Vertical offset applied after aligning with the floor.                  |

In addition to the required interface functions, the base Cast Actor provides the following helpers:

| Function               | Description                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| Get Cast Source        | Retrieves the actor responsible for the cast.                               |
| Get Weapon             | Retrieves a weapon from the source using a Gameplay Tag Query.              |
| Try Align With Floor   | Attempts to align with the floor if enabled.                                |
| Align With Floor       | Executes the trace logic. Can be overridden to customize behavior.          |
| Apply Effect To Target | Applies the configured Gameplay Effect to a specific target.                |

<img src="cbt_cast_actor.png" alt="Cast Actor" thumbnail="true" border-effect="line"/>

The example above illustrates a typical implementation:

1. Extends the `StartCast` function and calls the logic from **parent**.
2. Sets the Cast Actor’s location to match the owner’s shield, retrieved via `GetWeapon`.
3. Binds an event to the Particle System and resets (then activates) the Niagara Component.
4. Resets and activates the Audio Component.
5. When the particle effect completes, the actor is deactivated and returned to the pool.

> **Time To Live and Particles**
>
> If your Cast Actor is retrieved from the pool, ensure that the **Time to Live Outside Pool** value is **longer** than the particle effect duration. Otherwise, the effect may be cut off prematurely.
> {style=note}

### Modifying the Gameplay Effect

Cast Actors are designed to be **independent of the owner's Ability System Component**. This ensures they can apply
Gameplay Effects even if the source ASC is no longer valid at the time of execution.

If you need to modify the **Gameplay Effect Spec** generated by the Gameplay Ability, you can do so using
**Set By Caller Magnitudes**, **Curve Modifiers**, or **Dynamic Tags**.

You can implement the following functions for customization:

- `GetDynamicGameplayTags`: Adds dynamic Gameplay Tags to the effect spec as targets are acquired.
- `GetAdditionalSetByCallerMagnitudes`: Injects or overrides magnitudes in the spec using Set By Caller data.

If you need deeper customization of the **Effect Handle** itself, you can override:

- `ApplyGameplayEffectToData`: Full control over how the spec is applied to each target, _available only in C++._

## Actor Pooling
**Cast Actors** and **Targeting Actors** and are good candidates for **Actor Pooling**. This helps reduce the cost of 
**spawning** and **garbage collecting** these actors when they are frequently used in the game.

Both actors are **Poolable Actors**, ready to be used in conjunction with the **[Actor Pool](cbt_actor_pooling.md)** 
provided by Ninja Combat. For more information on enabling the pool and registering your Cast Actor, check the 
**[Actor Pool page](cbt_actor_pooling.md)**.
