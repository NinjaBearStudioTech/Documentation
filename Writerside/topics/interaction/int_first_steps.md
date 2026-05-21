# First Steps with Ninja Interaction
<primary-label ref="interaction"/>

This page guides you through the first steps for **Ninja Interaction**. Make sure to check the [**Interaction Setup**](int_setup.md)
instructions before continuing. This page assumes that [**Ninja Input**](ipt_overview.md) is installed, but all concepts 
related to interaction inputs can easily transfer to plain Enhanced Input setups.

This page also assumes that [**Ninja G.A.S.**](gas_overview.md) is installed, but all concepts related to the Gameplay Ability System 
can easily transfer to other G.A.S. setups.

The following steps aim to provide **an interactable actor that can be detected by the player**. We will use the generic
**Smart Object** and **State Tree** provided by Ninja Interaction.

## Interaction Targets

An **Interaction Target** is any actor in the world that responds to an interaction request from another actor, usually
an **Interaction Instigator or Source**, such as a **player character** or **AI agent**. Their behavior is defined by
two assets:

- **Interaction State Tree**: Defines each step that should happen when the interaction triggers.
- **Interaction Smart Object**: Defines the usable slots and their configuration, including their state trees.

Ninja Interaction provides generic assets to get you started.

<procedure title="Create the Interaction Target Actor" collapsible="true" default-state="expanded">
    <step>Create a new Actor based on <code>NinjaInteractionActor_StaticMesh</code> (or use the Skeletal Mesh, <code>NinjaInteractionActor_SkeletalMesh</code>, variation if appropriate).</step>
    <step>
        Set the provided generic <b>Smart Object</b> to the <b>Interaction Target Component</b>.
        <p><img src="int_target_actor_01.png" alt="Assign Smart Object to Target Component" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>Assign your mesh asset, matching the one used in the Smart Object preview.</step>
    <step>
        Add a collision component (e.g., <b>Box Collision</b>) that matches the object's shape, and set its <b>Collision Preset</b> to <code>InteractionTarget</code>, as per the <a href="collision_settings.md">collision setup</a>.
        <p><img src="int_target_actor_02.png" alt="Set Collision Preset" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        Optionally, add debug strings to track interactions in relevant events such as <code>HandleTargetRegistered</code> or <code>HandleFocusRemoved</code>.
        <p><img src="int_target_actor_03.png" alt="Debug Event Strings" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        Implement <code>FinishInteractionEvent</code>, which is invoked by the generic interaction State Tree.
        In this example, we'll simply apply a <b>Gameplay Effect</b> that grants health to the player.
        <p><img src="int_target_actor_04.png" alt="Finish Interaction Example" border-effect="line" thumbnail="true"/></p>
    </step>
</procedure>

## Interaction Sources

An **Interaction Source** (sometimes also referred to as the _Instigator_) is a Pawn or Character, and it is defined by 
the presence of the **Interaction Manager Component**. Sources must have access to an **Ability System Component** and 
will often include two collision components used to **register** and **focus** Interaction Targets.

<procedure title="Add the Interaction Manager Component" collapsible="true" default-state="expanded">
    <step>Navigate to your Player Pawn or Character Blueprint or C++ Class.</step>
    <step>Add the <b>Interaction Manager component</b>, <code>NinjaInteractionManagerComponent</code>.</step>
</procedure>

### Interactable Scan Collider

This **collision shape** (commonly a box or sphere) must be present on each interaction source actor. It is used to 
**register interaction targets** so they can later be focused and interacted with.

This collider must be identified by the **Component Tag** `Interaction.Component.InteractableScan` and the collider's 
**Object Type** should be `InteractionObject`, created during the [**Collision Settings**](collision_settings.md) setup.

<procedure title="Add the Interaction Scan Collider" collapsible="true" default-state="expanded">
    <step>In your main Pawn or Character, add a <b>Sphere Collision</b>.</step>
    <step>Set the component's <b>radius</b> to a reasonable value, like <code>800</code>.</step>
    <step>Add <code>Interaction.Component.InteractableScan</code> to the list of <b>Component Tags</b>.</step>
    <step>
        <p>Set the <b>Object Type</b> to <code>InteractionObject</code>.</p>
        <p><img src="int_source_component_scan.png" alt="Interactable Scan Collider" thumbnail="true" width="800" border-effect="line"/></p>
    </step>
</procedure>

### Interactable Focus Collider
<secondary-label ref="optional"/>

This **collision shape** (commonly a box or sphere) is optional and, if present, applies focus to targets nearby. If you
are using other strategies to detect focus, such as the **player camera center**, then you don't need this component.

This collider is usually smaller than the **Scan Collider** and, similarly, must be identified by the **Component Tag** 
`Interaction.Component.InteractableFocus`. The collider's **Object Type** should also be `InteractionObject`.

<procedure title="Add the Interaction Focus Collider" collapsible="true" default-state="expanded">
    <step>In your main Pawn or Character, add a <b>Box Collision</b> and place it in front of the character.</step>
    <step>Set the component's <b>dimensions</b> to a reasonable value, like <code>50x50x100</code>.</step>
    <step>Add <code>Interaction.Component.InteractableFocus</code> to the list of <b>Component Tags</b>.</step>
    <step>
        <p>Set the <b>Object Type</b> to <code>InteractionObject</code>.</p>
        <p><img src="int_source_component_focus.png" alt="Interactable Focus Collider" thumbnail="true" width="800" border-effect="line"/></p>
    </step>
