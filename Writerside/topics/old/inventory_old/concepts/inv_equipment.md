# Equipment
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Represents an <b>Item</b> in the <b>Game World</b>.</li>
        <li>Configured using an <b>Equipment Definition</b>, which is added to an item's <b>Equipment Fragment</b>.</li>
        <li>Equipment Definitions require <b>at least one state</b>.</li>
        <li>States define <b>visual</b> and <b>gameplay</b> aspects of the equipment.</li>
        <li>Complex equipment behavior or cosmetics can be implemented using <b>Equipment Actors</b>.</li>
        <li>Slots are <b>placement markers</b> used by <b>Equipment</b>.</li>
    </ul>
</tldr>

**Equipment** is the **physical representation** of **items** in the game world.

## Equipment Definition

The **Equipment Definition** specifies the equipment's behavior for each **state**. Each state can modify the user in 
many ways, such as:

1. **Modify Skeletal Meshes** assigned to certain slots. For example, replacing a shirt with an armor vest.
2. **Hide Component Slots** conflicting with the current state. For example, hiding facial hair when a mask is added.
3. **Spawn Actors** with additional features needed to represent an item. For example, spawning weapons with their own logic.
4. **Link or unlink Animation Layers**, which is useful to modify stances for certain types of equipment. For example, switching from _unarmed_ to _sword and shield_ animations.
5. **Apply gameplay elements**, such as Attributes, Effects, and Abilities.

Equipment Definitions are a **Primary Data Asset**, represented by the class `NinjaEquipmentDataAsset`. You can create 
new definitions using the **Context Menu** and navigating to the **Inventory** category.

Once configured, the Equipment Definition is set to an item via the **[Equipment Fragment](inv_equipment_fragment.md)**. 
You can reuse Equipment Definitions across different items.

### Configuring Assets for States

While configuring your assets for each state, keep the following general concepts in mind:

- **Unused Slot Tags**: These are Slot Tags that will be **hidden** while the state is active.
- **Slot Tag**: Refers to a **Container/Mesh Component** or **Socket** that can be used as the placement anchor.
- **Socket Name**: Applicable to **Mesh Components** that must be attached to different sockets.
- **Compatibility Checks**: You can use or create checks that must be valid for the asset to be used. This is useful to handle things like different _body types_.
- **Scene Component Selector**: Allows you to determine where a given Slot should be encountered. By default, this is the Character Mesh, but you might want to use other selection rules.

The following scene selectors are available:

| Scene Selector     | Description                                                                                                                                          |
|--------------------|------------------------------------------------------------------------------------------------------------------------------------------------------|
| Attached Actor     | Selects a component in an attached actor, by a given component tag. <br/> Useful if you want to attach an item to another actor, such as a backpack. |
| Character Mesh     | Returns the default Mesh from a character, or another scene component using the optional Gameplay Tag.                                               |
| Provider Interface | Invokes the selection method from `EquipmentSceneComponentProviderInterface`. Supports advanced logic.                                               |

## Equipment Instance

The **Equipment Fragment** is responsible for monitoring the container in which its owning item is currently stored.

Once the item is stored in an **Equipment Slot** — a container with the **Equipment** tag — its Equipment Fragment will 
**initialize** the Equipment or **synchronize its state**.

Initializing the equipment involves providing the **item** along with its **Equipment Definition** to the **Equipment 
Manager**, which will create a new **Equipment Instance** and replicate it to all clients.

The Equipment Instance is responsible for managing the equipment's **state** and performing any changes to the owner, 
as per the state's configuration.

> **Extending the Equipment Instance**
>
> Since the Equipment Instance primarily handles **state management**, modifications to this class are generally
> unnecessary unless you need to override how certain state elements are handled or introduce new ones.

> **Equipment Tags**
> 
> Equipments can be identified and classified by tags. Obtaining the Equipment Tags will return all tags from the
> **backing item** and **current container**.
{style="note"}

## State Management

Equipment Instances can change their current states in one of two ways:

1. By being moved into an **Equipment Slot** that sets a default state for its items. This is tracked by the **[Equipment Fragment](inv_equipment_fragment.md)**.
2. By activating the [State Gameplay Abilities](inv_abilities.md), which target a specific Equipment Instance.

Once these events are detected, the **Equipment Manager** will synchronize the correct **Equipment Instance**, ensuring 
that the appropriate state is updated.

## Equipment Actors

**Equipment Actors** are used when an item's Equipment requires more complex logic or visual representation.

A common example would be creating _weapons_, which may require additional logic, such as performing _melee traces_ or 
executing their own _Animation Blueprints_.

### Equipment Actor Interface

Any Actor can be used for this purpose, but they must implement the `EquipmentActorInterface`. This interface includes a few important methods:

1. **Getters** and **Setters** for the **Equipment Instance** that manages the actor, allowing access to the **item**, **manager components**, and **pawn**.
2. A function that marks the equipment as the **Effect Causer** when Gameplay Effects are applied from it. For example, weapons should typically be marked as the **Effect Causer** of a _damage effect_.

> **Multiple Equipment Actors**
>
> A state can have multiple actors attached to it, but usually, only one should be marked as the **Effect Causer**.

### Default Equipment Actor

The framework provides a **base implementation** of `EquipmentActorInterface`, which can be used as the parent class for 
specific Equipment Actors.

This class provides the following features:

1. Configures minimal **replication** settings, including replicating the **Equipment Instance**.
2. A default boolean property that can be toggled to determine if the equipment is an **Effect Causer**.

## Equipment Slots

An **Equipment Slot** is a placement marker for equipment in the inventory. Slots are identified by **Gameplay Tags**,
which can link them to specific **Mesh Components**, or by **Sockets**.

### Configuration

**Containers** can be configured as **Equipment Slots**. In this case, they can only store a **single item**. The item
must have an **Equipment Fragment** and must pass the **compatibility query**.

The primary characteristic of an Equipment Slot is the presence of the `Inventory.Container.Equipment` tag. This tag
restricts the container to store **only one item**.

When Containers are configured as **Equipment Slots**, the inventory system expects a **match** between the **container
tag** and a **Mesh Component** on the avatar with the same tag. You will need to map Containers and Components when your
equipment representation is a **Skeletal or Static Mesh**.

<img src="inv_equipment_slot_container.png" alt="Slots and Containers" thumbnail="true"/>

### Sockets

**Sockets** provide another method for defining **Equipment Slots**. They are particularly useful when your Equipment is
represented by an **Actor**, making traditional **Mesh Components** less viable, since these actors would actually be
attacked to the owner.

The mapping between **Slot Tags** and **Skeleton Sockets** is done in the **[Equipment Manager](inv_equipment_manager.md#configuration)**.
A common use case would be for weapons that are implemented using **Actors**.

### Default Meshes

You can set **Default Meshes** for slots without any equipment assigned to them. This is useful when a mesh needs to be
displayed to represent an empty slot, such as a _shirt_ or a _naked torso_.

To configure this, create a new **Equipment Slot Setup**, and add all appropriate meshes with the correct **Slot Tags**.
This configuration also supports **Compatibility Checks**, which is useful if you need to support multiple body types
using the same Data Asset.

The following example shows what this asset could look like. In the example, setting default meshes for the Head, Facial
Hair and the Body.

<img src="inv_equipment_defaults.png" alt="Default Meshes" thumbnail="true"/>

### Skeletal Meshes

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