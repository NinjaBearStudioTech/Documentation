# Assembling Meshes
<primary-label ref="inventory"/>

When working with multiple **Equipment Meshes** representing wearable items, such as armor, it's common to use multiple
**skeletal meshes** that need to follow the same animation.

Unreal Engine offers a few different approaches to deal with this requirement, such as the **Leader Pose Component** and
**Skeletal Mesh Merging**.

## Leader Pose Component

The default strategy used by the Inventory System is the **Leader Pose Component**. It allows you to configure a leader
pose that will have an **Animation Instance Blueprint**, and other meshes that will follow its animation.

So let's say that your character is composed of multiple meshes, representing the head, torso, pants, gloves, etc. You
need to define which one would be the **Leader Pose**. That's usually the head or a full body mesh, if you are using it.

The Leader Pose should be configured with the following settings:

| Setting                         | Value                              |
|---------------------------------|------------------------------------|
| `VisibilityBasedAnimTickOption` | Always Tick Pose And Refresh Bones |
| `bLightAttachmentsAsGroup`      | `true`                             |

From there, you need to configure all other Skeletal Mesh Components to follow the leader pose.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_leader_pose_setup.png" alt="Configuring Leader Pose Components" width="600" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <p>Header:</p>
        <code-block lang="c++" src="inv_leader_pose_setup.h"/>
        <br/>
        <p>Implementation:</p>
        <code-block lang="c++" src="inv_leader_pose_setup.cpp"/>
    </tab>
</tabs>

> **Collisions and Follower Meshes**
> 
> Follower meshes won't have their physical assets receiving collisions. You either need an invisible full body mesh that
> can handle collisions or specific collision volumes assigned to the body!
{style="warning"}

<seealso style="cards">
   <category ref="external">
    <a href="https://dev.epicgames.com/community/learning/tutorials/DlDx/how-to-make-modular-characters-with-body-parts-in-unreal-engine-5-leader-pose-component" summary="Community Tutorial about the Leader Pose Component.">Leader Pose Component</a>
   </category>
</seealso>

