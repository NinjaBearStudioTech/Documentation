# Interaction Targets
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li><b>Interaction Targets</b> are world actors that can be interacted with, powered by <b>Smart Objects</b> and <b>Gameplay Behaviors</b>.</li>
        <li>The <b>Interaction Target Component</b> manages events, functions, and integration with the <b>Smart Object Subsystem</b>.</li>
        <li>The <b>Interaction Target Interface</b> connects the component with the actor, mixing <b>optional helper functions</b> and <b>required core logic</b>.</li>
        <li>Each Smart Object slot uses an <b>Interaction Gameplay Behavior</b>, configured with tags, text, priorities, and a <b>State Tree</b> for execution.</li>
        <li><b>Interaction Actors</b> are the concrete objects placed in the world, provided as C++ base classes or ready-to-use Static/Skeletal Mesh subclasses.</li>
    </ul>
</tldr>

An **Interaction Target** is any actor in the world that responds to an interaction request from another actor, usually
an **Interaction Instigator**, such as a **player character** or **AI agent**.

Interaction Targets are implemented using two Unreal Engine frameworks: **Smart Objects** and **Gameplay Behaviors**. At 
the core, a dedicated **Interaction Target Component** ties these frameworks together, orchestrating the foundation of 
the system while exposing the functionality required by Ninja Interaction.

## Interaction Target Component

The `UNinjaInteractionTargetComponent` is the core component that must be **added to any actor** intended to participate
in interactions. It serves as the bridge between the actor, Smart Objects, and the Interaction System, with the following responsibilities:

1. Handle incoming interaction events, such as **focus gained/lost** and **interaction started**.
2. Track and manage **interaction sources** currently focusing on the actor, enabling them to **initiate interactions**.
3. Provide access to interaction details defined by the assigned **Smart Object**.
4. Integrate seamlessly with the **Smart Object Subsystem**.
5. Forward relevant functions from the **Interaction Target Interface** to the owning actor.

> **Scene Component**  
> 
> Since this class extends `USmartObjectComponent`, it is also a **Scene Component**. This means it must be placed in
> the actor's **component hierarchy**. A common setup is attaching it to the actor's mesh.
{style="note"}

The component provides several **events** that can be used to react to changes in focus, registration, or the interaction 
lifecycle.

| Event                    | Description                                                        |
|--------------------------|--------------------------------------------------------------------|
| `OnTargetRegistered`     | Fired when an interaction source becomes aware of this target.     |
| `OnTargetUnregistered`   | Fired when an interaction source loses awareness of this target.   |
| `OnFocusApplied`         | Fired when an interaction source begins focusing this target.      |
| `OnFocusRemoved`         | Fired when an interaction source stops focusing this target.       |
| `OnInteractionStarted`   | Fired when an interaction with this target begins.                 |
| `OnInteractionFinished`  | Fired when an interaction with this target completes successfully. |
| `OnInteractionCancelled` | Fired when an ongoing interaction with this target is cancelled.   |

The `UNinjaInteractionTargetComponent` also exposes several **Blueprint-accessible functions** for querying and controlling 
interactions. These functions let you check availability, retrieve details, and activate or deactivate specific interaction 
slots.

| Function                               | Description                                                                                                                                              |
|----------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------|
| `HasActiveInteractions`                | Returns `true` if the target has any active interaction slots defined by the assigned Smart Object.                                                      |
| `GetInteractions`                      | Retrieves a list of all interaction summaries defined by this component. Set `bIncludesDeactivated = true` to include slots that are currently inactive. |
| `GetInteractionSummaryForSlot`         | Returns the `FInteractionSummary` that describes the interaction associated with a specific Smart Object slot handle.                                    |
| `GetInteractionBehaviorConfiguration`  | Retrieves the `UGameplayBehaviorConfig_ExecuteInteraction` configuration for a given slot handle.                                                        |
| `GetLocationAndRotationForInteraction` | Provides the location and rotation for an interaction identified by a Gameplay Tag. Returns `true` if found.                                             |
| `GetLocationAndRotationForSlot`        | Provides the location and rotation for a specific slot handle. Returns `true` if found.                                                                  |
| `ActivateInteractionSlot`              | Activates the interaction slot identified by the Gameplay Tag, usually when gameplay conditions are met.                                                 |
| `DeactivateInteractionSlot`            | Deactivates the interaction slot identified by the Gameplay Tag, usually when requirements are no longer met.                                            |
| `TriggerInteractionBehavior`           | Executes the interaction behavior associated with a slot claim handle and a source actor. Returns `true` if the behavior is successfully triggered.      |

