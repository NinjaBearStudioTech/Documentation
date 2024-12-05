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

## Providing Custom Components

Custom Components can be created by **implementing the correct Interface**, or **extending the base class**. 

For cases where the base class is the default **Combat Manager**, you can implement the interface, only writing the logic
for any function necessary, and for the others, you can retrieve the Combat Manager from the _owner_ and call the original
function.

Once your new components are ready, add them to your character and return them using the **Combat System Interface**.
You only need to **override functions that are relevant to your new components**.

## Conditional Component Creation

Another way to provide custom components, when some per-character logic is required, is to override the appropriate
**Factory Methods** in the **Combat Manager Component**. 

All appropriate Factory Methods are listed in the table above.

## Movement Component

The Movement Component is a special case, since it overrides the **Character Movement Component**, therefore it is not
created, or directly used by the **Combat Manager Component**.

You can replace the Movement Component using C++ or in your Blueprint. 

<tabs group="sample">
    <tab title="Blueprint">
        <img src="cbt_override_movement_component.png" alt="Override default input component" border-effect="line"/>
    </tab>
    <tab title="C++">
        <code-block lang="c++" src="cbt_override_movement_component.cpp"/>
    </tab>
</tabs>