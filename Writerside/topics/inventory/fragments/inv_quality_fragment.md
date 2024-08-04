# Quality
<primary-label ref="inventory"/>

Manages an item's quality, based on a **Global Quality Table**.

## Quality Table

The Quality Fragment references the **Quality Mapping Table**, set in the **Inventory Settings**. This table maps Gameplay 
Tags representing item qualities, to their appropriate quality information, **Display Name** and **Color**.

> Create and set your Quality Mapping Table before adding Quality fragments to your items!
{style="warning"}

## Quality Configuration

The Quality Fragment receives a Gameplay Tag that represents the Quality for its item. If the provided Quality Tag maps
to a valid entry in the **Quality Mapping Table**, then the remaining information will be properly filled.

For data integrity purposes, editing the **Display Name** or **Color** of an item with a **valid quality** is blocked.
Once set, an item's quality **cannot be modified** at runtime. 

> Items with a **valid quality** will be tagged with the appropriate Quality Tag.
{style="note"}

