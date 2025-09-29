# Interaction Duration
<primary-label ref="interaction"/>
<secondary-label ref="advanced"/>

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
_soon_