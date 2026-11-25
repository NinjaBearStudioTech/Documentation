# Change Reputation Through Gameplay
<primary-label ref="factions"/>
<secondary-label ref="guide"/>

Make a town guard welcome a player who finishes a quest. The guard represents **Town Watch**. The player represents **Players** and has a secondary **Town Watch** membership starting at zero. [Assign and Change Memberships](fct_manage_memberships.md) shows how to grant that membership.

<procedure title="Give the Watch two standings">
    <step><p>Create a Data Table with the row type <b>Faction Reputation Table Row</b> (<code>FFactionReputationTableRow</code>). Add the two rows below. Set each row's display name to the name you want players to see.</p></step>
    <step><p>In <b>Project Settings → Ninja Factions</b>, assign the table to <b>Reputation Table</b> and set <b>Faction Solver Class</b> to <b>Target Reputation</b>. Start a new play session with these settings.</p></step>
</procedure>

| Row name | Min Reputation | Max Reputation | Attitude |
| --- | ---: | ---: | --- |
| Stranger | 0 | 9 | Neutral |
| Trusted | 10 | 99 | Friendly |

<procedure title="Award the quest reward">
    <step><p>On quest completion, get the player's Faction Component and call <b>Add Reputation</b> (<code>AddReputation</code>). Choose <b>Town Watch</b>, pass <code>12</code> as the amount, the quest giver as <b>Source</b>, and <code>Factions.Event.QuestCompleted</code> as <b>Event Tag</b>. In multiplayer, award it on the server.</p></step>
    <step><p>Use <b>Get Faction Membership</b> with Town Watch to read the new score. Call <b>Get Attitude</b> with the guard as <b>Source</b> and the player as <b>Target</b> to see how the reward changed their relationship.</p></step>
</procedure>

<tabs group="sample">
    <tab title="Blueprint" group-key="bp"><img src="fct_add_reputation.png" alt="Awarding reputation to a member for one faction" width="780" border-effect="line"/></tab>
    <tab title="C++" group-key="cpp"><code-block lang="C++" src="fct_add_reputation.cpp"/></tab>
</tabs>

## Let the Quest Choose the Reward

If one decision helps the Watch and upsets another guild, implement **Faction Source Interface** (`IFactionSourceInterface`) on the quest giver. In **Get Reputation Rewards** (`GetReputationRewards`), return a map of faction assets to signed amounts for that member and event. A negative amount spends or loses reputation. The player needs a membership in each affected faction.

Call **Add Reputation From Source** (`AddReputationFromSource`) on the player's component with the quest giver and event tag. The component asks the giver for its rewards. Override **Can Provide Faction Values** (`CanProvideFactionValues`) on the source to accept only rewards it can grant, or **Is Valid Faction Update** (`IsValidFactionUpdate`) on a component subclass for rules that apply to that member.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp"><img src="fct_add_reputation_source.png" alt="Requesting reputation rewards from a source actor" width="780" border-effect="line"/></tab>
    <tab title="C++" group-key="cpp"><code-block lang="C++" src="fct_add_reputation_source.cpp"/></tab>
</tabs>

## Update a Faction Menu

Populate the menu from the component's **Get Faction Memberships**. A **Faction List Widget** can also give the owning player a list of membership views with the faction, score, and tier. Bind to **On Reputation Changed** (`OnReputationChanged`) to refresh a score and **On Tier Changed** (`OnTierChanged`) to announce a new standing. Use the membership passed to the event to update the correct row.

## Try It in Play

Before the reward, expect **0 / Stranger / Neutral**. After the quest, expect **12 / Trusted / Friendly**. Pass `-3` to **Add Reputation** for a penalty. The new score is **9**, so the guard should see the player as Neutral again.

To inspect it in the **Gameplay Debugger**, aim at the member, open the overlay, and enable **Factions**. It shows membership count and the **main** faction's tag, team, reputation, and tier. To watch the Watch score here, make Town Watch the test character's main faction for this run. If the player keeps Players as their main faction, inspect their secondary Town Watch membership with **Get Faction Membership** and print the guard's **Get Attitude** result separately.

<tabs>
    <tab title="Overlay"><img src="fct_debugger_overlay.png" alt="Factions category showing the selected actor's main faction, score, and tier" width="780" border-effect="line"/></tab>
    <tab title="Controls"><p>In <b>Project Settings → Gameplay Debugger</b>, choose an activation key and category keys that are available on your keyboard.</p><img src="fct_debugger_setup.png" alt="Activation and category settings for the Gameplay Debugger" width="780" border-effect="line"/></tab>
</tabs>
