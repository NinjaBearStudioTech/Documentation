# Ability Data Asset
<primary-label ref="gas"/>

The custom **Ability System Component** provided by the framework can be initialized using an **Ability Data Asset**, which
defines **Attribute Sets**, **Gameplay Effects**, **Gameplay Abilities**, and **Gameplay Tags**.

<img src="gas_ability_data_asset.png" alt="Ability Data Asset" thumbnail="true" border-effect="line"/>

You can assign the Ability Data Asset in two ways:

1. **Directly in the Ninja GAS Ability System Component** — set it in the component's **Details** panel.  
   Useful when the same data asset is shared by multiple characters.
2. **Via the AbilitySystemDefaultsInterface**, implemented in an **Avatar** — the avatar provides the Data Asset to use.  
   Useful when each avatar has unique abilities but the ASC resides in a shared Player State.

## Data Asset Settings
You can configure **Attribute Sets**, **Gameplay Effects**, **Gameplay Abilities**, and replicated **Gameplay Tags** in the data asset.

### Attribute Sets

| Property             | Description                                                             |
|----------------------|-------------------------------------------------------------------------|
| `AttributeSetClass`  | Attribute Set class to grant.                                           |
| `InstantiationScope` | Scope for this Attribute Set (Local, Server, or Both).                  |
| `AttributeTable`     | Data table with default attribute values, based on `AttributeMetaData`. |

### Gameplay Effects

| Property              | Description                     |
|-----------------------|---------------------------------|
| `GameplayEffectClass` | Gameplay Effect class to grant. |
| `Level`               | Initial level.                  |

### Gameplay Abilities

| Property               | Description                                                                          |
|------------------------|--------------------------------------------------------------------------------------|
| `GameplayAbilityClass` | Gameplay Ability class to grant.                                                     |
| `Level`                | Initial level.                                                                       |
| `Input`                | Input assigned to this ability (old Input System). Not recommended for new projects. |

### Additional Properties

| Property                | Description                                |
|-------------------------|--------------------------------------------|
| `Initial Gameplay Tags` | Replicated gameplay tags added by default. |

## Ability System Defaults Interface
<secondary-label ref="advanced"/>

This interface allows you to **decouple the Ability Data from the Ability System Component**. It is particularly useful 
when the ASC resides in the **Player State** but multiple Characters can be used, each with their own abilities.

The base **Character** classes implement this interface and expose a **property** for the Data Asset. If left empty, it 
will be safely ignored. When provided, it takes priority over any Data Asset set directly on the ASC.

> **Implementing the Interface**  
> 
> This interface follows the same convention as the **Ability System Interface** and **cannot be implemented in Blueprint**.  
> It must be added to classes using **C++**.
