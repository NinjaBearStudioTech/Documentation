# First Steps: Give Two Actors Opposing Factions
<primary-label ref="factions"/>

Give a player and a zombie different teams, then ask how each sees the other. Start with a playable character, an enemy character, and the **Simple Attitude Check** solver from [Set Up Ninja Factions](fct_setup.md).

<procedure title="Create the two factions">
    <step><p>In the faction folder you registered, right-click and choose <b>Ninja Bear Studio → Ninja Factions → Faction</b>. Name the asset <b>Players</b>, set its display name to Players, choose <code>Factions.ID.Players</code> as its <b>Faction Tag</b>, and set <b>Team ID</b> to <code>1</code>. Keep its attitude toward its own faction <b>Friendly</b> and toward other factions <b>Neutral</b>.</p></step>
    <step><p>Create a second faction named <b>Zombies</b>. Give it the tag <code>Factions.ID.Enemies.Zombies</code> and team ID <code>10</code>. Add the tag in <b>Project Settings → Gameplay Tags</b> if needed. Set its attitude toward its own faction to <b>Neutral</b> and toward other factions to <b>Hostile</b>. Leave both attitude matrices empty.</p></step>
</procedure>

<tabs>
    <tab title="Players"><img src="fct_faction_players.png" alt="Players faction with team ID 1" width="780" border-effect="line"/></tab>
    <tab title="Zombies"><img src="fct_faction_zombies.png" alt="Zombies faction with team ID 10" width="780" border-effect="line"/></tab>
</tabs>

<procedure title="Give each character a starting team">
    <step><p>Add a <b>Faction Component</b> to the characters' shared base Blueprint, or to each character if they have separate bases.</p></step>
    <step><p>On the player's component, add <b>Players</b> under <b>Default Factions</b>. Check <b>Main Faction</b> and leave reputation at zero. Do the same on the zombie, choosing <b>Zombies</b>.</p></step>
    <step><p>For a standalone AI that uses Unreal's team and perception system, select <code>NinjaFactionAIController</code> as the zombie's <b>AI Controller Class</b> and enable <b>Auto Possess AI</b> for placed or spawned actors. Set the active Game Mode's <b>Player Controller Class</b> to <code>NinjaFactionPlayerController</code> or your subclass. If you already use a Ninja Bot controller, follow <a href="integration_bot_factions.md">Bot and Factions</a> for that part.</p></step>
</procedure>

## Try It in Play

1. Place a zombie in the level. In the Level Blueprint, create a reference to it and use **Get Player Pawn** for the player.
2. From a test event you can trigger after both have spawned, call the Faction Function Library's **Get Attitude**. Connect the zombie to **Source** and the player to **Target**. Print the **Attitude** output. Expect **Hostile**.
3. Swap the pins and trigger the event again. Expect **Neutral** because Players treats other factions as neutral. To make the hostility mutual, change Players' attitude toward Zombies with an [attitude matrix](fct_reputation_tiers.md#give-one-faction-an-exception).

If both checks return Neutral, call **Get Main Faction** on each actor. Check that the results are Zombies and Players and that **Simple Attitude Check** is selected.

## Next Steps

[Recruit a character during play](fct_manage_memberships.md) or [use the attitude in an AI tree](fct_bots.md).
