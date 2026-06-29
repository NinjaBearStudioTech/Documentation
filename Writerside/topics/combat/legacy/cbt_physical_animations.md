# Physical Animations

<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

Ninja Combat can use **physical animations** to create hit reactions when a combatant receives melee or ranged damage.

Physical animations blend regular animation with physics simulation, allowing a character to react to impact direction, hit strength, and affected bones without fully entering ragdoll. In Ninja Combat, this flow is handled by the **Physical Animation Component**, the **Physical Animation Interface**, and a **Damage Handler** that triggers reactions when damage is applied.

This feature is optional, but useful when characters should react physically to hits while still recovering back into animation.

## Physical Animation Interface

All Combat System interactions with physical animations go through `CombatPhysicalAnimationInterface`.

This interface acts as a bridge between damage handling and the component that performs the physical reaction. Any component implementing this interface can provide physical animation behavior, which allows projects to replace or extend the default implementation.

## Physical Animation Component

Ninja Combat provides `NinjaCombatPhysicalAnimationComponent`, which extends Unreal Engine's `UPhysicalAnimationComponent` and implements `CombatPhysicalAnimationInterface`.

The default component supports common hit reaction behavior, including reaction timing, blend weight, bone targeting, impact strength, follow-up hits, and debug output.

<procedure title="Add the Physical Animation Component" collapsible="true" default-state="collapsed">
    <step>In your Character Blueprint or base class, add <code>NinjaCombatPhysicalAnimationComponent</code>.</step>
    <step>Implement <code>GetPhysicalAnimationComponent</code> from the <code>CombatSystemInterface</code>, returning the <b>Physical Animation Component</b>.</step>
</procedure>

The default component provides the following features:

| Feature                    | Description                                                                                                                      |
| -------------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| Designer-friendly settings | Reaction time, recovery, blend weight, and impact thresholds are exposed in the component defaults.                              |
| Flexible bone targeting    | Reactions can use the bone hit by the attack, a default bone, or a replacement from a bone mapping.                              |
| Dynamic impulses           | Impact direction and strength can be calculated from melee hits or projectiles.                                                  |
| Follow-up handling         | Follow-up hits can extend the reaction up to `MaxReactionTime`, supporting fast combos without locking the character in physics. |
| Debug support              | Debug output can display information about each physical animation context.                                                      |

## Physical Animation Profiles

Physical reactions use a **Physical Animation Profile** configured in the owner's **Physics Asset**.

When the component initializes, it retrieves the configured profile from the combat mesh and uses it when applying hit reactions.

> **Default Physical Animation Profile**
>
> By default, the Physical Animation Component looks for a profile named `ImpactReaction`.
>
> You can override this name in the component defaults.
> {style="note"}

<procedure title="Create a Physical Animation Profile" collapsible="true" default-state="collapsed">
    <step>Open the <b>Physics Asset</b> assigned to the Skeletal Mesh that will play the physical animation.</step>
    <step>In the <b>Profiles</b> tab, under <b>Physical Animation Profiles</b>, create a new profile named <b>ImpactReaction</b>, or use the name configured in the component.</step>
    <step>Select the physics bodies that should participate in the impact reaction and add them to the current Physical Animation Profile.</step>
    <step>Adjust the relevant physics bodies and constraints until the reaction feels appropriate for your character.</step>
</procedure>

Physical animation quality depends heavily on the Physics Asset. Bodies, constraints, physical animation settings, and physics type all affect how the character transitions from animation into simulation and back again.

The **Physics Type** setting is especially important. It determines whether a body is **kinematic**, following animation, or **simulated**, participating in physics simulation.

> **Base Simulation Bones**
>
> For humanoid characters, `Spine_02`, `Spine_03`, or `Pelvis` are often good base simulation bones when you want broad upper-body or full-body reactions instead of precise per-bone simulation.
>
> These bones usually produce natural results when blending animation and physics.
> {style="tip"}

## Triggering Hit Reactions

Physical animation reactions are usually triggered from a **Damage Handler** configured in the character's **Damage Data Asset**.

The Physical Animation Damage Handler can react to melee or ranged damage and forward the impact context to the Physical Animation Component.

By default, the handler ignores **recurring damage**, such as damage effects that tick at an interval. If recurring damage should trigger physical reactions, enable that behavior in the handler settings.

For more information about Damage Data and Damage Handlers, see [**Damage and Mitigation**](cbt_concepts_damage_and_mitigation.md).

## Physical Animation Settings

The default component uses `FCombatPhysicalAnimationSettings` to configure how reactions behave.

You can find these settings in the Physical Animation Component's **Defaults Panel**.

| Setting Area        | Description                                                                                                                 |
| ------------------- | --------------------------------------------------------------------------------------------------------------------------- |
| Default Bone        | Forces all impacts to react from a single bone, such as `Spine_02`. Useful when precise hit bones are not needed.           |
| Bone Mapping        | Redirects specific hit bones to other bones with valid physics bodies. Useful when simplifying Physics Asset setups.        |
| Reaction Times      | Controls how long the reaction lasts, using `DefaultReactionTime`, `FollowUpReactionTime`, and `MaxReactionTime`.           |
| In and Out Blending | Uses `MaxBlendWeight` to control peak simulation strength and `KinematicInterpSpeed` to control recovery back to animation. |
| Strength Threshold  | Ignores light hits below `MinImpactStrengthThreshold` and scales stronger impacts up to `MaxImpactStrength`.                |

> **Handling Multiple Contexts**
>
> The default Physical Animation Component uses one profile that can be scaled by incoming impact strength.
>
> If your project needs multiple profiles, such as different reactions based on Gameplay Tags in the Effect Context, create a custom Physical Animation Component and override the getter and setter methods for the animation settings.
> {style="note"}

## Debug Mode

To display debug information for each physical animation context, enable **Debug Mode** in the Physical Animation Component's **Details Panel**.

Debug Mode can help validate the selected bone, impact direction, impact strength, reaction time, and recovery behavior while tuning hit reactions.

<seealso style="cards">
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/using-profiles-for-bodies-and-constraints-in-unreal-engine" summary="Official documentation for profiles, bodies and constraints.">Using Profiles for Bodies and Constraints</a>
        <a href="https://www.youtube.com/watch?v=46NfgXlnCzM" summary="PrismaticaDev's YouTube video about Physical Animations.">Physical Animation Starter Guide</a>
        <a href="https://www.youtube.com/watch?v=bnOd9KM0FeQ" summary="Unreal DevOp's YouTube video about Physical Animations.">Physical Animation Hit Reactions</a>
    </category>
</seealso>
