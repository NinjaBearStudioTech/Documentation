# Tag-Based Visibility
<primary-label ref="inventory"/>
<secondary-label ref="advanced"/>

<tldr>
    <p><b>Summary: Tag-Based Visibility</b></p>
    <ul>
        <li>Control whether an equipment actor is visible by tracking a specific <b>Gameplay Tag</b>.</li>
        <li>Visibility is automatically toggled on <b>GameplayTagAdded</b> / <b>GameplayTagRemoved</b> events.</li>
        <li>Optional delays (<code>DelayedWhenShown</code> / <code>DelayedWhenHidden</code>) allow smooth transitions without instantly popping actors in/out.</li>
        <li>Useful for setups where multiple equipment pieces remain active but only one is visible at a time.</li>
    </ul>
</tldr>

Equipment actors in **Ninja Inventory** can use a tag-driven approach to control their visibility in-game. This allows
developers to keep multiple weapons or tools **active and equipped** in the world while only displaying the ones that
should be **visible at a given moment**.

For example, a survival shooter might want a firearm to remain visible while a melee weapon stays hidden until the player
triggers a melee ability. Both are active and ready, but visibility is managed by tags.

## Configuration
Each equipment actor with a `UNinjaEquipmentActorComponent` can be configured with a **Visibility Tag**. When this tag
is present in the owning character's ASC (Ability System Component), the actor is shown. When it is removed, the actor is hidden.

This is handled entirely through **Gameplay Tag events**, usually driven by **Gameplay Effects** or other ASC-based logic.
For this purpose, the following properties can be used:

| Property            | Description                                                                        |
|---------------------|------------------------------------------------------------------------------------|
| `VisibilityTag`     | If set, this equipment is only visible if the tag is present in the owner's ASC.   |
| `DelayedWhenShown`  | If set, this delay is applied before showing the actor, due to the visibility tag. |
| `DelayedWhenHidden` | If set, this delay is applied before hiding the actor, due to the visibility tag.  |

> **Delays and Begin Play**
>
> Even though the visibility tag is checked during the component's **Begin Play** event, the delays are only applied
> when a **Gameplay Tag Event** is triggered by the Ability System Component.
{style="note"}

## Usage Example
The following example shows how to keep a **firearm** visible by default and, during a melee ability, **hide the firearm** and **show a melee weapon**. When the ability ends, visibility returns to the firearm.

<procedure title="Configuring tag-based visibility for actors" collapsible="true" default-state="expanded">
    <step title="Configure the firearm to use a visibility tag">
        <p>Assign the firearm's component a <code>Visibility Tag</code> of <code>Inventory.Equipment.Visibility.Firearm</code>.</p>  
        <p>Optionally set <code>Delayed when Shown</code> to a small value (e.g., <code>0.2</code>) to avoid instant pop-in when returning to the firearm.</p>
        <img src="inv_advanced_visibility_configuration_firearm.png" alt="Firearm component settings" thumbnail="true" border-effect="line"/>
    </step>
    <step title="Configure the melee weapon to use a visibility tag">
        <p>Assign the melee weapon's component a <code>Visibility Tag</code> of <code>Inventory.Equipment.Visibility.Melee</code>.</p>
        <p>Leave both delays at <code>0.0</code> for immediate swaps during the combo (or adjust if you want smoother transitions).</p>
        <img src="inv_advanced_visibility_configuration_melee.png" alt="Melee component settings" thumbnail="true" border-effect="line"/>
    </step>
    <step title="Create an Infinite Gameplay Effect for the firearm">
        <p>Create a Gameplay Effect (e.g., <b>GE_Visibility_Firearm</b>) with the following settings:</p>
        <ul>
            <li><b>Duration Policy:</b> Infinite</li>
            <li><b>Add Tags:</b> <code>Inventory.Equipment.Visibility.Firearm</code></li>
            <li><b>Ongoing Tag Requirements → Must Not Have Tags:</b> <code>Inventory.Equipment.Visibility.Melee</code> (so firearm visibility suspends while melee is active)</li>
        </ul>
        <img src="inv_advanced_visibility_effect_firearm.png" alt="Firearm visibility effect" thumbnail="true" border-effect="line"/>
    </step>
    <step title="Create an Infinite Gameplay Effect for the melee weapon">
        <p>Create a Gameplay Effect (e.g., <b>GE_Visibility_Melee</b>) with the following settings:</p>
        <ul>
            <li><b>Duration Policy:</b> Infinite</li>
            <li><b>Add Tags:</b> <code>Inventory.Equipment.Visibility.Melee</code></li>
        </ul>
        <img src="inv_advanced_visibility_effect_melee.png" alt="Melee visibility effect" thumbnail="true" border-effect="line"/>
    </step>
    <step title="Grant the firearm effect by default">
        <p>Using your GAS setup (Ninja GAS in this example), add <b>GE_Visibility_Firearm</b> to the player's <b>Default Gameplay Effects</b> so the firearm starts visible when the player spawns.</p>
        <img src="inv_advanced_visibility_data_asset.png" alt="Grant firearm effect by default" thumbnail="true" border-effect="line"/>
    </step>
    <step title="Apply the melee effect on ability activation">
        <p>In the melee ability (e.g., a combo ability), apply <b>GE_Visibility_Melee</b> on <b>ActivateAbility</b> and save the returned handle for later removal.</p>
        <img src="inv_advanced_visibility_ability_activate.png" alt="Apply melee effect on ability activate" thumbnail="true" border-effect="line"/>
    </step>
    <step title="Remove the melee effect when the ability ends">
        <p>On <b>EndAbility</b>, remove <b>GE_Visibility_Melee</b> using the saved handle. This restores the firearm's visibility effect.</p>
        <img src="inv_advanced_visibility_ability_end.png" alt="Remove melee effect on ability end" thumbnail="true" border-effect="line"/>
    </step>
</procedure>
