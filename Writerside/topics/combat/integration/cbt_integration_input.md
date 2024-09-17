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

## Disable Input

Some Gameplay Abilities will automatically add tags to their avatar that are recognized by **Ninja Input**.

The **Opportunity Attack Ability** adds tags to its owner that, by default, disables inputs for **movement** and **camera**.
This is done since the Opportunity Attack is expected to take control over both the character's movement and camera. 

The **Target Lock Ability** adds tags to its owner that, by default, disables inputs for the **camera**. This is done
since the Target Lock is expected to always focus on the current target, so the camera must be locked, at least on the 
**yaw** axis.

## Input Buffer

Ninja Input also provides an **[Animation-Based Input Buffer](ipt_input_buffer.md)**, a common requirement for certain 
Combat Systems. This can allow some interesting things, such as _buffering an Attack Input, while the character is 
performing an evade_, or vice-versa.

## Forward Reference

In some cases, the Input System may require a **Forward Reference** that always points forward. If you had to create one
for your game, it can be reused by the Combat System, which always has this requirement.

To reuse your Forward Reference from the Input System, you can simply add the `Combat.Component.ForwardReference` tag
to the **Arrow Component**, or you can return this Arrow Component in the `GetCombatForwardReference` function, from 
the **Combat System Interface**.