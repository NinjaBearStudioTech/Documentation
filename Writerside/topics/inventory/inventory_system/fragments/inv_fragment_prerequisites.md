# Prerequisites Fragment
<primary-label ref="inventory"/>

The **Prerequisite** Fragment stores a list of prerequisite objects that will determine if the item can be added to the
Inventory or not.

## Properties
This fragment has the following properties.

| Property           | Description                                                                          |
|--------------------|--------------------------------------------------------------------------------------|
| `Prerequisites`    | List of prerequisites that will determine if the item can be added to the inventory. |

## Operations
This fragment exposes the following operations.

| Function                | Description                                                                           |
|-------------------------|---------------------------------------------------------------------------------------|
| `EvaluatePrerequisites` | Evaluates all prerequisites and provides the reason why the item was blocked, if any. |