# Inventory Integration
<primary-label ref="combat"/> 

<tldr> 
    <ul> 
        <li>Use <code>ANinjaCombatEquipmentWeaponActor</code> or add <code>UNinjaEquipmentActorComponent</code> to your weapon actor.</li>
        <li>Replace the <b>Weapon Manager</b> with <code>UNinjaCombatEquipmentAdapterComponent</code> to fetch weapons from inventory.</li>
        <li>Configure all weapon-related data (attachments, sockets, features) directly on the <b>Inventory Item</b>.</li> 
    </ul> 
</tldr>

Ninja Combat introduces streamlined and flexible integration with [**Ninja Inventory**](inv_overview.md), where all  
weapon configuration is now handled by the **Inventory System**, while the Combat System simply requests weapons from it.

This integration is automatically enabled when both plugins are installed under the same folder structure, 
`{Project}/Plugins/NinjaBearStudio`, or both versions are installed from the Unreal store.

Once set up:

- Weapon spawning, attachment, features, and configuration are all handled by the **Inventory system**.
- The Combat system **no longer directly manages weapons**. Instead, it requests the correct weapon actor for each equipment slot.
- You can define **weapon-specific behavior** through **item fragments**, such as projectile behavior, combo tables, special abilities, or socket attachments.

> **Weapon Queries**
> 
> Differently than the default Weapon Manager, Weapon queries will be executed against the Item Data Asset, and not the 
> weapon class!
{style="note"}

## Weapon Actors
To make your weapon actors compatible with the Inventory + Combat integration, choose one of the following options:

- **Option 1 (recommended)**: Use `ANinjaCombatEquipmentWeaponActor` as your base weapon class. Consider creating your own **base subclass**, for project-specific logic.
- **Option 2**: If you cannot modify your weapon hierarchy, attach a `UNinjaEquipmentActorComponent` to your existing custom weapon actor class.

This allows the actor to represent an equipped item and receive runtime data from the inventory, such as:

- The item instance that backs the actor.
- Owner and socket data used for proper attachment.
- Fragments that define weapon stats, features, level, and other behavior.

<procedure title="Creating Inventory Weapons" collapsible="true"> 
    <step>If you're creating a new weapon actor, use <code>ANinjaCombatEquipmentWeaponActor</code> as your base class.</step> 
    <step>If you're using an existing hierarchy, simply add <code>UNinjaEquipmentActorComponent</code> to your actor.</step> 
    <step>Set your weapon actor as the <b>Actor Class</b> in the Inventory Equipment Fragment for the item.</step>
    <note>
        <p><b>Weapons are always Equipment Instances</b></p>
        <p>Weapons are always implemented as <b>Equipment Actors</b>, as they represent items with <b>physical presence</b> and <b>dedicated in-world logic</b>.</p>
    </note>
</procedure>

## Weapon Manager
To bridge the Combat System with the Inventory System, use a specialized Weapon Manager that knows how to fetch weapons 
from equipped inventory items.

Use the component `UNinjaCombatEquipmentAdapterComponent`, which implements `ICombatWeaponManagerInterface` and automatically 
integrates with Ninja Inventory, retrieving weapons from the [Inventory Manager](inv_inventory_management.md).

<procedure title="Using the Equipment Weapon Manager" collapsible="true"> 
    <step>Add a <b>Ninja Combat Equipment Adapter Component</b> to your character (search for <code>Equipment Adapter</code>).</step> 
    <step>In your <code>ICombatSystemInterface</code> implementation, return this component in <code>GetWeaponManager()</code>.</step> 
    <note>
        <p><b>Avoid Weapon Manager Duplicates</b></p>
        <p>If you're using the Equipment Adapter component, ensure that no other Weapon Manager component is active on your character.</p>
    </note>
</procedure>