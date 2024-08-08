# Inventory Widgets
<primary-label ref="inventory"/>

The Inventory System provides base widgets that can be used to create a **User Interface**. They are divided into the 
following categories:

1. **Abstractions**: Base widgets used for actual Inventory Widgets.
2. **Inventory Window**: A widget that represents the root of the Inventory UI.
3. **Container Views**: Multiple ways to represent containers in the UI.
4. **Item View**: Represents items in the UI.
5. **Item Tooltip**: A specialized item representation that follows a specific contract.
6. **Drop Zone**: An area that detects item drop operations to create item pickups.

## Anatomy of an Inventory UI

Let's break down what goes under the hood for a complete Inventory Window. The following image shows a traditional UI, 
with some notes. Let's break those down to understand what the system has to offer.

<img src="inv_ui_overview.png" alt="Widget Overview" width="750" thumbnail="false"/>

### Inventory Window

The Inventory Window is the base for the entire Inventory UI. This is a **Common Activatable Widget**, which is part of
the **[Common UI][1]** Library.

This means that the Inventory Window must be properly **Activated** and **Deactivated**, placing it correctly in the 
active widget hierarchy and navigation.

The Inventory Window widget has the following responsibilities:

1. Wait for the owner's inventory to initialize and bind to it.
2. Broadcast the Inventory to all relevant widgets in the **Widget Tree**.
3. Store the **Tooltip Controller** responsible for managing the **Reusable Tooltip**.

The Inventory Window is represented by `NinjaInventoryWindowWidget`.

### Container View

**Container Views** are areas of the UI that represent a specific **Container Instance**, which is defined by its **Container 
Data**. They have the following responsibilities:

1. Receive the **Inventory Manager** from the **Inventory Window**.
2. Obtain the correct **Container Instance** and bind to its **delegates**.
3. Create and configure new **Item Views** as needed, using the appropriate widget class.
4. Initialize their viewmodels with the container that will be watched.
5. Provide a method to **Refresh Items** when the viewmodel updates.
6. Host certain components that will actually render the container.

> **Why use a Viewmodel?**
>
> It might seem like the Container View could just watch items being updated directly, instead of using a viewmodel, which is true.
>
> Extending or creating a viewmodel to perform any operation on the items is a looser design that simplifies extension, while allowing the widget itself to be more strict.

The Container View is represented by `NinjaInventoryContainerWidget`.

#### Border Container

A **Border Container** only allows a **single widget** as its content, which makes it ideal for **Equipment Slots**. 
The content is usually an **Item View** widget.

The Border Container is represented by `NinjaInventoryContainerBorderWidget`.

#### Box Container

A **Box Container** renders its content in a **grid**, making it ideal for larger containers, such as a **Backpack**. 
It can also render **empty items**.

The Box Container is represented by `NinjaInventoryContainerBoxWidget`.

#### List Container
<secondary-label ref="wip"/>

A **List Container** renders its content in a **list**, making it useful for large scrollable datasets, such as 
**Vendors** and **Loot**.

### Item View

The **Item View** represents an actual **Item**, stored in a **Container**. The view is usually rendered by the 
**Container View**, as per a component's request. It has the following responsibilities:

1. Bind to **Viewmodels** to expose any relevant details about the item.
2. Handle **Drag and Drop** events that will trigger **Inventory Operations**.
3. Handle **Focus** events that will render or dismiss the **Reusable Tooltip**.
4. Determine if they can be **Focused** based on whether they have an **Item** or not.

It is represented by the `UNinjaInventoryItemWidget`.

### Reusable Tooltip

The **Item Tooltip** is instantiated only once by the Inventory Window and managed by the **Tooltip Controller**. It is 
an **optional** feature, but very helpful if you want to have tooltips for your **Item View**, as it will:

1. Piggyback on the native **Tooltip** functionality.
2. Reuse the same widget for **all** item views, avoiding unnecessary instances for both widgets and viewmodels.

It is represented by `NinjaInventoryTooltipWidget`.

### Drop Zone

Not shown in the image above, but also useful when handling **Drop** operations, the **Drop Zone** Widget is a transparent 
area that should cover any regions in the UI that allows players to drop items and generate **Pickups**.

It is represented by `NinjaInventoryDropZoneWidget`.

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/common-ui-quickstart-guide-for-unreal-engine
