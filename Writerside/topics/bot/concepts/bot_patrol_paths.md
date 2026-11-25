# Patrol Paths
<primary-label ref="bot"/>

A patrol route is a chain of points placed in the level. [Movement Modes and Patrol Paths](bot_movement_modes.md) explains 
how the guard follows the route. To create one with a special activity at a stop, follow [Build a Patrol Route](bot_guide_04_create_patrols.md).

## Smart Objects Integration

Patrol Points are implemented as **lightweight target point actors** rather than Smart Objects. This design choice prioritizes
simplicity and avoids the complexity of slot ownership and reservation during early design. 

If a project requires **Smart Object integration or Gameplay Behaviors**, Patrol Points can be extended by **attaching the 
appropriate Smart Object components** and interacting with them as usual.