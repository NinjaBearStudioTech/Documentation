# State Trees
<primary-label ref="bot"/>

<tldr>
    <p><b>Summary: State Trees</b></p>
    <br/>
    <ul>
        <li>Ninja Bot supports Unreal Engine State Trees as a primary decision system.</li>
        <li>State Trees combine hierarchical state machines with selector-style evaluation.</li>
        <li>They are well suited for state-driven AI with explicit transitions.</li>
    </ul>
</tldr>

Ninja Bot integrates with Unreal Engine's **State Tree** system as an alternative decision model to [**Behavior Trees**](bot_behavior_trees.md). 
Conceptually, State Trees can be understood as a **hierarchical state machine** enriched with **selector-style evaluation**, 
combining explicit state lifecycles with conditional execution.

As with Behavior Trees, State Trees in Ninja Bot **consume interpreted perception and awareness data** produced by the 
framework. Perception, awareness, and target selection remain external to the tree, allowing State Trees to focus purely 
on state management, transitions, and execution.

## When to Use State Trees

State Trees are particularly effective when AI behavior can be described as a **finite and well-defined set of states**, 
with transitions that are deliberate and meaningful. Common usage scenarios include:

- Agents with a known set of states such as Idle, Patrol, Investigate, Combat and Flee.
- Behavior driven by clear state transitions rather than constant reevaluation
- AI logic that benefits from explicit enter, tick, and exit lifecycles

### Utility-Driven and Emergent Behavior

While often associated with explicit transitions, State Trees also support emergent behavior through **utility-based** evaluation.

By assigning utility scores to states and weighting them using external data, State Trees can **select states dynamically** 
rather than relying solely on predefined transitions. These scores are typically calculated outside the tree, using systems 
that evaluate multiple **considerations** such as awareness level, distance, threat, or environmental context.

When used this way, State Trees can behave in a more **reaction-driven manner**, similar to Behavior Trees, while still 
retaining the structural benefits of state-based execution. This makes State Trees a flexible option that can support both
**deterministic, transition-driven AI**, and **reactive, utility-influenced decision-making**.

## State Tree Evaluators

Ninja Bot provides a small set of **State Tree evaluators** that expose perception and awareness data to State Trees. 
Evaluators are responsible for **gathering and publishing data into the State Tree execution context**, allowing states, 
conditions, and transitions to react to interpreted AI knowledge.

### Update Perception

The **Update Perception** evaluator exposes the **most relevant perception candidate** selected by the Perception Component. 
It **requests an evaluation** and **publishes perception and awareness data** to the State Tree.

| Property                       | Description                                                                             |
|--------------------------------|-----------------------------------------------------------------------------------------|
| **Sensed Actor**               | Reference to the actor currently selected as the most relevant perception candidate.    |
| **Candidate Score**            | Raw perception score assigned to the sensed actor.                                      |
| **Normalized Candidate Score** | Normalized perception score assigned to the sensed actor.                               |
| **Accumulated Awareness**      | Accumulated awareness value for the sensed actor.                                       |
| **Awareness Level**            | Discrete awareness level currently assigned to the sensed actor.                        |
| **First Perceived Location**   | Snapshot of the target’s location when first perceived in the current perception cycle. |
| **Current Target Location**    | Convenience value reflecting the actor’s current world location.                        |
| **Last Known Location**        | Snapshot of the target’s location at the moment awareness drops or the target is lost.  |

### Sensor Data

The **Sensor Data** evaluator optionally exposes sensorial information for a **specific target and sense**. It may be used 
in conjunction with the Update Perception evaluator, allowing State Trees to access detailed stimulus data when more nuanced
decision-making is required.

Multiple Sensor Data evaluators can be used simultaneously to query different senses registered with the agent.

> Since this evaluator reads from an Input Binding, you can also query perceptual data from actors that are not the one
> currently selected by the sense/awareness evaluation.
{style="note"}

| Property              | Description                                                              |
|-----------------------|--------------------------------------------------------------------------|
| **Sensed Actor**      | Input. Actor for which sensor data will be queried.                      |
| **Is Detected**       | Indicates whether the actor is currently detected by the selected sense. |
| **Strength**          | Strength of the detection, if present.                                   |
| **Age**               | Age of the detection in seconds.                                         |
| **Stimulus Location** | World location where the stimulus was received.                          |
| **Receiver Location** | Location of the agent when the stimulus was received.                    |
| **Tag**               | Additional tag assigned to the stimulus, if any.                         |

## State Tree Tasks

Ninja Bot provides the same set of tasks for State Trees as it does for [**Behavior Trees**](bot_behavior_trees.md#behavior-tree-tasks). 
These tasks allow State Trees to actively **emit perception events** or **request bot state changes** without embedding 
engine-specific logic into states.

### Report Noise Event

The **Report Noise Event** task emits a noise stimulus through Unreal Engine's Perception System as an explicit AI signal,
rather than as a byproduct of physical actions.

This task is typically used to **communicate intent or state changes to other agents**, such as deliberately revealing
presence, escalating awareness, or drawing attention.

| Property             | Description                                                                          |
|----------------------|--------------------------------------------------------------------------------------|
| **Event Instigator** | Input. Actor generating the noise. The actor’s location is used as the event source. |
| **Loudness**         | Normalized value (0–1) defining how strong the noise signal is.                      |
| **Event Range**      | Maximum distance within which other agents will be notified.                         |

### Report Team Event

The **Report Team Event** task notifies nearby **team members** through Unreal Engine's Perception System. It is typically
used for **coordination behaviors** such as alerting allies, requesting assistance, or sharing target information.

Unlike noise events, team events can carry richer context, including a target actor and an explicit location that could
also receive a **higher score modifier** than a sound (which is usually meant to be less precise).

| Property             | Description                                                                          |
|----------------------|--------------------------------------------------------------------------------------|
| **Event Instigator** | Input. Actor triggering the team event.                                              |
| **Target Actor**     | Input. Actor associated with the event, if applicable.                               |
| **Set Location**     | Enables explicit control over the location used by the event.                        |
| **Location**         | Location associated with the event. If not set, the target actor’s location is used. |
| **Event Range**      | Maximum distance within which team members will be notified.                         |
| **Event Age**        | Age assigned to the event, controlling how long it remains relevant.                 |
| **Event Strength**   | Strength assigned to the event, influencing how strongly it is perceived.            |

### Set Movement

The **Set Movement** task requests a **movement mode change** for the bot, using the configured **movement adapter**. It
provides a clean abstraction between AI decision logic and the underlying movement implementation.

State Trees can use this task to **switch between movement profiles without directly manipulating movement components**.

| Property                 | Description                                                                                                                                                           |
|--------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Movement Profile Tag** | Gameplay tag identifying the movement profile to apply. This tag must match a movement profile defined in the Bot Setup and supported by the active movement adapter. |
