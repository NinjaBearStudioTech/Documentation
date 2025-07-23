# Fragment ViewModels
<primary-label ref="inventory"/>

**Fragment ViewModels** expose specific **item fragments** to the user interface. They allow you to select only the data 
relevant for your widget and bind to it using the appropriate ViewModel type.

## Configuration

Fragment ViewModels are bound to a single item using either `SetItemInstance` or `SetItemView`. These methods can also 
be used to reset or change the current item being observed.

All Fragment ViewModels should be created using the `Inventory Resolver`.

> **Widget Placement**
> 
> Fragment ViewModels are typically used within **item widgets**, where each one binds to a specific data aspect (stack, 
> quality, etc.) and updates automatically as the item changes.
{style="note"}

## Dimensions Notifies

This ViewModel exposes data from the [**Dimensions Fragment**](inv_fragment_dimensions.md), including the item's 
footprint and rotation state.

| Field        | Description                                                                    |
|--------------|--------------------------------------------------------------------------------|
| `bIsRotated` | Indicates whether the item is currently rotated in its container.              |
| `Dimensions` | Returns the item's width and height as a `FVector2D`, accounting for rotation. |

## Durability Notifies

This ViewModel exposes data from the [**Durability Fragment**](inv_fragment_durability.md), allowing you to monitor an 
item's durability status and display appropriate UI feedback.

| Field               | Description                                                         |
|---------------------|---------------------------------------------------------------------|
| `bHasDurability`    | Indicates whether the item includes a Durability Fragment.          |
| `bIsIndestructible` | Returns `true` if the item cannot take durability damage.           |
| `bIsBroken`         | Indicates whether the item is broken (durability has reached zero). |
| `Durability`        | The current durability value of the item.                           |
| `MaximumDurability` | The maximum durability this item can have.                          |

## Economy Notifies

This ViewModel exposes data from the [**Economy Fragment**](inv_fragment_economy.md), allowing your UI to represent 
buy/sell permissions and pricing.

| Field            | Description                                                 |
|------------------|-------------------------------------------------------------|
| `bHasEconomy`    | Indicates whether the item includes an Economy Fragment.    |
| `bCanBeBought`   | Returns `true` if the item is marked as purchasable.        |
| `bCanBeSold`     | Returns `true` if the item is marked as sellable.           |
| `UnitBuyPrice`   | The per-unit price to buy this item.                        |
| `TotalBuyPrice`  | The total buy price, including the current stack quantity.  |
| `UnitSellPrice`  | The per-unit price to sell this item.                       |
| `TotalSellPrice` | The total sell price, including the current stack quantity. |

## Level Notifies

This ViewModel exposes data from the [**Level Fragment**](inv_fragment_level.md), allowing you to display and track an 
item's level progression.

| Field          | Description                                           |
|----------------|-------------------------------------------------------|
| `bHasLevel`    | Indicates whether the item includes a Level Fragment. |
| `Level`        | The current level assigned to the item.               |
| `MaximumLevel` | The maximum level this item can reach.                |

## Nested Container Notifies

This ViewModel exposes data from the [**Nested Container Fragment**](inv_fragment_nested_container.md), allowing you to 
access a container stored inside an item (e.g., a bag or box).

| Field                | Description                                                             |
|----------------------|-------------------------------------------------------------------------|
| `GetNestedContainer` | Returns the `Inventory Container` associated with the item, if present. |

## Quality Notifies

This ViewModel exposes data from the [**Quality Fragment**](inv_fragment_quality.md), allowing your UI to reflect the 
item's rarity or quality visually and textually.

| Field          | Description                                                              |
|----------------|--------------------------------------------------------------------------|
| `bHasQuality`  | Indicates whether the item includes a Quality Fragment.                  |
| `QualityTag`   | A gameplay tag that defines the item's quality (e.g., `Common`, `Rare`). |
| `QualityText`  | Localized display text for the item's quality.                           |
| `QualityColor` | A display color associated with the item's quality level.                |

## Stack Notifies

This ViewModel exposes data from the [**Stack Fragment**](inv_fragment_stack.md), allowing the UI to represent item 
quantities, limits, and stack display behavior.

| Field             | Description                                                               |
|-------------------|---------------------------------------------------------------------------|
| `bHasStack`       | Indicates whether the item includes stack data and if it should be shown. |
| `StackSize`       | The current quantity of the item in the stack.                            |
| `StackLimit`      | The maximum number of items allowed in a single stack.                    |
| `MaximumQuantity` | The maximum quantity allowed across the entire inventory.                 |

## User Interface Notifies

This ViewModel exposes data from the [**User Interface Fragment**](inv_fragment_user_interface.md), allowing your 
widgets to display localized text and icons for the item.

| Field         | Description                                                           |
|---------------|-----------------------------------------------------------------------|
| `DisplayName` | Localized name of the item, typically shown as the main label.        |
| `Category`    | Localized category or grouping label for the item.                    |
| `Description` | Localized description text, often used for tooltips or item details.  |
| `Icon`        | UI texture representing the item visually.                            |

## Weight Notifies

This ViewModel exposes data from the [**Weight Fragment**](inv_fragment_weight.md), allowing the UI to display item 
weight and calculate encumbrance effects.

| Field         | Description                                                   |
|---------------|---------------------------------------------------------------|
| `bHasWeight`  | Indicates whether the item includes a Weight Fragment.        |
| `UnitWeight`  | The weight of a single unit of the item.                      |
| `TotalWeight` | The total weight, factoring in the item’s current stack size. |
