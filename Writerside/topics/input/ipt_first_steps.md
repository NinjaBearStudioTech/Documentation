# First Steps with Ninja Input
<primary-label ref="input"/>

This page guides you through the first steps for **Ninja Input**. Make sure to check the [**Input Setup**](ipt_setup.md)
instructions before continuing.

The following steps aim to provide **a player controller, fully configured to use Ninja Input**. This includes optional
steps to ensure that certain pawns can provide **additional input setups when possessed**.

This page assumes you are starting from a new project, using something like the **Third Person Template**, so the plan 
is to migrate from the default setup to a Ninja Input configuration.

## Input Assets

Ninja Input deals with a few different Input Assets, which are covered in detail in the documentation. For now, keep in
mind that an input setup involves the following assets:

- **Input Action**: Represents a specific action, its triggers and modifiers. Introduced by the **Enhanced Input** module.
- **Input Mapping Context**: Maps certain actions to actual keys and may introduce additional modifiers. Introduced by the **Enhanced Input** module.
- **Input Handler**: Executes on events triggered by actions. Introduced by **Ninja Input**.
- **Input Setup**: Maps all actions in an Input Mapping Context asset, to specific handlers. Introduced by **Ninja Input**.

<procedure title="Configure the Input Setup" collapsible="true">
    <step>In the <b>Content Browser</b>, navigate to your <b>Input</b> folder.</step>
    <step>
        <p>Create a new <b>Input Setup</b>.</p> 
        <p>You can do so by right-clicking an empty area in the <b>Content Browser</b>, then navigating to <b>Ninja Bear Studio</b> &rarr; <b>Ninja Input</b> &rarr; <b>Input Setup</b>.</p>
    </step>
    <step>Open the new <b>Input Setup</b> and add your <b>Input Mapping Context</b>.</step>
    <step>Add three new entries to the <b>Input Handlers</b> list, selecting: <code>Character: Move</code>, <code>Character: Look</code> and <code>Character: Jump</code>.</step>
    <step>
        <p>For each one of these entries, expand their properties and add the appropriate <b>Input Action</b>.</p>
        <p>By default, the provided handlers reference Input Actions starting with `IA_NI`, which are included with Ninja Input.</p> 
        <p>You can either adopt them in your Input Mapping Context, or <b>replace them</b> with your project-related counterparts.</p>
        <img src="ipt_setup_input_setup_data.png" alt="Configure Input Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <tip>
        <p><b>Input Validation</b></p>
        <p>If you get a <b>Validation Error</b> while saving your <b>Input Setup</b>, it means there are <b>Input Actions</b> in your Input Mapping Context not related to any <b>Input Handler</b>.</p>
        <p>Check the <b>Message Log Window</b> and you will find which Input Actions are missing an Input Handler.</p>
        <p>This validation ensures every mapped action is correctly handled at runtime and <b>prevents input failures or unexpected behavior</b>.</p>
    </tip>
</procedure>

## Player Controller

The Input Manager Component is the most important component in the framework. It is responsible for registering, receiving
and dispatching **Input Actions** to the correct **Input Handlers**, small objects dedicated to handle specific inputs.

This component can be added to either the **Player Controller** or **Player Character**, but **not both**. For prototypes
and smaller projects, both are valid options, but in general, the **Player Controller is the best choice**, since:

- It leads to fewer requirements in the Player Character, allowing a leaner **character hierarchy**.
- Offers support for **different pawns**, providing their own Input Setups when possessed, via `InputSetupProviderInterface`.

<procedure title="Add the Input Manager Component" collapsible="true" default-state="expanded">
    <step>Create a <b>Player Controller</b> if you don't have one in your project yet. Make sure to set this Player Controller in your <b>Game Mode</b>.</step>
    <step>Add the <b>Input Manager Component</b>, <code>NinjaInputManagerComponent</code>, to your Player Controller.</step>
    <step>Add your <b>Input Setup</b> to the <b>Input Manager Component</b>.</step>
</procedure>

## Player Character

Possessed characters (or pawns) can provide additional features that work in conjunction with the Input Manager Component.

### Ability System Component
<secondary-label ref="optional"/>

If you plan to use Ninja Input with the **Gameplay Ability System**, make sure that your character implements the
**Ability System Interface** (`IAbilitySystemInterface`) and returns a valid **Ability System Component**.

### Forward Reference
<secondary-label ref="optional"/>

Certain types of games, such as a **top-down game with WASD movement** will require a reference that movement handlers
can use to calculate **forward** and **right** directions. In Ninja Input, this reference is called **Forward Reference**.

The Forward Reference is a **Scene Component** that always points toward the desired world-forward direction, usually 
world North or **Positive X**, instead of following the character rotation.

Any **Scene Component** in the **Character** can be used as a Forward Reference, but the most common choices are either
the **Camera** or an **Arrow Component**. To mark a component as the Forward Reference, add the `Input.Component.ForwardReference` 
component tag to it.

> **Automatic Creation**
>
> The Input Manager component can **automatically create a Forward Reference**. You can enable that behavior by
> setting the `ShouldCreateForwardReference` property to `true`, in the Input Manager defaults panel.
> 
> You can also modify the default creation logic, by overriding the `CreateForwardReference` function, in the **Input
> Manager Component**.
{style="tip"}

If you need more control over your Forward Reference component, then you can create your own Forward Reference and
assign the appropriate Gameplay Tag.

<procedure title="Add a Forward Reference component" collapsible="true" default-state="expanded">
    <step>In your <b>Base Character Class</b>, add an <b>Arrow Component</b>.</step>
    <step>Set the component's rotation mode to <b>Absolute Rotation</b>.</step>
    <step>Add the <code>Input.Component.ForwardReference</code> tag to the list of <b>Component Tags</b>.</step>
</procedure>

### Input Provider Interface
<secondary-label ref="optional"/>

If you plan on supporting multiple pawns, such as humanoids, vehicles or mounts, where each pawn has a different control
scheme, then consider allowing each pawn to support their own **Input Setups**. 

These setups are added when the pawn is **possessed**, in conjunction to the ones already defined in the Input Manager 
Component, and removed when the pawn is **unpossessed**. **Duplicated Input Setups are rejected**.

> **Player Controller Only**
>
> The Input Manager Component will look for the `InputSetupProviderInterface` interface in **Pawns** being **possessed**
> and **unpossessed**, so this setup only works when your Input Manager is added to the **Player Controller**.
{style="tip"}

<procedure title="Implement the Setup Provider Interface" collapsible="true" default-state="expanded">
    <step>Add the <code>InputSetupProviderInterface</code> to the pawn or character that will provide specific Input Setups.</step>
    <step>Create an array of <code>NinjaInputSetupDataAsset</code> references, so you can add Input Setups relevant to the Pawn.</step>
    <step>
        <p>Implement the <code>GetInputSetups</code> function, returning the array of setups.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="ipt_handlers_setup_provider.png" alt="Using the Input Provider Interface" border-effect="line" thumbnail="true" width="600"/>
            </tab>
            <tab title="C++" group-key="c++">
                <p><b>Header</b></p>
                <code-block lang="c++" src="ipt_provider_interface.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="ipt_provider_interface.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

## Next Steps
At this point, you have a working input setup with the following features:

1. Each **Input Action** activates its own **Input Handler**. 
2. The Player Controller owns the **Input Manager**.
3. Optionally, the base character has a **forward reference**.
4. Optionally, the base character can provide its own **Input Setup**.
 
From here, you can:

- Read more about the [**Input Manager Component**](ipt_input_management.md).
- Create custom [**Input Handlers**](ipt_input_handlers.md).
