# Evade Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Plays animations to represent evasive movements, such as <b>dodges</b>, <b>rolls</b> and <b>sidesteps</b>.</li>        
        <li>Supports <b>directional animations</b>, based on movement.</li>
        <li>Should be used with animations that include <b>root motion</b>.</li>
    </ul>
</tldr>

The **Evade Ability** plays an Animation with Root Motion. The ability supports both directional evades and default, 
non-directional ones, usually a sidestep, or evade forward.

The following table contains a breakdown of evade properties.

<img src="cbt_evade_ability.png" alt="Evade Ability" thumbnail="true" border-effect="line"/>

| Property                     | Description                                                                                             |
|------------------------------|---------------------------------------------------------------------------------------------------------|
| Evading Effect Class         | Gameplay Effect class applied while the avatar is performing an evade.                                  |
| Invulnerability Effect Class | Gameplay Effect class applied while the avatar is invulnerable.                                         |
| Offset                       | An offset applied to the direction calculation. May be useful for angled perspectives such as top-down. |
| Animation Provider           | Evades will commonly use the **Directional Evades** provider. More information below.                   |

## Directional Evade Provider

This **Animation Provider** allows you to map certain animations to a direction. Directions are calculated using the 
current **movement direction** and the character's **[forward reference](cbt_forward_reference.md)**.

You can adjust the direction ranges and names so they fit your requirements. You can also remove certain ranges, such as
the diagonal angles and consolidate them into the four main directions - forward, back, left and right.

As usual, you can also set a default animation and a default animation section.

## Animation Setup

You can have multiple Animation Montages to cover all support directions, or have a single Animation Montage with all
necessary Montage Sections.

<img src="cbt_evade_animation.png" alt="Evade Animation" thumbnail="true" border-effect="line"/>

> If you use a single Montage, make sure to **disconnect** all **montage sections**, so they are not played in sequence!
{style=note}
