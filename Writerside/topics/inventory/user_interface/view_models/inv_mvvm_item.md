# Item ViewModel
<primary-label ref="inventory"/>

The **Item ViewModel** acts as the **primary data entry** point for individual item widgets. 

It wraps either a full `Item Instance` (managed by the inventory system) or a lightweight `Item View` (used for detached 
or preview representations such as selected loot), providing a unified interface for UI consumption.

This ViewModel is commonly used in **ViewModel Extensions**, allowing container-based widgets (e.g., Lists, Grids) to 
dynamically inject item data into their entry widgets.

## Configuration

The `Item ViewModel` is typically instantiated by a **Container ViewModel** using a **ViewModel Extension**. In this flow:

1. The **container** provides the configured `Item ViewModel` for each **item entry**.
2. The UI list or box widget creates an instance of your **Item Widget**.
3. The extension automatically assigns the `Item ViewModel` to the widget.
4. From there, the `Item ViewModel` propagates data to any **bound Fragment ViewModels** or **UI functions**.

For this reason, the **Creation Type** of the `Item ViewModel` should always be set to `Manual`, as it is **injected 
externally** rather than constructed by the widget itself.

No custom setter functions are required for this process to work, the ViewModel system handles the data flow automatically.

## Notifies

The following ViewModel functions are exposed and can be bound to in the UI:

| Field             | Type     | Description                                                           |
|-------------------|----------|-----------------------------------------------------------------------|
| `HasItemView`     | Function | Returns `true` if a valid `Item View` is assigned.                    |
| `HasItemInstance` | Function | Returns `true` if a valid `Item Instance` is assigned.                |
| `GetItemView`     | Function | Returns the currently assigned `Item View`, or `null` if not set.     |
| `GetItemInstance` | Function | Returns the currently assigned `Item Instance`, or `null` if not set. |

> **Item Instances and Views**
>
>The Item ViewModel supports either an Item Instance or an Item View. Assigning one will automatically clear the other, 
> ensuring the ViewModel always reflects a single item source.
>
> In the base framework, both the Container and Loot ViewModels - the main systems that provide items to the UI - handle 
> this mechanism automatically when assigning their backend entities.
{style=note}
