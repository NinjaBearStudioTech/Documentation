# Input Integration
<primary-label ref="combat"/>

There is no direct integration between **Ninja Combat** and **Ninja Input**. However, there are some synergies worth
knowing, between both systems.

## Combo Inputs

First, **Ninja Input** greatly simplifies [activating **Gameplay Abilities** and sending **Gameplay Events**](ipt_gas_handlers.md),
including the option to send Gameplay Events if an Ability is already active, which is very useful for the Combo System.

The **[Combo System](cbt_combo_system.md)** uses **Gameplay Events** to advance the ongoing combo. It requires the Input
Action to be provided as one of the Payload's **Optional Objects**, so it can determine the appropriate combo branch.

This entire setup, along with all payload requirements, is implemented by default on Ninja Input, so no additional 
input handling code is required.

## Input Buffer

Ninja Input also provides an **[Animation-Based Input Buffer](ipt_input_buffer.md)**, a common requirement for certain 
Combat Systems. This can allow some interesting things, such as _buffering an Attack Input, while the character is 
performing an evade_, or vice-versa.