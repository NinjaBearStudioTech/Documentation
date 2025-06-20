# Opportunity System
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>
<secondary-label ref="experimental"/>

<tldr>
    <ul>
        <li>Orchestrates Animation Montages and Gameplay Effects played on the <b>Attacker</b> and <b>Victim</b>.</li>
        <li>Requires the <b>Contextual Anim Scene Actor Component</b> on both <b>participants</b> and the <b>Motion Warping Component</b> on the <b>attacker</b>.</li>
        <li>Uses the <b>Contextual Animation</b> plugin to prepare the scene between <b>attacker</b> and <b>victim</b>.</li>
        <li>The attack and reaction are configured using a <b>Contextual Anim Scene Asset</b>.</li>
    </ul>
</tldr>

The **Opportunity System** is used to implement abilities that can only execute under **certain conditions** and will
**pair animations** between the **attacker** and **victim**.

## Opportunity Attack Ability

An Opportunity Attack starts with the **Opportunity Attack Ability**.

<img src="cbt_execute_ability.png" alt="Opportunity Attack Ability" border-effect="line" thumbnail="true"/>

Within the **Opportunity Attack** category, you can set many relevant aspects of the attack, here's a breakdown of these
properties.

| Property              | Description                                                                                    |
|-----------------------|------------------------------------------------------------------------------------------------|
| Targeting Preset      | Targeting Preset data used to collect the appropriate target.                                  |
| Contextual Animation  | The Contextual Animation Asset pairing both attacker and victim animations.                    |
| Camera Animation      | The optional Camera Animation played while the Opportunity Attack executes.                    |
| Camera Anchor Class   | An Actor with a Camera, used as focus point for the Camera Animation.                          |
| Attacker State Class  | Gameplay Effect applied to the attacker, while executing the attack.                           |
| Victim State Class    | Gameplay Effect applied to the victim, while receiving the attack. This is **not** the damage. |
| Fallback Ability Tags | An optional Gameplay Ability to execute, if the Opportunity Attack cannot be triggered.        |

### Finding the Victim

Selecting the victim also uses the **Gameplay Targeting System**. You can provide a **Targeting Preset** that can select
the appropriate target for the Opportunity Attack.

This is very flexible, since you can use any of the Tasks currently available, but also create your own for some complex
situations, such as checking certain collisions with a trigger box, for example.

<img src="cbt_execute_targeting.png" alt="Targeting for Opportunity Attacks" border-effect="line" thumbnail="true"/>

In the example above, you can see the following selection logic:

1. The current target, from the Target Lock, is selected. This could be any other selection mode that you prefer.
2. It checks if the health is below a certain threshold.
3. It checks if the angle between targets is mostly a "facing angle". You could also use back angles for things like _backstabs_.

## Contextual Animations

Contextual Animations are a new feature in Unreal Engine, that can be used to pair animations between multiple roles.
To get started with it, please check this [great article][1] by Alvaro Jover-Alvarez (Vorixo).

<img src="cbt_execute_contextual_animation.png" alt="Contextual Animation for Opportunity Attacks" border-effect="line" thumbnail="true"/>

In summary, you need to execute the following steps:

1. Add `ContextualAnimSceneActorComponent` to characters that will **initiate** the attack (or just add it to your base character). 
2. Create a role asset based on `ContextualAnimRolesAsset`, and define your Victim and Attacker roles. Adjust each participant's rotation as necessary. In the example above, both actors are rotated at `-90` on the `yaw` axis.
3. Create a new Contextual Animation Scene, from the **Animation** menu, set the appropriate Role Asset to it.
4. Set your primary actor as the **Victim** and configure the example actors for all participants.
5. Add a new **AnimSet** and set the correct Animation Montages. Make sure that both Animation Montages have **Root Motion** and that it is **enabled**.
6. Click on the Attacker Animation Montage in the timeline and adjust its position.
7. Add a **Warp Point Definition**, set it as **Primary Actor** and provide a name, such as `ExecutionWarp`.
8. Click **Update Warp Points**.

At any moment, you can hit **Play** and check how the animations will play together. Whenever you make changes, you might
need to click **Reset Scene**.

You can also configure multiple animations on the same scene and define a **Selection Logic** for each one of them.

### Motion Warping

The Contextual Animation uses **Motion Warping** to place the targets correctly. That means that you need to:

1. Add the Motion Warping Component to all characters, or even better, add the **Combat Warping Manager Component**.
2. Add the Motion Warping **Animation Notify State** to your Animation Montages, and make sure to set the correct **Warp Name** for them.

### Handling Different Targets

If you want to reuse the same Contextual Animation between different targets, with the same skeleton but different 
proportions, then you might need to use **Sockets** as a Warp Point Definition, instead of the Primary Actor.

## Camera Animations

You can optionally add Camera Animations to an Opportunity Attack to make it more _cinematic_! For that, you need to 
create your Camera Animation in the **Sequencer** and set it to the ability.

<img src="cbt_execute_camera_sequencer.png" alt="Camera Sequencer for Opportunity Attacks" border-effect="line" thumbnail="true"/>

For this feature, you have a few additional **pre-requisites**:

1. Set `NinjaCombatPlayerCameraManager` as the Player Controller's Camera Manager, or any other Camera Manager that implements `CombatCameraManagerInterface`.
2. Set a **Camera Anchor Actor** to your Ability, this actor must have a Camera Component (or a Cine Camera Component). You can use `NinjaCombatCameraAnchorActor` or subclasses of it. 

## Applying Damage

As usual, damage is applied using **Gameplay Effects**. You have two Animation Notifies that can be used with this:

- **Melee Scan**: The same Animation Notify State used by Melee Attacks can be used here as well. 
- **Opportunity Damage**: This Animation Notify can be used to apply immediate damage, regardless of weapon collisions. 

[1]: https://vorixo.github.io/devtricks/contextual-anim/

<seealso style="cards">
    <category ref="related">
        <a href="cbt_melee_combat.md" summary="Details about the Melee Combat design.">Melee Combat</a>
        <a href="cbt_poise_and_stagger.md" summary="Details about the Poise and Stagger design.">Poise and Stagger</a>
    </category>
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine" summary="Official documentation for the Gameplay Ability System.">Gameplay Ability System</a>
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-targeting-system-in-unreal-engine" summary="Official documentation for the Gameplay Targeting System.">Gameplay Targeting System</a>
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/motion-warping-in-unreal-engine" summary="Official documentation for Motion Warping.">Motion Warping</a>
        <a href="https://vorixo.github.io/devtricks/contextual-anim/" summary="Excellent introduction to Contextual Animations, by Vorixo.">Contextual Animation</a>
    </category>
</seealso>