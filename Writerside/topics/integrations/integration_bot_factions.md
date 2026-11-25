# Bot and Factions
<primary-label ref="integrations"/>
<secondary-label ref="bot-sec"/>
<secondary-label ref="factions-sec"/>

Make a guard recognize its enemy through faction membership. Start with a guard that can [detect the player](bot_first_steps.md) and [two faction members](fct_first_steps.md).

<procedure title="Use faction attitudes for sight">
    <step><p>Create or select the Players and Enemies faction assets. Give them different team IDs. On Enemies, choose a friendly or neutral attitude toward its own faction and a hostile attitude toward Players.</p></step>
    <step><p>Assign Players as the player character's main faction and Enemies as the guard's main faction through their Faction components.</p></step>
    <step><p>With both plugins enabled, open <b>Edit → Project Settings → Ninja Bot</b>. Choose the <b>Faction Team Provider</b> under <b>Team Provider Class</b>.</p></step>
    <step><p>In the guard's <b>Sense Profile</b>, set Sight to detect enemies only. Save the assets.</p></step>
</procedure>

<img src="bot_advanced_integration_factions.png" alt="Faction team provider selected in Ninja Bot settings" width="780" border-effect="line"/>

## Try It in Play

Walk in front of the guard. It should select the player. Change the player to the guard's own faction and repeat from the same starting position. If it still gives chase, check the actual attitude between the two members and the Sight affiliation filter.
