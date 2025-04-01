# Targeting System
<primary-label ref="combat"/>

The Combat System vastly utilizes the **Gameplay Targeting System**. There are multiple new **Targeting Tasks** that
were introduced by this plugin, that can be used in **Targeting Presets**.

## Selection Tasks

| Targeting Task | Description                                                                               |
|----------------|-------------------------------------------------------------------------------------------|
| Camera         | Selects the actor at the center of the camera, ignoring the owner and any attached actor. |
| Current Target | Selects the target currently selected by the Target Lock system.                          |

## Filter Tasks

| Targeting Task | Description                                                              |
|----------------|--------------------------------------------------------------------------|
| Dead           | Filters targets that are dead.                                           |
| Distance       | Filters targets based on their distance from the owner.                  |
| Facing         | Filters targets based on their facing angle towards the owner.           |
| Health         | Filters targets based on their health.                                   |
| Projectile Hit | Filters targets that have not been hit by a projectile owner.            |
| Target Lock    | Filters targets that are not currently locked by the Target Lock system. |
