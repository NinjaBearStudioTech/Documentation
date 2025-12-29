# Awareness Targets
<primary-label ref="bot"/>
<secondary-label ref="advanced"/>

The **Awareness Target Component** (`UNinjaBotAwarenessTargetComponent`) can be added to actors that need to be **informed 
about AI awareness directed toward them**. This is most commonly used on player-controlled pawns, but it can be applied 
to any actor that should react to being perceived.

The component aggregates awareness data coming from multiple AI agents and **exposes a unified view** of how aware those 
agents are of the owning actor.

## Purpose and Usage

This component is useful when you want to **react to awareness changes** from the target's perspective, rather than from 
the AI's decision logic. Typical use cases include:

- Reacting when an AI **becomes aware** of the player for the first time
- Responding when **awareness is lost**
- **Driving feedback** such as: sound cues, camera effects, post-processing effects, gameplay cues or UI indicators

> The component does not define how these reactions are implemented. It only provides awareness aggregation and notification.
{style="note"}

## Notifications

Awareness changes are **broadcast whenever the aggregated awareness state changes**. These notifications are available 
through both **native** and **Blueprint-friendly** APIs.

These callbacks provide a **central hook for reacting to awareness changes** without coupling logic to AI controllers or 
perception components.

| Integration                           | Description                                                         |
|---------------------------------------|---------------------------------------------------------------------|
| `HandleAggregatedAwarenessChanged`    | Native event intended to be overridden in subclasses or Blueprints. |
| `OnAggregatedAwarenessChanged`        | Dynamic multicast delegate for Blueprint binding.                   |
| `Native_OnAggregatedAwarenessChanged` | Native delegate variant with lambda support                         |

