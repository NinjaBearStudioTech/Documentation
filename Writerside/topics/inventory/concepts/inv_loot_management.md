# Loot Management
<primary-label ref="inventory"/>
<secondary-label ref="wip"/>

Loot is a common feature in many games: players open a treasure chest or kitchen cabinet, chop a tree, defeat an enemy, 
and they are awarded loot. For this functionality, you can use the `UNinjaInventoryLootComponent`.

This Actor Component is designed to be added to any Actors that will provide loot. These Actors do not need their own 
Inventory Manager component; they only require the Loot Component, configured with all available loot and its rules.

## Loot Component

The Loot Component is an Actor Component that can be added to any Actors providing loot. It is a standalone component, 
so its owner does not need to also have an Inventory Manager. 

However, the Loot Component can work in tandem with the Inventory Manager. This setup is useful if you need to drop 
actual items from the component owner's inventory. 

For example, in a game where a defeated character drops any currently equipped weapon or armor, the Loot Component can 
collect lootable items from the Inventory Manager.

## Loot Sources

The Loot Component can use different Data Sources to determine what items are available for a loot request. These
sources can fetch data from different things like a Data Table, a Backend Server, the Lootable Actor's Inventory Manager
and so on.

You can create your own Loot Sources using the `UNinjaInventoryLootSource` as the Base Class.

## Loot Fragment

_Coming soon..._

## Selecting and Caching Loot

_Coming soon..._

## Notifying Loot

_Coming soon..._

## Granting Loot

_Coming soon..._