# UMG ViewModels
<primary-label ref="interaction"/>

## Introduction
The **ViewModel layer** is the bridge between **backend interaction data** and your **UMG widgets**.

In the Interaction System, ViewModels observe the live interaction state and expose it as **UI-friendly fields** so
prompts and HUD elements can update reactively without hard-wiring gameplay logic into widgets.

## Backend Data
The backend exposes the current **Interaction State**, which ViewModels present from two complementary **information perspectives**:

- **Interaction Source**: Represents the **instigator** (player or AI) and its relationship to nearby targets.
- **Interaction Target**: Represents data from the **target**, and the current state of its possible interactions. 

> **Perspectives are not Implementation**  
> 
> These perspectives are about **what viewpoint the data represents**.
> 
> They are **independent** from how or where you render the prompt. You can explore both perspectives, regardless if 
> your widget is added to the player HUD or attached to the interaction actor.
{style="note"}

## Actor Prompts
Actor prompts are placed on the **Interaction Target** actor using the `UNinjaInteractionWidgetComponent`.

> **Widget Component Subclass**
> 
> You can also use a component subclass or create your own version, compatible with ViewModels that implement 
> `IInteractionViewHostAwareInterface`, providing the component's owner as the host.

Starting with the simplest possible widget, the steps below show how to build an interaction prompt that reacts to 
**focus** and **interaction** state using the **Interaction Target ViewModel**.

<procedure title="Creating a simple Interaction Prompt" collapsible="true" default-state="expanded">
    <step><b>Create a widget</b> extending from your preferred base (e.g., <i>User Widget</i> or <i>Common User Widget</i>).</step>
    <step><b>Design a minimal "Interact Prompt".</b> This widget will be shown when <b>focus</b> is applied to the actor.</step>
    <step>
        <b>Implement</b> <code>SetFocusState</code>, receiving the <code>TargetFocusState</code> enum. Set the widget's visibility based on the enum:
        <ul>
            <li><b>None</b>, <b>Eligible</b> &rarr; <code>Collapsed</code></li>
            <li><b>Focused</b> &rarr; <code>Not Hit-Testable (Self & All Children)</code></li>
        </ul>
        <p><img src="int_ui_widget_target_set_focus_state.png" alt="SetFocusState implementation" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Implement</b> <code>SetInteractionState</code>, receiving the <code>TargetIInteractionState</code> enum. Set the widget’s visibility based on the enum:
        <ul>
            <li><b>None</b>, <b>Commited</b>, <b>Finished</b>, <b>Cancelled</b> &rarr; <code>Collapsed</code></li>
            <li><b>Started</b> &rarr; <code>Not Hit-Testable (Self & All Children)</code></li>
        </ul>
        <p><img src="int_ui_widget_target_set_interaction_state.png" alt="SetInteractionState implementation" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Add the Interaction Target ViewModel</b> to the widget. Set its <b>Creation Type</b> to <b>Resolver</b> and select the <b>Interaction Resolver</b> as the factory class.
        <p><img src="int_ui_mvvm_target_and_resolver.png" alt="Add Target VM and Resolver" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Bind</b> the ViewModel's fields to your functions so the widget reacts to state changes:
        <ul>
            <li>Bind the <b>focus</b> state to <code>SetFocusState</code></li>
            <li>Bind the <b>interaction</b> state to <code>SetInteractionState</code></li>
        </ul>
        <p><img src="int_ui_mvvm_target_bindings.png" alt="Bindings to SetFocusState and SetInteractionState" border-effect="line" thumbnail="true"/></p>
    </step>
    <note>
        <p>You can enhance the prompt with subtle animations (e.g., fading via <i>Render Opacity</i>) and pre-focus hints (e.g., using a <b>Registered</b> property on the ViewModel) to signal availability before focus is applied.</p>
    </note>
</procedure>

With the widget ready, assign it to your Interaction Target:

<procedure title="Setting the Interaction Prompt to the Target" collapsible="true" default-state="expanded">
    <step>
        <b>Add</b> <code>UNinjaInteractionWidgetComponent</code> to the Interaction Target and position it in the scene as needed.
    </step>
    <step>
        <b>Assign</b> your prompt widget to the component. Enable <b>Draw at Desired Size</b> for pixel-perfect sizing.
        <p><img src="int_ui_widget_component_on_target.png" alt="Widget Component on Interaction Target" border-effect="line" thumbnail="true"/></p>
    </step>
</procedure>

## HUD Prompts