# Gameplay Effects
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Gameplay Effects can be applied by Items, through Item Fragments extending the <code>GameplayEffect</code> Fragment.</li>
        <li>Gameplay Effects can be applied by Equipment, when the state in which they are defined becomes active.</li>
        <li>Gameplay Effects with any duration are also be removed when their Item is removed or Equipment State deactivates.</li>
        <li>Data is transferred from Item Fragments implementing the <code>ItemMagnitudeValue</code> interface, to Equipment Gameplay Effects, via <code>SetByCallerMagnitude</code> calls.</li>
        <li>The value defined for an Item Level, in the Item Level Fragment, can also be used as the Effect Level for Equipment Gameplay Effects.</li>
    </ul>
</tldr>

Gameplay Effects are used both by Items (via Fragments) and Equipment to set Attribute values, apply states via
Gameplay Tags, grant Gameplay Abilities, or bridging functionality with other external systems.

## Item Effects

Item Effects are applied, or at least defined, by Item Fragments. There are several ways these effects can be added or 
removed from the owner.

The first and most straightforward method is via the `GameplayEffect` fragment or its subclasses. This approach is 
useful if the item's presence in the Inventory is sufficient to warrant benefits or harmful effects to the owner. Effects 
with a _duration_ or set to _infinite_ will also be removed when the item is removed from the Inventory.

The `GameplayEffect` fragment is very flexible, as it supports [Dynamic Values](#dynamic-values "Dynamic Values") that 
can be set directly in the fragment and then transferred to the Item Gameplay Effect.

Fragments can also apply and remove Gameplay Effects via their Operations, in which case their Gameplay Effects are
granted
when a specific Fragment Operation is triggered. An example of this is the **Consumable** Fragment. You can know more
about
Fragment Operations in the [](inv_items_and_fragments.md) page.

Other fragments can manage their Gameplay Effects based on certain events, such as the **Equipment Fragment**, which 
applies the Equipment Level Effect when the item is in an Active Equipment State. This is an advanced use case, where
custom logic was necessary.

## Equipment Effects

Equipment Effects are applied when the Equipment State in which they are defined becomes active. Gameplay Effects with a 
_duration_ or set to _infinite_ will be automatically removed when their Equipment State deactivates.

If the Equipment's backing Item contains a Level fragment, the current Equipment Level set in that fragment will be 
transferred to any Gameplay Effects set by the active Equipment State at the moment the effect is applied. The value will 
be set in the Gameplay Effect using the `Inventory.Item.Data.Level` Gameplay Tag.

The Item Level can also be used as the Gameplay Effect Level when Equipment-related effects are being applied. This is 
useful if your Gameplay Effects scale based on the Equipment Level.

Additionally, any other fragments providing magnitude value via the appropriate interface are collected and their values 
are applied to the Gameplay Effect. You can read more about this in the [Dynamic Values](#dynamic-values "Dynamic Values") 
section.

## Dynamic Values
<secondary-label ref="advanced"/>

Items and Fragments can provide many types of values that are relevant to Gameplay Effects. The Gameplay Effect class 
offers three ways to retrieve values from their back-end:

1. **Set By Caller Magnitudes**: Allows external objects to set magnitudes via Gameplay Tags or Key Names.
2. **Magnitude Calculation Classes**: Contains logic used to obtain a magnitude value.
3. **Effect Execution Classes**: Overrides the entire effect execution.

The Inventory System leverages the first option to transfer values from Items, Fragments, and Equipment to Gameplay 
Effects applied by Item and Equipment instances. The `ItemMagnitudeValue` interface enables this functionality, being 
implemented by objects that want to contribute magnitude values.

### Magnitudes in Fragment Gameplay Effects

The simplest way to set dynamic values for Gameplay Effects applied by Fragments is to use the `Gameplay Effect` fragment. 
or Fragments derived from it. Such fragments can obtain dynamic values in two ways:

1. **Manually Set Values**: Values are manually set in the `EffectMagnitudes` map using a Data Tag and the actual value. 
This approach is useful for dynamic values derived from static ones defined in the fragment itself.

2. **Overridden Values**: Values returned by the `TryOverrideDefaultMagnitudeValue` function. This approach is useful 
for dynamic values determined by custom logic or retrieved from other sources, such as the owning Item or other objects 
accessible from it.

> **Be careful with stack overflows!**
>
> A fragment should not query and provide dynamic values to the backing item via the `ItemMagnitudeValue` Interface.
>
> Having both roles in the same fragment will result in a stack overflow, as the fragment requests a value from the 
> backing item, and the item will request a value back from the fragment!
{style="warning"}

### Magnitudes in Equipment Gameplay Effects

Gameplay Effects applied by Equipment States can also benefit from dynamic values provided by their backing Items and, 
indirectly, the Item's Fragments.

When an Equipment State activates and applies its Gameplay Effects, it collects dynamic magnitudes provided by the backing 
item via the `ItemMagnitudeValue` interface. The default item implementation cascades that call to all Fragments implementing 
the same interface. All values are collected into a map and then returned, allowing them to be applied to the Gameplay Effect.

Another option, configurable in the Gameplay Effect settings for an Equipment State, is to use the Item Level as the Effect 
Level. When this option is set to true, the system searches for a fragment that implements the core `UpgradeableItem` 
interface, such as the **Item Level** fragment, and sets the Effect Level to the current item level value.

> **Equipment and the `ItemMagnitudeValue` Interface**
>
> The default `NinjaEquipment` does not implement the `ItemMagnitudeValue` interface. 
> 
> However, if you create your own Equipment class and implement this interface, values will be automatically retrieved 
> from it, without any further changes being required!
{style="note"}
