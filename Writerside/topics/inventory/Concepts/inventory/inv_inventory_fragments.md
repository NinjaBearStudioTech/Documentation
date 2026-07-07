# Item Fragments
<primary-label ref="inventory"/>

**Item Fragments** define modular behavior for inventory items. Each fragment adds a specific capability, such as being 
stackable, equippable, droppable, consumable, or usable as a container.

Fragments can contribute gameplay tags, runtime memory, operations, event handling, and integrations with other inventory 
systems. An item can combine multiple fragments to build its full behavior, such as a stackable consumable, a two-handed 
weapon, a nested bag, or a lootable item with quality and weight.

## Fragment Summary

| Fragment                | Summary                                                                                                                                                                    |
|-------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Consumable**          | Allows an item to be consumed, usually applying a Gameplay Effect to the owner. Supports single-use, stack-based charges, durability-based charges, or unlimited use.      |
| **Container Placement** | Defines where an item is stored, including its container and position. This is the standard placement fragment used by container layouts.                                  |
| **Dimensions**          | Defines the 2D spatial footprint of an item for spatial layouts, including width, height, rotation, and optional occupancy masks.                                          |
| **Drop**                | Allows an item to be removed from inventory and spawned into the world as a Pickup Actor.                                                                                  |
| **Durability**          | Tracks item wear, breakage, repair, and durability-based state.                                                                                                            |
| **Dynamic Attributes**  | Defines item-level attributes that may use fixed values, random ranges, or level-based tables. These can also be exported to Gameplay Effects as Set By Caller magnitudes. |
| **Economy**             | Enables buying and selling logic, including price calculation, wealth validation, and item transfer.                                                                       |
| **Equipment**           | Defines how an item behaves when equipped, including equipment states, runtime equipment instances, and soft asset references.                                             |
| **Firearm**             | Allows configuration of ammo for a firearm.                                                                                                                                |
| **Gameplay Effect**     | Applies a Gameplay Effect to the owner while the item is active and its conditions are valid.                                                                              |
| **Key**                 | Allows an item to unlock external actors, optionally consuming the key when used.                                                                                          |
| **Level**               | Tracks an item's level and upgrade state. Also provides level data to other fragments, such as Gameplay Effect and Dynamic Attributes.                                     |
| **Linked Container**    | Specialized placement fragment for items that occupy multiple containers at once, such as two-handed weapons occupying both main-hand and off-hand slots.                  |
| **Loot**                | Marks an item as eligible for loot selection and provides loot tags, context requirements, and selection weight.                                                           |
| **Nested Container**    | Gives an item its own internal container, allowing bags, crates, boxes, and similar storage items.                                                                         |
| **Offhand**             | Defines an offhand anchor socket for equipment, usually used by animation systems such as FABRIK, CCDIK, or Control Rig.                                                   |
| **Prerequisites**       | Evaluates custom prerequisite objects to determine whether an item can be added to an inventory.                                                                           |
| **Quality**             | Defines the item's quality tier, display text, color, and quality gameplay tag using the project's quality mapping table.                                                  |
| **Stack and Quantity**  | Defines stack size, maximum inventory quantity, stack merging, splitting, and stack-size events.                                                                           |
| **User Interface**      | Provides UI-facing item data such as display name, category, description, and icon.                                                                                        |
| **Weight**              | Defines item weight and contributes to inventory encumbrance calculations, including stack-aware weight totals.                                                            |

Fragment memories store **per-item runtime state** for fragments that need data beyond the static item definition. These
data structures can be **saved**, **loaded**, **replicated**, or **transferred** when items move between inventories.

