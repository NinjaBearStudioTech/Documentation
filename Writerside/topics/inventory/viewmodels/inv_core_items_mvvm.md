# Inventory Items
<primary-label ref="inventory"/>

Provides all items available **Gameplay Attributes** assigned to the **Inventory Owner**.

This viewmodel is meant to be used at the **Inventory UI** level. It will bind to changes in a **Container** when the
owning widget receives the **Container Instance**. 

Any widget extending `UNinjaInventoryContainerWidget` will do that **automatically**, but ou can also set the container 
via the `SetContainer` function in the viewmodel.

| Field                   | Description                          | Update Condition                                                      |
|-------------------------|--------------------------------------|-----------------------------------------------------------------------|
| Get Items               | Retrieves all items in the container | Items are added, removed or their position changes in the container.  |

All widgets representing **Container Views** will provide a `RefreshItems` function that is compatible with the viewmodel's 
`GetItem` output. Once invoked by the change, it will update its own container representation. These are the current views:

- `UNinjaInventoryContainerBorderWidget`: A border meant to represent a single item, usually an **Equipment Slot**.
- `UNinjaInventoryContainerBoxWidget`: A **Wrap Box** that can display items in a **grid**, based on their **positions**.
