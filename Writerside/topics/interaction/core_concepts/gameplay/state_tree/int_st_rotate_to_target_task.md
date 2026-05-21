# Rotate to Target Task
<primary-label ref="interaction"/>

Continuously **rotates a pawn toward a target location** while the task is active.

If the pawn uses controller yaw, the controller rotation is updated. Otherwise, the pawn actor rotation is updated directly. 
**Rotation mode is restored on exit**.

This task alone **never finishes the state**, and it's mostly meant to use in conjunction with the [**Player Move task**](int_st_move_to_task.md), 
which should finish the state when the target is reached.

For AI, you just need to use the default AI Move To and the Controller Focus.

| Property                             | Type      | Description                                                                     |
|--------------------------------------|-----------|---------------------------------------------------------------------------------|
| Player Controller                    | Input     | Player controller owning the pawn.                                              |
| Target Location                      | Input     | World-space location to face.                                                   |
| Rotation Speed Degrees Per Second    | Parameter | Rotation speed in degrees per second.                                           |
| Use Controller Rotation If Available | Parameter | Prefer rotating controller, if the pawn is set to rotate to its controller yaw. |