# Behavior Trees
<primary-label ref="bot"/>

<tldr>
    <p><b>Summary: Behavior Trees</b></p>
    <br/>
    <ul>
        <li>Ninja Bot supports Unreal Engine Behavior Trees as a primary decision system.</li>
        <li>Behavior Trees are well suited for reactive and interruptible AI behavior.</li>
        <li>The framework supports dynamic injection of subtrees at runtime.</li>
    </ul>
</tldr>

Ninja Bot integrates with Unreal Engine's **Behavior Tree** system by treating it as a **consumer of interpreted perception 
and awareness**, rather than as a driver of sensing logic. Perception, awareness, and target selection are handled by the 
framework, while Behavior Trees focus exclusively on **decision-making and action execution**.

## When to Use Behavior Trees

Behavior Trees are particularly well suited for **reactive AI behavior**, where decisions must **adapt quickly to changing 
conditions** exposed to the tree, through a **Blackboard**.

> When Behavior Trees are set as the **Bot Brain**, a **Blackboard Component** will also be instantiated and assigned to
> the AI Controller.
{style="note"}

Ninja Bot enables Behavior Trees to react to **perception-driven conditions** exposed through Blackboard keys. This makes 
Behavior Trees an effective choice for combat-focused or moment-to-moment decision-making, where **emergent behavior** is 
expected from the AI Agents.

## Dynamic Behavior Tree Injection

Ninja Bot extends standard Behavior Tree usage by supporting **dynamic subtree injection** through the Bot Data Asset. 
Rather than authoring entirely separate trees, designers can:

- Define a base tree that handles **shared behavior** such as navigation
- Inject **specialized subtrees** at runtime based on gameplay tags

Dynamic injection allows behavior variation to be expressed through data rather than controller subclasses, keeping AI
logic modular, reusable, and designer-friendly. Common examples include:

- Injecting melee or ranged attack logic into a shared "Attack" branch
- Swapping investigation or combat behaviors based on equipment or role
- Injecting complex subtrees for bosses or elites 

## Behavior Tree Services

Ninja Bot provides a small set of **Behavior Tree services** that expose perception and awareness data to the tree. These 
services are designed to **bridge the gap between the perception system and decision logic** without embedding sensing 
or awareness calculations directly into Behavior Tree nodes.

Services are intentionally **focused** and **data-oriented**. They update Blackboard values that can be **consumed by 
decorators and tasks**, allowing Behavior Trees to remain reactive and easy to reason about.

### Update Perception

The **Update Perception** service is a ticking service responsible for **evaluating perception and updating the current 
best target**. It triggers perception evaluation, resolves the most relevant sensed actor, and writes perception and awareness 
data to the **Blackboard**.

This service is **typically placed high in the tree** so that all downstream logic reacts to the same evaluated 
**perception state**.

| Property                           | Description                                                                                       |
|------------------------------------|---------------------------------------------------------------------------------------------------|
| **Sensed Actor Key**               | Blackboard key where the currently selected sensed actor is stored.                               |
| **Candidate Score Key**            | Blackboard key where the raw perception score for the selected actor is stored.                   |
| **Normalized Candidate Score Key** | Blackboard key where the normalized perception score for the selected actor is stored.            |
| **Accumulated Awareness Key**      | Blackboard key storing the accumulated awareness value for the sensed actor.                      |
| **Awareness Level Key**            | Blackboard key storing the discrete awareness level derived from accumulated awareness.           |
| **First Perceived Location Key**   | Snapshot of the target's location when it is first perceived during the current perception cycle. |
| **Current Target Location Key**    | Convenience value that always reflects the actor's current transform.                             |
| **Last Known Location Key**        | Snapshot of the target's location at the moment awareness drops or the target is lost.            |

### Sensor Data

The **Sensor Data** is an optional service that exposes detailed stimulus data for a **specific sense and actor**. It is 
intended for more intricate behavior where raw sense information is required, such as reacting differently to sound strength, 
stimulus age, or tagged events.

Multiple Sensor Data services can be used simultaneously to query different senses registered with the agent.

> Since this service reads from the Blackboard, you can also query perceptual data from actors that are not the one 
> currently selected by the sense/awareness evaluation.
{style="note"}

| Property                  | Description                                                                         |
|---------------------------|-------------------------------------------------------------------------------------|
| **Sense Class**           | Sense type to query and expose, such as sight, hearing, or damage.                  |
| **Sensed Actor Key**      | Blackboard key used to read the target actor for which sensor data will be exposed. |
| **Detected Key**          | Blackboard key storing whether the stimulus is currently considered detected.       |
| **Strength Key**          | Blackboard key storing the strength of the stimulus.                                |
| **Age Key**               | Blackboard key storing the age of the stimulus in seconds.                          |
| **Stimulus Location Key** | Blackboard key storing the location where the stimulus was triggered.               |
| **Receiver Location Key** | Blackboard key storing the location where the stimulus was received by the agent.   |
| **Tag Key**               | Blackboard key storing any additional gameplay tags associated with the stimulus.   |

## Behavior Tree Tasks

Ninja Bot provides a small set of **Behavior Tree tasks** that allow AI logic to actively **interact with the perception 
system and bot movement layer**. These tasks are designed to emit signals or request state changes, rather than perform 
perception evaluation directly.

Tasks are intentionally **lightweight** and **composable**, allowing designers to trigger perception events or adjust 
movement behavior from within a Behavior Tree without coupling logic to engine systems.

### Report Noise Event

The **Report Noise Event** task emits a noise stimulus through Unreal Engine's Perception System as an explicit AI signal, 
rather than as a byproduct of physical actions.

This task is typically used to **communicate intent or state changes to other agents**, such as deliberately revealing 
presence, escalating awareness, or drawing attention.

| Property                 | Description                                                                                                                 |
|--------------------------|-----------------------------------------------------------------------------------------------------------------------------|
| **Event Instigator Key** | Blackboard key referencing the actor generating the noise. The actor's current location is used as the source of the event. |
| **Loudness**             | Normalized value (0–1) defining how strong the noise signal is.                                                             |
| **Event Range**          | Maximum distance within which other agents can be notified of the noise event.                                              |

### Report Team Event

The **Report Team Event** task notifies nearby **team members** through Unreal Engine's Perception System. It is typically 
used for **coordination behaviors** such as alerting allies, requesting assistance, or sharing target information.

Unlike noise events, team events can carry richer context, including a target actor and an explicit location that could
also receive a **higher score modifier** than a sound (which is usually meant to be less precise).

| Property                 | Description                                                                                                                                |
|--------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| **Event Instigator Key** | Blackboard key referencing the actor that triggered the event.                                                                             |
| **Target Actor Key**     | Blackboard key referencing the actor associated with the event, if applicable.                                                             |
| **Location Key**         | Blackboard key defining the location associated with the event. This may be the instigator, the target, or an arbitrary point of interest. |
| **Event Range**          | Maximum distance within which team members will be notified of the event.                                                                  |
| **Event Age**            | Age value assigned to the event, used to control how long it remains relevant.                                                             |
| **Event Strength**       | Strength value assigned to the event, influencing how strongly it is perceived by recipients.                                              |

### Set Movement

The **Set Movement** task requests a **movement mode change** for the bot, using the configured **movement adapter**. It 
provides a clean abstraction between AI decision logic and the underlying movement implementation.

Behavior Trees can use this task to **switch between movement profiles without directly manipulating movement components**.

| Property                 | Description                                                                                                                                                           |
|--------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Movement Profile Tag** | Gameplay tag identifying the movement profile to apply. This tag must match a movement profile defined in the Bot Setup and supported by the active movement adapter. |
