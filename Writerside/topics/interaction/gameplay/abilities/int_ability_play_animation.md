# Play Animation
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li>Plays the interaction animation and <b>synchronizes progress/outcome</b> with the requesting <b>State Tree</b>.</li>
        <li>Grant to the <b>Interaction Source</b> by default; activates when the paired State Tree task emits its <b>animation event</b>.</li>
        <li>Can apply an <b>Interaction Effect</b> to the owner during execution (e.g., gameplay tags, cues).</li>
        <li>Extension points: <b>HandleMontageStarted</b>, <b>HandleMontageFinished</b>, <b>HandleMontageInterrupted</b>.</li>
    </ul>
</tldr>

The **Play Animation** ability is the runtime bridge between the interaction's **State Tree** and the character's
animation system. 

It is typically granted to the **Interaction Source** by default so that, when the accompanying State Tree task 
fires its **animation event**, this ability activates, collects data from the **current interaction** and determines
the best Animation Montage to play.

While running, it will apply an **Interaction Effect** to the owner. You can use this to achieve behaviors such as:

- Apply **Gameplay Tags** that may affect the character in other ways, for example, affecting [**equipment visibility**](inv_tag_visibility.md).
- Apply **Gameplay Tags** that will [**block player input**](ipt_character_handlers.md) to avoid movement during the interaction.
- Add **Gameplay Cues** for sounds, effects or other cosmetic effects on the character.
- Grant **Gameplay Abilities** to trigger additional behaviors.

> **Breakdown and Advanced Features**
> 
> For more details about the Animation Layer, including this Ability, please check the [**Interaction Animation**](int_adv_interaction_animations.md)
> topic, which includes setting up the **Chooser Table**, **overriding default Animation Montages** and so on.

## Properties

These properties will determine how this Gameplay Ability operates.

| Property                                   | Description                                                               |
|--------------------------------------------|---------------------------------------------------------------------------|
| `AnimationChooserTable`                    | Chooser table used to resolve the animation.                              |
| `InterruptAnimationOnInteractionCancelled` | If set to true, interrupts the animation if the interaction is cancelled. |
| `bInterruptAnimationOnInteractionFinished` | If set to true, interrupts the animation if the interaction is cancelled. |
| `InteractionEffectClass`                   | Gameplay effect applied while the ability is active.                      |
| `InteractionEffectLevel`                   | Level in which the Gameplay Effect will be applied.                       |

## Functions

You can extend these functions (Blueprint or C++) to hook into the animation lifecycle:

| Function                   | Description                                                                                                           |
|----------------------------|-----------------------------------------------------------------------------------------------------------------------|
| `GetPlayRate`              | Dynamically adjusts the play rate for an animation/summary.                                                           |
| `GetSectionName`           | Dynamically sets the section name for an animation/summary.                                                           |
| `HandleMontageStarted`     | Called when the montage begins playing. Make sure to call `parent`/`super` when extending this function.              |
| `HandleMontageFinished`    | Called when the montage completes normally. Make sure to call `parent`/`super` when extending this function.          |
| `HandleMontageInterrupted` | Called when the montage is interrupted or cancelled. Make sure to call `parent`/`super` when extending this function. |
