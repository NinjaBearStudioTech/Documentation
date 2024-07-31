# Consumable
<primary-label ref="inventory"/>

Enables the **consumable** trait, along with the accompanying **Consume** operation. 

Consumable items are tagged as `Inventory.Item.Trait.Consumable`.

## Tracking Charges

Charges are tracked based on the value set for the `Charges` property in the fragment. These are the options:

- **Gameplay Attribute**: The item uses a Gameplay Attribute to track charges.
- **Stack Fragment**: The item uses its own stack to track charges.
- **None**: No charges are tracked, you may still set a cooldown.

> If you are using a Gameplay Attribute, then make sure to also configure the Consume Gameplay Effect to decrease the 
> charges in the Attribute that keeps track of them!
{style="note"}

## Consume Operation

The Consume Fragment supports the "**Consume**" operation, which triggers the backing Gameplay Ability, responsible for
the GAS aspects and Animation.

Consuming the item applies the Gameplay Effect set in the Fragment, and optionally handles charges, as per the strategy
also set in the fragment.(Gameplay Attribute or Stack Fragment).

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_consume_operation.png" alt="Consume operation sample in Blueprints"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++">
        void UInventoryExamples::Consume(UNinjaInventoryItem* Item)
        {
            const TInstancedStruct&lt;FInventoryFragmentPayload&gt;&amp; Payload = UNinjaInventoryGameplayFunctionLibrary::CreateConsumePayload(Item);
            InventoryManager-&gt;TryPerformOperation(Payload);
        }
        </code-block>
    </tab>
</tabs>

## Consume Ability

The Consume Fragment needs a Gameplay Ability to actually execute. You must create your Gameplay Ability using the
`UInventoryAbility_ConsumeItem` ability as a base, and then assign that ability to your character.

You can find more information about this Ability in its own reference page, but for now, it's important to mention that
it will allow you to configure an Animation for this event. This animation can receive a Notify State to actually show
a consumable item.

## Animation Notify State
<secondary-label ref="wip"/>

The animation used to represent the Consume Operation most likely needs a mesh to represent the consumable itself. 

The `Attach Consumable Mesh` Notify State can be used to temporarily attach a mesh to the character, representing the
consumable being used. It has the following parameters:

| Parameter     | Description                                                                              |
|---------------|------------------------------------------------------------------------------------------|
| Mesh Type     | Type of mesh used to represent the consumable item.                                      |
| Mesh          | A **soft pointer** to the skeletal or static mesh.                                       |
| Slot Tag      | The Gameplay Tag used to find the proper Skeletal or Static Mesh component in the owner. |
| Attach Socket | An optional socket used to re-attach the component to an appropriate location.           |
| Slots to Hide | Slots that must be hidden while the consumable is attached. For example, the weapon.     |

> Even though this Notify State is stable as it is right now, it should evolve so in the future can obtain meshes 
> dynamically, from the actual item being consumed.

This Notify State uses **Soft Pointers** to the mesh assets, which are loaded using the **Asset Manager** as the Notify
State starts. Once it reaches its end, the handle to the loaded mesh is released.