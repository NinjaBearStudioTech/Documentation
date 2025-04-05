# Input Setup
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>An <b>Input Setup</b> bundles an <b>Input Mapping Context</b> with their appropriate <b>Input Handlers</b>.</li>
        <li>The <b>Input Manager</b> can have <b>default</b> Input Setups available in all situations.</li>
        <li>Input Setups can be <b>added</b> or <b>removed</b> using the appropriate functions in the <b>Input Manager</b>: <code>AddInputSetupData</code> and <code>RemoveInputSetupData</code>.</li>
        <li>New Pawns set to a <b>Player Controller</b> can grant their own Input Sets via <code>InputSetupProviderInterface</code>. They are automatically added and removed when the pawn is <b>possessed</b> and <b>unpossessed</b>.</li>
    </ul>
</tldr>

Input Setups are **Data Assets** used to bundle an **Input Mapping Context** to all appropriate **Input Handlers**.
These bundles are provided to the Input Manager either as **default setups** or managed during **runtime**.

You can categorize Input Setups as:

- **Default**: Always available to the player pawn.
- **Situational**: Added or removed based on specific contexts.

## Default Input Setups

Default Input Setups are **always active** and are assigned within the Input Manager Component’s **Default Settings**.

The system supports multiple Default Input Setups, providing the flexibility to organize your inputs into as many 
**logical bundles** as needed.

The specifics of which default setups to add will vary depending on the project's scope. Smaller games might benefit 
from having all setups added as default. In contrast, larger games may require more deliberate management of input contexts.

> **Context Priorities**
>
> If you have overlapping Setups/Contexts (e.g., **Basic Locomotion** and **Mount Locomotion**), consider adjusting 
> their priorities to ensure that the more specific context (like "Mount Locomotion") takes precedence and properly 
> **consumes the input**.
{style="note"}

## Situational Input Setups

Situational Input Setups are **activated on-demand** and are triggered by specific events, allowing for the addition or 
removal of Input Setups as needed.

### Add and Remove Functions

The **Input Manager Component** provides dedicated functions to add or remove Input Setups whenever necessary. It’s 
important to ensure that any context you add is properly removed later to avoid unexpected behavior.

> **Input Context Mapping Duplicates**
>
> The Input Manager Component does not allow **duplicate contexts**. Attempting to add a context that has already been 
> processed will generate a warning in the `LogNinjaInput` category.
{style="note"}

These functions are available in both Blueprints and C++ and can be used as needed. Here are common usage cases:

- Begin or End Play of certain actors that provide additional input options to players.
- When the User Interface activates and new inputs are available.
- Inputs granted, based on certain conditions that must be met.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_add_remove_setup.png" alt="Adding or Removing Setups" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="ipt_add_remove_setups.cpp"/>
    </tab>
</tabs>

### Input Setup Provider Interface

Situational Input Setups can also be managed via the **Input Setup Provider Interface**.

This interface can be implemented by any pawn. When a Player Controller possesses such a pawn, its Input Manager 
Component checks for this interface and automatically adds the provided setups. The setups are then removed when the 
pawn is unpossessed.

> **Player Controller Only**
>
> The Input Manager Component will look for this interface in **Pawns** being **possessed** and **unpossessed**. This 
> Setup only works when your Input Manager is in the **Player Controller**!
{style="note"}

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_setup_provider_interface.png" alt="Using the Input Provider Interface" border-effect="line" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="ipt_provider_interface.h"/>
        <br/>
        <code-block lang="c++" src="ipt_provider_interface.cpp"/>
    </tab>
</tabs>

### Globally Enable or Disable Inputs

Inputs can be completely **disabled**, and later on **enabled** at the **Input Manager** component level. 

This can be useful when doing in-game cutscenes or other similar operations where all inputs should be discarded, 
without the need to remove/add current **Setups**.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_global_enable_disable.png" alt="Globally Enable/Disable inputs" border-effect="line" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="ipt_global_enable_disable.cpp"/>
    </tab>
</tabs>

<seealso style="cards">
   <category ref="related">
        <a href="p01g01_configure_inputs.md" summary="Configure Input Handlers in your project, from scratch."/>
    </category>
</seealso>
