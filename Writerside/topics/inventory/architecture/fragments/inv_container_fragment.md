# Container
<primary-label ref="inventory"/>

Manages the **container** and **position** where the backing item is stored, and provides the **Move** and **Swap** 
operations, along with other utility functions.

> You should always have a Container fragment in your items!
{style="note"}

## Modifying Requests

Since it implements `IItemContextModifierInterface`, this fragment is invoked for every item added to the inventory, to 
ensure they are placed either in the position that has been originally requested, or the next best one available.

Everything happens automatically, and you don't need to worry about it, but if the item cannot be placed, then it will
be marked for a **drop** and additional information will be available in the logs, under the `LogNinjaInventory` category.

## Item Placement

If you want to invoke the placement operation yourself for other purposes, you can invoke the appropriate function,
`SetBestContainerAndPositionForItem`, which will evaluate the best container and position for an item.

If you just want to know what are the best container and position available, without persisting the item, you can also
use `FindBestContainerForItem` and `FindBestPositionForItem`.

There are other useful functions that you may want to explore for other placement queries, such as `IsValidPosition`
and `IsPreferredContainer`.

> When used in conjunction with the Stack fragment, make sure to place the Container **after** the Stack. This ensures
> that new items created by the Stack fragment are properly placed.
{style="note"}

## Move Operation

This fragment provides the **Move** operation, which can be created via the `CreateMovePayload` function. It moves the 
item to a new container and position.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_move_operation.png" alt="Move operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Move(UNinjaInventoryItem* Item, UNinjaInventoryContainer* Container, int32 Position)
        {
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateMovePayload(Item, Container, Position);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>

## Swap Operation

This fragment provides the **Swap** operation, which can be created via the `CreateSwapPayload` function. Swaps two items,
exchanging their containers and positions.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_swap_operation.png" alt="Swap operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Swap(UNinjaInventoryItem* ItemA, UNinjaInventoryItem* ItemB)
        {
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateSwapPayload(ItemA, ItemB);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>

## Additional Containers

An item can add additional containers to the inventory. This is useful for items that can provide **their own storage**,
like _boxes_, _pots_ and so on.

Containers added via this fragment are registered to the inventory, along with their items. Once the item is removed, 
the container is removed with it.

Keep in mind that you can also add containers from an **active equipment**, meaning that containers are only registered 
when an item is **activated**. This is more suited represent items like a _backpack_.
