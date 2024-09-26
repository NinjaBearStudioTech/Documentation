# Item Durability
<primary-label ref="inventory"/>

Exposes information from the [**Durability Fragment**](inv_durability_fragment.md).

| Field             | Description                            | Update Condition                            |
|-------------------|----------------------------------------|---------------------------------------------|
| Is Indestructible | Informs if the item is indestructible. | None.                                       |
| Is Broken         | Informs if the item is broken.         | Durability reaches zero or changes from it. |
| Durability        | Current durability                     | Wear is added or the item is repaired.      |