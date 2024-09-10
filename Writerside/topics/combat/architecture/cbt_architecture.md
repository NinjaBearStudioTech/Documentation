# Architecture
<primary-label ref="combat"/>

This section includes **deep dive** on important **technical aspects** of the Combat System.

**[Components and Extensions](cbt_component_extensions.md)**
: The Combat System uses multiple **components** to modularize its functionality, which is defined by many **interfaces**.
This section will guide you through these elements, their roles, and how to extend them.

**[Weapon Architecture](cbt_weapon_architecture.md)**
: The Weapon Manager and Weapon Actor are two of the most important elements in the Combat System. This topic will 
walk you through these, and related objects, so you can extend and integrate them with other systems.

**[Actor Pooling](cbt_actor_pooling.md)**
: The Actor Pool Manager enables reusing actors such as Projectiles and Targeting Actors, so your project can save 
performance by reducing the cost of frequently spawning and destroying actors.

**[User Interface](cbt_user_interface.md)**
: The Combat System manages key information, including 'vitals', 'damage', and other status effects. UMG View Models
are available to expose such information to your user interface.
