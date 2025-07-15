# Equipment Instances and States
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Equipment Instances and States</b></p>
    <br/>
    <ul>
        <li>Equipment Instances are created automatically by the Equipment Manager when eligible items are added to <b>Equipment Containers</b>.</li>
        <li>Each instance can represent an <b>Actor</b> or a <b>Mesh</b> in the world, depending on configuration.</li>
        <li>Equipment States define how each presence is represented per equipment state tag.</li>
    </ul>
</tldr>

## Equipment Instances
When an eligible item is added to an Equipment Container, the **Equipment Manager** automatically creates an `NinjaInventoryEquipment` 
instance to represent its presence in the world. These instances are tracked and updated based on the item's state and container configuration.

Equipment Instances are used to drive the **physical presence** of an item - either for visuals, gameplay, or both. 
Equipment can be represented in two main ways:

- **Actor**: For complex interactions, behaviors and multi-mesh representations.
- **Mesh**: For simpler visual representation (static or skeletal mesh).

The chosen type is defined per **Equipment State**, allowing different representations depending on the item's current 
usage. For example: a weapon might be an Actor, with a skeletal mesh and dedicated animation while equipped, but a simple
static mesh while stored.

### Equipment Actors
When using actors for equipment:

- There are no requirements on actor hierarchy (base classes or interfaces).
- The actor must include a `NinjaEquipmentActorComponent`.

This component receives a reference to the `UNinjaInventoryEquipment` instance that spawned it and provides support functions  
to access the **owning equipment and item**, the **equipment manager** and the **inventory manager*.. 

### Custom Equipment Logic
You can subclass `NinjaInventoryEquipment` to implement custom logic and assign your subclass directly to the [**Equipment Fragment**](inv_fragment_equipment.md). 
This enables additional gameplay systems, data storage, and access to custom behavior per equipment instance.

## Equipment States
Equipment States define how each `NinjaInventoryEquipment` is represented in the world, based on the item's current 
equipment **state tag**.

These are configured in the **Equipment Fragment** and mapped using one or more `FGameplayTag`s. Not all equipment states 
need to be represented visually - only those listed in the fragment will be created.

> **Performance Note**  
> 
> Equipment assets (such as actors or meshes) **shared** between states are reused and not recreated.
{style="note"}

Each `InventoryEquipmentState` provides detailed control over how the item should appear or behave in a specific state.

| Property                         | Description                                                                                        |
|----------------------------------|----------------------------------------------------------------------------------------------------|
| `EquipmentStateTags`             | All equipment state tags covered by this configuration. Multiple tags can share the same settings. |
| `EquipmentType`                  | Determines if this state uses an `Actor`, `StaticMesh`, or `SkeletalMesh`.                         |
| `ActorClass`                     | Actor class to spawn for this state (if type is `Actor`).                                          |
| `StaticMesh`                     | Static mesh to display for this state (if type is `StaticMesh`).                                   |
| `SkeletalMesh`                   | Skeletal mesh to display for this state (if type is `SkeletalMesh`).                               |
| `bFollowsParentMesh`             | Whether the skeletal mesh should follow the parent avatar’s mesh as a follower (leader pose).      |
| `SkeletalMeshAnimClass`          | Animation blueprint to use if the skeletal mesh is not using a leader pose.                        |
| `bOverridesParentFinderStrategy` | If true, overrides the default Attach Parent Finder.                                               |
| `AttachParentFinderClass`        | Custom `NinjaEquipmentAttachParentFinder` used to determine the parent component for attachments.  |
| `bOverrideContainerSocket`       | Whether to override the socket defined in the Equipment Container.                                 |
| `AttachSocketName`               | Name of the socket to use when attaching the actor or mesh.                                        |
| `EquipmentAnimLayerClass`        | Animation layer class added to the avatar when this state is active.                               |
| `AttributeSets`                  | Attribute sets granted to the avatar while in this equipment state.                                |
| `GameplayEffects`                | Gameplay Effects applied to the avatar when entering this state.                                   |
| `Containers`                     | Additional containers granted while this state is active (e.g., ammo pouches or sheath slots).     |