> **System Backbone**
> 
> These functions can be used directly when needed, but most of the time they are invoked automatically by the underlying 
> layers of the system. This makes the component more of a **backbone** than a **front-facing** participant for end-users.
{style="note"}

## Interaction Target Interface

The `IInteractionTargetInterface` defines how an **Interaction Target Actor** communicates with its **Interaction Target 
Component** and the overall interaction system.

This interface is implemented by the `UNinjaInteractionTargetComponent`, which already provides default implementations 
for many behaviors (such as focus handling or availability checks). Because of this, some functions are **optional** for 
the actor to override, while others are **required** and must always be implemented to define the actor's actual 
**interaction logic**.

### Optional Functions

These functions have **neutral defaults**. They can be left unimplemented unless the actor needs to customize how it
responds to availability, focus, or registration events.

| Function                    | Description                                                                      |
|-----------------------------|----------------------------------------------------------------------------------|
| `IsAvailableForInteraction` | Checks if the target can currently be focused. Default: always available.        |
| `CanHandleInteraction`      | Checks if the target can handle a given interaction type. Default: always true.  |
| `HandleTargetRegistered`    | Called when the target is registered by an interaction source. Default: no-op.   |
| `HandleTargetUnregistered`  | Called when the target is unregistered by an interaction source. Default: no-op. |
| `HandleFocusApplied`        | Called when focus is applied by an interaction source. Default: no-op.           |
| `HandleFocusRemoved`        | Called when focus is removed by an interaction source. Default: no-op.           |

> **Interface Usage**
>
> While these functions give you hooks to extend or customize behavior, most of the time the default component
> handles interactions automatically. Override them only when your actor requires specialized logic.
{style="note"}

### Required Functions

These functions must be implemented by the actor, as they define the **core interaction behavior**.

| Function                        | Description                                                                                                                                                           |
|---------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `GetInteractionTargetComponent` | Returns the `UNinjaInteractionTargetComponent` that contains the target's interaction definitions.                                                                    |
| `StartInteraction`              | Starts the interaction logic for this object. From here, the actor controls the lifecycle of the interaction, including when to end the associated Gameplay Behavior. |
| `FinishInteraction`             | Ends the interaction logic for this object, either because it completed naturally or was interrupted.                                                                 |

## Smart Objects

Interaction Targets are built on top of the **Smart Objects** framework, which enables multiple possible interactions,
represented as **slots**. Each **Interaction Target Component** requires a **Smart Object Definition** to define these
slots.

Each slot may include one or more **Gameplay Behaviors**, which apply the logic and data associated with that specific
interaction. The Interaction System provides a dedicated **Interaction Behavior**, responsible for orchestrating the
Interaction Interface and handling the associated animations.

> **Slots and Supported Interactions**  
> 
> Each supported interaction is represented by its own **dedicated slot**, containing the **Interaction Behavior**.
{style="note"}

By using Smart Objects to define interactable targets, you can also take advantage of additional framework features:

1. **Filter Tags**: Require specific tags (e.g. `tag.player`) before certain interactions are available.
2. **Preconditions**: Define conditions such as requiring an inventory item (e.g. a key) before a slot can be activated.
3. **Slot Transform Adjustments**: Fine-tune the transform used for the Interaction Source actor placement.

