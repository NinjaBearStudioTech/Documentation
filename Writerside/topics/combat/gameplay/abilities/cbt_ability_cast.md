# Cast Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The <b>Cast Ability</b> enables the creation of common "spells".</li>
        <li>It supports the <b>Gameplay Targeting System</b>, a dedicated and stand-alone <b>Cast Actor</b> and also <b>Ability System Target Actors</b>.</li>
        <li>All relevant actors are integrated with the <b>Actor Pool</b>.</li>
    </ul>
</tldr>

The **Cast Ability** enables the creation of common "spells", like Area of Effect, Shields, Summons, Buffs etc.

<img src="cbt_cast_ability.png" alt="Cast Ability" thumbnail="true" border-effect="line"/>

## Cast Actor

The Combat System provides a **Cast Actor** that can be used in conjunction with the **Cast Ability**, when configured 
to **Spawn an Actor** to collect targets colliding with its **Sphere Component**.

The actor class, `NinjaCombatCastActor` is an implementation of `CombatCastInterface`, and can be used as a base class
for any Blueprints or C++ classes. This class is also a valid [**Poolable Actor**](cbt_actor_pooling.md).

The following properties are available to adjust aspects of the Cast Actor:

| Property                | Description                                                             |
|-------------------------|-------------------------------------------------------------------------|
| Should Ignore Source    | If set to true, automatically ignores the cast source in the collision. |
| Try to Align with Floor | If set to true, automatically tries to align the actor with the floor.  |
| Floor Trace Channel     | Trace Channel used to detect the floor.                                 |
| Floor Offset            | Offset added to the floor location.                                     |

Additionally, the Cast Actor provides the following functions, in addition to the base interface implementation

| Function               | Description                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| Get Cast Source        | Retrieves the actor responsible for this Cast.                              |
| Get Weapon             | Retrieves a weapon from the source, using a Gameplay Tag Query.             |
| Try Align With Floor   | Attempts to align the current actor with the floor, if configured to do so. |
| Align With Floor       | Actual logic, including the trace. Can be overridden do adjust the logic.   |
| Apply Effect To Target | Applies the Gameplay Effect to a target.                                    |

Here is an example of a Cast Actor:

<img src="cbt_cast_actor.png" alt="Cast Actor" thumbnail="true" border-effect="line"/>

1. Extends the `StartCast` function, and call the logic from **parent**.
2. Sets the location of the Cast Actor as the same location as the owner's shield, retrieved via `GetWeapon`.
3. Binds an event to the Particle System and activates it. It **resets** the Niagara Component.
4. Activates the audio component. Is **resets** the Audio Component.
5. When Particles are completed, deactivates the Poolable Actor.

> **Time To Live and Particles**
> 
> If your Cast Actor is retrieved from the pool, make sure that the value set to **Time to Live Outside Pool** is 
> bigger than the duration of the visual effects. Otherwise, the particles will be deactivated too early.

### Modifying the Gameplay Effect

The Cast Actor is designed in a way so it will not rely on the owner's Ability System Component. That is important as 
the owner's ASC might not be available anymore to apply Gameplay Effects, when the Cast Actor collects a target.

But if you need to modify the Gameplay Effect Spec set by the Gameplay Ability, then you can do so via Set By Caller
Magnitudes, Curve Modifiers and Dynamic Tags.

The following functions can be implemented for this purpose:

- `GetDynamicGameplayTags`: Determines dynamic Gameplay Tags applied to the spec, when a cast target is acquired.
- `GetAdditionalSetByCallerMagnitudes`: Adds/replaces magnitudes available in the GE with current values.

If you need more drastic changes to the Effect Handle, then you should look into the `ApplyGameplayEffectToData` function,
but that modification is only available in C++.