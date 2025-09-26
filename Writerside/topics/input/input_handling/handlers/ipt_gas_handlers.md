# G.A.S. Handlers
<primary-label ref="input"/>

These Input Handlers are designed to work with the **Gameplay Ability System (GAS)**.

## Accessing the Ability System Component
Input Handlers related to GAS can retrieve the owner's Ability System Component (ASC) via the **Input Manager**, which 
implements `AbilitySystemInterface`.

> **ASC Source**
>
> By default, the Input Manager provides the ASC assigned to the **Pawn** associated with it, even if the manager is added to a **Controller** or a **Pawn**.
{style="note"}

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_retrieve_asc.png" alt="Retrieving the ASC" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="ipt_retrieve_asc.cpp"/>
    </tab>
</tabs>

## Ability Activation
Gameplay Abilities can be activated using any of the standard GAS mechanisms: **Class**, **Ability Tags**, or **Input IDs**. 
Each method has a corresponding Input Handler, but all operate under the same behavior model:

- On a **Pressed** Input Trigger, the ability will activate.
- If the ability is **Momentary**, it will be cancelled when a **Released** trigger is received.
- If the ability is **Toggled**, a second **Pressed** trigger will cancel the ability.

Some triggers, such as **Tap** and **Double Tap**, require more nuanced handling to detect the intended behavior. For 
those cases, use the `NinjaInputAbilityActivationCheck` class, which you can subclass to define custom logic.

### Toggled and Momentary Tags
All Ability Activation Handlers automatically detect the following tags on the activating ability:

- `Input.Ability.Momentary`: Activates the ability when a **Pressed Trigger** fires, and ends the ability when a **Released Trigger** fires.
- `Input.Ability.Toggled`: Activates the ability when a **Pressed Trigger** fires, and ends the ability when another **Pressed Trigger** fires, if the ability is still active.

### Sending Events to Active Abilities
All Ability Activation Handlers optionally support sending a **Gameplay Event** to an **already active** ability. This 
feature is controlled via the **SendEventIfActive** property. If enabled, the following properties are used:

| Property                | Purpose                                      |
|-------------------------|----------------------------------------------|
| ActiveEventTag          | Gameplay Tag representing the event.         |
| Trigger Event Locally   | Triggers the event on the **local client**.  |
| Trigger Event On Server | Triggers the event on the **server**.        |

The payload follows the same structure used in the **[Send Gameplay Event](#send-gameplay-event)** Input Handler.

## Ability Interruption
Abilities can be **interrupted** using the same methods as activation: **Class**, **Ability Tags**, and **Input IDs**.

For conditional interruption, these handlers expose a `CanCancelAbility` function, called on each cancellation attempt. 
Returning `true` will allow the ability to be cancelled.

## Target Confirmation
Some abilities may wait for the player to **Confirm** or **Cancel** a target. GAS exposes specific functions for this 
purpose, and the following Input Handlers support it:

- **Ability Target Confirm**: Sends a **Confirm** signal to the Ability Component.
- **Ability Target Cancel**: Sends a **Cancel** signal to the Ability Component.

## Send Gameplay Event
This Input Handler sends a **Gameplay Event** to the owner's ASC. The payload contains the following parameters:

| Parameter       | Value                                      |
|-----------------|--------------------------------------------|
| Instigator      | Actor that triggered the input.            |
| Target          | Actor that triggered the input.            |
| EventTag        | Gameplay Tag configured on the handler.    |
| Event Magnitude | Magnitude of the input value.              |
| Optional Object | The Input Action that triggered the event. |
