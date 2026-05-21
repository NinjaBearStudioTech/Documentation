# Key Fragment
<primary-label ref="inventory"/>

The **Key** Fragment is used when an external actor, such as a door or chest, must be unlocked. The fragment also supports
removal policies applied when the key is used.

## Fragment Tags
This fragment adds the `Inventory.Item.Trait.Key` tag to an item, which can be used by queries to search for keys.
You can also add other tags to the item to further define the key type, such as `Inventory.Item.Type.Key.Red` or
`Inventory.Item.Type.Key.Skeleton`.

## Properties
This fragment has the following properties.

| Property            | Description                                                                                                                                             |
|---------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|
| `ConsumptionMode`   | Defines what happens to a key when used. Valid values are `None` (the key is kept) or `ConsumeKey` (one key is removed from the inventory / stack).     |
| `UnlockActionClass` | A class that will be executed when the key is used. It can perform arbitrary logic on the unlockable actor, such as calling an `Unlock` function on it. |

> **Consuming Keys**
>
> The fragment is compatible with **stacks**. If a key is stacked, then one unit is removed. If that was the last
> unit, the item is deleted. The item is also deleted if it does not have a Stack Fragment.
{style="note"}

## Operations
This fragment exposes the following operations.

| Function    | Description                                                                              |
|-------------|------------------------------------------------------------------------------------------|
| `TryUseKey` | Attempts to use a key, applying the consumption mode and triggering the assigned action. |

## Unlock Action
Keys use a dedicated **Unlock Action** object to execute unlocking logic, instead of using an interface provided by the
framework. The reason for that is so the unlockable actor **does not have a direct dependency** on classes from the 
Inventory system.

The base class, `UNinjaInventoryUnlockAction`, does not execute any specific logic by default, but you can create 
subclasses to execute any behavior required by your unlockable actor. This class only provides one function: `Unlock`, 
which takes the key fragment calling it and the unlockable actor.

## Function Library
To simplify key usage, Ninja Inventory provides a convenient function in its static function library that can be
used in Blueprints or C++ to attempt to unlock an actor using a key: `TryUnlockWithKey`.

This function takes the Inventory Owner, the Unlockable actor, and a Key Query used as search criteria for the key item.
If the unlocking operation succeeds (including any key consumption), the function returns true.