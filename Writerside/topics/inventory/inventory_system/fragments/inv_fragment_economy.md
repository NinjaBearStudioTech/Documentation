# Economy
<primary-label ref="inventory"/>

The **Economy** fragment enables an item to be bought or sold by inventory owners. It defines both unitary prices and 
total prices, calculated based on **[stack size](inv_fragment_stack.md)**, if applicable. 

The system handles **wealth validation**, **Gameplay Effect application**, and **memory transfer** during transactions.

> **Wealth Tracking**
> 
> By default, this fragment will use the **Attribute** and **Gameplay Effect** provided by the Inventory system. You can 
> change those to adhere to implementations, but make sure that both the Attribute and Effect are compatible!
{style="note"}

## Fragment Tags
This fragment does not contribute any tags by default. However, it interacts with the `Wealth` attribute (or another 
attribute set), and may broadcast events based on inventory changes (such as adding/removing items).

## Properties
This fragment has the following property.

| Property                  | Description                                                        |
|---------------------------|--------------------------------------------------------------------|
| `CanBeBought`             | Whether the item can be bought by a target inventory manager.      |
| `RemoveWhenBought`        | If `true`, removes the item from the source when it's bought.      |
| `BuyPrice`                | Price for one unit of the item (if `CanBeBought` is `true`).       |
| `CanBeSold`               | Whether the item can be sold to a target inventory manager.        |
| `SellPrice`               | Price for one unit of the item (if `CanBeSold` is `true`).         |
| `WealthChangeEffectClass` | Gameplay Effect class applied when wealth changes occur.           |
| `WealthAttribute`         | Gameplay attribute used to read and apply wealth during purchases. |

## Operations
This fragment exposes the following operations.

| Function            | Description                                                         |
|---------------------|---------------------------------------------------------------------|
| `CanBeBought`       | Returns `true` if the item is marked as buyable.                    |
| `CanBeSold`         | Returns `true` if the item is marked as sellable.                   |
| `CanBuy`            | Checks if the target manager has enough wealth to buy the item.     |
| `CanSell`           | Checks if the item can be sold by the source manager to the target. |
| `GetBuyPrice`       | Returns the unitary buy price.                                      |
| `GetSellPrice`      | Returns the unitary sell price.                                     |
| `GetTotalBuyPrice`  | Returns total buy price considering stack.                          |
| `GetTotalSellPrice` | Returns total sell price considering stack.                         |
| `Buy`               | Transfers item to the target and deducts wealth, if valid.          |
| `Sell`              | Transfers item to the target and adds wealth to source, if valid.   |

## Memory
This fragment does not define or use a memory struct. Instead, it interacts with other systems such as the Stack fragment 
and the inventory manager's wealth state.

> **Selecting Fragment Memories**
>
> Memories stored for an item are transferred during buy/sell operations, so things like "stack size" are carried.
>
> However, some memories are irrelevant, such as the container position, so it is filtered-out. You can fine-tune which
> memories should be added/removed by overriding `ShouldAddMemoryToItem`.
{style="note"}

## Event Payload
This fragment does not define its own event or payload structure. However, events may be triggered indirectly through:

- Inventory item **additions and removals**.
- **Wealth changes** via Gameplay Effects.
- **Stack size changes** when items are split or merged during transactions.