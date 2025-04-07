# G.A.S. Handlers
<primary-label ref="input"/>

These Input Handlers are meant to be used with the **Gameplay Ability System**, to **Activate** or **Cancel** Abilities
and **Send Gameplay Events**.

## Accessing the Ability System Component

Input Handlers related to the Gameplay Ability System can retrieve the owner's Ability System Component from the **Input
Manager**, which is a valid implementation of `AbilitySystemInterface`.

> **ASC Source**
> 
> By default, the Input Manager provides the Ability System Component assigned to the **Pawn** related to it, regardless
> if it was added to a **Controller** or a **Pawn**.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_retrieve_asc.png" alt="Retrieving the ASC" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="ipt_retrieve_asc.cpp"/>
    </tab>
</tabs>

## Activate Abilities

You can activate and interrupt Gameplay Abilities using any methods currently supported by the Gameplay Ability System:
**Class**, **Ability Tags** and **Input IDs**, each one with its respective Input Handler. However, all these Input 
Handlers operate in the same way.

- By default, they react to the `Triggered` event, usually from a `Pressed` Input Trigger. That **Activates** the ability.
- If set to **Toggle**, on a second successful `Pressed` event, the Input Handler will check if an Ability is active and, if so, **cancel** it.
-Alternatively, adding a `Released` Input Trigger also will **cancel** the ability.

Certain Event Triggers like **Tap** and **Double Tap** need a special check to determine if the actuation truly happened.

For that purpose, the `NinjaInputAbilityActivationCheck`, which handles these specific cases. You can extend this class
to handle other specific scenarios.

> **Planning Event Triggers**
>
> You can create **activate/cancel** behaviors with **one** Input Action configured with **Pressed** and **Released** Event Triggers.
>
> You can create **toggle** behaviors with **separate** Input Actions configured with a **Pressed** Event Trigger, and an Input Handler set to **toggle**.

These Input Handlers can also send a **Gameplay Event** to an ability that already has been **activated**. This is useful
to handle scenarios such as a **combo**, as implemented by the **[Combat System](cbt_combo_system.md)**.

This option is enabled by the **SendEventIfActive** property. If enabled, the following properties will become available.

| Property                | Purpose                                     |
|-------------------------|---------------------------------------------|
| ActiveEventTag          | Gameplay Tag representing the Event.        |
| Trigger Event Locally   | Triggers the Event on the **Local Client**. |
| Trigger Event On Server | Triggers the event on the **Server**.       |

The **Event Payload** will be configured like the one send from the **[Send Gameplay Event](#send-gameplay-event)** Input Handler.

## Cancel Abilities

Abilities can be **interrupted** using the same methods supported for activation, **Class**, **Ability Tags** and 
**Input IDs**.

## Target Confirmation

Gameplay Abilities can wait for the player to **Confirm** or **Cancel** a target. This requires specific functions in 
the **Ability System Component** to be called. For that, the following Input Handlers are available:

- **Ability Target Confirm**: Sends a Confirmation Input to the Ability Component.
- **Ability Target Cancel**: Sends a Cancellation Input to the Ability Component.

## Send Gameplay Event

Sends a **Gameplay Event** to the owner's **Ability System Component**. Events sent from this Input Handler will contain
the following information in their **Payload**

| Parameter       | Value                                      |
|-----------------|--------------------------------------------|
| Instigator      | Actor that triggered the Input.            |
| Target          | Actor that triggered the Input.            |
| EventTag        | Gameplay Tag provided to the Handler.      |
| Event Magnitude | Magnitude of the Input Value.              |
| Optional Object | The Input Action that triggered the event. |