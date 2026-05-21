# Interaction State Tree
<primary-label ref="interaction"/>

The **Interaction State Tree** is provided by **Interaction Targets** and used by the **Interaction Source**. It defines 
all steps that occur during an interaction once it is activated.

By defining interaction steps in a State Tree, you can support very different interaction flows without writing custom 
code for each case. For example, in the same game you can have:

1. A _chest_ that moves the player to a specific position, plays an Animation Montage, and then triggers the interaction on the chest actor.
2. A _door_ that removes a key from the player's inventory, configures IK for the door handle in the player animation, and plays an Animation Montage.
3. A _switch_ that checks the world state (for example, whether power is enabled) and, if so, finds a lift actor and moves it to the current level.

Interaction State Trees must always be created using the `NinjaInteractionComponentSchema`. 

## State Tree Design

You can use the State Tree elements provided by the Interaction System or implement your own. **Keep the following design 
considerations in mind**:

1. At some point, the Interaction Tree must execute the **Interaction Behavior**, usually using the [**Trigger Behavior Task**](int_st_trigger_behavior_task.md).
2. When the interaction starts, the Interaction Tree is activated. You can track elapsed time within the tree itself and trigger the behavior once the **elapsed time** reaches the **desired duration**. Do not rely on input actions configured with a "Hold" trigger for this purpose.
3. Ensure that all states eventually **terminate the Interaction Tree execution**.
4. On failures, you should always release the handle, usually using the [**Release Handle Task**](int_st_release_handle_task.md).

## Default State Trees

Ninja Interaction provides two default Interaction Trees for common interaction patterns:

| Interaction Tree | Description                                                                                  |
|------------------|----------------------------------------------------------------------------------------------|
| Generic          | Tracks accumulated time (if enabled) and triggers the interaction behavior.                  |
| Animation        | Similar to Generic, but triggers an Animation Montage event as part of the interaction flow. |
