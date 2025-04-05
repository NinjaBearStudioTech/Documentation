# Combat System
<primary-label ref="combat"/>

<tldr>
    <p><b>Summary: Combat System Interface and Combat Manager</b></p>
    <br/>
    <ul>
        <li>Add the <b>Combat Manager Component</b> to your base character class.</li>
        <li>Optionally, add a <b>Forward Reference</b> to your base character class.</li>
        <li>Optionally, add the <b>Combat Movement Component</b> to your base character class.</li>
        <li>Optionally, use the <b>Combat Animation Instance</b> as your base Animation Blueprint class.</li>
        <li>Add the <b>Combat System Interface</b> to your base character classes.</li>
        <li>Configure the <b>Combat Mesh</b> and if necessary, the <b>Combat Animation Blueprint</b>.</li>
    </ul>
</tldr>

## Combat Manager Component
The Combat Manager Component is the most important component in the framework. It is the backbone for all other components
and actors to operate, and should be present in every Pawn or Character considered a _combatant_. 

For more information about how to extend this component, please check the [](cbt_component_extensions.md) page. For now,
we will simply add it to the **base character class**.

<procedure title="Add the Combat Manager Component" collapsible="true" default-state="expanded">
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

## Forward Reference
Certain features, such as the Evade Ability, may require a global forward reference, a Scene Component that **always points 
forward**, typically an Arrow Component with **absolute rotation**. 

The **Combat Manager** can create a default Forward Reference as needed, but if you are using **[](ipt_overview.md)**, then you 
should create your own, so you can have the flexibility needed for that integration. For more details, please 
check [Input Integration](cbt_integration_input.md#forward-reference)

<procedure title="Add a Forward Reference component" collapsible="true" default-state="expanded">
    <step>In your <b>Base Character Class</b>, create a new <b>Arrow Component</b>, parented to the <b>Root Component</b>.</step>
    <step>Add the <code>Combat.Component.ForwardReference</code> tag to the list of <b>Component Tags</b>.</step>
    <step>Set the <b>Transform</b> to use <b>Absolute Rotation</b>, so it always points forward.</step>
    <tabs group="sample">
        <tab title="Blueprint" group-key="bp">
            <img src="cbt_setup_forward_reference.png" alt="Add the Forward Reference" width="800" thumbnail="true" border-effect="line"/>
        </tab>
        <tab title="C++" group-key="cpp">
            <p><b>Header</b></p>
            <code-block lang="c++" src="cbt_setup_forward_reference.h"/>
            <p><b>Implementation</b></p>
            <code-block lang="c++" src="cbt_setup_forward_reference.cpp"/>
        </tab>
    </tabs>
</procedure>

## Combat Movement Component

Ninja Combat includes the `NinjaCombatCharacterMovementComponent` class, a version of the Character Movement Component 
that can handle different **movement speeds**, due to changes in **blocking** and **strafing** states.

> **Optional Step**
>
> The **Combat Movement Component** is an **optional** feature. You can skip this section if you are not planning on
> using it, or using another movement framework such as Mover 2.0.
>
> It is still recommended to see how this class operates internally, to learn more about the delegate bindings and how
> it reacts to character changes.

<procedure title="Set the Combat Character Movement Component" collapsible="true" default-state="expanded">
    <step>
        <p>In your <b>Base Character Class</b>, add the <code>CombatSystemInterface</code>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="cbt_setup_override_movement_component.png" alt="Override default input component" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="c++" src="cbt_override_movement_component.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

## Animation Instance

Ninja Combat includes the `NinjaCombatAnimInstance` class, a version of the Animation Instance that can serve as the 
base class for an Animation Blueprint, handling animation updates related to **blocking** and **strafing** states.

> **Optional Step**
>
> The **Combat Animation Instance** is an **optional** feature. You can skip this section if you are using your own
> animation or dedicated character locomotion systems.
> 
> It is still recommended to see how this class operates internally, to learn more about the delegate bindings and how 
> it reacts to character changes.

<procedure title="Set the Combat Animation Instance" collapsible="true" default-state="expanded">
    <step>Create an <b>Animation Blueprint</b>, using <code>NinjaCombatAnimInstance</code> as the base class.</step>
    <step>Set the new Animation Blueprint to your <b>Character Mesh</b>.</step>
</procedure>

For more information about the properties and functions available in this Animation Instance class, please check the
[dedicated Character Animation page](cbt_character_animation.md).

## Combat System Interface
The **Combat System Interface** defines the contract that Pawns and Characters must follow, to integrate with **Ninja Combat**.
All functions in this interface are **optional**, but let's implement some and go through the reasons why.

| Function                    | Reason                                                                                                                                                                                                    |
|-----------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `GetCombatManager`          | The system performs a Component Scan to find the Combat Manager. Returning it avoids the component iteration.                                                                                             |
| `GetCombatMesh`             | The system can find meshes tagged with `Combat.Component.Mesh` or the Character Mesh. Returning the mesh avoids component iteration, or obtaining the wrong mesh, in case of a Runtime Retargeting setup. |
| `GetCombatAnimInstance`     | The Animation Instance from the Combat Mesh is always used. But if you have a Runtime Retargeting setup, you need to provide the Animation Blueprint that is actually driving the animation.              |
| `GetCombatForwardReference` | The system can create a default Forward Reference, but if you are using Ninja Input, a custom Component Tag must be added to the Scene Component.                                                         |

> **Runtime Retargeting**
> 
> Certain setups, such as projects based on the **Game Animation Sample Project** (G.A.S.P.), use **Runtime Retargeting**
> for their characters. 
> 
> In such cases, the Combat Mesh is always the **visible** mesh (the _Retarget Target_), and the Animation Blueprint is 
> the one from **hidden** mesh (the _Retarget Source_).
{style=note}

<procedure title="Add the Combat System Interface" collapsible="true" default-state="expanded">
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