# Input System
<primary-label ref="input"/>

<tldr>
    <p><b>Summary: Input Manager and Handlers</b></p>
    <br/>
    <ul>
        <li>Add the <b>Input Manager Component</b> to your <b>base character class</b> or <b>player controller</b>.</li>
        <li>Optionally, add a <b>Forward Reference</b> to your base character class.</li>
        <li>Remove default <b>Input Mapping Contexts</b> and <b>input logic</b> from your character class to prevent conflicts.</li>
        <li>Prepare and configure the <b>Input Setup</b>.</li>
    </ul>
</tldr>

## Input Manager Component
The Input Manager Component is the most important component in the framework. It is responsible for registering, receiving
and dispatching **Input Actions** to the correct **Input Handlers**, small objects dedicated to handle specific inputs.

> **Input Handlers**
> 
> Input Handlers are small and reusable objects that are responsible for handling incoming player input. It is expected
> that each **Input Action** has at least one **Input Handler** related to it.
> 
> Ninja Input provides multiple Input Handlers and you can **extend them or create new ones in Blueprint or C++**. For 
> more information about Input Handlers, please check the **[Input Handler page](ipt_input_handlers.md)**.
{style=note}

This component can be added to either the **Player Controller** or **Player Character**, but not both. For prototypes 
and smaller projects, both are valid options, but in general, the Player Controller is the best choice: 

- Fewer requirements in the Player Character, allowing a leaner **character hierarchy**.
- Support for **different pawns**, providing their own Input Setups when possessed, via `InputSetupProviderInterface`.

<procedure title="Add the Input Manager Component" collapsible="true" default-state="expanded">
    <step>
        <p>In your <b>Base Character Class</b>, add the <b>Input Manager Component</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="ipt_add_component.png" alt="Add the Input Manager Component" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p><b>Header</b></p>
                <code-block lang="c++" src="ipt_setup_manager_component.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="ipt_setup_manager_component.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

## Creating and Assigning Input Setups
The Input Manager uses a dedicated **Data Asset** to group **Input Mapping Contexts**, **Input Actions** and **Input Handlers**:
the **Input Setup**.

You can have multiple setups, grouping inputs by their role, such as "_Locomotion Inputs_", "_Driving Inputs_", "_UI
Inputs_" and so on. Please check the [Input Management page](ipt_input_management.md) for information about adding and
removing them in runtime.

<procedure title="Remove the original input handling logic" collapsible="true">
    <step>Open your <b>Project Settings</b>, navigate to <b>Enhanced Input</b> and make sure that there are no <b>Default Mapping Contexts</b>.</step>    
    <step>Navigate to your <b>Character Blueprint</b>, open it and go to the <b>Event Graph</b>.</step>
    <step>Remove all input-related nodes, including the ones connected to <b>Begin Play</b>.</step>
</procedure>

<procedure title="Configure the Input Setup" collapsible="true">
    <step>In the <b>Content Browser</b>, navigate to your <b>Input</b> folder.</step>
    <step>Right click to open the <b>Context Menu</b>, navigate to the <b>Input</b> category and select <b>Ninja Input Setup</b>. Name it in a way that it correlates with your <b>Input Mapping Context</b>, for example: <code>IMC_Gameplay</code> &rightarrow; <code>IS_Gameplay</code>.</step>
    <step>Open the new <b>Input Setup</b> and add your <b>Input Mapping Context</b>.</step>
    <step>Add three new entries to the <b>Input Handlers</b> list, selecting: <code>Character: Move</code>, <code>Character: Look</code> and <code>Character: Jump</code>.</step>
    <step>
        <p>For each one of these entries, expand their properties and add the appropriate <b>Input Action</b>.</p>
        <p>By default, they will have Input Actions starting with <code>IA_NI</code>, which are the ones provided by Ninja Input. Make sure to <b>replace them</b> with your project-related counterparts.</p>
        <img src="ipt_setup_input_setup_data.png" alt="Configure Input Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <tip>
        <p><b>Input Validation</b></p>
        <p>If you get a <b>Validation Error</b> while saving your <b>Input Setup</b>, it means there are <b>Input Actions</b> in your Input Mapping Context not related to any <b>Input Handler</b>.</p>
        <p>Check the <b>Message Log Window</b> and you will find which Input Actions are missing an Input Handler.</p>
        <p>This validation ensures every mapped action is correctly handled at runtime and <b>prevents input failures or unexpected behavior</b>.</p>
    </tip>
</procedure>

<procedure title="Assign the Input Setup to the Input Manager" collapsible="true">
    <step>Navigate to the <b>Player Controller</b>, where the <b>Input Manager</b> was added.</step>
    <step>Click the <b>Input Manager Component</b> to open its <b>Default Values</b>.</step>
    <step>
        <p>Add the newly-created <b>Input Setup</b> to the list of <b>Input Setups</b>.</p>
        <img src="ipt_setup_data_assignment.png" alt="Add the Input Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

## Forward Reference
Certain types of games, such as a **top-down game with WASD movement** will require a reference that movement handlers
can use to calculate **forward** and **right** directions. In Ninja Input, this reference is called **Forward Reference**.

> **Optional Step**
>
> For first-person, third-person and other games where the **camera follows the character direction**, the Forward Reference
> component is not required by Ninja Input.

The Forward Reference is a **Scene Component** that always points _North_ (or _Positive X_) in relation to the world,
instead of following the **character rotation**. This means it is set to have **absolute rotation**.

Any **Scene Component** in the **Character** can be used as a Forward Reference, but the most common choices are either
the **Camera** or an **Arrow Component**. To mark a component as the Forward Reference, all you have to do is add the
`Input.Component.ForwardReference` component tag it.

The **Input Manager** component can automatically create a Forward Reference for you. You can enable that behavior by
setting the `ShouldCreateForwardReference` property to `true`, in the Input Manager defaults panel.

If you need more control over your Forward Reference component, then you can create your own Forward Reference and 
assign the appropriate Gameplay Tag.

<procedure title="Creating a Forward Reference" collapsible="true" default-state="expanded">
    <step>
        <p>In your <b>Base Character Class</b>, add the <b>Input Manager Component</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="ipt_setup_forward_reference.png" alt="Forward Arrow Reference" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p><b>Header</b></p>
                <code-block lang="c++" src="ipt_forward_arrow.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="ipt_forward_arrow.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

> **Integration With Ninja Combat**
>
> If you are also using **Ninja Combat**, then you can use the same Forward Reference for both systems. For additional
> details, please check Ninja Combat's [Input Integration page](cbt_integration_input.md#forward-reference).
