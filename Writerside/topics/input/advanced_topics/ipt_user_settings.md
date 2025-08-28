# User Settings
<primary-label ref="input"/>
<secondary-label ref="advanced"/>

Ninja Input includes a dedicated **Enhanced Input User Settings** class that extends Epic's base implementation and 
centralizes player-facing preferences like **mouse** and **gamepad sensitivity**, plus **axis inversion**. 

## Setting the Custom Class
To use the custom class, configure it in **Project Settings**.

> You'll also do this when enabling [Input Remapping](ipt_remapping_setup.md), so you may have completed it already.

<procedure title="Enable Enhanced Input User Settings" collapsible="true" default-state="expanded">
    <step>Open <b>Project Settings</b>.</step>
    <step>Go to <b>Engine</b> &rarr; <b>Enhanced Input</b> and expand <b>User Settings</b>.</step>
    <step>Check <b>Enable User Settings</b>.</step>
    <step>Set <code>UNinjaInputUserSettings</code> (or your subclass) as the <b>User Settings Class</b>.</step>
    <img src="ipt_remapping_settings.png" alt="Enable Input User Settings" width="600"/>
</procedure>

## Available Properties
These properties live in the settings object and are consumed by the modifiers at runtime.

| Property               | Description                                                                                 |
|------------------------|---------------------------------------------------------------------------------------------|
| `InvertVerticalAxis`   | Inverts the **Y** component of 2D inputs (and any 1D action you designate as "vertical").   |
| `InvertHorizontalAxis` | Inverts the **X** component of 2D inputs (and any 1D action you designate as "horizontal"). |
| `MouseSensitivityX`    | Multiplier applied to **mouse delta X**.                                                    |
| `MouseSensitivityY`    | Multiplier applied to **mouse delta Y**.                                                    |
| `GamepadSensitivity`   | Scalar gain for gamepad sticks (applied per component).                                     |

> **Getters and Setters**
>
> Properties are **protected** and should be read/updated through their **getters/setters**
> (e.g., `GetMouseSensitivityX()`, `SetMouseSensitivityX()`).
{style="note"}

## Input Modifiers
Attach these modifiers to your **Input Actions** to apply the settings at runtime.

| Input Modifier          | Description                                                                                     |
|-------------------------|-------------------------------------------------------------------------------------------------|
| **Gamepad Sensitivity** | Scales gamepad stick values by `GamepadSensitivity`.                                            |
| **Invert XY Axis**      | Inverts **X** and/or **Y** using `InvertHorizontalAxis` / `InvertVerticalAxis`. Works on 1D/2D. |
| **Mouse Sensitivity**   | Scales **mouse delta** per axis using `MouseSensitivityX` / `MouseSensitivityY` (X/Y only).     |

**Examples**

- **IA_Look (Mouse Delta):** `Mouse Sensitivity` → `Invert XY Axis`
- **IA_Look (Gamepad Stick):** `Gamepad Sensitivity` → `Invert XY Axis`
- **IA_Move (Gamepad Stick):** `Gamepad Sensitivity`

## User Interface
All values can be exposed and managed through the **Input Settings View Model**. It's a **two-way** ViewModel:
UI updates propagate to the settings object (and vice versa).

- When initializing this ViewModel, set the **Resolver** to the **Ninja Input** resolver.
- After applying changes from your options screen, call your usual "apply/save" flow so the settings persist. This ViewModel provides a dedicated function for that.
