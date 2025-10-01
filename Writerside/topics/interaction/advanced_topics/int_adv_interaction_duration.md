# Interaction Duration
<primary-label ref="interaction"/>
<secondary-label ref="advanced"/>

<tldr>
    <ul>
        <li>Set a non-zero <b>Duration</b> on the interaction’s <b>Interaction Behavior</b> (Smart Object) to make it <b>hold-to-activate</b> (0 = instant).</li>
        <li>In the <b>State Tree</b>, add a <b>Wait</b> state (Delay Task) bound to the Evaluator’s <b>Duration</b>, and transition when <b>ElapsedTime ≥ Duration</b>; support cancel on release.</li>
        <li>Update the actor’s <b>Interaction Prompt</b> to show a <b>progress bar</b> during the hold: use <b>Active Interaction</b> (Resolver) + <b>Interaction Summary</b> (Manual) ViewModels and bind <b>ElapsedTimePercent → Progress</b>; hide on finish/cancel.</li>
        <li>Input: <b>Pressed</b> starts the interaction; include an optional <b>Released</b> trigger to allow cancel/interrupt during the hold window.</li>
    </ul>
</tldr>

Many interactions are **hold-to-activate**: the player must press a button for a set **duration** before the interaction 
actually occurs. The Interaction System supports this pattern with minimal changes to assets you've already created—no 
new gameplay concepts required.

- **Smart Object / Interaction Behavior**  
  Set a non-zero **Duration** on the interaction's behavior so the system treats it as hold-to-activate. (Leave at `0` for instant interactions.) See [](int_interaction_targets.md).

- **State Tree**  
  Ensure the State Tree used by this interaction **gates execution by duration** (e.g., tracks progress, respects cancellation on release, and commits when the timer completes). This is the same tree referenced by your Smart Object slot configuration.

- **UI Widget (Prompt)**  
  In your prompt widget from [User Interface and ViewModels](int_ui_mvvm.md), **react to interaction state** and optionally **display progress** (e.g., a ring/bar bound to a ViewModel field) during the hold window. The prompt should also hide/rollback cleanly on cancel.

> **Input Integration**
> 
> You [already wired](int_integration_input.md) input for **Pressed** (start) and optional **Released** (cancel). With a 
> non-zero Duration, that same input flow powers hold-to-activate without additional handlers. 
{style="note"}

## Smart Object
Set a **non-zero Duration** on the interaction's **Interaction Behavior** to make it hold-to-activate. A value of `0` 
keeps the interaction **instant**.

<procedure title="Setting a Duration in the Smart Object" collapsible="true" default-state="expanded">
    <step>Open the <b>Smart Object</b> previously created for the Interaction Target and navigate </step>
    <step>In the <b>Interaction Behavior</b> configuration, set <b>Duration</b> to <code>0.8</code> seconds.</step>
    <p><img src="int_adv_target_so_duration.png" alt="Set Duration on the Interaction Behavior" border-effect="line" thumbnail="true"/></p>
</procedure>

## State Tree
For the State Tree, we need to **wait** for the interaction’s **Duration** to complete before executing the behavior.

<procedure title="Waiting for the Duration in the State Tree" collapsible="true" default-state="expanded">
    <step>Open the <b>State Tree</b> previously created and assigned to the Interaction Target.</step>
    <step>
        <p>Add a new child state (e.g., <b>Wait</b>) directly under the <b>Root</b>, and add a <b>Delay Task</b> to it. Bind the task’s <b>Duration</b> to the value exposed by the <b>Interaction State</b> evaluator.</p>
    </step>
    <step>
        In the <b>Wait</b> state, add a transition with an <b>OnTick</b> trigger to the next executable state (typically <b>Execute Interaction</b>).  
        Add a <b>Condition</b> that checks: <b>ElapsedTime</b> (from the Interaction State evaluator) <b>Greater or Equal</b> <b>Duration</b> (from the same evaluator).
    </step>
    <p><img src="int_adv_target_st_delay_node.png" alt="Wait state with Delay Task bound to Duration" border-effect="line" thumbnail="true"/></p>
</procedure>

> **Explore Other Advanced Scenarios**
>
> Handling the interaction with the State Tree allows you to create multiple dynamic interaction scenarios. For example:
> 
> - Doing something as soon as the interaction starts, before the elapsed time reaches the duration.
> - Have a task running along the wait, that broadcasts the player state to other enemies roaming the area.
>
> Feel free to explore additional state machines that cover such scenarios.
{style="note"}

## Interaction Prompt
Now update the Interaction Prompt you added on the actor in the [](int_ui_mvvm.md) page.

<procedure title="Updating the Interaction Prompt on the Actor" collapsible="true" default-state="expanded">
    <step>
        <b>Add the Active Interaction ViewModel</b> to the widget.
        Set <b>Creation Type</b> to <b>Resolver</b> and select the <b>Interaction Resolver</b>.
        <p><img src="int_adv_target_mvvm_active_interaction.png" alt="Active Interaction VM with Resolver factory" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Add the Interaction Summary ViewModel</b> to the widget.
        For this one, set <b>Creation Type</b> to <b>Manual</b> (it will use an instance provided by the Active Interaction ViewModel).
        <p><img src="int_adv_target_mvvm_summary.png" alt="Interaction Summary VM with Manual creation" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Add a Progress Bar</b> (or equivalent progress indicator) to the widget. We'll configure the binding later.
        <p><img src="int_adv_target_widget_progress_bar.png" alt="Progress Bar added to the prompt widget" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Update the Event Graph</b> to hide the Progress Bar by default.
        <p><img src="int_adv_target_widget_event_graph.png" alt="Event Graph default hides the progress bar" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Update</b> <code>SetFocusState</code> to also hide the Progress Bar when no focus is applied.
        <p><img src="int_adv_target_widget_set_focus_state.png" alt="SetFocusState hides the progress bar when idle" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Update</b> <code>SetInteractionState</code> to also hide the Progress Bar when no interaction is in progress.
        <p><img src="int_adv_target_widget_set_interaction_state.png" alt="SetInteractionState hides the progress bar when idle" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Create</b> <code>SetCurrentTarget</code>.
        This function receives the current target actor, sets the <b>active summary</b> on the widget, and shows the Progress Bar.
        <p><img src="int_adv_target_widget_set_current_target.png" alt="SetCurrentTarget updates the progress bar and bindings" border-effect="line" thumbnail="true"/></p>
    </step>
    <step>
        <b>Add bindings</b> so the widget reacts automatically:
        <ul>
            <li><code>ActiveInteraction.GetCurrentInteractionTarget</code> &rarr; <code>SetCurrentTarget</code></li>
            <li><code>InteractionSummary.GetElapsedTimePercent</code> &rarr; <code>ProgressBar.Percent</code></li>
        </ul>
        <p><img src="int_adv_target_mvvm_bindings.png" alt="Bindings for current target and elapsed percent" border-effect="line" thumbnail="true"/></p>
    </step>
</procedure>
