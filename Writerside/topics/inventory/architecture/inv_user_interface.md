# User Interface
<primary-label ref="inventory"/>

The Inventory System provides base **Widgets** that can be used as a foundation to your User Interface.

It also provides multiple **UMG Viewmodels** that can be used to connect the Inventory Data to the UI. They are **event-oriented**,
so the UI will only be notified when data actually changes in the backend.

> **Common UI**
>
> Main Inventory Widgets are using **[Common UI][1]** when applicable. 
> 
> Make sure to familiarize yourself with that framework, especially regarding the **activation** and **deactivation** 
> process and the **input routing**.
{style="note"}

[](inv_widgets.md)
: Details all Widgets and Components available in the Inventory System, explaining their functionality and usage.
It's strongly recommended to use these widgets as a foundation for your Inventory UI.

[UMG Viewmodels](inv_viewmodels.md)
: All inventory and item data is exposed to the UI via UMG Viewmodels, which are an event-driven implementation of the 
MVVM pattern used for communication between the model and view layer. A catalogue of all UMG Viewmodels is available as
well.


[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/common-ui-quickstart-guide-for-unreal-engine