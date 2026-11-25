# Movement Modes and Patrol Paths
<primary-label ref="bot"/>

A route tells a guard **where to go**. Its movement mode tells it **how to get there**. A guard can walk from post to post, run after the player, then walk again when it resumes its patrol.

## Choose Walking and Running Speeds

Give each movement mode a gameplay tag. In a **Bot Movement Adapter**, map each tag to the settings your character uses. The supplied Character Movement adapter works with Unreal's Character Movement Component. Assign the adapter to the Bot Setup and use **Set Movement** in either tree before the move task.

## Lay Out a Route

Place patrol point actors on navigable ground. Set **Next Patrol Point** on each one and link the last back to the first to make a loop. Give points on the same route a common tag so a guard can find its starting point. Once it has joined the route, it follows the links.

A point can also supply a behavior. For example, put a search at the lookout and a short wait at the gate. The tree moves to the point, runs the activity, then calls **Advance Patrol Point**.

[Set walking and running speeds](bot_guide_01_movement_profile.md) or [build a patrol route](bot_guide_04_create_patrols.md).

## Connect Your Own Movement System

Create a Blueprint or C++ subclass of `UNinjaBotMovementAdapter` and override **Set Movement** (`SetMovement`). Use the requested tag to apply a gait to the controller's pawn. For example, map **AI.Movement.Running** to the jog setting in your locomotion system. After applying the change, call `NotifyMovementChanged` and return true. Assign the adapter as the **Movement Mode Adapter Class** in Bot Setup.

To listen on the pawn or controller, implement **Bot Movement Watcher Interface** and handle `HandleBotMovementChanged`. The event supplies the accepted tag and the adapter, so you can update the character's animation gait when the mode changes.
