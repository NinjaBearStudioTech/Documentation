# Ability Data Asset
<primary-label ref="gas"/>

The custom **Ability System Component** provided by the framework can be initialized using **Ability Data Asset**, which
includes **Attribute Sets**, **Gameplay Effects**, **Gameplay Abilities** and **Gameplay Tags**.

<img src="gas_ability_data_asset.png" alt="Ability Data Asset" thumbnail="true" border-effect="line"/>

You can set this Data Asset in two ways:

1. Directly to the **Ninja GAS Ability System Component**, setting it in the component's **Details Tab**.
2. Implementing the **AbilitySystemDefaultsInterface**, set in an **Avatar**.

### Ability System Defaults Interface
<secondary-label ref="advanced"/>

This interface offers flexibility to **separate the Ability Data from the Ability System Component**. This can be useful
in a scenario where the ASC stays in the **Player State** but multiple Characters can be used, with their own Abilities. 

The base **Character** classes implement this interface and expose a **property** for the Data Asset. If left empty, is 
will be safely ignored, but when provided, it takes priority over any Data Asset directly set in the ASC.

> **Implementing the Interface**
> 
> This interface follows the same convention as the Ability System Interface and **cannot be implemented in Blueprint**, 
> so it must be added to classes using **C++**. 
 