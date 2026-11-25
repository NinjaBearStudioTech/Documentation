# Build a Key Remapping Menu
<primary-label ref="input"/>
<secondary-label ref="guide"/>
<secondary-label ref="experimental"/>

Give the local player a Jump binding they can change, save, and reset. Start with the controller and a working Jump action from [First Steps](ipt_first_steps.md). This example uses the first key slot and UMG ViewModels.

<procedure title="Make Jump available to the settings menu">
    <step><p>Open <b>Project Settings → Engine → Enhanced Input → User Settings</b>. Enable User Settings. Set <b>User Settings Class</b> to <code>NinjaInputUserSettings</code> and <b>Default Player Mappable Key Profile</b> to <code>NinjaInputPlayerMappableKeyProfile</code>, or your subclasses.</p></step>
    <step><p>In the active mapping context, select the Jump key mapping. Choose <b>Override Settings</b> and <code>NinjaInputPlayerMappableKeySettings</code>. Give the mapping a stable name such as Jump_Keyboard, a Display Name of Jump, and a Display Category of Movement. Choose the keyboard/mouse Input Filter. Use unique names for distinct bindings.</p></step>
    <step><p>Keep notification of user settings enabled when registering the context. A mapping must be known to the local player's profile before the menu can list it.</p></step>
</procedure>

<img src="ipt_remapping_mappable_key_settings.png" alt="Player-mappable name, category, and input filter for a binding" width="720" border-effect="line"/>

<procedure title="Build the menu from the row up">
    <step><p>In a row Widget Blueprint, add <b>Key Mapping Entry ViewModel</b> with creation type <b>Manual</b>. Bind the label to DisplayName and the displayed key to CurrentKey. Use a key selector and send the selected key to <b>Rebind Key to First Slot</b>. Wire a Reset button to <b>Reset Key Binding</b>.</p></step>
    <step><p>Create a category widget with a manual <b>Key Mapping Category ViewModel</b>. Use DisplayCategory for the heading. Pass each item in <b>Get Bindings</b> to a row as its manual ViewModel. Use <b>Get Gamepad Bindings</b> or <b>Get Keyboard And Mouse Bindings</b> for separate device tabs.</p></step>
    <step><p>In the menu widget, add <b>Key Mappings ViewModel</b> with creation type <b>Resolver</b> and choose <b>Input Resolver</b>. Bind GetCategories to the category list and pass each category ViewModel to its widget. With a ViewModel extension on a panel, bind the collection to <b>Set Items</b>.</p></step>
    <step><p>Create the menu for the local Player Controller and show it. Wire Apply to <b>Save Input Settings</b> on its root ViewModel. Use <b>Is Saving Settings</b> to disable Apply while a save is in progress.</p></step>
</procedure>

<img src="ipt_remapping_mvvm_resolver_init.png" alt="Input Resolver selected for the root Key Mappings ViewModel" width="720" border-effect="line"/>

## Customize the Rebind

For a second slot or a custom key picker, call `RebindKey` with `FMapPlayerKeyArgs` containing the mapping name, new key, and slot. The supplied reset helper restores the first slot. To report a rejected mapping yourself, call `RemapKey` on the manager and check its result. Version 6.1.20 also returns the failure reasons. To show button icons, configure platform controller data in Common UI and bind **Icon Brush** on the entry.

## Try It in Play

Change Jump to a spare key, apply, close the menu, and jump with the new key. Start another session with the same local profile and check the binding. Reset it, save, and test the original key. If the menu is empty, check that the context was registered with user settings and that the root widget has the owning player.
