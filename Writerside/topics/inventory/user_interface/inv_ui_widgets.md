# Inventory Widgets
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Inventory Widgets</b></p>
    <br/>
    <ul>
        <li>All available widgets are powered by <b>dedicated controller classes</b> that handle logic and ViewModel setup.</li>
        <li>The system supports both <b>UMG</b> and <b>Common UI</b>, allowing developers to choose their preferred UI framework.</li>
        <li>Base widgets simplify development by providing <b>plug-and-play</b> components with minimal setup required.</li>
        <li>Controllers ensure consistent behavior between UI stacks, without introducing bias or divergence in features.</li>
        <li>Custom widgets can reuse these controllers to inherit behavior while applying unique layouts or designs.</li>
    </ul>
</tldr>

Ninja Inventory provides a unified UI architecture that works across both **UMG** and **Common UI**. This is achieved 
through the use of **widget controllers**, which encapsulate the logic needed to manage ViewModels, handle events, and 
display inventory data correctly.

## Supported Stacks

Each widget category is backed by a controller class and ships with ready-to-use base widgets for both supported UI frameworks:

| Widget Type   | Controller                                | UMG Widget                      | Common UI Widget                      |
|---------------|-------------------------------------------|---------------------------------|---------------------------------------|
| **Item**      | `NinjaInventoryItemWidgetController`      | `NinjaInventoryItemWidget`      | `NinjaInventoryItemCommonWidget`      |
| **Container** | `NinjaInventoryContainerWidgetController` | `NinjaInventoryContainerWidget` | `NinjaInventoryContainerCommonWidget` |

These widgets are functionally equivalent. You are free to choose your preferred stack and **the underlying behavior 
remains identical**.

## Item Widget Behavior

The Item Widget is responsible for:

- Owning the **Inventory Item View Model** (manual creation).
- Propagating this View Model to all **fragment ViewModels** (using the Inventory Resolver).
- Managing tooltip logic, mouse/focus interactions, and widget state.
- Supporting both **Item Instances** and **Item Views**.

Both base widgets (`NinjaInventoryItemWidget`, `NinjaInventoryItemCommonWidget`) come pre-wired to:

- Receive and assign the Item ViewModel.
- Call `SetItemInstance` or `SetItemView` as needed.
- Update child ViewModels automatically.

## Container Widget Behavior

The Container Widget is responsible for:

- Owning the **Inventory Container View Model** (resolver-based).
- Using a **ViewModel Extension** to output a list of **Item View Models**.
- Spawning and binding individual **Item Widgets**.
- Managing container-wide state, such as layout fill or active selection.

The base widgets (`NinjaInventoryContainerWidget`, `NinjaInventoryContainerCommonWidget`) automatically:

- Load the Container Definition from a `ContainerDataAsset`.
- Retrieve and assign the correct container from the Inventory Manager.
- Bind item data to the Item ViewModels and spawn appropriate widgets.

## Customization Guidelines

To build a custom widget while leveraging system logic:

1. **Reparent** your widget to the corresponding base widget (UMG or Common UI).
2. In the **Designer tab**, modify the layout freely.
3. Keep any existing ViewModel references intact unless explicitly overridden.
4. Use the provided ViewModel functions (e.g., `SetItemInstance`, `SetItems`) in your bindings.

This pattern keeps your layout clean while retaining full access to the inventory framework's automation.

## Summary

Widget controllers are the internal engine behind all inventory widgets. They abstract the complexity of ViewModel 
management, making it possible to:

- Mix and match UMG and Common UI widgets in your project.
- Build custom visual components without rewriting backend logic.
- Ensure consistent behavior across your entire user interface.

Whether you're building stylized loot panels or a tactical grid-based equipment screen, the underlying logic remains 
unified and reusable.
