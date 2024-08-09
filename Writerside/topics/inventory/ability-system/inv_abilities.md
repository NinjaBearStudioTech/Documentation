# Gameplay Abilities
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Inventory owners and avatars must implement <code>AbilitySystemInterface</code>.</li>
        <li>All ability classes are fully implemented but are marked as <code>abstract</code> and must be configured.</li>
        <li>The Inventory System can grant and remove abilities set to Equipment States or granted by managed Gameplay Effects.</li>
    </ul>
</tldr>

There are two types of **Gameplay Abilities** to consider when working with the Inventory System:

- **Inventory Abilities**: These are essential for the Inventory to function and should be granted by default to the character.
- **Managed Abilities**: These are assigned to Equipment Definitions and are added or removed when certain states are active.

All Inventory Abilities extend from `NinjaInventoryGameplayAbility`.

## Ability Animations

Abilities can also extend from `NinjaInventoryAnimationAbility`, which adds animation properties to the base Inventory 
Ability.

Animations are provided from a **Data Table**, using `InventoryAnimationTableRow` as the row structure. This entry has 
the following properties:

| Property        | Description                                                            |
|-----------------|------------------------------------------------------------------------|
| Montage Query   | Gameplay Tag Query applied to the incoming **Gameplay Tag Container**. |
| Montage To Play | A **soft reference** to the Animation Montage to play.                 |
| Montage Section | The section in the montage.                                            |

Each ability creates its **Gameplay Tag Container** in an appropriate way, and this container is matched with the **Montage 
Query**. Once a valid animation is found, it is **asynchronously loaded** and played. The **asset handle** remains valid while the ability is active.

Another important parameter in Animation Abilities is the **Animation Strategy**, which defines how the presence of a 
valid animation affects the ability's execution:

- **AlwaysExecute**: Performs the inventory operation regardless of whether an animation is found.
- **WhenAnimationStarts**: Performs the inventory operation when the animation starts.
- **WaitForGameplayEvent**: Waits for a gameplay event triggered by the animation.

## Activate Equipment

This ability is designed to **activate** equipment obtained via a **Gameplay Tag Query** or **Trigger Payload**. If an 
Equipment Instance cannot be obtained, the ability is **canceled**.

### Equipment Tag Query

The first way to target an item is via a **Gameplay Tag Query**. Be as explicit as possible to avoid incorrect items, 
though you can deliberately retrieve more than one item if needed.

For example, the following query collects all **Equipment Instances** from both Primary Slots (_main-hand_ and _off-hand_) 
that are currently _deactivated_.

<img src="inv_ability_state_query.png" alt="Query Sample" thumbnail="true"/>

### Trigger Payload

If you need more precision in selecting the item, you can activate the ability via a **Gameplay Event**.

The ability expects to find an Equipment Instance in the **Payload**, checking both Optional Objects for the Equipment 
Instance. This strategy takes **priority** over the Equipment Tag Query.

### Equip/Store Animation

For the equip/store animation, the ability prepares a container with the following details:

1. Adds the Gameplay Tag set in the **Animation Event Tag**.
2. Adds all **Equipment Tags** from the item that has been found.

To ensure precise timing in your animation, allowing items to change their states at specific frames, you can add the
**Send Equipment Event** animation notify. This can be used in conjunction with the **WaitForGameplayEvent** setting.

The Notify expects the following details:

- A **Gameplay Event Tag** matching the ability's **Animation Event Tag**.
- A **Gameplay Tag Container** indicating which of the **pre-selected equipment** should be modified. 

> **Pre-Selected Equipment**
> 
> The Equipment Tags set in the Animation Notify are used to select the correct equipment stored by the Ability. It 
> will not execute against the Inventory Manager itself, so you can be more lenient.

## Deactivate Equipment

This ability is designed to **deactivate** equipment obtained via a **Gameplay Tag Query** or **Trigger Payload**. 
It's a variation of the **Activate Ability** and follows the same specifications.

## Consume Item

This ability is designed to apply the **Consume Effect** from an item and decrease its stack as needed.

Similar to the Activate and Deactivate abilities, it searches for consumable items using either a **Gameplay Tag Query** 
or a **Trigger Payload**. If a **Consumable Item** cannot be obtained, the ability can play a _Not Found_ animation, or 
if this animation is not set, it will **cancel** the ability.

### Consume Animation

For the consume animation, the ability prepares a container with the following details:

1. Provides all **Item Tags** from the item that has been found.
2. Provides tags for the **Item Found** and **Item Not Found** scenarios.