## Interaction Gameplay Behavior

Each **slot** in a Smart Object can include **Behavior Definitions** that define the gameplay logic executed when the
slot activates for a given target. These behaviors are provided by the **Gameplay Behavior Smart Objects** module.

Once a behavior is added, you can configure its properties. An interaction slot should typically use the **Execute 
Interaction** behavior (or a custom subtype). This behavior exposes the following properties:

| Property                 | Description                                                                                                                                                                                                                                     |
|--------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `InteractionTypeTag`     | Gameplay Tag that represents this specific interaction on the target.                                                                                                                                                                           |
| `InteractionPriorityTag` | Gameplay Tag that defines the priority of this interaction relative to others on the same target. Useful when a target supports multiple interactions (e.g., *Open* and *Lock*) that need to be ordered for systems like the UI.                |
| `DisplayText`            | Friendly text used for interaction prompts in the UI.                                                                                                                                                                                           |
| `InteractionTree`        | State Tree asset representing the flow and logic of this interaction. Must use the `NinjaInteractionComponentSchema`.                                                                                                                           |
| `Duration`               | Duration of the interaction in seconds. Clamped to zero or higher. A value of zero means "immediate".                                                                                                                                           |
| `bCanBeDestroyed`        | If true, the interaction will succeed if the target actor is destroyed during execution. If false, the interaction will be cancelled when the target actor is destroyed. Useful for cases like doors or portals being unloaded mid-interaction. |

> **Interaction State Tree**  
> 
> The interaction state tree executes on the [**Interaction Source**](int_interaction_source.md). It defines the sequence 
> of steps the source must perform to carry out the interaction.
> 
> For example, moving and rotating toward the target, playing animations, and triggering the actual interaction behavior.
{style="note"}

## Interaction Actor

An **Interaction Actor** is the actual interactable object placed in the world. It serves as the concrete implementation
of an interaction target, combining the component, interface, and visual representation. An Interaction Actor typically:

1. Contains an **Interaction Target Component** with a fully configured Smart Object.
2. Implements the **Interaction Target Interface**.
3. Includes a mesh to visually represent the object.
4. Provides a scene component with its collision set to the [**Interaction Target**](int_collisions.md) preset.

Ninja Interaction includes a core abstract base class and two ready-to-use subclasses:

- `ANinjaInteractionActor`: Abstract base class for custom interaction actors in C++.
- `ANinjaInteractionActor_StaticMesh`: Interaction actor represented by a **Static Mesh**.
- `ANinjaInteractionActor_SkeletalMesh`: Interaction actor represented by a **Skeletal Mesh**.  

## Configuring an Interaction Target

To put these concepts into practice, we'll walk through the process of building a fully functional **Interaction Target**. 
This involves three main steps:

1. Create a **State Tree** that defines the flow of the interaction when triggered by a source. We'll start with a simple, generic interaction tree.
2. Create a **Smart Object** that includes the Interaction Behavior, and configure its slot to use the newly-created **State Tree**.
3. Create the **Interaction Actor**, add the Interaction Target Component, and assign the newly-created **Smart Object** to it.

The following procedures will guide you through each step in detail.