| Fragment                | Memory                                       | Description                                                                                                                                  |
|-------------------------|----------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------|
| **Container Placement** | `InventoryItemFragmentContainerMemory`       | Stores the current container and position for the item.                                                                                      |
| **Dimensions**          | `InventoryItemFragmentDimensionsMemory`      | Stores the item's current rotation state.                                                                                                    |
| **Durability**          | `InventoryItemFragmentDurabilityMemory`      | Stores the item's current durability.                                                                                                        |
| **Dynamic Attributes**  | `InventoryItemFragmentAttributeMemory`       | Stores default dynamic attribute values. Runtime attributes are stored separately by the item instance for optimized replication and access. |
| **Equipment**           | `InventoryItemFragmentEquipmentMemory`       | Stores the item's current equipment state. Created only when the item is placed in an Equipment layout.                                      |
| **Level**               | `InventoryItemFragmentLevelMemory`           | Stores the item's current level.                                                                                                             |
| **Linked Container**    | `InventoryItemFragmentContainerMemory`       | Stores the linked container reference and position used by the linked placement.                                                             |
| **Nested Container**    | `InventoryItemFragmentNestedContainerMemory` | Stores the nested container key owned by the item.                                                                                           |
| **Stack and Quantity**  | `InventoryItemFragmentStackMemory`           | Stores the item's current stack size.                                                                                                        |

## Fragment Operations

The following operations are exposed by the fragments for runtime queries, state changes, and integration with inventory 
systems.

