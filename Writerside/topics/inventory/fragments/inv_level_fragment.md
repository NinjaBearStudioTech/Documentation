# Level
<primary-label ref="inventory"/>

Defines the item level, optionally applying **upgradeable** trait, which enables the **Upgrade** operation.

Upgradeable items are tagged as `Inventory.Item.Trait.Upgradeable`.

## Minimum and Maximum Values

An item's level must be between zero and whatever value is specified in the fragment as **Maximum Level**.

All values set to the `SetLevel` or `Upgrade` functions, or via the **Upgrade Operation** will always ensure that the
incoming value is clamped to those limits.

## Tracking Levels

The fragment provides the following ways to track an item's level:

1. Via the `GetLevel` function, for occasional queries on the current level.
2. Via the `OnLevelChanged` delegate, which broadcasts each time the value changes.

## Level Attributes

The [Attribute Set](inv_attributes.md) included with this inventory system provides two attributes related to the item
level, the **Equipment Level** and the **Average Equipment Level**. 

This fragment works in conjunction with those fragments. Whenever an **item** is added to an **equipment slot**, thus
initializing an **equipment**, it will contribute to both attributes, increasing the total and average equipment level.

## Gameplay Effects

Other objects in the system can use the item level as the effect level for a Gameplay Effect that must be applied.
This is very useful if you want to the magnitudes in your Gameplay Effect to **scale** based on the item's **power**. 

## Upgrade Operation

During an **upgrade**, the level can be modified in two ways: **absolute** or **incremental** value.

- **Absolute**: The value provided in the operation **replaces** the current level.
- **Incremental**: The value provided is **added** to the current level. 

> Incremental updates can be useful when the current level is unknown, but it must be updated by a given amount.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_upgrade_operation.png" alt="Upgrade operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Upgrade(UNinjaInventoryItem* Item, int32 Value, bIncrement)
        {
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateUpgradePayload(Item, Value, bIncrement);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>

If your design requires a direct approach to upgrade an item, you can use the function exposed by the fragment. Please note
that it becomes your responsibility to manage **network authority**.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_upgrade_function.png" alt="Upgrade function sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UWeaponManager::ImproveWeapon(UNinjaInventoryItem* Item, int32 Value, bIncrement)
        {
            UItemFragment_Level* LevelFragment = Item->FindFragment&lt;UItemFragment_Level&gt;();
            if (bIncrement)
            {
                LevelFragment->Upgrade(Item, Value);
            }
            else
            {
                LevelFragment->SetLevel(Item, Value);
            }
        }
        </code-block>
    </tab>
</tabs>

> For the upgrade operation you can always decide if you want to provide an absolute level or increment the level by
> a certain amount.
