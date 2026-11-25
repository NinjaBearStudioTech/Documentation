# Bot and Factions: Resolve Teams for Perception
<primary-label ref="integrations"/>
<secondary-label ref="bot-sec"/>
<secondary-label ref="factions-sec"/>

Make a lookout notice a rival while letting a teammate walk past. Ninja Factions decides how the lookout regards each actor. Ninja Bot's Sight sense uses that attitude to decide whom to report.

<procedure title="Give the lookout two recognizable targets">
    <step><p>Start with the <a href="fct_first_steps.md">two-faction setup</a> and a <a href="bot_first_steps.md">guard with working sight</a>. Give the guard and one visitor the same main faction, and the other visitor a different main faction. Use distinct team IDs. Set the guard's faction to <b>Friendly</b> toward itself and <b>Hostile</b> toward the rival.</p></step>
    <step><p>Keep the guard's Ninja Bot controller. With both plugins enabled, open <b>Project Settings → Ninja Bot</b> and choose <b>Faction Team Provider</b> for <b>Team Provider Class</b>. It looks up team IDs and attitudes through Ninja Factions automatically. You set membership once on each actor.</p></step>
    <step><p>In the guard's <b>Sense Profile</b>, enable <b>Detect Enemies</b> for Sight. Turn off friendly and neutral detection. Give both visitors the same sight-source setup so that only their faction differs.</p></step>
</procedure>

<img src="bot_advanced_integration_factions.png" alt="Faction Team Provider selected in the Ninja Bot project settings" width="780" border-effect="line"/>

To give a disguised visitor an exception, customize the Factions [attitude solver](fct_reputation_tiers.md). Override `SolveAttitude` in Blueprint, or `SolveAttitude_Implementation` in C++, and apply the disguise rule when the guard is the source and the visitor is the target. Call the parent solver for ordinary encounters. To draw a debug label, use the Faction Function Library's `GetMainTeamIdForMember` for the team and `GetAttitude` for the guard's actual opinion.

## Try It in Play

Walk each visitor through the same patch of ground, one at a time. Only the rival should become a sight target. If both visitors are ignored, call **Get Attitude** with the guard as **Source** and each visitor as **Target**. A Hostile result points you toward the Sight filter or sight-source setup. A Neutral result points you toward the memberships, selected solver, or faction attitude settings.
