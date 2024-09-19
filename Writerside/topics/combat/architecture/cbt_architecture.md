# Architecture
<primary-label ref="combat"/>

This section includes **deep dive** on important **technical aspects** of the Combat System.

**[Components and Extensions](cbt_component_extensions.md)**
: The Combat System uses multiple **components** to modularize its functionality, which is defined by many **interfaces**.
This section will guide you through these elements, their roles, and how to extend them.

**[Weapon Architecture](cbt_weapon_architecture.md)**
: The Weapon Manager and Weapon Actor are two of the most important elements in the Combat System. This topic will 
walk you through these, and related objects, so you can extend and integrate them with other systems.

**[Character Animation](cbt_character_animation.md)**
: The Combat System provides and uses multiple animation elements in its implementation. This topic will cover them,
and provide details on how they can be used to connect the Combat System to Animation Systems.

**[Movement Component](cbt_movement_component.md)**
: Abilities such as the **Target Lock** or **Blocking** are usually tied to changes in the Movement Component, such as
alternating between "Strafing" and "Forward-Facing" movement, or changing the current maximum speed.

**[Actor Pooling](cbt_actor_pooling.md)**
: The Actor Pool Manager enables reusing actors such as Projectiles and Targeting Actors, so your project can save 
performance by reducing the cost of frequently spawning and destroying actors.

**[User Interface](cbt_user_interface.md)**
: The Combat System manages key information, including 'vitals', 'damage', and other status effects. UMG Viewmodels
are available to expose such information to your user interface.
