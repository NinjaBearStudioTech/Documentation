# Assign and Change Memberships
<primary-label ref="factions"/>
<secondary-label ref="guide"/>

Let a player join the Town Watch, wear its colors for a mission, and leave when the mission ends. Start with a player whose main faction is **Players**, as in [First Steps](fct_first_steps.md). Create a **Town Watch** faction asset in the same folder with its own tag and team ID, for example `Factions.ID.TownWatch` and `2`.

<procedure title="Recruit the player">
    <step><p>From the quest or recruiter, get the player's <b>Faction Component</b>. Call <b>Add Faction</b> with the Town Watch asset, starting reputation <code>0</code>, the recruiter as <b>Source</b>, and <code>Factions.Event.QuestCompleted</code> as <b>Event Tag</b>. Leave <b>Main Faction</b> off. In multiplayer, run the quest award on the server.</p></step>
    <step><p>Call <b>Has Membership</b> with Town Watch to check that the player joined. <b>Get Main Faction Membership</b> should still return Players. Adding the same faction again leaves the existing membership in place.</p></step>
    <step><p>When the mission starts, call <b>Set Main Faction</b> with Town Watch. The player now represents the Watch for team checks. Their Players membership stays on the component.</p></step>
    <step><p>When the mission ends, call <b>Set Main Faction</b> with Players, then <b>Remove Faction</b> with Town Watch. You can only remove a secondary membership this way. If the player should keep their Watch reputation, leave that membership in place.</p></step>
</procedure>

## React to Membership Changes

Bind to the Faction Component's Blueprint-assignable delegates. Each passes the affected membership, so the same events can drive a quest objective or update a faction menu.

| Hook | When to use it |
| --- | --- |
| `OnFactionAdded` | Show a new membership or unlock a guild objective when the player joins. |
| `OnMainStatusChanged` | Read the membership's **Main Faction** flag to move the active-team marker when the player changes sides. |
| `OnFactionRemoved` | Remove the faction's entry from a menu when the player leaves. |

To restrict who can recruit the player, override **Is Valid Faction Assignment** (`IsValidFactionAssignment`) on a Faction Component subclass. The default rule expects a valid source and an event under `Factions.Event`. When the source implements `IFactionSourceInterface`, its **Can Provide Faction Values** hook also gets a say.

If an entire Game Feature grants membership, use its **Add Factions** action. Choose the receiving actor class and memberships. The actor must be registered as a Game Framework Component Manager receiver and expose a Faction Component.

## Try It in Play

Trigger each mission step and print the main faction and membership count. Starting with Players alone, expect **Players / 1**, **Players / 2** after recruitment, **Town Watch / 2** during the mission, and **Players / 1** after leaving. If recruitment is ignored, check the source, event tag, and whether the player already belongs to the Watch.
