# Economy
<primary-label ref="inventory"/>

Determines if an item can be **bought** or **sold**, along with their respective **prices**.

## Buying and Selling
<secondary-label ref="wip"/>

The fragment allows you to set prices for **buy** and **sell** operations, but the operations themselves are still a 
work-in-progress and should be available in a future update.

## Stack Integration

You can obtain **total** prices for buying and selling, which will take into consideration the current item stack.

- `GetTotalBuyPrice`: Provides the buy price multiplied by the item stack. Always zero if the item cannot be bought.
- `GetTotalSellPrice`: Provides the sell price multiplied by the item stack. Always zero if the item cannot be sold.
