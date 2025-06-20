# Components and Extensions
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

The Combat System has multiple parts represented by **interfaces**. This design allows developers to replace parts of 
the system, by replacing components with their own functionality.

The only component that cannot be swapped by interface level is the **Combat Component**, since it is the backbone of 
the Combat System. Still, it provides many extension points as virtual/overridable **functions**.

The following table shows all components that can be swapped on interface level.

| Interface                    | Implementation               | Factory Method                     |
|------------------------------|------------------------------|------------------------------------|
| `ComboManagerInterface`      | `ComboManagerComponent`      | `CreateComboManagerComponent`      |
| `DamageManagerInterface`     | Base Combat Manager          | `CreateDamageManagerComponent`     |
| `DefenseManagerInterface`    | Base Combat Manager          | `CreateDefenseManagerComponent`    |
| `DissolveManagerInterface`   | `DissolveComponent`          | `GetAndCacheDissolveManager`       |
| `MotionWarpingInterface`     | `MotionWarpingComponent`     | `CreateMotionWarpingComponent`     |
| `MovementManagerInterface`   | `CharacterMovementComponent` | N/A                                |
| `PhysicalAnimationInterface` | `PhysicalAnimationComponent` | `CreatePhysicalAnimationComponent` |
| `TargetManagerInterface`     | Base Combat Manager          | `CreateTargetManagerComponent`     |
| `WeaponManagerInterface`     | `WeaponManagerComponent`     | `GetAndCacheWeaponManager`         |

## The Combat Manager Component

The Combat Manager Component is the main component in the system. It does not have its own interface, since it's always
expected to be present in a combatant (including potential subclasses).

This component is the default implementation of other interfaces (see table above) and will create additional components
as needed. You can always override this behavior by providing your own components implementing the appropriate interfaces.
In that case, the Combat Manager will find these instances and use them as needed.

The Combat Manager also hosts useful delegates, both from the required interfaces and some of its own. They should be 
useful when defining your own gameplay features.

| Delegate                        | Source          | Purpose                                                                                       |
|---------------------------------|-----------------|-----------------------------------------------------------------------------------------------|
| `OnAttackStarted`               | Combat Manager  | Informs that an attack is starting. Provides the Ability Tags and the locked target (if any). |
| `OnCombatTargetChanged`         | Target Manager  | Notifies a new target obtained or a target lost.                                              |
| `OnStaggerStateChanged`         | Damage Manager  | Notifies changes in the _Staggered_ state.                                                    |
| `OnDamageReceived`              | Damage Manager  | Notifies incoming damage.                                                                     |
| `OnOwnerFinishedDying`          | Damage Manager  | Notifies the death of a combatant.                                                            |
| `OnBlockingStateChanged`        | Defense Manager | Notifies changes in the _Blocking_ state.                                                     |
| `OnInvulnerabilityStateChanged` | Defense Manager | Notifies changes in the _Invulnerability_ state.                                              |

### Delegate Binding

Except for delegates exposed directly by the Combat Manager itself, you should use the appropriate **interfaces** to 
bind to other Delegates. You can unbind from them using the interface as well.

The following examples show how to bind and unbind from delegates, via the appropriate interfaces.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="cbt_delegate_binding_interfaces.png" alt="Binding via Interfaces" border-effect="line" thumbnail="true" width="600"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="cbt_delegate_interface_binding.cpp"/>
    </tab>
</tabs>

## Custom Combat Components

Custom Components can be created by **implementing the correct Interface**, or **extending the base class** provided by
the Combat framework. You can then add your new components to your character, and return them using the **Combat System 
Interface**. 

### Implementing the Interface

You can simply create a new Actor Component, implement the desired interface and fill the necessary logic. If you want 
to reuse logic already available in the base **Combat Manager**, you can always perform an **interface call** to that
component too.

### Subclassing Components

Another alternative is to subclass the provided components. You can do that for components that are independent, such as
the **Motion Warping**, or even the main **Combat Manager**. In this case, replace the base components as needed.

### Conditional Component Creation

Another way to provide custom components, when some per-character logic is required, is to override the appropriate
**Factory Methods** in the **Combat Manager Component**. All appropriate Factory Methods are listed in the table above.

