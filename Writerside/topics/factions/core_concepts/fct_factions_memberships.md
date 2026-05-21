# Factions and Memberships
<primary-label ref="factions"/>

Factions and Memberships are the main concept for the Faction System. A **Faction** can represent many common concepts 
in games such as a _team_, _brotherhood_, or just _factions_.

Then, actors can be added to Factions through a **Membership**. 

## Faction Data Asset

Factions are represented by a Data Asset, `NinjaFactionDataAsset`. It contains basic information about a Faction that
is used throughout the system.

| Property                                | Description                                                                        |
|-----------------------------------------|------------------------------------------------------------------------------------|
| Display Name                            | Localized name for the Faction.                                                    |
| Faction Tag                             | A Gameplay Tag that uniquely identifies the Faction. Filtered by `Factions.ID`.    |
| Team ID                                 | Team used by the Unreal Engine. Each Faction most likely has their unique Team ID. |
| Color                                   | Color optionally used when showing this Faction in the user interface.             |
| Tags                                    | Additional tags that can be used for additional filtering.                         |
| Default Attitude Towards My Faction     | Default attitude towards members of the same faction.                              |
| Default Attitude Towards Other Factions | Default attitude towards members of other factions.                                |
| Attitude Matrix                         | Exception cases for attitudes between this and other factions.                     |

> **Remember to update the Asset Manager**
> 
> The Faction Data Asset is a **Primary Asset** and must be registered in the **Asset Manager**. You can find more 
> information about this in the [Setup page](fct_setup.md).
{style="note"}

## Faction Component

Each **Faction Member** must have the Faction Component, `NinjaFactionComponent`. This component provides relevant 
methods used to manage Factions, Memberships and Reputation.

## Adding Factions

Adding a Faction to the Faction Component means creating a new **Membership**. Factions can be added in a few different
ways:

1. By adding **default memberships** to the component.
2. Using the **Add Faction** function.
3. Via the **Gameplay Feature**, using the **Add Faction** Action.

### Main Faction

Each component should establish its **Main Faction**. The Main Faction identifies the primary faction used to define 
the attitude **from a source towards a target**.