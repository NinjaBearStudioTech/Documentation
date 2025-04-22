# Input Integration
<primary-label ref="combat"/>

There is no direct integration between **Ninja Combat** and **Ninja Input**. However, there are some synergies worth
knowing, between both systems.

## Combo Inputs

First, **Ninja Input** greatly simplifies [activating **Gameplay Abilities** and sending **Gameplay Events**](ipt_gas_handlers.md),
including the option to send Gameplay Events if an Ability is already active, which is very useful for the Combo System.

The **[](cbt_combos.md)** uses **Gameplay Events** to advance the ongoing combo and in some scenarios,
it may also require the Input Action to be provided as one of the Payload's **Optional Objects**.

You have two ways to implement this using Ninja Input.

### Single Input Handler

You can use an Ability Activation Input Handler and enable the option to **Send Gameplay Events if Active**. This checks 
if the Gameplay Ability being activated is already active, and if so, sends a Gameplay Event instead.

<img src="cbt_integration_input_combo_01.png" alt="Single Input Handler" thumbnail="true"/>

This is a good approach if your Input Handler directly activates the Combo Ability.

### Two Input Handlers

Alternatively, you can use an Ability Activation Input Handler and a Send Gameplay Event handler. The first one is used
to activate the Ability and the second one is used to send Gameplay Events.

<img src="cbt_integration_input_combo_02a.png" alt="Activation Input Handler" thumbnail="true"/>

<img src="cbt_integration_input_combo_02b.png" alt="Event Input Handler" thumbnail="true"/>

This is a good approach if you are using the Opportunity Attack and then a combo as a fallback, or others scenarios 
where the main ability cannot know for sure if the Combo Ability is Active.

> **Event Handlers in Other Keys**
> 
> You can also add Event Handlers to other keys, when your combo supports multiple inputs. For example, sending a
> Gameplay Event with the same button as the Secondary Attack.

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