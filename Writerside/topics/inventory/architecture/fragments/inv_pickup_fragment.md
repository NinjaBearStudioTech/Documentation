# Pickup
<primary-label ref="inventory"/>

Enables the **droppable** trait, along with the accompanying **Drop** operation. 

Droppable items are tagged as `Inventory.Item.Trait.Droppable`.

## Pickup Actor

An item dropped in the world requires an **actor** to represent its presence, and allow other pawns, such as the 
**player**, to retrieve it.

These actors are defined by the `InventoryPickupInterface` and any actor implementing it will be a viable choice for 
the class selection property.

The system provides the following actors that can be used as a starting point:

| Actor                       | Description                                                                                         |
|-----------------------------|-----------------------------------------------------------------------------------------------------|
| `PickupActor`               | Basic pickup actor without any cosmetics, but with the proper data structure.                       |
| `EquipmentAwarePickupActor` | Configures the mesh based on the item's Equipment configuration. Integrated with the Asset Manager. |
| `PhysicsPickupActor`        | Adds physics to the Equipment Pickup.                                                               |

> Actors have the `NinjaInventory` prefix to their names, here omitted for legibility purposes.

You are free to build your pickup actors with any of the base actors above. Keep in mind that these actors **will not
provide interaction features**, such as collision detection.

## Drop Operation

The Drop operation allows you to set important properties to customize the operation:

1. **Location**: Where in the world the item will be dropped.
2. **Is Local Only**: In multiplayer scenarios, determines if the item is dropped for the local player or all players.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_drop_operation.png" alt="Drop operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Drop(UNinjaInventoryItem* Item, const FVector& Location, bool bIsLocalOnly)
        {
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateDropPayload(Item, Location, bIsLocalOnly);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>

## Adding a Pickup

A pickup actor can be directly added to the **Inventory Manager** without any conversions.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_add_pickup.png" alt="Add pickup to inventory"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Interact(AExamplePickup* Pickup)
        {
            FInventoryItemContext& Result;
            InventoryManager-&gt;Result(Pickup, Result);
        }
        </code-block>
    </tab>
</tabs>
