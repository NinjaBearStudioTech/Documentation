# Architecture
<primary-label ref="combat"/>

This section includes **deep dive** on important **technical aspects** of the Combat System.

**[](cbt_component_extensions.md)**
: The Combat System uses multiple **components** to modularize its functionality, which is defined by many **interfaces**.
This section will guide you through these elements, their roles, and how to extend them.

**[](cbt_weapon_architecture.md)**
: The Weapon Manager and Weapon Actor are two of the most important elements in the Combat System. This topic will 
walk you through these, and related objects, so you can extend and integrate them with other systems.

**[](cbt_character_animation.md)**
: The Combat System provides and uses multiple animation elements in its implementation. This topic will cover them,
and provide details on how they can be used to connect the Combat System to Animation Systems.

**[](cbt_movement_component.md)**
: Abilities such as the **Target Lock** or **Blocking** are usually tied to changes in the Movement Component, such as
alternating between "Strafing" and "Forward-Facing" movement, or changing the current maximum speed.

**[](cbt_actor_pooling.md)**
: The Actor Pool Manager enables reusing actors such as Projectiles and Targeting Actors, so your project can save 
performance by reducing the cost of frequently spawning and destroying actors.

**[](cbt_user_interface.md)**
: The Combat System manages key information, including 'vitals', 'damage', and other status effects. UMG Viewmodels
are available to expose such information to your user interface.

**[](cbt_targeting_system.md)**
: The Combat System vastly utilizes the **Gameplay Targeting System**. There are multiple new **Targeting Tasks** that
were introduced by this plugin, that can be used in **Targeting Presets**.

**[](cbt_motion_warping.md)**
: The system uses **Motion Warping** to properly adjust attack animations, and potentially others, so the animations 
will position and rotate their owners based on their given targets.

**[](cbt_artificial_intelligence.md)**
: The Combat System contains utility elements for AI Agents. These elements are built for both Artificial Intelligence
frameworks in Unreal Engine - **Behavior Trees** and **State Trees**.