| Fragment                | Operation                            | Description                                                                                          |
|-------------------------|--------------------------------------|------------------------------------------------------------------------------------------------------|
| **Consumable**          | `CanConsume`                         | Returns whether the item can currently be consumed.                                                  |
| **Consumable**          | `Consume`                            | Applies the configured effect and updates stack or durability when applicable.                       |
| **Consumable**          | `ConsumeWithCallback`                | Consumes the item and returns the applied Gameplay Effect handle through a callback.                 |
| **Container Placement** | `GetDefaultContainer`                | Returns the item's default container from memory.                                                    |
| **Container Placement** | `GetContainer`                       | Returns the container currently storing the item.                                                    |
| **Container Placement** | `GetPosition`                        | Returns the item's current position in its container.                                                |
| **Container Placement** | `SetContainerAndPosition`            | Manually updates the item's container and position.                                                  |
| **Container Placement** | `GetOrSelectContainerForItem`        | Uses memory, default placement, preferred containers, or dynamic selection to resolve a container.   |
| **Container Placement** | `SelectContainerForItem`             | Finds the best container for an item.                                                                |
| **Container Placement** | `SelectPositionForItem`              | Finds a valid position in the item's current container.                                              |
| **Container Placement** | `SelectPositionForItemInContainer`   | Finds a valid position in a specific container.                                                      |
| **Container Placement** | `TryAddItem`                         | Attempts to add an item to a container and position.                                                 |
| **Container Placement** | `TryMoveItem`                        | Attempts to move an item, swapping when needed.                                                      |
| **Container Placement** | `TrySwapItems`                       | Swaps two items between their positions.                                                             |
| **Dimensions**          | `GetBaseDimensions`                  | Returns the item's original width and height.                                                        |
| **Dimensions**          | `GetDimensions`                      | Returns the current dimensions, including rotation.                                                  |
| **Dimensions**          | `GetDimensionsFromDefaultMemory`     | Returns dimensions from default item memory.                                                         |
| **Dimensions**          | `CanRotate`                          | Returns whether the item supports rotation.                                                          |
| **Dimensions**          | `CanRotateItemInPlace`               | Checks whether the item can rotate in its current occupied space.                                    |
| **Dimensions**          | `IsRotated`                          | Returns whether the item is currently rotated.                                                       |
| **Dimensions**          | `IsRotatedFromDefaultMemory`         | Returns whether default memory marks the item as rotated.                                            |
| **Dimensions**          | `SetRotated`                         | Updates the item's rotation state.                                                                   |
| **Drop**                | `Drop`                               | Spawns a Pickup Actor using the configured Environment Query and removes the item from inventory.    |
| **Drop**                | `DropAtLocation`                     | Spawns a Pickup Actor at a specific location.                                                        |
| **Durability**          | `CanBreak`                           | Returns whether the item can break.                                                                  |
| **Durability**          | `IsBroken`                           | Returns whether the item is currently broken.                                                        |
| **Durability**          | `IsBrokenFromDefaultMemory`          | Returns whether default item memory represents a broken item.                                        |
| **Durability**          | `IsIndestructible`                   | Returns whether the fragment marks the item as indestructible.                                       |
| **Durability**          | `GetMaximumDurability`               | Returns the item's maximum durability.                                                               |
| **Durability**          | `GetDurability`                      | Returns the item's current durability.                                                               |
| **Durability**          | `GetDurabilityFromDefaultMemory`     | Returns durability from default item memory.                                                         |
| **Durability**          | `SetDurability`                      | Sets the item's current durability.                                                                  |
| **Durability**          | `AddWear`                            | Reduces durability by a given amount.                                                                |
| **Durability**          | `Repair`                             | Restores durability to full.                                                                         |
| **Dynamic Attributes**  | `HasAttribute`                       | Checks whether the item has an attribute matching a tag.                                             |
| **Dynamic Attributes**  | `GetAttribute`                       | Returns an attribute value.                                                                          |
| **Dynamic Attributes**  | `GetAllAttributes`                   | Returns all runtime attributes for the item.                                                         |
| **Dynamic Attributes**  | `GetAllAttributesFromDefaultMemory`  | Returns all attributes from default memory.                                                          |
| **Dynamic Attributes**  | `AddToDefaultItem`                   | Adds resolved attributes to default item data.                                                       |
| **Dynamic Attributes**  | `SetAttribute`                       | Sets an attribute value.                                                                             |
| **Dynamic Attributes**  | `RemoveAttribute`                    | Removes an attribute from the item.                                                                  |
| **Economy**             | `CanBeBought`                        | Returns whether the item is marked as buyable.                                                       |
| **Economy**             | `CanBeSold`                          | Returns whether the item can be sold.                                                                |
| **Economy**             | `CanBuy`                             | Checks whether the target has enough wealth to buy the item.                                         |
| **Economy**             | `CanSell`                            | Checks whether the source can sell the item to the target.                                           |
| **Economy**             | `GetBuyPrice`                        | Returns the unit buy price.                                                                          |
| **Economy**             | `GetSellPrice`                       | Returns the unit sell price.                                                                         |
| **Economy**             | `GetTotalBuyPrice`                   | Returns the stack-aware total buy price.                                                             |
| **Economy**             | `GetTotalSellPrice`                  | Returns the stack-aware total sell price.                                                            |
| **Economy**             | `Buy`                                | Transfers the item to the buyer and deducts wealth.                                                  |
| **Economy**             | `Sell`                               | Transfers the item and grants wealth to the seller.                                                  |
| **Equipment**           | `SetEquipmentState`                  | Updates the item's equipment state.                                                                  |
| **Equipment**           | `GetEquipmentState`                  | Returns the current equipment state.                                                                 |
| **Equipment**           | `GetCurrentEquipmentStateDefinition` | Returns the definition for the current equipment state.                                              |
| **Equipment**           | `GetEquipmentStateDefinition`        | Returns the definition for a specific equipment state.                                               |
| **Equipment**           | `GetAssetSoftPaths`                  | Returns soft asset paths referenced by equipment states.                                             |
| **Equipment**           | `GetEquipmentManager`                | Finds the Equipment Manager related to the item owner.                                               |
| **Equipment**           | `GetDefaultEquipmentClass`           | Returns the runtime equipment class used by the item.                                                |
| **Gameplay Effect**     | `ActivateItem`                       | Applies the Gameplay Effect when conditions pass.                                                    |
| **Gameplay Effect**     | `DeactivateItem`                     | Removes the Gameplay Effect.                                                                         |
| **Gameplay Effect**     | `CanApplyEffect`                     | Evaluates whether the effect should be applied.                                                      |
| **Gameplay Effect**     | `GetEffectLevel`                     | Returns the level used for the Gameplay Effect.                                                      |
| **Gameplay Effect**     | `ReapplyGameplayEffect`              | Removes and reapplies the Gameplay Effect.                                                           |
| **Gameplay Effect**     | `HandleItemEvent`                    | Responds to relevant item events, such as container or level changes.                                |
| **Gameplay Effect**     | `GetLevelFromFragment`               | Retrieves level data from the Level Fragment.                                                        |
| **Gameplay Effect**     | `GetLevelFromCurve`                  | Evaluates effect level from a curve.                                                                 |
| **Key**                 | `TryUseKey`                          | Attempts to use the key on an unlockable actor.                                                      |
| **Level**               | `CanUpgrade`                         | Returns whether the item can be upgraded.                                                            |
| **Level**               | `IsMaximumLevel`                     | Returns whether the item is at maximum level.                                                        |
| **Level**               | `GetLevel`                           | Returns the item's current level.                                                                    |
| **Level**               | `GetLevelFromDefaultMemory`          | Returns level from default item memory.                                                              |
| **Level**               | `GetMaximumLevel`                    | Returns the maximum item level.                                                                      |
| **Level**               | `SetLevel`                           | Sets the item's level.                                                                               |
| **Level**               | `Upgrade`                            | Increases the item level when possible.                                                              |
| **Linked Container**    | `GetLinkedContainer`                 | Returns the linked container associated with the item.                                               |
| **Linked Container**    | `MatchesPrimaryContainer`            | Checks whether a container matches the primary container query.                                      |
| **Linked Container**    | `MatchesLinkedContainer`             | Checks whether a container matches the linked container query.                                       |
| **Nested Container**    | `GetNestedContainer`                 | Returns the internal container owned by the item.                                                    |
| **Offhand**             | `GetOffHandSocketTransform`          | Returns the offhand anchor transform for an equipment instance.                                      |
| **Prerequisites**       | `EvaluatePrerequisites`              | Evaluates whether the item can be added to an inventory and returns a blocking reason if applicable. |
| **Quality**             | `GetQualityTag`                      | Returns the item's quality gameplay tag.                                                             |
| **Quality**             | `GetQualityText`                     | Returns the localized quality name.                                                                  |
| **Quality**             | `GetQualityColor`                    | Returns the quality color.                                                                           |
| **Stack and Quantity**  | `CanMergeStacks`                     | Checks whether two item stacks can merge.                                                            |
| **Stack and Quantity**  | `GetMaximumQuantity`                 | Returns the maximum quantity allowed in the inventory.                                               |
| **Stack and Quantity**  | `GetStackLimit`                      | Returns the maximum size of one stack.                                                               |
| **Stack and Quantity**  | `GetStackSize`                       | Returns the current stack size.                                                                      |
| **Stack and Quantity**  | `GetStackSizeFromDefaultMemory`      | Returns stack size from default item memory.                                                         |
| **Stack and Quantity**  | `SetStackSize`                       | Sets the stack size.                                                                                 |
| **Stack and Quantity**  | `MergeStacks`                        | Merges two stacks when possible.                                                                     |
| **Stack and Quantity**  | `SplitStack`                         | Splits a stack into a separate item.                                                                 |
| **Stack and Quantity**  | `CountItemQuantity`                  | Counts the total quantity of matching items in the inventory.                                        |
| **Stack and Quantity**  | `TryMergeIntoExistingStacks`         | Attempts to merge an item into existing incomplete stacks.                                           |
| **User Interface**      | `GetDisplayName`                     | Returns the item's display name.                                                                     |
| **User Interface**      | `GetCategory`                        | Returns the item's category text.                                                                    |
| **User Interface**      | `GetDescription`                     | Returns the item's description text.                                                                 |
| **User Interface**      | `GetIcon`                            | Returns the item icon.                                                                               |
| **Weight**              | `GetItemWeight`                      | Returns the total item weight, including stack size.                                                 |
| **Weight**              | `CalculateEncumbrance`               | Calculates total inventory encumbrance from valid items.                                             |
| **Weight**              | `RefreshEncumbranceAttribute`        | Updates the owner's encumbrance attribute.                                                           |