</procedure>

### Gameplay Abilities

Two Gameplay Abilities must be granted to the Interaction Source so it can scan and execute interactions:

- `InteractionAbility_FindInteractableActor`: Scans the list of registered targets and, based on the **provided Scan Task**, selects the best candidate for focus or interaction.
- `InteractionAbility_ExecuteInteraction`: Executes the selected interaction by bridging communication between the source and the target components.

<procedure title="Grant Interaction Abilities" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new <b>Gameplay Ability Blueprint</b>, extending from <code>InteractionAbility_FindInteractableActor</code>. Name it <code>GA_Interaction_Scan</code>.</p>
        <ul>
            <li>If you are using the <b>focus box collision</b>, you can use the default <b>Interaction Task Class</b> (<code>AbilityTask_FindClosestInteractionTarget</code>).</li>
            <li>If you'd rather apply focus using the <b>player camera</b>, then change the task to <code>AbilityTask_TraceInteractionTarget</code>.</li>
        </ul>
    </step>
    <step>Create a new <b>Gameplay Ability Blueprint</b>, extending from <code>InteractionAbility_ExecuteInteraction</code>. Name it <code>GA_Interaction_Execute</code>.</step>
    <step>Create a <b>Gameplay Effect Blueprint</b> and name it <code>GE_InteractionSetup</code>. This will allow you to easily reuse the Interaction Setup across different Ability Setup assets.</step>
    <step>Open the Gameplay Effect and add a <b>Grant Gameplay Abilities</b> component.</step>
    <step>Add both Interaction Abilities to the list of granted abilities.</step>
    <step>In your <b>G.A.S. Setup</b>, add the Interaction Setup Gameplay Effect.</step>
</procedure>

## Player Input

To **start** or **interrupt** interactions, all you need to do is call the related functions in the **Interaction Manager
component**:

- `TryInitializeInteractionWithCurrentTarget`: Attempts to initialize an interaction with the target currently selected. An optional Gameplay tag can be used to specify a slot, when more than one is available.
- `TryCancelCurrentInteraction`: Attempts to cancel an ongoing interaction with a target. An optional Gameplay Tag can be used to inform the cancellation reason.

These can be invoked by players, as a result of Input Actions, or by AI agents, from Behavior or State Tree tasks. When
using [**Ninja Input**](ipt_overview.md), you can create a dedicated **Input Handler** to handle both states. The procedure 
below shows how to create that handler, but the same manager functions can be called from any input binding.

<procedure title="Create the Interaction Input Handler" collapsible="true" default-state="expanded">
    <step>
        <b>Create an Input Action</b> (e.g., <code>IA_Interact</code>).
        <ul>
            <li>Add a <b>Pressed</b> trigger.</li>
            <li><i>Optional:</i> add a <b>Released</b> trigger for hold-to-activate / cancellable interactions.</li>
        </ul>
    </step>
    <step><b>Create an Input Handler</b> that <b>extends</b> <code>NinjaInputHandler</code> (from Ninja Input), and implement <code>HandleTriggeredEvent</code>.</step>
    <step>Retrieve the <b>Interaction Manager</b> from the pawn associated with the <b>Input Manager</b>, and verify it is valid.</step>
    <step>
        <p>Branch on the incoming <b>Input Action Value</b> (convert to bool):</p>
        <ul>
            <li><code>true</code> &rarr; call <code>TryInitializeInteractionWithCurrentTarget</code></li>
            <li><code>false</code> &rarr; call <code>TryCancelCurrentInteraction</code> with reason tag <code>Interaction.Event.CancelledButtonPress</code></li>
        </ul>
    </step>
    <step>
        <p><b>Bind the handler</b> in your input setup (mapping context / action bindings) so it runs for <code>IA_Interact</code>.</p>
        <p><img src="int_integration_input_handler.png" alt="Input handler branching to start/cancel via Interaction Manager" border-effect="line" thumbnail="true"/></p>
    </step>
    <tip>
        <p><b>Boolean Value Conversion</b></p>
        <p>The conversion function is an <i>auto-cast</i> function, meaning <b>you won't be able to find it in the context menu!</b></p>
        <p>Instead, you must <b>drag</b> the Value parameter pin to the Branch's Condition parameter, to automatically create the conversion.</p>
    </tip>
</procedure>

## Next Steps
At this point, you have an **interactable actor** that can be detected by both **players** and **AI agents**, and can be
interacted with, using a dedicated Input Handler or equivalent input code.

1. The interaction target actor was configured.
2. The interaction source can register and focus targets.
3. The interaction abilities can scan and execute interactions.
4. Player input can start or cancel interactions.

From here, you can:

- Learn more about [**Interaction Targets**](int_interaction_targets.md), their assets and features. 
- Learn more about [**Interaction Sources**](int_interaction_source.md) and their features.
- Add [**Animations**](int_adv_interaction_animations.md) to your interaction State Trees. 
