# Opportunity Attacks
<primary-label ref="combat"/>
<secondary-label ref="experimental"/>

**Opportunity Attacks** are powerful, context-sensitive actions triggered in specific scenarios, such as _executing a 
staggered enemy_, _ambushing a foe from stealth_, or _finishing off a weakened target_.

These attacks often involve **synchronized animations** between participants and are designed to deliver a **cinematic 
impact**, supported by **camera transitions** and **context-aware animation blending**.

> **Contextual Animations are Experimental**
>
> The Contextual Animation System in Unreal Engine is currently marked as **experimental**. Therefore, the Opportunity 
> System in Ninja Combat is also marked as such.
{style=warning}

## Opportunity Targets
By default, Opportunity Attacks will use the **[Gameplay Targeting System][1]** to find an **eligible target**. This 
allows great flexibility when defining targets, based on _distance_, _present gameplay tags_, _facing angle_ and so on.

> **Ninja Interaction Integration**
> 
> Opportunity Targets can be acquired via the **[Interaction System][2]**, either by using its **Selection Tasks**, or 
> just by setting the AoE task to detect **Interaction Targets**.

[1]: cbt_gameplay_targeting_system.md
[2]: int_overview.md