# Hit Reaction Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Activated on each successful hit, even if damage was <b>zero</b>.</li>        
        <li>Supports a default animation and other animations specific to certain <b>damage types</b>.</li>
        <li>Supports <b>directional hit reactions</b>, with a flexible calculation system.</li>
    </ul>
</tldr>

The **Hit Reaction Ability** supports directional hit reactions and maps certain incoming damage types to specific 
animations. This ability is typically activated via **Gameplay Events**, so it should always be added to the character 
by default.

<img src="cbt_damage_hit_reaction.png" alt="Hit Reaction Ability" thumbnail="true" border-effect="line"/>

## Ability Trigger

By default, the Hit Reaction is activated by the Combat Manager, from the perspective of a _Damage Manager._ 

Incoming hits will be handled and result in the activation of the Hit Reaction, unless it's an effect that overrides it, 
such as **Fatal Damage**, which would trigger the [**Death Ability**](cbt_ability_death.md) instead.

Since the activation is made via a **Gameplay Effect**, you can also trigger it from other systems if necessary.

## Directional Hit Reactions

The **Hit Reaction Ability** uses the **Directional Hits** Animation Provider, which can select a specific Animation 
Montage or Montage Section based on certain angle ranges:

<img src="cbt_damage_hit_directions.png" alt="Hit Reaction Angles" thumbnail="true" border-effect="line"/>

In this example, the system uses the appropriate **Montage Sections** from the Animation Montage to play reactions based 
on the hit direction.

<img src="cbt_damage_directional_animation.png" alt="Hit Reaction Animation" thumbnail="true" border-effect="line"/>

> When using montage sections, make sure to break their links in the Montage Section panel. Otherwise, all sections will 
> play in sequence!
{style="note"}

## Hit Angle Calculation

The **Hit Reaction Animation Provider** calculates the hit angle using two sources: the **Hit Result Location** and the 
**Attacker Location**. You can customize their influence using the **Hit Location Weight** and **Attacker Location Weight** 
properties.

This flexibility allows you to **fully consider**, **fully ignore**, or create a **blended angle** based on both sources. 
The following image illustrates this concept:

<img src="cbt_damage_hit_angle.png" alt="Hit Reaction Calculation" thumbnail="true"/>

## Contextual Hit Reactions

The Animation Provider also supports different **Hit Reaction Contexts**. These are mappings between Gameplay Tags in
the incoming damage and specific Animation Montages.

<img src="cbt_damage_hit_directions_context.png" alt="Hit Reaction Animation" thumbnail="true" border-effect="line"/>

In the example above, two contextual animations were set, one for **knockback** attacks and another one for **stagger**
damage. The animations set to these contexts will also respect the main configuration for directional attacks.

> If no context matches the incoming damage, then the **default** Animation Montage set in the Animation Provider is used.
{style="tip"}

The Hit Reaction will determine the context by filtering Gameplay Tags present in the damage **instigator** and **target**,
considering the Gameplay Tags set in the equivalent properties, **Instigator Tags Filter** and **Target Tags Filter**.
