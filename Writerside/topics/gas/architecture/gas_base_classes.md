# Base ASC Classes
<primary-label ref="gas"/>

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

> **Character Hierarchy**
> 
> The `NinjaGASPlayerCharacter` is only relevant if your game architecture has the Ability System Component in the 
> **Player State**. Otherwise, this class offers no added benefit from the base `NinjaGASCharacter`. 
