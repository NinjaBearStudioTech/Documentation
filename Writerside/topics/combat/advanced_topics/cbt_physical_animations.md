# Physical Animations
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

Combat systems commonly use **physical animations** for **hit reactions**. Ninja Combat provides this functionality via
its **Physical Animation Component** and **Damage Handler**.

## Physical Animation Interface
All interactions with the Physical Animation Component happen through the `CombatPhysicalAnimationInterface`, which acts 
as a **bridge** between the Combat System and any implementation of physical reactions.

## Physical Animation Component
The Combat System provides its own Physical Animation Component, which extends `UPhysicalAnimationComponent`, Unreal Engine's
default system for blending physics simulation and animation. Implements the `CombatPhysicalAnimationInterface`.

<procedure title="Adding the Physical Animation Component" collapsible="true" default-state="expanded">
    <step>In your Character Blueprint or Base class, add <code>NinjaCombatPhysicalAnimationComponent</code>.</step>
    <step>Implement <code>GetPhysicalAnimationComponent</code> from the <code>CombatSystemInterface</code>, returning the <b>Physical Animation Component</b>.</step>
</procedure>

The default Physical Animation Component provided by Ninja Combat also provides the following features:

- **Designer-Friendly Setup**: Impact reaction **time**, **recovery** and **blend weight** are all exposed in the component's default settings.
- **Flexible Bone Targeting**: Reactions can happen from specific bones hit during an attack or others selected from a replacement mapping.
- **Dynamic Impulses**: Direction calculated from trace, scaled by incoming strength, from **melee weapons** or **projectiles**.
- **Follow-up handling**: Follow-up hits add time up to `MaxReactionTime`, better supporting fast combos and avoiding "physics lock".
- **Debug Support**: On-screen and log info about each hit, toggleable via `bEnableDebugMode`.

## Physical Profiles
When a physical reaction is activated, it will use a specific **Physical Animation Profile** set in the owner's **combat
mesh**, which is retrieved and stored on `BeginPlay`.

> **Default Physical Animation Profile**
> 
> By default, the profile name used by the Physical Animation Component is named `ImpactReaction`. You can override this
> name, per component, in its **default settings panel**.
{style="note"}

<procedure title="Creating a Physical Animation Profile" collapsible="true" default-state="expanded">
    <step>Open the <b>Physics Asset</b> assigned to the <b>Skeletal Mesh</b> that will play the physical animation.</step>
    <step>In the <b>Profiles</b> tab, under <b>Physical Animation Profiles</b>, create a new profile in the <b>Current Profile</b> box. Name it <b>ImpactReaction</b> to match the component setting.</step>
    <step>With the new profile enabled, select all <b>physics bodies</b> relevant to the Impact simulation, and <b>add them to the current physical animation profile</b>.</step>
    <step>Adjust your <b>physics bodies</b> and their <b>constraints</b> so they react correctly for your scenario, this varies case-by-case.</step>
</procedure> 

To work with Physical Animation Profiles, it is important to understand how the **Physics Asset**, its **bodies** and
**constraints** are configured. In particular, settings under **Physical Animation**, that are enabled when a body is
added to the profile.

Another important element is the **Physics Type**, present under the **Physics** category. This allows you to determine
if the body is **kinematic** (follows animation) or **simulated** (executes physics simulation). 

With these settings you can fine-tune your Physical Animations so they can transition nicely from animation to physics
simulation, in any context supported by your game. You can find more information about this in the list of references.

> **Base Simulation Bones**
> 
> Use `Spine_02`, `Spine_03`, or `Pelvis` as your simulation base for humanoids, when you are not looking for precise, 
> per-bone, simulation.
> 
> These bones often produce the most natural results when blending animation and physics.

## Triggering Impact Animations
In Ninja Combat, you can define what happens when a character takes damage, via the [**Damage Data Asset**](cbt_damage_and_defense.md)
asset, and its list of **Damage Handlers**.

The **Physical Animation** handler can be used to trigger the Physical Animation on a character, when any **melee** or
**ranged** damage is applied.

By default, the Damage Handler will not execute from **recurring damage** - which are recurring effects set to a given
interval. If such reactions are desirable, then they be enabled via the handler's exposed properties. 

## Physical Animation Settings
The default **Physical Animation** system uses `FCombatPhysicalAnimationSettings` to store the context for an animation.
The table below shows possible adjustments that can be obtained from this data structure.

| Adjustment         | Details                                                                                                                                                  |
|--------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------|
| Default Bone       | Forces all impacts to react from a single bone (e.g. `Spine_02`). Use when precision is not needed.                                                      |
| Bone Mapping       | Redirects specific bones (e.g. `Pelvis`) to valid ones with physics bodies. Useful for simplifying setups.                                               |
| Reaction Times     | Adjust how long the simulation lasts: use `DefaultReactionTime` for initial hits, `FollowUpReactionTime` for combos, and `MaxReactionTime` as a ceiling. |
| In/Out Blending    | Use `MaxBlendWeight` for full simulation, and `KinematicInterpSpeed` to control how fast the character recovers to animation.                            |
| Strength Threshold | Ignore light hits below `MinImpactStrengthThreshold`. Scale response between min and `MaxImpactStrength`.                                                |

You can find these settings in the Physical Animation Component's **Defaults Panel**.

> Handling Multiple Contexts
>
> The default Physical Animation Component only handles one profile, that can be scaled by the incoming **strength**.
>
> You can support multiple profiles if needed (e.g. based on Gameplay Tags in the incoming Effect Context), by overriding 
> the getter and setter methods for the animation settings in a custom Physical Animation Component.
{style="note"}

## Debug Mode
To enable a visual display of each physical animation context, enable **Debug Mode** in the component's **Details Panel**.

<seealso style="cards">
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/using-profiles-for-bodies-and-constraints-in-unreal-engine" summary="Official documentation for profiles, bodies and constraints.">Using Profiles for Bodies and Constraints</a>
        <a href="https://www.youtube.com/watch?v=46NfgXlnCzM" summary="PrismaticaDev's YouTube video about Physical Animations.">Physical Animation Starter Guide</a>
        <a href="https://www.youtube.com/watch?v=bnOd9KM0FeQ" summary="Unreal DevOp's YouTube video about Physical Animations.">Physical Animation Hit Reactions</a>
    </category>
</seealso>

