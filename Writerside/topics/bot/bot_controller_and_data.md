# AI Controller and Data
<primary-label ref="bot"/>

<tldr>
    <p><b>Summary: AI Controller and Data</b></p>
    <br/>
    <ul>
        <li>Ninja Bot defines AI behavior through a shared controller and reusable data assets.</li>
        <li>Perception, awareness, and bot-specific behavior are configured through data, not code.</li>
        <li>Bot pawns provide their Data Assets via <code>BotSetupProviderInterface</code>.</li>
    </ul>
</tldr>

Once the [perception and awareness models](bot_perception_and_awareness.md) are established, the next step is to **define 
bots through data**. 

In Ninja Bot, AI agents are assembled by combining a **shared AI controller**, a **data asset that aggregates bot configuration**, 
the **decision asset** (Behavior Tree, State Tree or other solutions) and a project-specific pawn class.

This approach allows multiple bots to **share the same controller logic** while expressing their differences entirely through 
data. Other than providing their **Bot Data Assets**, Ninja Bot does not impose requirements on the pawn class.

## Bot Controller

The Ninja Bot system provides a **shared AI controller**, `ANinjaBotAIController`, responsible for initializing and 
coordinating all runtime systems required by a bot. Any pawn that should participate in the Ninja Bot framework **must be 
assigned this controller or a subclass derived from it**.

The controller itself contains no bot-specific logic. Instead, it acts as an **orchestration layer** that loads configuration 
data, **initializes perception and awareness**, and **sets up the appropriate AI brain based on data-driven definitions**.

### Initialization Responsibilities

During initialization, the Bot Controller performs the following steps:

1. Loads the assigned Bot Data Asset from the Pawn, via `BotSetupProviderInterface`
2. Initializes the Brain Component based on the logic type defined by the data asset (Behavior Tree or State Tree)
3. Initializes and configures the Perception Component using the provided Sense Profile
4. Applies optional awareness configuration if an Awareness Profile is present

This process ensures that all bots follow a consistent initialization path while remaining fully data-driven. Furthermore,
Since the asset loading is **asynchronous**, the controller exposes two ways to detect when initialization has completed:

- Querying the `HasCompletedBotSetup` function
- Subscribing to the `OnBotSetupComplete` delegate

> AI logic should only begin execution once the setup phase has completed successfully. You can observe the Gameplay
> Debugger or confirm the initialization status in the **Visual Logger**.

### Bot Controller Properties

| Property                                  | Description                                                                                                                                                                                                                                                                                                                                                |
|-------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Apply Focus to Perception Target**      | When enabled, the controller automatically applies focus to the current perception target. If finer control is required, focus management can instead be handled explicitly by the brain asset (Behavior Tree or State Tree). By default, gameplay focus is applied. The focus type can be customized by overriding `GetFocusPriorityForPerceptionTarget`. |
| **Perception Target Acquired Event Tag**  | Gameplay tag fired when a new perception target is acquired. This event is sent to the owner's Ability System and can be used to trigger gameplay logic such as target lock abilities.                                                                                                                                                                     |
| **Perception Target Dismissed Event Tag** | Gameplay tag fired when the current perception target is dismissed. This event is sent to the owner's Ability System and can be used to deactivate abilities or clear targeting state.                                                                                                                                                                     |

### Gameplay Ability Integration

The **Target Acquired** and **Target Dismissed** event tags are designed to integrate cleanly with the **Gameplay Ability 
System**. When these events are fired:

- A gameplay event is sent to the owner's Ability System
- The newly acquired or dismissed perception target is provided as an optional event object 

> This pattern matches the [**Target Lock Gameplay Ability**](cbt_ability_target_lock.md) provided by Ninja Combat and 
> allows AI perception to drive combat or interaction systems without tight coupling.
{style="note"}

## Bot Data Asset

The Bot Data Asset defines how an AI agent is **configured within the Ninja Bot framework**. It aggregates **decision logic**, 
**perception setup**, **awareness interpretation**, and **movement behavior** into a single reusable, data-driven definition.

The asset is provided to the AI Controller via `BotSetupProviderInterface`, which must be implemented by any pawn that 
participates in the Ninja Bot system. Through this interface, **the pawn supplies the Bot Data Asset that defines its behavior**.

As established during [setup](bot_setup_asset_manager.md), the Bot Data Asset is a **Primary Data Asset** and must be registered 
with the Asset Manager. Once registered:

1. The AI Controller can load the asset on demand
2. Asset loading is handled asynchronously
3. The asset remains loaded while one or more bots are using it

This allows multiple bots to safely share the same configuration without duplicating data or code.

### Brain Configuration

The Bot Data Asset defines which **decision system** is used as the bot's brain. Ninja Bot supports multiple brain types, 
allowing projects to mix and match authoring styles without changing controller logic.

| Brain Type        | Description                                                                             |
|-------------------|-----------------------------------------------------------------------------------------|
| **Behavior Tree** | Uses Unreal Engine Behavior Trees, suitable for hierarchical and reactive behavior.     |
| **State Tree**    | Uses Unreal Engine State Trees, suitable for state-driven and lifecycle-oriented logic. |
| **Custom**        | Instantiates a user-defined Brain Component, allowing full control over AI execution.   |

> The selected brain type determines which assets are loaded and which runtime components are instantiated by the AI Controller.

> Ninja Bot does not favor any brain type and treats them as interchangeable consumers of perception and awareness data.

### Movement Mode Adapters

Movement modes allow bots to express **how they move** without coupling AI logic to a specific movement implementation. 
Examples include _walking_, _running_, _sprinting_, or other custom locomotion states.

The Bot Data Asset specifies a **Movement Mode Adapter**, which acts as a proxy between AI logic and the actual movement 
system. Behavior Trees or State Trees can **request movement mode changes** without needing to know how those modes are 
implemented.

Ninja Bot provides a default adapter compatible with **Character Movement Components**. Projects are free to implement 
their own adapters by extending `UNinjaBotMovementAdapter`, enabling support for other locomotion systems.