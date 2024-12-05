# Durability
<primary-label ref="inventory"/>

Enables the **durable** trait, along with the accompanying **Wear** and **Repair** operations. 

Durable items can be indestructible or break, which tags them as `Inventory.Item.Trait.Indestructible` and 
`Inventory.Item.Trait.Broken`, respectively. 

## Tracking Durability

The fragment provides the following ways to track an item's durability:

1. Via the `GetDurability` function, for occasional queries on the current durability.
2. Via the `OnDurabilityChanged` delegate, which broadcasts each time the value changes.

## Broken Items

When the durability reaches zero, an item is considered **Broken** and is tagged as `Inventory.Item.Trait.Broken`. You
can also query if an item is broken using the `IsBroken` function from this fragment.

Items can also have their wear effect disabled, making them **indestructible**. These items are tagged as `Inventory.Item.Trait.Indestructible`.
and this feature can also be checked using the `IsIndestructible` function from this fragment.

> You can automatically remove a broken item by tracking changes in the durability. When the item breaks, you can remove
> it via the appropriate operation in the Inventory Manager.

## Wear Operation

This fragment provides the **Wear** operation, which can be created via the `CreateWearPayload` function. It reduces the
item's durability and marks the item as broken, by tagging as `Inventory.Item.Broken`.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_wear_operation.png" alt="Wear operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Wear(UNinjaInventoryItem* Item, int32 WearAmount)
        {
            // If not set, the Wear Amount in the payload function will default to 10.
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateWearPayload(Item, WearAmount);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>

If your design requires a direct approach to adding wear, you can use the function exposed by the fragment. Please note
that it becomes your responsibility to manage **network authority**.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_wear_function.png" alt="Wear function sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UDamageManager::AddWear(UNinjaInventoryItem* Item, int32 WearAmount)
        {
            UItemFragment_Durability* DurabilityFragment = Item->FindFragment&lt;UItemFragment_Durability&gt;();
            DurabilityFragment->AddWear(Item, WearAmount);
        }
        </code-block>
    </tab>
</tabs>

> All functions and operations used to add **wear** will check if the item can actually break, before applying changes
> to the durability. You don't need to perform these validations!
{style="note"}

## Repair Operation

This fragment provides the **Restore** operation, which can be created via the `CreateRestoreRepair` function. It 
restores the item's durability to its original value, and it removes the `Inventory.Item.Broken` Gameplay Tag.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_repair_operation.png" alt="Repair operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Repair(UNinjaInventoryItem* Item)
        {
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateRepairPayload(Item);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>