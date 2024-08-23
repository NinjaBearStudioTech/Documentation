# Equipment Slots
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Slots are <b>placement markers</b> used by <b>Equipment</b>.</li>
        <li>They are represented by Gameplay Tags assigned to <b>Mesh Components</b> or <b>Sockets</b>.</li>
        <li>Slots can have <b>default meshes</b> assigned to them, used when no equipment is set.</li>
        <li>An Equipment Slot can store <b>equipment</b> and <b>cosmetic</b> items.</li>
    </ul>
</tldr>

An **Equipment Slot** is a placement marker for equipment in the inventory. Slots are identified by **Gameplay Tags**, 
which can link them to specific **Mesh Components** or **Sockets**.

## Containers

**Containers** can be configured as **Equipment Slots**. In this case, they can only store a **single item**. The item 
must have an **Equipment Fragment** and must pass the **compatibility query**.

The primary characteristic of an Equipment Slot is the presence of the `Inventory.Container.Equipment` tag. This tag 
restricts the container to store **only one item**.

When Containers are configured as **Equipment Slots**, the inventory system expects a **match** between the **container 
tag** and a **Mesh Component** on the avatar with the same tag. You will need to map Containers and Components when your
equipment representation is a **Skeletal or Static Mesh**.

<img src="inv_equipment_slot_container.png" alt="Slots and Containers" thumbnail="true"/>

## Sockets

**Sockets** provide another method for defining **Equipment Slots**. They are particularly useful when your Equipment is 
represented by an **Actor**, making traditional **Mesh Components** less viable.

The mapping between **Slot Tags** and **Skeleton Sockets** is done in the **[Equipment Manager](inv_equipment_manager.md#configuration)**. 
A common use case would be for weapons that are implemented using **Actors**.

## Default Meshes

You can set **Default Meshes** for slots without any equipment assigned to them. This is useful when a mesh needs to be 
displayed to represent an empty slot, such as a _shirt_ or a _naked torso_.

To configure this, create a new **Equipment Slot Setup**, and add all appropriate meshes with the correct **Slot Tags**. 
This configuration also supports **Compatibility Checks**, which is useful if you need to support multiple body types 
using the same Data Asset.

## Skeletal Meshes

Some slots will be **Skeletal Meshes** representing items worn by the character, such as an **Armor Vest** or **Pants**.
It's expected that these components will follow the **Primary Mesh** in any animations.

The most common way to do that is by setting up a **Leader Pose Component**, so all relevant equipment slots are set as 
**followers** of the main mesh driving the animation

When configuring your **Leader Mesh**, make sure to adjust these settings:

- `VisibilityBasedAnimTickOption`: `AlwaysTickPoseAndRefreshBones`
- `bLightAttachmentsAsGroup`: `true`

As for your **Follower Meshes**, make sure to adjust these settings:

- `bUseBoundsFromLeaderPoseComponent`: `true`;
- `bUseAttachParentBound`: `true`;

> **Merge Mesh**
> 
> In the future, **Mesh Merge** support is planned as well.

<seealso style="cards">
   <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/working-with-modular-characters-in-unreal-engine" summary="Techniques available in the engine to work with modular character.">Working with Modular Characters</a>
    </category>
</seealso>