## Fragment Events

Fragment events are emitted when a fragment changes meaningful item state, such as placement, durability, level, stack 
size, or equipment state. These events allow inventory systems, UI, and gameplay logic to react to item changes without
tightly coupling to the fragment that produced them.

| Fragment                | Event                                            | Description                                                            |
|-------------------------|--------------------------------------------------|------------------------------------------------------------------------|
| **Container Placement** | `Inventory.Event.Item.PlacementInitialized`      | Emitted when the item's placement is initialized.                      |
| **Container Placement** | `Inventory.Event.Item.ContainerChanged`          | Emitted when the item's container changes.                             |
| **Container Placement** | `Inventory.Event.Item.PositionChanged`           | Emitted when the item's position changes.                              |
| **Dimensions**          | `Inventory.Event.Item.RotationChanged`           | Emitted when the item's rotation state changes.                        |
| **Drop**                | `Inventory.Event.Item.DroppedFromInventory`      | Emitted when the item is dropped and a Pickup Actor is spawned.        |
| **Durability**          | `Inventory.Event.Item.DurabilityChanged`         | Emitted when durability changes.                                       |
| **Dynamic Attributes**  | `Inventory.Event.Item.DynamicAttribute.Created`  | Emitted when a dynamic attribute is added.                             |
| **Dynamic Attributes**  | `Inventory.Event.Item.DynamicAttribute.Updated`  | Emitted when a dynamic attribute value changes.                        |
| **Dynamic Attributes**  | `Inventory.Event.Item.DynamicAttribute.Removed`  | Emitted when a dynamic attribute is removed.                           |
| **Equipment**           | `Inventory.Event.Item.EquipmentStateChanged`     | Emitted when the item's equipment state changes.                       |
| **Level**               | `Inventory.Event.Item.LevelChanged`              | Emitted when the item level changes.                                   |
| **Stack and Quantity**  | `Inventory.Event.Item.StackChanged`              | Emitted when the item stack size changes.                              |

