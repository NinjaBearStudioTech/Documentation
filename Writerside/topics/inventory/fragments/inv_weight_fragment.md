# Weight
<primary-label ref="inventory"/>

Specifies the individual weight of an item. Also provides the total weight, when considering the current **stack**.

## Tracking Weight

An items weight (unit or total) can be obtained via the fragment's `GetWeight` and `GetTotalWeight` functions.

However, a better approach to keep track of changes in the weight, which usually happens due to changes in the **stack**,
is to bind to the `OnWeightChanged` delegate available in this fragment.

## Stack Integration

Whenever the **Stack** changes, the weight fragment will also broadcast a change, providing the new **Total Weight**.