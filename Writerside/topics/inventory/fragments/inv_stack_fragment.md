# Stack
<primary-label ref="inventory"/>

Manages the **stack** and storage **limits**. Provides the **Combine** and **Split** operations.

> You should always have a Stack fragment in your items, even if it's just to set storage limits!
{style="note"}

## Modifying Requests

Since it implements `IItemContextModifierInterface`, this fragment is invoked for every item added to the inventory, to
ensure the request is properly split in correct stack sizes, and optionally that incomplete stacks in the inventory can 
be filled first, before creating new items.

Everything happens automatically, and you don't need to worry about it, but if the item cannot be placed, then it will
be marked for a **drop** and additional information will be available in the logs, under the `LogNinjaInventory` category.

## Fragment Synergies

The Stack Fragment has an indirect synergy with the [**Container Fragment**](inv_container_fragment.md). Since additional 
item stacks can be created from new items being added to the inventory, these should also be modified by the Container
Fragment, so make sure to always add your Stack Fragment **before** the Container Fragment.

the Stack Fragment also has a more direct synergy with the [**Pickup Fragment**](inv_pickup_fragment.md), as it will
deliberately mark items to be dropped when they cannot be properly added to the inventory. The presence of the Pickup
Fragment will even influence a new stack being allowed into the inventory. 

## Item Limits

Even if items are not stackable, you can use the Stack Fragment to define their **maximum limits** in the inventory. 
When items reach that limit, attempts to adding new items will most likely result in an item being **dropped**.

## Merging New Items

You can choose to automatically **merge** new items being added to the inventory. This means that incomplete stacks will
be reused, before new items can be created. 

You can enable this behavior by toggling the `Automatically Merge New Items` property either in the **Inventory Settings**
or per-item, in the Stack Fragment added to the **Item Definition**.

## Strict Stacks

Another flexible behavior provided by the Stack Fragment is the ability to decide if the inventory will only add items
that can have their entire stack received, dropping the entire stack otherwise.

If disabled, then the amount that can be received will be added to the inventory and the remainder will be **dropped**.

## Combine Operation

This fragment provides the **Combine** operation, which can be created via the `CreateCombinePayload` function. It moves 
It combines two items, merging their stacks and leaving behind any leftovers in the original item.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_combine_operation.png" alt="Combine operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Combine(UNinjaInventoryItem* ItemA, UNinjaInventoryItem* ItemB)
        {
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateCombinePayload(ItemA, ItemB);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>

## Split Operation

This fragment provides the **Split** operation, which can be created via the `CreateSplitPayload` function. It splits a 
given item's stack, creating a new item with the requested stack size.

> The new item will go through the regular `AddItem` flow in the Inventory Manager. Fragments that can modify new items,
> such as the **Container Fragment**, will execute normally.
> 
> However, the **Stack Fragment** recognizes items being added from a **Split** operation, and it won't try to merge 
> stacks automatically.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_split_operation.png" alt="Split operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Split(UNinjaInventoryItem* Item, int32 Amount)
        {
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateStackPayload(Item, Amount);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>