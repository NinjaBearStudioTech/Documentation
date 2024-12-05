# Local Gameplay Cues
<primary-label ref="gas"/>

Following [Dan Tranek's documentation about Local Gameplay Cues][1], the original Gameplay Cue system, albeit powerful, 
can be expensive in terms of RPCs. Furthermore, there is a limit of how many cues can be triggered via RPC, per net update.

Ninja GAS provides two ways for you two **add** and **remove** local Gameplay Cues: directly in the **Ability System 
Component** or using the provided **Function Library**.

> **Animation Notifies**
> 
> The Animation Notify and Notify State provided by the Gameplay Ability System already uses local Gameplay Cues, so 
> if you are triggering cues using these Animation features, then you do not need to do anything else.
{style="note"}

> **Ninja Combat**
>
> Gameplay Cues triggered by **[](cbt_overview.md)**, such as melee and projectile impacts, are already **applied locally** 
> by the Combat Framework. No integration or changes are necessary. 

## Ability System Component

Although the Ability System Component has a dedicated method to add and remove local Gameplay Cues, this method is not
exposed to Blueprints. The custom Ability System Component, `NinjaGASAbilitySystemComponent` exposes that, so this feature
can be used on that layer.

## Function Library

To simplify this flow, you can simply use the provided **Function Library** to add or remove local Gameplay Cues from a
given actor. The function signature is very similar.

[1]: https://github.com/tranek/GASDocumentation?tab=readme-ov-file#483-local-gameplay-cues