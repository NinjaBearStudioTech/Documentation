# Interaction Manager
<primary-label ref="interaction"/>

The **Interaction Manager** captures and stores available **Interaction Targets** for a pawn or character. Once captured, 
these targets can be **focused**, making them eligible for **Interaction Flow**. 

## Collision Components

One or more collision components must be present in every Pawn or Character that interacts with world elements. They are 
identified via the Gameplay Tag: `Interaction.Component.InteractableScan`.

### Collision Setup

Proper collision configuration ensures the **Interaction Manager** detects **Interaction Targets**. Follow the instructions 
in the [](int_setup.md) page or use another setup appropriate for your project.

> **Interaction Channel**
>
> It is recommended to have dedicated **Collision Presets**, with appropriate collision responses, for all participants 
> in the interaction flow. For more information, see the [](int_setup.md) page.  
{style="note"}

There are two roles involved in the collision system:

- **Interaction Scan Collision**: One or more Collision Components attached to the Interaction Manager's owner, responsible for scanning and detecting interactable targets within their range.
- **Interaction Target Collision**: A Collision Component attached to Interactable Actors. Enables interactable actors to be detected by the scan.

You should have a proper **Collision Preset** for each one of these roles. Collision Presets provide a predefined set of 
collision responses, simplifying configuration and ensuring consistent behavior across all components.

#### Interaction Scan Collision

Configure all Interaction Scan Collision components so they use the **Interaction Source** preset, created during the initial setup.

<img src="int_manager_collision_setup_scan.png" alt="Scan Collision Setup" thumbnail="true" border-effect="line"/>

> **Identify Collision Scans**
>
> Ensure Collision Components related to the Interaction Manager are identified by the correct **Component Tag**, 
> `Interaction.Component.InteractableScan`
{style="note"}

#### Interaction Target Collision

Configure all Interaction Target Collision components so they use the **Interaction Target** preset, created during the initial setup.

<img src="int_manager_collision_setup_target.png" alt="Target Collision Setup" thumbnail="true" border-effect="line"/>

## Target Focus

Once interactable targets are identified, they are made available to the **Ability System**. This allows players to 
**focus** on targets using methods such as:

- **By distance**: Automatically selects the nearest target.
- **By camera**: Focuses on the target in the player’s line of sight.
- **Direct interaction**: Interact without needing to focus on a specific target.

These options are explored in greater detail on the [](int_abilities.md) page.

## Replication

The Interaction Manager is also responsible for replicating available actors. However, replication is **server-to-owning-client only**.
As a result, non-owning clients cannot detect interaction targets without additional replication logic.

- **Server-to-Owning Client Replication:** Updates about interaction targets are sent only to the owning client.
- **Simulated Proxies:** These clients do not receive updates unless additional logic is implemented.

This ensures efficient network usage while maintaining synchronization for the player initiating the interactions.

## Interaction Events

The Interaction Manager can notify other systems by broadcasting actors via **Multicast Delegates**. These delegates 
allow seamless integration with other systems that need to respond to interaction changes.

- `OnInteractableActorFound`:  Triggers when the Interaction Manager detects a new interactable target.
- `OnInteractableActorLost`: Triggers when a previously detected interactable target is no longer available.
- `OnFocusApplied`: Triggers when an actor has received focus from this component.
- `OnFocusRemoved`: Triggers when an actor has lost focus from this component.

> **Events and Networking**
>
> The events are broadcast in both **Authoritative** and the **Owning Client**. **Simulated clients** will not receive these events!
{style="note"}