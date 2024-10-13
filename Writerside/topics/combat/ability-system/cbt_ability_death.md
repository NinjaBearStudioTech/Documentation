# Death Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Executes logic and animations to represent the owner's <b>death</b>.</li>        
        <li>Automatically triggered when <b>fatal damage</b> is received.</li>
        <li>Should be granted by default to the character.</li>
    </ul>
</tldr>

The **Death Ability** concepts are similar to the ones in the [](cbt_ability_hit_reaction.md): It should be granted by
**default**, supports **directional hits** and **damage contexts**.

> By default, the Death Animation uses the standard **Animation Provider**. If you want to use **directional hits** and 
> **damage contexts**, make sure to switch to the **Directional Hits** provider.
{style="note"}

## Death Flow

The Death Ability is triggered by the "death flow", when **fatal damage** is received, without any defense mechanisms
available to revert that. That will trigger the **Death Ability** 

Once the ability ends, it will finish the death flow in the character. Alternatively, the [Death Animation Notify](cbt_character_animation.md#animation-notifies) 
can also be used to send a**Gameplay Event** to the Death Ability, which initiates the final stage of the death flow.

Finally, as a fallback, you can set a maximum duration for the Death Flow in the [Damage Data Asset](cbt_damage_and_defense.md#damage-data),
so it will force the last step in the death flow, regardless of where the Death Animation is.

## Animation Setup

Depending on your setup, Animation Montages used for Death Animations can be simple and allow the Death Ability to end
with the animation. Alternatively, they can be **looping**, making sure the character will remain at a certain Animation 
State, like so:

<img src="cbt_death_animation.png" alt="Death Animation" thumbnail="true" border-effect="line"/>

In the example above, you will find the following:

- This is Animation Montage handle directional animations, containing multiple montage sections.
- Each main direction section leads to a loop section, when the character has fully stopped moving.
- The **Ragdoll** notify is used when appropriate.
- The **Death** notify is used just before the loop.

## Interrupting Abilities

A death event most likely has to interrupt other ongoing abilities. A good way to do that is adding a list of abilities
that should be cancelled to the list of tags in the **Cancel Abilities With Tag** container.

However, if you are using the [](cbt_opportunity_system.md) for potentially fatal abilities, such as _executions_, then  
you might also want to consider blocking the activation of the **Death Ability** if the **Victim** tag is present.

> The Victim Gameplay Tag applied by the **Opportunity System** is `Combat.State.Opportunity.Victim`.
{style="tip"}
