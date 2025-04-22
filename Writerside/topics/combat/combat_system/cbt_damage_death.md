# Handling Death
<primary-label ref="combat"/>

The **death flow** begins when **fatal damage** is received and no defense mechanisms (such as Last Stand) are available to prevent it.  
Once initiated, it triggers the **Death Ability**, which manages the character's final actions and cleanup.

When the **Death Ability** ends, the character is destroyed and the death flow is completed.  
Alternatively, a **Gameplay Event** can be sent manually, typically from a [Death Animation Notify](cbt_character_animation.md#animation-notifies), 
to finalize the flow earlier.

As a fallback, you can set a **maximum duration** for the death flow in the [Damage Data Asset](cbt_damage_and_defense.md#damage-data), 
which forces cleanup even if the animation hasn’t completed.

The **Damage Manager Component** exposes the following delegates:

- `OwnerDiedDelegate`: Triggered when the character enters the death flow.
- `OwnerFinishedDyingDelegate`: Triggered when the death flow completes.

## Death Ability
The **Death Ability** should be granted **by default** to all combatants.  
It interrupts any active abilities and handles the final phase of death, including animations and destruction logic.

> By default, the Death Animation uses the **Standard Animation Provider**.  
> If you want to support **Directional Hits** or **Damage Contexts**, switch to the **Directional Hits** provider.  
{style="tip"}

## Animation Setup
You can configure the death animation to either **end naturally** or **loop** in a specific animation state.  
Looping is useful for holding ragdoll poses or “collapsed” states before cleanup.

<img src="cbt_death_animation.png" alt="Death Animation" thumbnail="true" border-effect="line"/>

In this example:

- The Animation Montage supports **directional deaths**, with multiple montage sections.
- Each direction section transitions into a **loop** section when the character has stopped moving.
- A **Ragdoll Notify** is placed at the transition point to enable full physics simulation.
- A **Death Notify** is placed just before the loop to trigger the final death step.

## Interrupting Abilities
When a death occurs, other active abilities may need to be cancelled.  
To do that, configure the **Cancel Abilities With Tag** container in the Death Ability to include the relevant tags.

> **Opportunity Attacks**
>
> If you're using the [](cbt_opportunity_attacks.md) for executions or similar mechanics,  
> prevent the Death Ability from triggering while the `Combat.State.Opportunity.Victim` tag is active.  
{style="tip"}
