# Hit Reaction Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Activated on each successful hit, even if damage was <b>zero</b>.</li>        
        <li>Supports a default animation and other animations specific to certain damage types.</li>
        <li>Supports directional hit reactions, that may consider the hit location or attacker as a reference.</li>
    </ul>
</tldr>

The **Hit Reaction Ability** supports directional hit reactions and maps certain incoming damage types to specific 
animations. This ability is typically activated via **Gameplay Events**, so it should always be added to the character 
by default.

<img src="cbt_damage_hit_reaction.png" alt="Hit Reaction Ability" thumbnail="true" border-effect="line"/>

## Directional Hit Reactions

The **Hit Reaction Ability** uses the **Hit Reaction Animation Provider**, which can select a specific Animation Montage 
or Montage Section based on certain angle ranges:

<img src="cbt_damage_hit_directions.png" alt="Hit Reaction Angles" thumbnail="true" border-effect="line"/>

In this example, the system uses the appropriate **Montage Sections** from the Animation Montage to play reactions based 
on the hit direction.

<img src="cbt_damage_directional_animation.png" alt="Hit Reaction Animation" thumbnail="true" border-effect="line"/>

## Hit Angle Calculation

The **Hit Reaction Animation Provider** calculates the hit angle using two sources: the **Hit Result Location** and the 
**Attacker Location**. You can customize their influence using the **Hit Location Weight** and **Attacker Location Weight** 
properties.

This flexibility allows you to **fully consider**, **fully ignore**, or create a **blended angle** based on both sources. 
The following image illustrates this concept:

<img src="cbt_damage_hit_angle.png" alt="Hit Reaction Animation" thumbnail="true"/>
