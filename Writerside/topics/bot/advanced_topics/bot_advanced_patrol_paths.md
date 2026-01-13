# Patrol Paths
<primary-label ref="bot"/>
<secondary-label ref="advanced"/>

Patrol Paths in Ninja Bot are defined using **Patrol Point Actors** (`ANinjaBotPatrolPointActor`) placed directly in the 
level. Each patrol point can **reference a subsequent patrol point**, forming a simple directed path. A patrol point may 
also **terminate the path** by not referencing a successor.

In addition to defining movement flow, patrol points can **optionally inject additional bot logic** by providing dynamic 
Behavior Trees or State Trees. This allows designers to **alter or extend behavior contextually** as a bot reaches specific 
points along a patrol route.

Patrol Point Actors support **Gameplay Tags**, enabling bots to discover **compatible patrol paths at runtime**. Agents 
can use EQS queries to search for patrol points of the appropriate type within a given range and filter them by tags, 
allowing patrol behavior to adapt dynamically to the environment or agent role.

## Patrol Point Properties

Patrol Point Actors expose a small set of properties that define how they participate in patrol paths and optionally 
influence bot behavior.

| Property                | Description                                                                                                                                                      |
|-------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Patrol Point Tags**   | Gameplay tags used to identify and categorize this patrol point. These tags can be used by EQS queries or other discovery logic to find compatible patrol paths. |
| **Logic Type**          | Defines whether this patrol point provides additional logic to the bot. When set to `None`, the patrol point only defines navigation flow.                       |
| **Behavior Tree Asset** | Behavior Tree provided by this patrol point when the logic type is set to Behavior Tree. The tree can be dynamically injected by compatible bots.                |
| **State Tree Asset**    | State Tree provided by this patrol point when the logic type is set to State Tree. The tree can be dynamically injected by compatible bots.                      |
| **Next Patrol Point**   | Reference to the next patrol point in the path. When unset, the patrol route terminates at this point.                                                           |

Patrol Points support the following logic types:

| Logic Type        | Description                                                                                                                                            |
|-------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------|
| **None**          | The patrol point does not provide any additional logic and acts only as a navigation target.                                                           |
| **Behavior Tree** | Provides a dynamic Behavior Tree to be injected when the bot reaches this patrol point. Compatible only with bots using Behavior Trees as their brain. |
| **State Tree**    | Provides a dynamic State Tree to be injected when the bot reaches this patrol point. Compatible with bots using either Behavior Trees or State Trees.  |

> Patrol point logic is injected dynamically and must be compatible with the bot’s configured brain type. Logic modes are 
> not swapped at runtime and, although Behavior Trees can execute State Trees from a task, this form of injection is not 
> supported at this time.
{style="note"}

## AI Integration

<tabs group="brain_type">

<!-- Behavior Tree Assets -->
<tab title="Behavior Tree" group-key="bt">
<p>
Ninja Bot provides a set of <b>Behavior Tree nodes</b> that allow patrol logic to be driven directly from Patrol Point Actors. 
These nodes focus on <b>dynamic behavior injection</b> and <b>patrol progression</b>, keeping patrol paths data-driven.
</p>
<p>
The <b>Set Patrol Point Behavior Service</b> attempts to inject a <b>dynamic Behavior Tree</b> provided by the current 
patrol point. When the service becomes relevant:
</p>
<ol>
<li>It reads the patrol point from the <b>Blackboard</b>, usually obtained via an <b>Environment Query</b>.</li>
<li>If the patrol point provides a <b>dynamic Behavior Tree</b>, it <b>injects it using the configured tag</b>.</li>
<li>If no tree is provided by the actor, <b>it attempts to inject one from the bot setup</b>.</li>
<li>If no tree is available from the setup, <b>it will use the default value set in the task</b>.</li>
</ol>
<table>
    <thead>
        <tr>
            <th>Property</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><b>Dynamic Injection Tag</b></td>
            <td>Gameplay tag used to inject the dynamic behavior. Must match the injection point defined in the Behavior Tree.</td>
        </tr>
        <tr>
            <td><b>Patrol Point Key</b></td>
            <td>Blackboard key referencing the patrol point actor providing the behavior.</td>
        </tr>
    </tbody>
</table>
<p>
The <b>Advance Patrol Point Task</b> progresses the patrol route by <b>resolving the next patrol point</b> from the current one.
It updates the patrol point reference in the Blackboard, allowing the bot to continue along a patrol as the branch restarts.
</p>
<table>
    <thead>
        <tr>
            <th>Property</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><b>Patrol Point Key</b></td>
            <td>Blackboard key referencing the current patrol point. This value is updated to the next patrol point when the task executes.</td>
        </tr>
    </tbody>
</table>
</tab>

<!-- State Tree Assets -->
<tab title="State Tree" group-key="st">
<p>
Ninja Bot provides a set of <b>State Tree tasks</b> that enable patrol logic to be driven directly by Patrol Point Actors. 
These tasks allow patrol paths to **inject contextual logic** and <b>advance patrol progression</b> in a data-driven manner.
</p>
<p>
The <b>Set Patrol Point Behavior Task</b> attempts to inject a <b>dynamic State Tree</b> provided by the current patrol point.
When the state is entered, the following sequence occurs:
</p>
<ol>
    <li>It reads the patrol point from the <b>context</b>, usually obtained through an <b>Environment Query</b>.</li>
    <li>If the patrol point provides a <b>dynamic State Tree</b>, it injects it using the configured <b>Dynamic Injection Tag</b>.</li>
    <li>If no State Tree is provided by the patrol point actor, it attempts to inject one from the <b>Bot Setup</b>.</li>
    <li>If no State Tree is available from the Bot Setup, it falls back to the <b>default value</b> configured on the state.</li>
</ol>
<table>
    <thead>
        <tr>
            <th>Property</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><b>Patrol Point</b></td>
            <td>Input. Reference to the actor representing the current patrol point.</td>
        </tr>
        <tr>
            <td><b>Dynamic Injection Tag</b></td>
            <td>Gameplay tag used to inject the dynamic State Tree. Must match the State Tree node configured as a linked asset.</td>
        </tr>
    </tbody>
</table>
<p>
The <b>Advance Patrol Point Task</b> progresses the patrol route by <b>resolving the next patrol point</b> from the current one.
It updates the patrol point reference in the context, allowing the Bot to continue along the patrol route as the state restarts.
</p>
<table>
    <thead>
        <tr>
            <th>Property</th>
            <th>Description</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><b>Patrol Point</b></td>
            <td>Input. Reference to the current patrol point actor.</td>
        </tr>
        <tr>
            <td><b>Result</b></td>
            <td>Output reference where the next patrol point actor is written.</td>
        </tr>
    </tbody>
</table>
</tab>
</tabs>

## Smart Objects Integration

Patrol Points are implemented as **lightweight target point actors** rather than Smart Objects. This design choice prioritizes 
simplicity and avoids the complexity of slot ownership and reservation during early design. If a project requires **Smart 
Object integration or Gameplay Behaviors**, Patrol Points can be extended by **attaching the appropriate Smart Object components** 
and interacting with them as usual.