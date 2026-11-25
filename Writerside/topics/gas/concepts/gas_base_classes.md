# Ownership and Initialization
<primary-label ref="gas"/>

The **owner** holds the Ability System Component (ASC). The **avatar** is the actor that performs the ability. On a guard these are usually the same character. On a player they can be the Player State and the currently possessed pawn.

| What should happen in your game | Base class to use |
| --- | --- |
| A new character or pawn starts with its own abilities. | `NinjaGASCharacter` or `NinjaGASPawn` owns the component. |
| The player keeps a shared component when changing bodies. | `NinjaGASPlayerState` owns it. `NinjaGASPlayerCharacter` or `NinjaGASPlayerPawn` exposes it on the possessed avatar. |
| A world object needs attributes only when something uses it. | `NinjaGASActor` supports lazy initialization. |
| A Paper2D character needs either character ownership model. | Use `NinjaGASPaperCharacter` or `NinjaGASPaperPlayerCharacter` respectively. |

## When a Player Changes Pawns

Keep abilities such as a player's recall spell on the Player State. Put a vehicle's boost or a character's double jump in the avatar's bundle. With the default settings the Player State keeps its grants, and the component replaces the old avatar's grants with those of the new pawn. **Reset State When Avatar Changes** requests a full reset. Leave it off when shared progress should survive possession.

The supplied player classes connect the component on possession and when the Player State arrives on a client. For your own C++ pawn, expose the shared component through `IAbilitySystemInterface::GetAbilitySystemComponent` and call `InitAbilityActorInfo(PlayerState, Pawn)` when both are available on the server and owning client. Code that follows the player can subscribe to the component's `OnAbilitySystemAvatarChanged` delegate. The new avatar is passed to the listener.

## Actors That Only Sometimes Need Abilities

For a breakable prop based on `NinjaGASActor`, set **Ability System Initialization Mode** to **Lazy** and put its bundle in the actor's **Default Ability Setup**. The first server request for the component creates it. A client may need to wait for replication. Choose **Eager** for a prop that must have its attributes as soon as it enters play.

In a C++ Attribute Set used by lazy actors, use `LAZY_GAMEPLAYATTRIBUTE_REPNOTIFY` in the attribute's replication callback so a value arriving before the component is ready can be applied later. For a property called `Durability`, the callback body can use `LAZY_GAMEPLAYATTRIBUTE_REPNOTIFY(UPropAttributeSet, Durability, OldValue);`. The macro is in `AbilitySystem/NinjaGASAttributeSet.h`.

Follow [First Steps](gas_first_steps.md) to set up either character type and inspect the owner and avatar in play.
