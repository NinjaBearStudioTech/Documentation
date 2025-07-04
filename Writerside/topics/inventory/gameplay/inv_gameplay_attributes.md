# Gameplay Attributes
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Add the <code>NinjaInventoryAttributeSet</code> to your Ability System Component.</li>
        <li>Initialize the Attribute Set with a <b>Data Table</b> that uses <code>AttributeMetaData</code> as the <b>row type</b>.</li>
        <li>Use the <b>initialization sample</b> below to avoid missing attributes.</li>
    </ul>
</tldr>

The Inventory Framework includes its own Attribute Set, containing multiple relevant categories such as **Weight**,
**Equipment Level** and an abstract concept of **Wealth**.

The Attribute Set is represented by the `NinjaInventoryAttributeSet` class, make sure to add it to the Ability System
Component assigned to your Character or Player State.

## Available Attributes

The following table contains all attributes available in the Inventory System's Attribute Set.

| Attribute               | Description                                                                             | Meta |
|-------------------------|-----------------------------------------------------------------------------------------|------|
| `Wealth`                | Current wealth for the character. Can represent any type of in-game currency.           | No   |
| `EquipmentLevel`        | Aggregation of the level from all equipment pieces in use. Maintained automatically.    | Yes  |
| `AverageEquipmentLevel` | Average Equipment Level. Maintained automatically.                                      | Yes  |
| `WeightLimit`           | Maximum weight capacity for this inventory.                                             | No   |
| `Encumbrance`           | Weight currently carried by the avatar, considering stacks. Maintained automatically.   | Yes  |
| `BackpackSlots`         | Slots available for the Backpack container. Provided for convenience, but not required. | No   |

### Average Equipment Level

This **Meta Attribute** is calculated by the `GetAverageGearLevel` function in the [Equipment Manager](inv_equipment_management.md).
The attribute is updated when the total **Equipment Level** changes. The calculation logic can be represented as:

```Generic
float absolute_level = aggregate_levels();
int container_count = get_relevant_containers().size();
return absolute_level / max(relevant_container_count, 1)
```

This means the average level is defined by the **absolute item level** divided by the amount of **relevant containers**
configured in the inventory layout.

## Initialization Data

You can use this Json to facilitate the creation the Data Table used to initialize the Inventory Attributes.
Please note that only attributes that are not maintained automatically were included.

The Data Table Row type used to create Attribute Set Data for initialization is provided by the Gameplay Ability System
You can create your data table using the `AttributeMetaData` structure.

<code-block lang="json" src="inv_attributes.json" collapsible="true" collapsed-title="Inventory Attributes"/>