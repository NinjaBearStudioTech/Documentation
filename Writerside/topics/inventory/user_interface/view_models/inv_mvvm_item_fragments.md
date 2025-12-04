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

## Dimensions

This ViewModel exposes data from the [**Dimensions Fragment**](inv_fragment_dimensions.md), including the item's 
footprint and rotation state.

| Field        | Description                                                                    |
|--------------|--------------------------------------------------------------------------------|
| `bIsRotated` | Indicates whether the item is currently rotated in its container.              |
| `Dimensions` | Returns the item's width and height as a `FVector2D`, accounting for rotation. |

## Durability

This ViewModel exposes data from the [**Durability Fragment**](inv_fragment_durability.md), allowing you to monitor an 
item's durability status and display appropriate UI feedback.

| Field               | Description                                                         |
|---------------------|---------------------------------------------------------------------|
| `bHasDurability`    | Indicates whether the item includes a Durability Fragment.          |
| `bIsIndestructible` | Returns `true` if the item cannot take durability damage.           |
| `bIsBroken`         | Indicates whether the item is broken (durability has reached zero). |
| `Durability`        | The current durability value of the item.                           |
| `MaximumDurability` | The maximum durability this item can have.                          |
| `DurabilityPercent` | Durability percent considering current/maximum.                     |

## Dynamic Attributes

This ViewModel exposes all [**Dynamic Attributes**](inv_fragment_dynamic_attributes.md) assigned to an item, allowing 
them to be fully displayed, including relevant configuration details, in the user interface.

The ViewModel exposes the following fields:

| Field                   | Description                                                 |
|-------------------------|-------------------------------------------------------------|
| `bHasDynamicAttributes` | Indicates whether the item includes any dynamic attributes. |
| `GetDynamicAttributes`  | Provides a list of dynamic attribute information.           |

And the list of dynamic attributes includes the following properties:

| Property        | Description                                            |
|-----------------|--------------------------------------------------------|
| `AttributeTag`  | Gameplay tag that uniquely identifies the attribute.   |
| `Value`         | Current value for the attribute.                       |
| `MinValue`      | For ranged values, this is the minimum possible value. |
| `MaxValue`      | For ranged values, this is the maximum possible value. |
| `ValueMode`     | Value mode for this attribute (fixed or ranged).       |
| `AttributeName` | The attribute name set in the Data Asset.              |
| `Description`   | The attribute description set in the Data Asset.       |

## Economy

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

## Linked Container

This ViewModel notifies when an item is in a **linked** state, meaning the item is a mirror position, in a linked
container, configured by the [**Linked Container Fragment**](inv_fragment_linked_container.md).

| Field          | Description                                  |
|----------------|----------------------------------------------|
| `bIsLinked`    | Informs if the item is in a linked scenario. |

Using this ViewModel requires a reference container, which must be set by the **Item ViewModel**. This is a **one-time** 
binding that establishes which container the ViewModel should compare against when determining whether the item is currently linked.

<img src="inv_ui_mvvm_linked_container_binding.png" alt="Linked Container Binding"/>

## Level

This ViewModel exposes data from the [**Level Fragment**](inv_fragment_level.md), allowing you to display and track an 
item's level progression.

| Field          | Description                                           |
|----------------|-------------------------------------------------------|
| `bHasLevel`    | Indicates whether the item includes a Level Fragment. |
| `Level`        | The current level assigned to the item.               |
| `MaximumLevel` | The maximum level this item can reach.                |

## Nested Container

This ViewModel exposes data from the [**Nested Container Fragment**](inv_fragment_nested_container.md), allowing you to 
access a container stored inside an item (e.g., a bag or box).

| Field                | Description                                                             |
|----------------------|-------------------------------------------------------------------------|
| `GetNestedContainer` | Returns the `Inventory Container` associated with the item, if present. |

## Quality

This ViewModel exposes data from the [**Quality Fragment**](inv_fragment_quality.md), allowing your UI to reflect the 
item's rarity or quality visually and textually.

| Field          | Description                                                              |
|----------------|--------------------------------------------------------------------------|
| `bHasQuality`  | Indicates whether the item includes a Quality Fragment.                  |
| `QualityTag`   | A gameplay tag that defines the item's quality (e.g., `Common`, `Rare`). |
| `QualityText`  | Localized display text for the item's quality.                           |
| `QualityColor` | A display color associated with the item's quality level.                |

When using the **Quality Color** as a background or visual indicator, you may want to define a fallback color for when 
no item is assigned. By default, the color is set to **transparent**, but you can customize this by setting the **Default 
Color** property on the ViewModel.

<img src="inv_ui_mvvm_fragment_quality_default_color.png" alt="Default Quality Color"/>

## Stack

This ViewModel exposes data from the [**Stack Fragment**](inv_fragment_stack.md), allowing the UI to represent item 
quantities, limits, and stack display behavior.

| Field             | Description                                                               |
|-------------------|---------------------------------------------------------------------------|
| `bHasStack`       | Indicates whether the item includes stack data and if it should be shown. |
| `StackSize`       | The current quantity of the item in the stack.                            |
| `StackLimit`      | The maximum number of items allowed in a single stack.                    |
| `MaximumQuantity` | The maximum quantity allowed across the entire inventory.                 |

## User Interface

This ViewModel exposes data from the [**User Interface Fragment**](inv_fragment_user_interface.md), allowing your 
widgets to display localized text and icons for the item.

| Field         | Description                                                           |
|---------------|-----------------------------------------------------------------------|
| `DisplayName` | Localized name of the item, typically shown as the main label.        |
| `Category`    | Localized category or grouping label for the item.                    |
| `Description` | Localized description text, often used for tooltips or item details.  |
| `Icon`        | UI texture representing the item visually.                            |

## Weight

This ViewModel exposes data from the [**Weight Fragment**](inv_fragment_weight.md), allowing the UI to display item 
weight and calculate encumbrance effects.

| Field         | Description                                                   |
|---------------|---------------------------------------------------------------|
| `bHasWeight`  | Indicates whether the item includes a Weight Fragment.        |
| `UnitWeight`  | The weight of a single unit of the item.                      |
| `TotalWeight` | The total weight, factoring in the item’s current stack size. |
