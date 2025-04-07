# Input Management
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>In this page, you will learn about managing your <b>Input Setups</b> using the <b>Input Manager Component</b>.</li>
        <li>Input Handlers are <b>stateless</b> and <b>completely separated</b> from their characters.</li>
        <li>The <b>Input Manager Component</b> is the only source to detect, add and remove <b>Input Setups</b>.</li>
        <li>You can <b>globally enable and disable</b> input handling if needed.</li>
    </ul>
</tldr>

The Input System was designed to cleanly **separate player input logic** from Pawn or Character classes. By doing so,
it promotes **separation of concerns** and **reusability** of such logic, even across **different projects**.

## Input Manager Component
The **Input Manager** is the backbone of the Input System. It's responsible for initializing and maintaining **Input
Setups** and **routing Input Actions to appropriate Input Handlers**.

> **Chain of Responsibility**
>
> In OOP terms, the Input Manager implements the **Chain of Responsibility** pattern. It allows all Handlers to evaluate
> incoming Inputs to decide on whether they will execute or ignore them.

The following functions are accessible to any **Input Handler** or external callers.

| Function                        | Category   | Description                                                                                                               |
|---------------------------------|------------|---------------------------------------------------------------------------------------------------------------------------|
| `ShouldProcessInputs`           | General    | Informs if this Input Manager is currently processing inputs.                                                             |
| `EnableInputProcessing`         | General    | Globally enables input processing.                                                                                        |
| `DisableInputProcessing`        | General    | Globally disables input processing.                                                                                       |
| `IsUsingKeyboardAndMouse`       | Context    | Informs if the player's input device is the **keyboard and mouse**.                                                       |
| `GetForwardVector`              | Context    | Provides the forward vector, based on the **Pawn** or **Forward Reference**.                                              |
| `GetRightVector`                | Context    | Provides the right vector, based on the **Pawn** or **Forward Reference**.                                                |
| `GetLastInputVector`            | Context    | Provides the last input vector handled by the owner, via `Pawn Movement Component` or `LastInputVectorProviderInterface`. |
| `GetPawn`                       | Context    | Provides the Pawn related to this component.                                                                              |
| `GetController`                 | Context    | Provides the Controller related to this component.                                                                        |
| `IsLocallyControlled`           | Context    | Informs if the player is locally controlled.                                                                              |
| `GetAbilitySystemComponent`     | Context    | Provides the **Ability System Component** related to the current Pawn.                                                    |
| `HasSetupData`                  | Setup Data | Checks if a given **Setup Data** is assigned to the component.                                                            |
| `HasCompatibleInputHandler`     | Setup Data | Checks if there is an Input Handler set for a given Input Action and Trigger Event.                                       |
| `AddInputSetupData`             | Setup Data | Processes a Setup Data, registering its Input Contexts and Handlers.                                                      |
| `RemoveInputSetupData`          | Setup Data | Removes a Setup Data previously registered.                                                                               |
| `RotateControllerToMouseCursor` | Utility    | Rotates the current controller to the mouse location.                                                                     |

## Default Input Setups
You can provide **default input setups** in two ways:

- **Default Properties**: By setting them directly into the **Input Manager**, in its Defaults Panel. These are always added to any possessed pawn and cannot be removed.
- **Pawn Interface**: The pawn possessed by the owning Controller can provide input setups via `InputSetupProviderInterface`. They will be removed when the pawn is unpossessed.

> **Default Input Setups**
> 
> Adding default Input Setups to the Input Manager, so they are available to all possessed characters, was covered in 
> the **[Input System Setup page](ipt_input_system.md)**.

Providing Input Setups for each pawn is especially useful for games where players possess multiple Pawns with distinct 
input needs (e.g., vehicles, turrets, or UI-driven characters).

> **Player Controller Only**
>
> The Input Manager Component will look for the `InputSetupProviderInterface` interface in **Pawns** being **possessed**
> and **unpossessed**, so this setup only works when your Input Manager is added to the **Player Controller**.
{style="note"}

<procedure title="Implementing the Setup Provider Interface" collapsible="true" default-state="expanded">
    <step>Make sure to set your <b>Input Manager</b> to the <b>Player Controller</b>.</step>
    <step>Add the <code>InputSetupProviderInterface</code> to the pawn that will provide specific Input Setups.</step>
    <step>Create an array of <code>NinjaInputSetupDataAsset</code> references, so you can add Input Setups relevant to the Pawn.</step>
    <step>
        <p>Implement the <code>GetInputSetups</code> function, returning the array of setups</p>
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

## Runtime Management
Input Setups can be added and removed at runtime. This is useful when you want certain inputs to only become available
when specific gameplay elements happen.

The **Input Manager Component** provides dedicated functions to add or remove Input Setups whenever necessary. It is
important to ensure that any context you add is properly removed later to avoid unexpected behavior.

> **Input Context Mapping Duplicates**
>
> The Input Manager Component does not allow **duplicated Input Mapping Contexts**. Attempting to add a context that has 
> already been processed will generate a warning in the `LogNinjaInput` category.
> 
> You can check if a setup was already registered using the `HasSetupData` function.
{style="note"}

Input Setups can be **added** and **removed** using `AddInputSetupData` and `RemoveInputSetupData`. 

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_add_remove_setup.png" alt="Adding or Removing Setups" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="ipt_add_remove_setups.cpp"/>
    </tab>
</tabs>

## Global State
You can completely **disable** and **enable** input handling in an **Input Manager**. This can be useful during in-game 
cutscenes, when all input should be blocked without removing active Input Setups.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_global_enable_disable.png" alt="Globally Enable/Disable inputs" border-effect="line" thumbnail="true" width="600"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="ipt_global_enable_disable.cpp"/>
    </tab>
</tabs>
