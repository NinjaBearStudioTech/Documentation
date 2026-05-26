# Combat Components
<primary-label ref="combat"/>

Ninja Combat uses a small set of **core components** to connect Characters, Pawns, abilities, animation, targeting, 
damage, defense, and weapons.

At the center of this setup is the **Combat Manager Component**, which acts as the main access point for combat-related 
systems. Most supporting systems are exposed through interfaces, so projects can use the default components, replace 
specific parts, or extend the framework with custom implementations.

This page explains the main combat components, how they are discovered, and which parts can be customized.

## Combat System Interface

The **Combat System Interface** defines the contract that Pawns and Characters must follow, to integrate with **Ninja Combat**.
All functions in this interface are **optional**, but implementing the main ones directly avoids runtime lookups and makes 
your combat setup explicit.

| Function                    | Description                                                                                                                                                                           |
|-----------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `GetCombatManager`          | Provides the Combat Manager Component. By default, searches for the component in the actor. It is recommended to return the Combat Manager Component instance directly.               |
| `GetCombatMesh`             | Provides the Combat Mesh. By default, searches for a mesh tagged with `Combat.Component.Mesh` or the Character Mesh. It is recommended to return the correct Skeletal Mesh Component. |
| `GetCombatAnimInstance`     | Provides the Animation Instance from the Combat Mesh. The instance from the Combat Mesh is used by default.                                                                           |
| `GetCombatForwardReference` | Provides the Forward Reference. By default, searches for a scene component tagged with `Combat.Component.ForwardReference`. It is recommended to return the desired reference.        |

> **Runtime Retargeting**
>
> Certain setups, such as projects based on the **Game Animation Sample Project** (G.A.S.P.), use **Runtime Retargeting**
> for their characters.
>
> In such cases, the Combat Mesh is always the **visible** mesh (the Retarget Target), and the Animation Blueprint is
> the one from **hidden** mesh (the Retarget Source).
{style=tip}

<procedure title="Implement the Combat System Interface" collapsible="true" default-state="collapsed">
    <step>In your <b>Base Character Class</b>, add the <code>CombatSystemInterface</code>.</step>
    <step>Implement the <code>GetCombatManager</code> function, so it returns the <b>Combat Manager Component</b>.</step>
    <step>
        <p>Implement the <code>GetCombatMesh</code> function, so it returns the <b>Character Mesh</b>.</p>
        <tip>If you're using Runtime Retargeting (e.g., with the G.A.S.P. sample), make sure <code>GetCombatMesh</code> returns the <i>Retarget Target</i> (visible mesh).</tip>
    </step>
    <step>
        <p>Implement the <code>GetCombatAnimInstance</code> function, so it returns the <b>Character Animation Instance Blueprint</b>.</p>
        <tip>If you're using Runtime Retargeting (e.g., with the G.A.S.P. sample), make sure <code>GetCombatAnimInstance</code> returns the Animation Blueprint from the <i>Retarget Source</i> (hidden mesh).</tip>
    </step>
    <step>Implement the <code>GetCombatForwardReference</code> function, so it returns the <b>Forward Reference Component</b> (e.g., the <code>Arrow Component</code>).</step>
    <tabs group="sample">
        <tab title="Blueprint" group-key="bp">
            <img src="cbt_setup_combat_interface.png" alt="Add the Combat System Interface" width="800" thumbnail="true" border-effect="line"/>
        </tab>
        <tab title="C++" group-key="cpp">
            <p><b>Header</b></p>
            <code-block lang="c++" src="cbt_setup_combat_system_interface.h"/>
            <p><b>Implementation</b></p>
            <code-block lang="c++" src="cbt_setup_combat_system_interface.cpp"/>
        </tab>
    </tabs>
</procedure>

## Component Architecture

The **Combat Manager Component** is the most important component in the framework. It is the backbone for all other 
components and actors to operate, and should be present in every **Pawn** or **Character** considered a _combatant_.

> **Combat Manager Location**
>
> The Combat Manager should always be added to the **Pawn** or **Character**, regardless of the location of the related
> Ability System Component, which can be added to the Pawn or Player State, as usual.
{style=tip}

The Combat System has multiple parts represented by **interfaces**. This design allows developers to replace parts of
the system, by replacing components with their own functionality.

The only component that cannot be swapped at the interface level is the **Combat Manager Component**, since it is the 
backbone of the Combat System. Still, it provides many extension points through virtual and overridable functions.

The following table shows all components that can be swapped at the interface level.

