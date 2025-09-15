# Play Animation
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li>Plays the interaction animation and <b>synchronizes progress/outcome</b> with the requesting <b>State Tree</b>.</li>
        <li>Grant to the <b>Interaction Source</b> by default; activates when the paired State Tree task emits its <b>animation event</b>.</li>
        <li>Consumes an interaction event carrying a <code>UNinjaInteractionAnimationPayload</code> (or subtype), extracts details, and plays the montage.</li>
        <li>Can apply an <b>Interaction Effect</b> to the owner during execution (e.g., gameplay tags, cues).</li>
        <li>Extension points: <b>HandleMontageStarted</b>, <b>HandleMontageFinished</b>, <b>HandleMontageInterrupted</b>.</li>
    </ul>
</tldr>

The **Play Animation** ability is the runtime bridge between the interaction's **State Tree** and the character's
animation system. 

It is typically granted to the **Interaction Source** by default so that, when the accompanying State Tree task 
fires its **animation event**, this ability activates, reads the **UNinjaInteractionAnimationPayload** (or a subtype), 
and plays the requested animation. 

While running, it can optionally apply an **Interaction Effect** to the owner (e.g., tags/cues).

## Functions

You can extend these functions (Blueprint or C++) to hook into the animation lifecycle:

| Function                   | Description                                          |
|----------------------------|------------------------------------------------------|
| `HandleMontageStarted`     | Called when the montage begins playing.              |
| `HandleMontageFinished`    | Called when the montage completes normally.          |
| `HandleMontageInterrupted` | Called when the montage is interrupted or cancelled. |

> **Keep Default Behavior**
> 
> When extending these functions, make sure to call `parent`/`super` to preserve their original behaviors.

## Animation Payload
This ability expects an interaction event whose payload is a **UNinjaInteractionAnimationPayload** (or a custom subtype).
The payload encapsulates the animation selection and any execution hints needed by this ability.

For more advanced selection logic, such as choosing from a **Chooser Table**, switching by context, or adjusting play
rates, create a **subtype** and implement **SelectMontageToPlay** (Blueprint or C++). 
