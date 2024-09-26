# Gameplay Effect
<primary-label ref="inventory"/>

Allows applying arbitrary **Gameplay Effects** when an item is added to the inventory. Effects that are not **instant**
will also be removed when the item leaves the inventory.

## Effect Level

This fragment allows you to set any Effect Level that you want, but it can also use the **item level** for that.

This is useful if you want to have scalable Gameplay Effects, based on the actual item that is applying them. If the
fragment is set to use the item level, but the item does not provide that fragment, then the Effect Level property is
used.

## Item Lifecycle

The Gameplay Effect is applied and removed when the item is added and removed from the inventory. This is useful to
implement items that must provide some bonus or penalty, just for being in the inventory.

## Set By Caller Magnitudes

Gameplay Effects can have dynamic values set externally by their caller, via the `SetByCallerMagnitude` feature.
This fragment allows you to define values to data tags that will be set to the Gameplay Effect applied.