| Interface                    | Implementation               | Factory Method                     |
|------------------------------|------------------------------|------------------------------------|
| `AmmoStorageInterface`       | `AmmoStorageComponent`       | N/A                                |
| `ComboManagerInterface`      | `ComboManagerComponent`      | `CreateComboManagerComponent`      |
| `DamageManagerInterface`     | Base Combat Manager          | `CreateDamageManagerComponent`     |
| `DefenseManagerInterface`    | Base Combat Manager          | `CreateDefenseManagerComponent`    |
| `MotionWarpingInterface`     | `MotionWarpingComponent`     | `CreateMotionWarpingComponent`     |
| `MovementManagerInterface`   | `CharacterMovementComponent` | N/A                                |
| `PhysicalAnimationInterface` | `PhysicalAnimationComponent` | `CreatePhysicalAnimationComponent` |
| `TargetManagerInterface`     | Base Combat Manager          | `CreateTargetManagerComponent`     |
| `WeaponManagerInterface`     | `WeaponManagerComponent`     | `GetAndCacheWeaponManager`         |

## Combat Manager Component

The Combat Manager Component is the main component in the system. It does not have its own interface, since it's always
expected to be present in a combatant (including potential subclasses).

This component is the default implementation of other interfaces (see table above) and will create additional components
as needed. You can always override this behavior by providing your own components implementing the appropriate interfaces.
In that case, the Combat Manager will find these instances and use them as needed.

The Combat Manager also hosts useful delegates, both from the required interfaces and some of its own. These are useful 
when defining your own gameplay features.

| Delegate                        | Source          | Purpose                                                                                       |
|---------------------------------|-----------------|-----------------------------------------------------------------------------------------------|
| `OnAttackStarted`               | Combat Manager  | Informs that an attack is starting. Provides the Ability Tags and the locked target (if any). |
| `OnCombatTargetChanged`         | Target Manager  | Notifies a new target obtained or a target lost.                                              |
| `OnStaggerStateChanged`         | Damage Manager  | Notifies changes in the _Staggered_ state.                                                    |
| `OnDamageReceived`              | Damage Manager  | Notifies incoming damage.                                                                     |
| `OnOwnerFinishedDying`          | Damage Manager  | Notifies the death of a combatant.                                                            |
| `OnBlockingStateChanged`        | Defense Manager | Notifies changes in the _Blocking_ state.                                                     |
| `OnInvulnerabilityStateChanged` | Defense Manager | Notifies changes in the _Invulnerability_ state.                                              |

<procedure title="Add the Combat Manager Component" collapsible="true" default-state="collapsed">
    <step>
        <p>In your <b>Base Character Class</b>, add the <b>Combat Manager Component</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="cbt_setup_combat_manager.png" alt="Add the Combat Manager Component" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p><b>Header</b></p>
                <code-block lang="c++" src="cbt_setup_combat_manager_component.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="cbt_setup_combat_manager_component.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

### Delegate Binding

Except for delegates exposed directly by the Combat Manager itself, you should use the appropriate **interfaces** to 
bind to other delegates. You can unbind from them using the same interface.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="cbt_delegate_binding_interfaces.png" alt="Binding via Interfaces" border-effect="line" width="720"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="cbt_delegate_interface_binding.cpp"/>
    </tab>
</tabs>

## Custom Combat Components
<secondary-label ref="advanced"/>

Custom components can be created by **implementing the correct interface** or **extending one of the base classes** 
provided by the Combat framework. You can then add your new components to your character and return them through the 
**Combat System Interface**.

### Implementing the Interface

You can create a new Actor Component, implement the desired interface, and provide the necessary logic. If you want
to reuse logic already available in the base **Combat Manager**, you can always perform an **interface call** to that
component too.

### Subclassing Components

Another alternative is to subclass the provided components. You can do that for components that are independent, such as
the **Motion Warping**, or even the main **Combat Manager**. In this case, replace the base components as needed.

### Conditional Component Creation

Another way to provide custom components, when some per-character logic is required, is to override the appropriate
**Factory Methods** in the **Combat Manager Component**. All appropriate Factory Methods are listed in the table above.

## Combat Movement Component
<secondary-label ref="optional"/>

Ninja Combat includes the `NinjaCombatCharacterMovementComponent` class, a version of the Character Movement Component
that can handle different **movement speeds**, due to changes in **blocking** and **strafing** states. 

You can replace the default Character Movement Component with the Combat version in Blueprint or C++.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="cbt_setup_override_movement_component.png" alt="Override default movement component" border-effect="line" width="720"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="cbt_override_movement_component.cpp"/>
    </tab>
</tabs>

## Animation Instance
<secondary-label ref="optional"/>

Ninja Combat includes the `NinjaCombatAnimInstance` class, a version of the Animation Instance that can serve as the
base class for an Animation Blueprint, handling animation updates related to **blocking** and **strafing** states.

This is optional, but useful when your Animation Blueprint needs direct access to common combat animation state.