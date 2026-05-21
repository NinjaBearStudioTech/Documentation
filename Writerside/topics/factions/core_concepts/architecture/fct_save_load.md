# Save and Load
<primary-label ref="factions"/>

If you are using **Reputations** in your project, then you probably need to **save** and **load** the player's **memberships**.

This mechanism was designed using **multiple layers**, so you can perform the entire save and load operations with the 
Faction Manager, or use parts of it with your own save system.

## Faction Save Game

The Faction System provides the `NinjaFactionSaveGame` class, which can be used to serialize and deserialize membership
information from a Faction Manager component.

This means you can create a dedicated Faction Save File using Unreal Engine's default [save game mechanism][1].

### Saving Memberships

You can save all Memberships into a save file by calling the **Save Factions** function in the Save Game object, passing 
the Faction Component that should be saved.

<img src="fct_save_memberships.png" alt="Save Memberships" thumbnail="true" border-effect="line"/>

### Loading Memberships

You can load all Memberships from a save file by calling the **Load Factions** function in the Save Game Object, passing
the Faction Component that should receive them.

<img src="fct_load_memberships.png" alt="Load Memberships" thumbnail="true" border-effect="line"/>

> **Loading Factions overrides current entries**
> 
> The load operation will always reset all current memberships and load the ones from file. If you need to handle that
> scenario, listen to the **Faction Removed** delegate and perform any necessary clean up.

> **Loading Factions is also asynchronous**
>
> You might not get data right after calling `LoadFactions`, since this function must run asynchronous code, to load 
> Data Assets for incoming Factions. If you need to react right away, the use the **Faction Added* delegate.
{style="note"}

## Other Save Systems
<secondary-label ref="advanced"/>

You can also integrate the save mechanism with other save systems. In that case you need to look into the following
functions provided by the Faction Manager:

| Function                               | Description                                               |
|----------------------------------------|-----------------------------------------------------------|
| `GetFactionRecordForSerialization`     | Provides a consolidated Record of the Faction component.  |
| `GetMembershipRecordsForSerialization` | Provides a list of Membership Records from the component. |
| `AddFactionFromMembership`             | Adds a Faction/Reputation from a Membership.              |

<seealso style="cards">
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/saving-and-loading-your-game-in-unreal-engine" summary="Official documentation for the Save and Load system.">Saving and Loading Your Game</a>
    </category>
</seealso>

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/saving-and-loading-your-game-in-unreal-engine