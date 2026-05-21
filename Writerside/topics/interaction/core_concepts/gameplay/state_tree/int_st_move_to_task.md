# Player Move To Task
<primary-label ref="interaction"/>

Moves the **player** to an Interaction Point, using a **Path Following request**.

This task expects the incoming Player Controller to own a `PathFollowingComponent`, similar to what an AIController provides 
internally. This allows the player character to follow **NavMesh paths** without controller swapping or AI possession.

While active, movement and rotation are owned by the interaction logic, enabling controlled strafing and facing toward the 
interaction target until the destination is reached or the task is aborted.

For AI agents, the equivalent behavior should use the standard StateTree Move task (AI Move), which already integrates 
with AIControllers and path following.


| Property          | Type  | Description                              |
|-------------------|-------|------------------------------------------|
| Player Controller | Input | Player controller that will be moved.    |
| Target Location   | Input | Target location to to move to.           |
| Acceptance Radius | Input | Acceptance radius for arrival.           |
| Can Strafe        | Input | Allow strafing while following the path. |

> You can access the **Player Controller** and **Player Pawn** assigned to the Interaction Manager through the 
> [**Player Context Evaluator**](int_st_player_context_evaluator.md).
{style=note}