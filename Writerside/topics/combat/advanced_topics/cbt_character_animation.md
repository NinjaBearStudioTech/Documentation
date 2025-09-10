# Character Animation
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

Since many features of the Combat System rely on animation, Ninja Combat provides optional animation support classes that 
can be integrated into your character's animation layer.

These animation assets are entirely optional. You may use your own animation system, as long as you replicate the internal 
logic required by the Combat System.

## Animation Instance
The default Animation Instance, `NinjaCombatAnimInstance`, can be used as the base class for character animation logic. 
It provides common locomotion variables and is connected to the Combat System to track important states such as Target 
Lock, Blocking, and Stagger.

To use this class, create a new Animation Instance in Blueprint or C++, using `NinjaCombatAnimInstance` as the parent 
class. This class is highly flexible—you can still use it even if your locomotion logic is fully customized.

The following properties are available and can be accessed by searching for `Get [Variable Name]`, or through **property bindings**:

| Variable              | Data Type | Category   | Description                                                              |
|-----------------------|-----------|------------|--------------------------------------------------------------------------|
| InAir                 | `boolean` | Locomotion | Indicates if the character is in midair.                                 |
| Crouching             | `boolean` | Locomotion | Indicates if the character is crouched.                                  |
| Accelerating          | `boolean` | Locomotion | True when the character has input acceleration (useful for transitions). |
| Moving                | `boolean` | Locomotion | True when the character is currently moving.                             |
| MovingForward         | `boolean` | Locomotion | True when the character is moving forward (uses angle threshold).        |
| StartedMoving         | `boolean` | Locomotion | True if the character started moving this frame.                         |
| Acceleration          | `float`   | Locomotion | The current input acceleration magnitude.                                |
| Speed                 | `float`   | Locomotion | The 2D magnitude of the character's velocity.                            |
| DisplacementSpeed     | `float`   | Locomotion | Distance moved since last frame (useful for root motion blending).       |
| Velocity              | `vector`  | Locomotion | The velocity vector (direction and magnitude).                           |
| Strafing              | `boolean` | Locomotion | Indicates if the character is strafing (based on Combat System updates). |
| Blocking              | `boolean` | Combat     | Indicates if the character is currently blocking.                        |
| Staggered             | `boolean` | Combat     | Indicates if the character is staggered.                                 |
| Dead                  | `boolean` | Combat     | Indicates if the character has died.                                     |
| FullBodyBlend         | `float`   | Blends     | Blend alpha for full-body montages (typically 0 when moving).            |
| UpperBodyBlend        | `float`   | Blends     | Blend alpha for upper-body layers (default is always 1).                 |
| ForwardAngleThreshold | `float`   | Settings   | Angle used to determine whether movement is considered “forward.”        |

> **Variable Usage**
>
> You don't need to use all variables—many are provided for convenience and can be modified or ignored depending on your needs.

All calculations are implemented in dedicated functions, which can be overridden in Blueprint or C++ for further customization.

| Function                      | Override? | Description                                                                      |
|-------------------------------|-----------|----------------------------------------------------------------------------------|
| `TryGetCharacterOwner`        | No        | Similar to `TryGetPawnOwner`, but returns a `Character` type.                    |
| `GetCharacterMovement`        | No        | Returns the Character Movement Component.                                        |
| `HandleCombatTargetChanged`   | Yes       | Called when the combat target changes—useful for updating strafing behavior.     |
| `HandleStaggeredStateChanged` | Yes       | Called when the stagger state changes—use to update the animation graph.         |
| `HandleDyingState`            | Yes       | Called when the character dies—can trigger death states or montages.             |
| `HandleBlockingStateChanged`  | Yes       | Called when the blocking state changes—can drive animation layers or montages.   |
| `CalculateLocomotionValues`   | Yes       | Calculates all locomotion variables listed above.                                |
| `CalculateBlendValues`        | Yes       | Calculates blend values (e.g., full-body vs. upper-body). Runs after locomotion. |

> **Extending Functionality**
>
> You can override any of the listed functions in Blueprint to fully adapt the animation logic without writing C++ code,
> although you can also use C++ if needed/preferred. The base implementation is designed to be easily extended.

## Animation Notifies
Multiple Notifies and Notify States are available to handle multiple aspects of the system.

| Notify             | Type         | Description                                                                                      |
|--------------------|--------------|--------------------------------------------------------------------------------------------------|
| Cast               | Notify       | Sends a **Gameplay Event** to the **Cast Ability** to trigger the actual cast.                   |
| Combo Window       | Notify State | Defines a part of an attack or ability that can receive input to advance a combo.                |
| Death              | Notify       | Sends a **Gameplay Event** to the **Death Ability** to start the "Finish Dying" flow.            |
| Invulnerability    | Notify State | Applies the **Invulnerability Effect** for the duration of the state.                            |
| Launch Projectile  | Notify       | Sends a **Gameplay Event** to the **Attack Ability** to launch a projectile.                     |
| Melee Scan         | Notify State | Sends **Gameplay Events** to the **Attack Ability** to start and stop melee scans.               |
| Opportunity Damage | Notify       | Sends a **Gameplay Event** to the **Opportunity Attack Ability** to apply any deliberate damage. |
| Parry Window       | Notify State | Defines a part of an **attack** that can be **parried**.                                         |
| Ragdoll            | Notify       | Requests the owner to enter **ragdoll** mode.                                                    |

Notifies are a great way to connect gameplay events to something visual that can be easily identified by players. But
keep in mind that Animation Notifies are **frame-rate dependant** and might be skipped during low FPS scenarios. 

If that is a potential problem for you, then you should consider reinforcing their functionality into **fallback systems**.

## Animation Providers
These classes are used by **Gameplay Abilities** to select an appropriate animation for the character. The following
providers are readily available:

| Provider                   | Description                                                                                                                                                           |
|----------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Default Provider           | A simple Animation Provider that uses a specific Animation and optionally a section.                                                                                  |
| Directional Provider       | An abstract Animation Provider that can select animations or sections based on an angle.                                                                              |
| Directional Evade Provider | Selects the animation using an angle calculated from the Character Movement and Forward Reference.                                                                    |
| Hit Reaction Provider      | Selects the animation using an angle calculated from the Target and an incoming hit, or using a **Chooser Table**.                                                    |
| Random Animation Provider  | Randomly selects on animation montage from a list of possible choices.                                                                                                |
| Weapon Animation Provider  | Retrieves an Animation from the source object (usually the weapon) for the ability. <br/> The source object must implement `CombatAnimationContextProviderInterface`. |

### Animation Montage Provider Interface
This interface can be added to any **Gameplay Ability** using an Animation Provider. When added, it can provide default
values directly from the Gameplay Ability, that will override any value defined by the provider.

This interface can be added to Owners or Weapons, when used in conjunction with the Weapon Animation Provider. This will
allow the same ability to be reused across multiple weapons and have specific animations provided by the weapons.
