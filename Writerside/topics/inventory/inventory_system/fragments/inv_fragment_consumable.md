# Consumable Fragment
<primary-label ref="inventory"/>

The **Consumable** fragment allows an item to be used or consumed, applying a Gameplay Effect to the owning actor 
(typically the player).

It can optionally interact with **[Stack](inv_fragment_stack.md)** and **[Durability](inv_fragment_durability.md)** fragments
to control how many uses are available. If no stack or durability limits are defined, the item is considered to have 
**unlimited** uses.

## Fragment Tags
This fragment adds the `Inventory.Item.Trait.Consumable` tag to an item, which introduces the **Consumable** trait.

## Properties
This fragment has the following properties.

| Property           | Description                                                                    |
|--------------------|--------------------------------------------------------------------------------|
| `ConsumableEffect` | Gameplay Effect to apply when consumed.                                        |
| `EffectLevel`      | Level used when applying the Gameplay Effect. Defaults to `1.0`.               |
| `ReduceStack`      | Whether consuming this item should reduce its stack.                           |
| `QuantityPerUse`   | Stack quantity to consume (only if `ReduceStack` is true).                     |
| `ReduceDurability` | Whether consuming this item should apply durability wear.                      |
| `WearPerUse`       | Amount of durability wear applied on use (only if `ReduceDurability` is true). |

## Operations
This fragment exposes the following operations.

| Function                              | Description                                                                       |
|---------------------------------------|-----------------------------------------------------------------------------------|
| `CanConsume(Item)`                    | Returns whether the item can be consumed based on stack and durability.           |
| `Consume(Item)`                       | Applies the effect and reduces stack/durability if applicable.                    |
| `ConsumeWithCallback(Item, Callback)` | Same as `Consume`, but provides a callback with the applied GameplayEffectHandle. |

## Memory
The Consumable fragment does not have a memory. However, if the effect is successfully applied, the resulting Gameplay 
Effect Handle is stored in the list of active handles within the item instance.

## Event Payload
The Consumable fragment does not broadcast a dedicated event. You can still respond to consumption through:

- Stack or durability changes.
- Gameplay Effect events from the Ability System Component.
- Gameplay Tag events from the Ability System Component.

## Gameplay Ability
You can use the fragment directly, but if you need to play an animation or perform other gameplay events when consuming 
the item, you can use the **Consume Gameplay Ability**. This ability performs those additional tasks before calling the 
fragment's core functions.
