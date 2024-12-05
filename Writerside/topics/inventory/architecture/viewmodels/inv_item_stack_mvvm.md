# Item Stack
<primary-label ref="inventory"/>

Exposes information from the [**Stack Fragment**](inv_stack_fragment.md).

| Field         | Description                               | Update Condition                |
|---------------|-------------------------------------------|---------------------------------|
| Has Stack     | Informs if the item is stacked or not.    | Item stack is greater than one. |
| Stack Size    | Current stack size.                       | Stack size changes.             |
| Stack Limit   | Maximum size for a stack.                 | None.                           |
| Maximum Limit | Maximum amount of items in the inventory. | None.                           |