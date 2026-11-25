# Configure Teams and Attitudes
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Make the [First Steps guard](bot_first_steps.md) ignore an ally and chase an enemy. This route uses Unreal's native team interface and requires a C++ character class. For a Blueprint workflow using faction assets, follow [Bot and Factions](integration_bot_factions.md).

<procedure title="Give the guard and the player team IDs">
    <step><p>On the character class used for the guard and the player, implement <code>IGenericTeamAgentInterface</code> from <code>GenericTeamAgentInterface.h</code>. Add <code>AIModule</code> to the module dependencies if needed.</p></step>
    <step><p>Expose a byte property named <b>TeamId</b> on the character defaults. Override <code>FGenericTeamId GetGenericTeamId() const</code> and return <code>FGenericTeamId(TeamId)</code>. The default provider reads the actors being compared, including the guard's pawn.</p></step>
    <step><p>Compile and set the guard's team to <b>1</b> and the player character's team to <b>2</b>. In <b>Edit → Project Settings → Ninja Bot</b>, select <b>Default Team Provider</b>.</p></step>
</procedure>

<procedure title="Limit sight to enemies">
    <step><p>Open the guard's <b>Sense Profile</b> and expand Sight. Under <b>Detection by Affiliation</b>, enable enemies and clear friendlies and neutrals. Save.</p></step>
</procedure>

<img src="bot_guide_perception_sense_profile_hostile_only.png" alt="Sight configured to detect enemies" width="780" border-effect="line"/>

## Try It in Play

With Unreal's default team attitudes, the guard should chase the player on team 2. Stop play, change the player to team 1, and repeat from the same position. The guard should keep roaming. If both tests behave alike, check the team property on the possessed pawn and the profile assigned to the guard.
