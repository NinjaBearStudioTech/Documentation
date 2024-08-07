# Item Economy
<primary-label ref="inventory"/>

Exposes information from the [**Economy Fragment**](inv_economy_fragment.md).

| Field            | Description                           | Update Condition |
|------------------|---------------------------------------|------------------|
| Can Be Bought    | Informs if the item can be bought.    | None.            |
| Can Be Sold      | Informs if the item can be sold.      | None.            |
| Unit Buy Price   | Unitary buy price for a single item.  | None.            |
| Total Buy Price  | Price to buy the current stack.       | Stack changes.   |
| Unit Sell Price  | Unitary sell price for a single item. | None.            |
| Total Sell Price | Price to sell the current stack.      | Stack changes.   |