Event payloads are the **data structures sent with fragment events**. They provide the context needed to understand what 
changed, such as the item involved, the previous value, and the new value. 

Systems listening to fragment events can use these payloads to update UI, trigger gameplay reactions, synchronize state, 
or respond to inventory changes without needing to query everything manually.

| Fragment                | Payload                                  | Events                                                                             |
|-------------------------|------------------------------------------|------------------------------------------------------------------------------------|
| **Container Placement** | `InventoryItemContainerPlacementPayload` | `PlacementInitialized`, `ContainerChanged`, `PositionChanged`                      |
| **Dimensions**          | `InventoryItemDimensionsPayload`         | `RotationChanged`                                                                  |
| **Drop**                | `InventoryItemDropPayload`               | `DroppedFromInventory`                                                             |
| **Durability**          | `InventoryItemDurabilityPayload`         | `DurabilityChanged`                                                                |
| **Dynamic Attributes**  | `InventoryItemAttributesPayload`         | `DynamicAttribute.Created`, `DynamicAttribute.Updated`, `DynamicAttribute.Removed` |
| **Equipment**           | `InventoryItemEquipmentEventPayload`     | `EquipmentStateChanged`                                                            |
| **Level**               | `InventoryItemLevelPayload`              | `LevelChanged`                                                                     |
| **Stack and Quantity**  | `InventoryItemStackAndQuantityPayload`   | `StackChanged`                                                                     |
