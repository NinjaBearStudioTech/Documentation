# Combos and AI Agents
<primary-label ref="combat"/>
<secondary-label ref="beta"/>

The **Combo Ability** can be used by AI agents via **Behavior Trees** or **State Trees**.

In both cases, the agent listens to the **Combo Manager’s delegate** indicating when the **Combo Window** is open. Once the window opens, the AI sends an input to advance the combo, either via a **Gameplay Tag** or an **Input Action**.

## Behavior Trees
Combos can be advanced in **Behavior Trees** using the provided `Advance Combo Service`.

<procedure title="Advancing Combos using Behavior Trees" collapsible="true" default-state="expanded">
    <step>Add a <b>Task Node</b> to activate the <b>Combo Ability</b>.</step>
    <step>Add the <b>Advance Combo Service</b> to the same Task Node. Configure it by providing the <b>Event Tag</b> or <b>Input Action</b> used to advance the combo.</step>
</procedure>

By default, the service uses a fixed event or input, but you can override its behavior by implementing:

- `GetComboInputAction`: Return a pre-defined or dynamic Input Action for branching.
- `GetComboGameplayTag`: Return a pre-defined or dynamic Gameplay Tag for branching.

## State Trees
Combos can be advanced in **State Trees** using the `Advance Combo Task`.

<procedure title="Advancing Combos using State Trees" collapsible="true" default-state="expanded">
    <step>Add a <b>State Node</b> that activates the <b>Combo Ability</b>.</step>
    <step>Add a <b>Child State</b> containing the <b>Advance Combo Task</b>. Configure it with a fixed <b>Event Tag</b> or <b>Input Action</b>.</step>
</procedure>

As with Behavior Trees, the task uses static values by default, but can be extended via:

- `GetComboInputAction`
- `GetComboGameplayTag`

This allows branching or other dynamic behavior based on runtime data.
