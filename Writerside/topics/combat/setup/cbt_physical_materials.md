# Physical Materials
<primary-label ref="combat"/>

<tldr>
    <p><b>Summary: Physical Materials</b></p>
    <br/>
    <ul>
        <li>Physical Materials are used by the Combat System to <b>detect and react</b> to surfaces hit by <b>weapons</b> and <b>projectiles</b>.</li>
        <li>It is common to have a few <b>Physical Materials</b> in the project, but they are <b>optional</b>, not required by Ninja Combat.</li>
        <li>If you have a <b>footsteps</b> system, then you can most likely consolidate all Physical Material setup for both systems.</li>
    </ul>
</tldr>

In Ninja Combat, **weapons** and **projectiles** can react differently, depending on the **surface** that they hit. 
Configuring these reactions will be covered in the [Weapon Actor configuration page](cbt_weapon_actors.md) but before
that, we should configure all **Physical Materials** used in the project.

You can find more information about Physical Surfaces and Materials in the **[official Unreal Engine documentation][1]**

> **Optional Step**
>
> Your project may not require different physical surfaces, or you might prefer to continue to combat-related topics and
> come back to this setup later on. If so, this topic is optional and not a Ninja Combat pre-requisite.

## Physical Surfaces
Physical Surfaces are used to identify unique **Physical Materials**.

<procedure title="Creating Physical Surfaces" collapsible="true" default-state="expanded">
    <step>Open the <b>Physical Surface</b> list, located in <b>Edit</b> &rarr; <b>Project Settings</b> &rarr; <b>Physics</b>.</step>
    <step>
        <p>In the <b>Physical Surface</b> section, add all entries required by your project.</p>
        <img src="cbt_setup_physical_surfaces.png" alt="Configuring Physical Surfaces" width="800" thumbnail="true" border-effect="line"/>
    </step>
</procedure>

Alternatively, you can add the surfaces above as a **starting point**, by adding the following lines to the `DefaultEngine.ini`
file, located in the project's `Config` folder. Make sure to add them under the `[/Script/Engine.PhysicsSettings]` section.

<code-block lang="ini" src="cbt_setup_physical_surfaces.ini" collapsible="true" collapsed-title="Physical Surfaces"/>

## C++ Physical Surfaces
It might be useful to have access to your Physical Surfaces in C++. To do so, you can create a simple **header file**
(`.h`), with the following contents. They are matching the sample above, so make sure to adjust this example to your needs.

<code-block lang="C++" src="cbt_setup_physical_surfaces.h" collapsible="true" collapsed-title="CustomPhysicalSurfaces.h"/>

## Physical Materials
Once your Physical Surfaces are configured, you can create **Physical Materials**. 

<procedure title="Creating Physical Materials" collapsible="true" default-state="expanded">
    <step>Create a new <b>Physical Material</b> from the <b>Content Browser</b>. They are in the <b>Physics</b> category.</step>
    <step>
        <p>In your <b>Physical Material</b> set the <b>Physical Surface</b> that correctly matches it.</p>
        <img src="cbt_setup_physical_materials.png" alt="Configuring Physical Materials" width="800" thumbnail="true" border-effect="line"/>
    </step>
    <step>
        <p>Repeat these steps for all <b>Physical Surfaces</b> in your project.</p>
        <img src="cbt_setup_physical_materials_done.png" alt="Physical Materials Collection" width="800" thumbnail="true" border-effect="line"/>
    </step>
</procedure>

You can assign these **Physical Materials** in a few different ways:

| Source              | Assignment                                                                                                         |
|---------------------|--------------------------------------------------------------------------------------------------------------------|
| Skeletal Meshes     | In each collider in the **Physics Asset**, or in the **PhysMat Override** in the Skeletal Mesh Component settings. |
| Static Meshes       | In the Collision Settings for the asset, or in the **PhysMat Override** in the Static Mesh Component settings.     |
| Pawns or Characters | Either in their Skeletal/Static meshes, or dedicated **Collision Components** attached to bones in the Skeleton.   |

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/physical-materials-in-unreal-engine