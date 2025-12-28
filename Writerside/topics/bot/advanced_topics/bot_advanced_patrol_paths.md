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

## Behavior Tree Integration

Ninja Bot provides a set of **Behavior Tree nodes** that allow patrol logic to be driven directly from Patrol Point Actors. 
These nodes focus on **dynamic behavior injection** and **patrol progression**, keeping patrol paths data-driven.

### BT Service: Set Patrol Point Behavior

The **Set Patrol Point Behavior** service attempts to inject a **dynamic Behavior Tree** provided by the current patrol 
point. When the service becomes relevant:

1. It reads the patrol point from the **Blackboard**, usually obtained via an **Environment Query**
2. If the patrol point provides a **dynamic Behavior Tree**, it **injects it using the configured tag**
3. If no tree is provided by the actor, **it attempts to inject one from the bot setup**
4. If no tree is available from the setup, **it will use the default value set in the task**

| Property                  | Description                                                                                                    |
|---------------------------|----------------------------------------------------------------------------------------------------------------|
| **Dynamic Injection Tag** | Gameplay tag used to inject the dynamic behavior. Must match the injection point defined in the Behavior Tree. |
| **Patrol Point Key**      | Blackboard key referencing the patrol point actor providing the behavior.                                      |

### BT Task: Advance Patrol Point

The **Advance Patrol Point** task progresses the patrol route by **resolving the next patrol point** from the current one.
It updates the patrol point reference in the Blackboard, allowing the bot to continue along a patrol as the branch restarts.

| Property             | Description                                                                                                                 |
|----------------------|-----------------------------------------------------------------------------------------------------------------------------|
| **Patrol Point Key** | Blackboard key referencing the current patrol point. This value is updated to the next patrol point when the task executes. |

### Behavior Tree Sample
The sample illustrates a patrol-oriented Behavior Tree. The structure demonstrates how patrol discovery, execution, and 
progression can be composed with both native and Ninja Bot nodes.

<img src="bot_advanced_patrol_bt_example.png" alt="Patrol Example in Behavior Trees" width="800" border-effect="line"/>

> A detailed breakdown of Blackboard keys, services, tasks, and execution flow is available in the Guides section under 
> [**Creating Patrolling Agents**](bot_guide_create_patrols.md).
{style="note"}

## State Tree Integration

Ninja Bot provides a set of **State Tree tasks** that enable patrol logic to be driven directly by Patrol Point Actors. 
These tasks allow patrol paths to **inject contextual logic** and **advance patrol progression** in a data-driven manner.

### ST Task: Set Patrol Point Behavior

The **Set Patrol Point Behavior** task attempts to inject a **dynamic State Tree** provided by the current patrol point. 
When the state is entered:

1. It reads the patrol point from the **context**, usually obtained via an **Environment Query**
2. If the patrol point provides a **dynamic State Tree**, it **injects it using the configured tag**
3. If no tree is provided by the actor, **it attempts to inject one from the bot setup**
4. If no tree is available from the setup, **it will use the default value set in the state**

| Property                  | Description                                                                                                      |
|---------------------------|------------------------------------------------------------------------------------------------------------------|
| **Patrol Point**          | Input. Reference to the actor representing the current patrol point.                                             |
| **Dynamic Injection Tag** | Gameplay tag used to inject the dynamic State Tree. Must match the State Tree node configured as a linked asset. |

### ST Task: Advance Patrol Point

The **Advance Patrol Point** task progresses the patrol route by **resolving the next patrol point** from the current one.
It updates the patrol point reference in the context, allowing the bot to continue along a patrol as the state restarts.

| Property         | Description                                                  |
|------------------|--------------------------------------------------------------|
| **Patrol Point** | Input. Reference to the current patrol point actor.          |
| **Result**       | Reference where the next patrol point actor will be written. |

### State Tree Sample
The sample illustrates a patrol-oriented State Tree. The structure demonstrates how patrol discovery, execution, and
progression can be composed with both native and Ninja Bot tasks.

<img src="bot_advanced_patrol_st_example.png" alt="Patrol Example in State Trees" width="800" border-effect="line"/>

> A detailed breakdown of context setup, evaluators, tasks, and execution flow is available in the Guides section under
> [**Creating Patrolling Agents**](bot_guide_create_patrols.md).
{style="note"}

## Smart Objects Integration

Patrol Points are implemented as **lightweight target point actors** rather than Smart Objects. This design choice prioritizes 
simplicity and avoids the complexity of slot ownership and reservation during early design. If a project requires **Smart 
Object integration or Gameplay Behaviors**, Patrol Points can be extended by **attaching the appropriate Smart Object components** 
and interacting with them as usual.