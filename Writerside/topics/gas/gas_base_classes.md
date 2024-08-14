# Base ASC Classes
<primary-label ref="gas"/>
<secondary-label ref="wip"/>

This framework provides a few **Base Classes** that can be used for common ASC usage scenarios. It also provides a 
**Data Asset** to configure default Attribute Sets, Gameplay Effects and Gameplay Abilities for ASC users.

## Base Classes

Use the following table as a reference, when creating your usual **ASC-related** classes.

| Base Class                | Scenario                                                                             |
|---------------------------|--------------------------------------------------------------------------------------|
| `NinjaGASActor`           | **Actors** with their own Ability System Component.                                  |
| `NinjaGASPawn`            | **Pawns** with their own Ability System Component.                                   |
| `NinjaGASCharacter`       | **Characters** with their own Ability System Component.                              |
| `NinjaGASPlayerCharacter` | **Characters** that will use the Ability System Component from the **Player State**. |
| `NinjaGASPlayerState`     | **Player State** with its Ability System Component.                                  |

## Default Data

The **Ability System Component** in the framework can receive **initial data** via **Ability Bundle** Data Asset.

This Data Asset will only load its assets **on demand**, when they are actually used by the Ability System Component.
They will remain loaded until there are no Ability System Components using the same Ability Bundle.

You can set Ability Bundles in two ways:

1. Directly to the **Ability System Component**, in its **Details Tab**.
2. Via the **AbilitySystemDefaultsInterface**, set in an **Avatar**.

### Ability System Defaults Interface
<secondary-label ref="advanced"/>

The base **Character** classes already implement this interface and expose the appropriate settings as **properties**.
This creates a separation between abilities in the ASC and a potential **override** in the **Avatar**.

This interface **cannot be implemented in Blueprint**, so it must be added to other classes in **C++**. 