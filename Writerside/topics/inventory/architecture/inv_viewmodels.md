# Inventory Viewmodels
<primary-label ref="inventory"/>

To exchange backend data with the UI, the Inventory System uses **UMG Viewmodels**. They support event-driven bindings
that can trigger changes in the User Interface, when an update happens in the backend.

There are two categories of Viewmodels in the project:

1. **Inventory**: These will provide information and broadcast changes about the **Layout**, **Attributes** and **Item Lists**.
2. **Item**: These will provide information and broadcast changes from **Fragments**. You can expect a **one-to-one** relationship between **Fragments** and **Viewmodels**.

> Please make sure to familiarize yourself with **Viewmodels** in the [official documentation][1]!
{style="note"}

## Initializing Viewmodels

You can decide what is the best way to initialize your Viewmodels. For the **Inventory** itself, it might be easier to
simply initialize all pertinent view models during along with the **widget's initialization**.

> When initializing with the owning widget, Viewmodels are created between `PreConstruct` and `Construct`, but only if
> they have actual **bindings**.

As for the **Items**, you might need to ponder if you can have each item initializing all view models right away or 
manually initialize them and destroy them in more appropriate situations.

Regardless, it's recommended to have your Viewmodels configured to initialize along with each Item's widget, while the
Inventory UI is being built. Once completed, you can **profile and evaluate** what is the best initialization strategy.

### Inventory Initialization

Viewmodels that will connect to the **Inventory itself** will usually do so when the **Inventory Manager** broadcasts
its initialization event. At that moment, Inventory Widgets connected to Viewmodels will broadcast any appropriate data.

### Container Initialization

Certain Viewmodels must connect to **Containers**. this can be done in two ways:

- By invoking the `SetContainer` function at any appropriate moment. This will allow the Viewmodel to bind to the Container's **delegates**.
- **Owning widgets** will have a container set in their properties, or will receive one. When that happens, they will invoke the `SetContainer` function.

### Item Initialization

Similar to the Container Initialization, Viewmodels connected to **Items** will do so in two ways:

- By invoking the `SetItem` function at any appropriate moment. This will allow the Viewmodel to bind to the Item's **delegates**.
- **Owning widgets** storing items will invoke the `SetItem` function whenever items are created. They will also send `null` values for empty items.

## Binding Viewmodels

Viewmodels will expose properties that can be bound to **Properties** and **Functions**. These elements will be **notified**
about any changes in the viewmodel's data, allowing them to and **update accordingly**.

### Binding to Variables

Binding viewmodels to **variables** is the simplest form of integration between the backend and the UI. Whenever a value
changes in the backend data, the variable will be updated to reflect that change. Here are some examples:

- Binding the **Inventory Window Title** to the Layout's **Display Name**.
- Binding the **Stack** fragment data to an Item's widget, so the current stack size is displayed.
- Binding the **Weight** fragment data to an Item's widget, so the base and total weight are displayed.

> You don't need to use all bindings available in a Viewmodel! Pick the ones that are necessary for your User Interface.

### Binding to Function

Binding viewmodels to **Functions** is a powerful way to trigger more complicated behavior that usually involves many
aspects of the user interface. Here are some examples:

- Binding to **changes in Container Items** to update an entire container.
- Binding to the **Quality Color** to change the **title** and **background color** of an item widget.
- Set a widget's **visibility** based on a **boolean value**.

### Applying Conversions

Binding to a Function certainly allows a lot of flexibility while converting values between a viewmodel and a widget.
Many functions are already available in the form of **Conversions**, which you can leverage in many ways, such as:

- Convert a **numeric value** to a **text representation**, including **rounding** and **grouping** settings.
- Modify **texts** to **trim**, or **change case**.

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/umg-viewmodel