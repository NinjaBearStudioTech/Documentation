# Character Animation
<primary-label ref="combat"/>

Since many aspects of the Combat System are related to animation systems, Ninja Combat provides some Animation assets
that can be used for the character animation.

None of these Animation assets are mandatory, and you are free to use other Animation Systems, as long as the internal
functionality is transferred.

## Animation Instance

The default Animation Instance, `NinjaCombatAnimInstance`, can be used as the base class for Character Animations. It 
provides common locomotion variables, and it is connected to the Combat System to track important states, such as Target
Lock, Blocking and Stagger.

You can use this class by simply creating a new Animation Instance, in Blueprint or C++, using `NinjaCombatAnimInstance`
as a base. This class can be modified in many ways, so you can still consider using it as a base class, even if your
locomotion calculations are completely different.

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
| Hit Reaction Provider      | Selects the animation using an angle calculated from the Target and an incoming hit.                                                                                  |
| Random Animation Provider  | Randomly selects on animation montage from a list of possible choices.                                                                                                |
| Weapon Animation Provider  | Retrieves an Animation from the source object (usually the weapon) for the ability. <br/> The source object must implement `CombatAnimationContextProviderInterface`. |

### Animation Montage Provider Interface

This interface can be added to any **Gameplay Ability** using an Animation Provider. When added, it can provide default
values directly from the Gameplay Ability, that will override any value defined by the provider.

This interface can be added to Owners or Weapons, when used in conjunction with the Weapon Animation Provider. This will
allow the same ability to be reused across multiple weapons and have specific animations provided by the weapons.
