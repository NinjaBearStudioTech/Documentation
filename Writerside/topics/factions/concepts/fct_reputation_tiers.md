# Reputation and Tiers
<primary-label ref="factions"/>

In some games, it is very common for players to improve their _standing_ with certain Factions, from many activities
available in the game, such as _quests_.

The Faction System provides this logic via **Reputation**. A faction member has a certain amount of reputation with a
Faction, which places them at a certain membership **Tier**. Then, during gameplay, multiple events can add or subtract
reputation, changing the tier and therefore, how other members can react to a member.

## Reputation Data Table

Tiers are defined by a **Data Table**, which can be set to the project globally, in the Faction Settings page. The row
structure must be `FactionReputationTableRow`.

When creating this Data Table, you will need to provide the following information.

| Property       | Description                                                                                         |
|----------------|-----------------------------------------------------------------------------------------------------|
| Display Name   | A localized value for the tier name.                                                                |
| Color          | A color that can be used in the User Interface, when representing this tier.                        |
| Min Reputation | Minimum reputation required to enter this tier. The lowest tier should always start at zero.        |
| Max Reputation | Maximum reputation supported by this tier. The last available tier represents the reputation limit. |
| Attitude       | AI attitude towards other faction members, while in this tier.                                      |

You can use the following JSON as a starting point for your Data Table.

<code-block lang="json" src="fct_reputation_tiers.json" collapsible="true" collapsed-title="Reputation JSON Sample"/>

## Faction Source Interface

This is an interface that can be added to certain objects that can modify a member's Reputation. Some examples:

- The Player enters a zone delimited by a volume and its Reputation is modified. In this case, the volume can be a source.
- The Player defeats an enemy and gains Reputation with a Faction, but looses Reputation with another one. The enemy can be a source.
- The Player finishes a quest and gains Reputation, the quest giver or quest object can be a source.

These gains can also be dynamic, customized to the Faction Member requesting them and Event, which makes this approach
very flexible.

## Managing Reputation

Reputation is added via the **Faction Manager**, directly or via objects implementing the Faction Source interface.

### Add Reputation

Reputation can be added directly, using the `AddReputation` function.

<tabs group="sample">
     <tab title="Blueprint" group-key="bp">
        <img src="fct_add_reputation.png" alt="Add Reputation" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="C++" src="fct_add_reputation.cpp"/>
    </tab>
</tabs>

When adding Reputation, the following parameters are expected by the function:

| Parameter    | Description                                                                                    |
|--------------|------------------------------------------------------------------------------------------------|
| Faction Data | Data Asset representing the target Faction.                                                    |
| Reputation   | Amount of reputation to add to the membership.                                                 |
| Source       | Object responsible for this change. It could be an implementation of `FactionSourceInterface`. |
| Event Tag    | Gameplay Tag explaining the type of event that originated this change.                         |

> **Decreasing Reputation**
> 
> You can also decrease the current Reputation by providing **negative numbers**!
{style="note"}

If the source implements the **Faction Source Interface**, it will be given an opportunity to make sure that the change
being requested is truly viable.

This can be used to make sure that RPCs sent to the server, requesting changes in the Reputation, are **valid**.

### Add Reputation From Source

Reputation can be added from any sources, using the `AddReputationFromSource` function.

<tabs group="sample">
     <tab title="Blueprint" group-key="bp">
        <img src="fct_add_reputation_source.png" alt="Add Reputation from Source" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="C++" src="fct_add_reputation_source.cpp"/>
    </tab>
</tabs>

### Tiers

When Reputation changes, it may also modify the current **Tier**. This process is done automatically, based on the 
Data Table containing the tier information.

## Delegates

Changes in the **Reputation** and **Tier** can be tracked by binding to the appropriate **Multicast Delegates** in the
Faction Manager.

- **OnReputationChanged**: Broadcast whenever **Reputation** changes (client and server).
- **OnTierChanged**: Broadcast whenever the **Tier** changes (client and server).
