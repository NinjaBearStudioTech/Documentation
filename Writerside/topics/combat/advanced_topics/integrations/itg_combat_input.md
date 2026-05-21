# Input Integration
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li><b>Ninja Input</b> integrates with Ninja Combat to simplify combat input wiring and combo flows.</li>
        <li>Use built-in <b>GAS handlers</b> for straightforward activations (e.g., attacks, casts) and <b>combat handlers</b> for Combo Input nuances.</li>
        <li>Certain abilities auto-apply <b>control tags</b> that temporarily disable <b>movement</b> and/or <b>camera</b> input (e.g., <i>Opportunity Attack</i> disables both; <i>Target Lock</i> locks camera yaw by default).</li>
        <li>The <b>animation-based input buffer</b> lets players queue inputs (e.g., buffer an attack during an evade).</li>
        <li>Reuse your Input System's <b>Forward Reference</b> by tagging its Arrow Component <code>Combat.Component.ForwardReference</code> or implementing <code>GetCombatForwardReference</code>.</li>
    </ul>
</tldr>

[**Ninja Input**](ipt_overview.md) provides functionalities and synergies that simplify coding input for your combat system.

## Combo Inputs

On top of the multiple [**GAS-related handlers**](ipt_gas_handlers.md) available in Ninja Input for straightforward activations
(such as common attacks and casts), you’ll also find other [**combat-related handlers**](ipt_combat_handlers.md) designed for
Ninja Combat—specifically, to handle nuances of the [**Combo Input**](cbt_combos_input.md).

## Disable Input

Some Gameplay Abilities automatically add tags to their avatar that are recognized by **Ninja Input**.

The **Opportunity Attack Ability** adds tags to its owner that, by default, disable input for **movement** and **camera**.
This is because the opportunity attack is expected to take control over both the character’s movement and camera.

The **Target Lock Ability** adds tags to its owner that, by default, disable input for the **camera**. This is done since
Target Lock should keep focus on the current target, so the camera must be locked—at least on the **yaw** axis.

## Input Buffer

Ninja Input also provides an **[Animation-Based Input Buffer](ipt_input_buffer.md)**, a common requirement for certain
combat systems. This enables behaviors such as buffering an **attack** input while the character is performing an **evade**
(or vice versa).

## Forward Reference

In some cases, the input system requires a **Forward Reference** that always points forward. If you already have one in
your game, it can be reused by the combat system, which has the same requirement.

To reuse your Forward Reference from the input system, either add the `Combat.Component.ForwardReference` tag to the
**Arrow Component**, or return that Arrow Component in `GetCombatForwardReference` from the **Combat System Interface**.
