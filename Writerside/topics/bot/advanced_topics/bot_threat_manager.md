# Threat Manager
<primary-label ref="bot"/>
<secondary-label ref="advanced"/>
<secondary-label ref="experimental"/>

The **Threat Manager** is an opt-in system that enables **threat assessment** and **threat-based** target selection. This 
evaluation model is commonly used in RPG-style gameplay, where an agent may choose between multiple targets based on factors 
such as **damage dealt** or **deliberate threat generation**.

When enabled, the Threat Manager evaluates threat independently of perception strength and **broadcasts the highest-threat 
target back into the perception system**, allowing standard awareness and decision logic to react accordingly.

## Threat vs Awareness

Threat and awareness are **evaluated independently** and serve different purposes. **Awareness** determines whether a 
target is known and can be acted upon. **Threat** determines which known target should be prioritized.

Keeping these systems separate allows detection and prioritization to be tuned independently while still feeding into 
the same **perception and decision logic**.

## Threat Manager Component

The **Threat Manager Component** should be added to the **AI Controller**. Once enabled, it automatically integrates with 
the Perception Component and **listens for damage-related stimuli**. Whenever a Damage Sense stimulus is received, the component:

1. Tracks the source actor
2. Accumulates total damage applied per actor
3. Maintains an internal table of threat values

> Automatic binding to the Damage Sense can be enabled or disabled via the `bBindToDamageSense` property, in the Threat
> Manager Component's default settings.
{style="note"}

The accumulated threat table is normalized, and the actor with the highest resulting threat score is selected as the current 
threat target. When a new threat target is determined, **a Threat Sense event is emitted**.

In addition to damage-driven threat, gameplay systems may **deliberately inject threat** by calling `RegisterThreatSource`, 
providing a source actor and an explicit threat score. This allows non-damaging actors to contribute to threat generation,
which is often the case for certain RPG roles like _healers_.

## Threat Sense

The Threat Sense is a **custom sense introduced by this module**. It is triggered whenever the Threat Manager selects a 
new highest-threat target. When a threat event is emitted, the sense provides:

1. The highest-threat target actor
2. The normalized threat score

From this point onward, the agent processes the Threat Sense stimulus **in the same way it would process any other perception 
stimulus**. This allows threat relevance to be authored using the **same tools** as sight, hearing, or other senses, including 
weighting, normalization, and awareness contribution. As a result, **threat can be tuned per perception archetype** and 
blended naturally with other sensory inputs.

> The Threat Sense must be registered in the bot's Sense Configuration. It is handled as any other sense by the Perception System.
{style="note"}

You can send one-off Threat events, using the static function provided by the Threat Sense class. This function can be
used natively or in Blueprints, and it's useful to trigger external, specific events that are supposed to **force threat**
like a "_taunt_".

## Threat Modifier Interface

Actors that participate in threat evaluation may implement `IBotThreatModifierInterface` to influence how much threat they 
generate. This interface allows actors to:

- Increase their threat contribution
- Reduce or dampen their perceived threat

This is particularly useful for role-based gameplay, such as **implementing class archetypes** like _tanks_ or _damage 
dealers_, where threat generation is **intentionally biased**. 