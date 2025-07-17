# Consume Ability
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Consume Ability</b></p>
    <br/>
    <ul>
        <li>Consumes one or more items, reducing their quantity or durability.</li>
        <li>Requires the item to include a <b>Consumable Fragment</b> that defines consumption rules.</li>
        <li>Supports a <b>fallback animation</b> for failed consumption attempts (e.g., no quantity left).</li>
    </ul>
</tldr>

The **Consume Ability** executes a **consumption** action on one or more selected items. This action typically decreases
the item's **quantity**, **durability**, depending on the [fragment configuration](inv_fragment_consumable.md).

This ability is commonly used for **potions**, **food**, **ammunition**, **scrolls**, and other consumables that can be
depleted through use.

## Item Requirement

Only items that include a [**Consumable Fragment**](inv_fragment_consumable.md) are eligible to be consumed by this ability.
The fragment determines whether the item can be consumed at the time of activation (e.g., enough quantity or durability remaining).

## Fallback Animation on Failure

If no eligible items are found - whether due to empty stacks, invalid conditions, or missing fragments - the ability can
optionally play a **fallback animation** to indicate failure.

This feature is particularly useful for immersive feedback (e.g., "_no arrows left_", "_can't eat now_") in combat or
exploration gameplay.

| Property          | Description                                                                                              |
|-------------------|----------------------------------------------------------------------------------------------------------|
| `FailedActionTag` | Optional verb tag to use when consumption fails. If valid, it will attempt to play a fallback animation. |

When this tag is set:

- A fallback animation will be resolved using the **Chooser Table**.
- The system builds a criteria object with the `FailedActionTag` and a generic `Consumable` item tag.
- If a valid montage is found, the fallback animation plays instead of canceling the ability.

This fallback only affects presentation - no item is consumed or modified when it plays. If the tag is not set or the 
fallback montage is not found, the ability will behave normally and **cancel execution with no animation**.