<procedure title="Create a generic Interaction State Tree" collapsible="true" default-state="expanded">
    <step>Create a new <b>State Tree</b> asset, extending from the <b>NinjaInteractionComponentSchema</b>.</step>
    <step>Add the <b>Interaction State Evaluator</b> to the tree, and bind the <b>Interaction Manager</b> property to the context entry.</step>
    <step>Add a new state called <b>Execute Interaction</b>, as a child of the root state. This will trigger the actual interaction behavior on the target.</step>
    <step>
        <p>In the <b>Execute Interaction</b> state, add the <b>Trigger Target Behavior</b> task and configure the bindings:</p>
        <ul>
            <li><b>Interaction Manager</b> &rarr; context entry</li>
            <li><b>Target Actor</b> &rarr; provided by the Evaluator</li>
            <li><b>Claim Handle</b> &rarr; provided by the Evaluator</li>
        </ul>
        <note>Make sure the task completion mode is set to <b>Complete when all tasks are done</b>.</note>
    </step>
    <step>
        <p>Configure the following <b>transitions</b> for this task:</p>
        <ul>
            <li><b>On State Succeeded</b> &rarr; <b>Tree Succeeded</b></li>
            <li><b>On Tree Failed</b> &rarr; <b>Tree Failed</b>.</li>
        </ul>
    </step>
    <img src="int_target_generic_state_tree.png" alt="Generic State Tree" border-effect="line" thumbnail="true"/>
</procedure>

<procedure title="Create the Smart Object definition" collapsible="true" default-state="expanded">
    <step>Create a new <b>Smart Object</b> asset.</step>
    <step>Set the <b>Object Mesh Path</b> used to preview this interactable target, or select the <b>Actor Class</b> if you already have one.</step>
    <step>Add a new <b>slot</b> and give it a meaningful name, such as <b>Open</b>.</step>
    <step>Configure the <b>shape</b> (size, offset, and rotation) to represent the slot. This will later be used for Interaction Source placement.</step>
    <step>Add an <b>activity tag</b> that identifies this slot, such as <code>Interaction.Type.Open</code>.</step>
    <step>Add a new <b>Behavior Definition</b> and select <b>Gameplay Behavior Smart Object Behavior Definition</b> as the type.</step>
    <step>Set <b>Execute Interaction</b> as the <b>Behavior Configuration</b>.</step>
    <step>Configure the <b>Interaction Type Tag</b> with a tag that uniquely identifies this interaction for this Smart Object, for example <code>Interaction.Type.Open</code>.</step>
    <step>Optionally set a <b>Display Text</b> for this interaction, which will be shown by the user interface when displaying interaction prompts.</step>
    <step>Assign the <b>State Tree</b> created earlier as the <b>Interaction Tree</b>.</step>
    <step>Set a <b>Duration</b> of <code>0.8</code> seconds for this interaction. This defines how long the user must press a button, to interact with the target.</step>
    <img src="int_target_smart_object.png" alt="Smart Object Setup" border-effect="line" thumbnail="true"/>
</procedure>

<procedure title="Create the Interaction Target Actor" collapsible="true" default-state="expanded">
    <step>Create a new Actor based on <code>UNinjaInteractionActor_StaticMesh</code> (or use the Skeletal Mesh variation if appropriate).</step>
    <step>
        Set the <b>Smart Object</b> you created earlier to the <b>Interaction Target Component</b>.
        <p><img src="int_target_actor_01.png" alt="Assign Smart Object to Target Component" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>Assign your mesh asset, matching the one used in the Smart Object preview.</step>
    <step>
        Add a collision component (e.g., <b>Box Collision</b>) that matches the object’s shape, and set its <b>Collision Preset</b> to <code>InteractionTarget</code>, as per the <a href="int_collisions.md">collision setup</a>.
        <p><img src="int_target_actor_02.png" alt="Set Collision Preset" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        Optionally, add debug strings to track interactions in relevant events such as <code>HandleTargetRegistered</code> or <code>HandleFocusRemoved</code>.
        <p><img src="int_target_actor_03.png" alt="Debug Event Strings" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        Implement the <code>FinishInteractionEvent</code>, which will be invoked by the generic interaction tree.  
        For now, you can add a debug string, or implement more complex behavior such as showing an inventory window to the player.
        <p><img src="int_target_actor_04.png" alt="Finish Interaction Example" border-effect="line" thumbnail="true"/></p>
    </step>
    <tip>Start with something simple and familiar (like debug strings or a basic effect). Once you confirm the setup works, expand with custom logic such as opening UIs or triggering gameplay effects.</tip>
</procedure>
