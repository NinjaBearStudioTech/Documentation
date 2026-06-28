# Paired Animations
<primary-label ref="combat"/>
<secondary-label ref="experimental"/>
<secondary-label ref="advanced"/>

**Paired Animations** are synchronized combat actions where two or more actors participate in the same animation scene.
They are commonly used for **Opportunity Attacks**, such as *executing a staggered enemy*, *ambushing a foe from stealth*, 
or *finishing off a weakened target*.

These actions are designed to deliver a stronger cinematic impact than a regular attack. They can combine synchronized 
animations, contextual target selection, Motion Warping, fatal damage handling, and optional camera transitions.

Paired Animations use Unreal Engine's **Contextual Animation** plugin, which allows a scene to define multiple **roles** 
and play synchronized animations for each participant.

> **Experimental Feature**
>
> The Contextual Animation system in Unreal Engine is currently marked as **experimental**. Because of this, Paired 
> Animations and Opportunity Attacks in Ninja Combat should also be treated as experimental.
> {style=warning}

## Roles

A contextual animation scene is built around **roles**. Each role identifies one participant in the scene and determines 
which animation that participant will play.

From a combat perspective, most paired animations involve one **attacker** and at least one **target**. The scene uses 
these roles to select the correct animations and align the participants through **Motion Warping**.

In Ninja Combat, the default role mapping is:

1. The **primary role** represents the **target** or **victim**.
2. The **secondary role** represents the **attacker**, usually the Ability Avatar.

The target is collected by the **Target Preset** assigned to the ability. The attacker is provided by the ability itself.

Roles are defined using a **Contextual Animation Roles Data Asset** (`ContextualAnimRolesAsset`).

## Contextual Animation Asset

The **Contextual Animation Asset** defines the animation scene. It determines which animations are available for each role 
and how participants should be positioned relative to each other.

A single asset can also contain multiple animation options. Conditions can be used to choose between them, which allows 
related paired animations to be grouped together instead of requiring a separate ability for every variation.

For example, a single Opportunity Attack could use different paired animations depending on distance, angle, weapon type, 
or target state.

### Animation Montages

Animation Montages used by Paired Animations are usually prepared like other montages used by the Combat System.

The **attacker montage** may include combat notifies such as:

1. **Melee Scan Notify States**, for attacks that should apply damage through melee traces.
2. **Fatal Damage Notify**, for attacks that should finish the target at a specific moment.
3. **Motion Warping Notify States**, when the attacker must adjust position to reach the target.

The **target montage** usually does not require special setup unless it represents a fatal reaction. In that case, 
configure it like a montage used by the [**Death Ability**](cbt_concept_vulnerable_states.md#death-ability), including 
the **Death Animation Notify** and, when appropriate, the **Ragdoll Notify**.

> **Roles and Motion Warping**
>
> You can decide whether the *attacker moves to the victim* or the *victim moves to the attacker*.
> 
> Regardless of the setup, the actor that moves into position should use the **secondary role**, have a configured **Motion 
> Warping** component, and include the necessary Motion Warping notify in its animation.
> {style=note}

## Opportunity Attack Ability

The **Opportunity Attack Ability** is the main ability type used to play paired combat animations.

It collects the actors that will participate in the scene, provides them to the Contextual Animation system, and starts 
the synchronized animation. It can also coordinate supporting features such as target selection, camera animations, and 
fatal damage timing.

### Target Selection

By default, Opportunity Attacks use the **Gameplay Targeting System** to find an eligible target.

This allows target selection to be based on conditions such as distance, facing angle, gameplay tags, current state, or 
any other criteria supported by your targeting setup.

> **Ninja Interaction Integration**
>
> Opportunity Targets can also be acquired through the [**Interaction System**](int_overview.md). This can be done with 
> Interaction Selection Tasks, or by configuring an AoE task to detect Interaction Targets.

### Additional Roles

Some scenes may require more than the default attacker and target. For example, a paired animation could involve a third 
actor, a hostage, or an environmental prop.

Additional participants can be provided by overriding `CollectAdditionalSceneActors` in the Opportunity Attack Ability. 
This function supplies extra role names and actors to the contextual animation scene.

### Fallback Abilities

The ability can also set fallback abilities that can be activated if no targets are available for the Opportunity Attack.
This can be useful if you are sharing buttons, between multiple abilities, such as "primary attack" and "execution".

## Camera Animations
<secondary-label ref="optional"/>

Opportunity Attacks can optionally play a **Camera Animation** to add cinematic flair to the paired animation.

Camera animations are usually created with **Sequencer** and played through the **Camera Manager** associated with the 
Ability Avatar's **Player Controller**.

You can use the camera manager provided by Ninja Combat, `NinjaCombatPlayerCameraManager`, or provide your own camera 
manager that implements `CombatCameraManagerInterface`.

### Camera Anchor

The **Camera Anchor** provides the camera used by the animation.

You can extend this actor when you need different camera behavior, such as using a **Cine Camera**, fully switching to 
a setup based on **Gameplay Cameras**, or applying custom positioning and target tracking rules.

For transition settings, you usually do not need to extend the Camera Anchor. The Opportunity Attack Ability provides 
the `BuildCameraAnimationParameters` extension point, which can be used to configure camera blending and playback parameters.

<seealso style="cards">
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/unreal-engine/gameplay-targeting-system-reference-in-unreal-engine" summary="A reference for the Gameplay Targeting System plugin framework in Unreal Engine.">Gameplay Targeting System Reference</a>
        <a href="https://vorixo.github.io/devtricks/contextual-anim/" summary="An overview of using the Contextual Animation plugin in multiplayer games.">Contextual Animation Overview</a>
    </category>
</seealso>
