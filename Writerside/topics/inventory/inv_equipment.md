# Equipment, States, and Actors
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Represents an <b>Item</b> in the <b>Game World</b>.</li>
        <li>Configured using an <b>Equipment Definition</b>, which is added to an item's <b>Equipment Fragment</b>.</li>
        <li>Equipment Definitions require <b>at least one state</b>.</li>
        <li>States define <b>visual</b> and <b>gameplay</b> aspects of the equipment.</li>
        <li>Complex equipment behavior or cosmetics can be implemented using <b>Equipment Actors</b>.</li>
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
- **Scene Component Selector**: Allow you to determine where a given Slot should be encountered. By default, this is the Character Mesh, but you might want to use other selection rules.

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

