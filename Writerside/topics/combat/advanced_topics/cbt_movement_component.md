# Movement Component
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

Certain features in the Combat System may affect the **character movement**. For that integration, Ninja Combat provides 
its own **optional** version of the **Character Movement Component**.

## Combat Movement Component
The **Combat Movement Component** is an **optional** Movement Component that **extends** `CharacterMovementComponent`. 

This component implements the `ICombatMovementManagerInterface`, adding the following functionalities:

1. Handling important events in the Combat System that may affect **movement settings**. Currently, this means setting the "walk speed" when the character is **blocking**, and setting "strafing" or "input direction" movement modes when the character is **locked on a target**. 
2. Exposing appropriate **setters** for properties that might need to be changed during runtime.

As detailed in the [Setup page](cbt_combat_system.md#combat-movement-component), you can add the Combat Component to your Character using **Blueprints** or **C++**.

## Other Movement Systems
Even though the Movement Component is only accessed via its **interface**, the Combat System still indirectly relies on
an implementation of the **Character Movement Component**, since the Gameplay Ability System and the Contextual Animation
System are directly integrated with it.

### Gameplay Ability System
This module is the foundation of the Combat System. Its core component manages predicted Root Motion from Gameplay Abilities
and this is done in conjunction with the Character Movement Component.

This functionality is deep inside the Ability System Component in a method that is not marked as virtual. Even though
this framework is production ready, it might see changes to this behavior (or this behavior may not be necessary), when
the new Movement Framework in Unreal engine, **Mover 2.0** becomes more popular.

### Contextual Animation System
This module is used by the [](cbt_opportunity_attacks.md) to execute **Paired Animations**. Its core
component integrates with the Character Movement Component to modify certain settings and then to revert them later.

For now, the methods doing that are not virtual so there's no way to modify that behavior, so it can use a different type
of Movement Framework. However, the component always checks for a valid Movement Component, so you can still transfer
that functionality to another location. 

It is important to mention that the system is still new and marked as **experimental** so that will hopefully change in
the future, especially with the new Movement Framework in Unreal Engine, **Mover 2.0**.
