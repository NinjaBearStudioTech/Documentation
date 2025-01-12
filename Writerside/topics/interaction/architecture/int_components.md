# Interaction Manager
<primary-label ref="interaction"/>

The **Interaction Manager** captures and stores available **Interaction Targets** for a pawn or character. Once captured, 
these targets can be **focused**, making them eligible for the **Interaction Flow**.

## Collision Components

The component must be present in every Pawn or Character that interacts with world elements. By default, it collects 
**Interaction Targets** using **Collision Components** attached to the owner. These components are identified via the 
Gameplay Tag: `Interaction.Component.InteractableScan`.

> **Interaction Channel**  
> It is recommended to use dedicated trace and object channels for Interaction Actors. For detailed setup instructions, 
> see the [](int_setup.md) page.  
{style="note"}

The collision configuration is very important as it ensures that the Interaction Manager will detect Interaction Targets!
Following the Collision Setup from the [](int_setup.md) page, this is how you would configure your collision presets.

### Scan Component

The Collision Component in the **Interaction Source**, known as **Collision Scan**, should be set as an `InteractionObject`,
**ignore** the `InteractionScan` channel and **overlap** `InteractionObject`. Only **Query Collisions** should be enabled. 

<img src="int_manager_collision_setup_scan.png" alt="Scan Collision Setup" thumbnail="true" border-effect="line"/>

As for **Interaction Targets**, they should also have a dedicated Collision Component set as `InteractionObject`, **block** 
both `InteractionScan` and `InteractionObject`. Only **Query Collisions** should be enabled.

<img src="int_manager_collision_setup_target.png" alt="Target Collision Setup" thumbnail="true" border-effect="line"/>

### Target Focus

Once interactable targets are identified, they are made available to the **Ability System**. This allows players to 
**focus** on targets using methods such as:

- **By distance**: Automatically selects the nearest target.
- **By camera**: Focuses on the target in the player’s line of sight.
- **Direct interaction**: Interact without needing to focus on a specific target.

These options are explored in greater detail on the [](int_abilities.md) page.

## Replication

The Interaction Manager is also responsible for replicating available actors. However, replication is **server-to-owning-client only**:

- The **owning client** receives updates about available interaction targets.
- **Simulated proxies** (non-owning clients) do not receive these updates.

This ensures efficient network usage while maintaining synchronization for the player initiating the interactions.

## Interaction Events

The Interaction Manager can notify other systems by broadcasting actors via **Multicast Delegates**. These delegates 
allow seamless integration with other systems that need to respond to interaction changes.

- `OnInteractableActorFound`: Notifies subscribers when new Interaction Actors are found.
- `OnInteractableActorLost`: Notifies subscribers when Interaction Actors are no longer available.
