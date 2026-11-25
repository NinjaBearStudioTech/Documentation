# First Steps: Set Up a Combatant
<primary-label ref="combat"/>

Build one character that can both deal and receive damage. Use it for the player and for a stationary test target. Start with [Combat setup](cbt_setup.md).

<procedure title="Connect the character and its animation">
    <step><p>Use a Character Blueprint with an initialized Ability System Component. For a character-owned component, the character is both owner and avatar. For a Player State-owned component, use the possessed character as the avatar.</p></step>
    <step><p>Add <code>NinjaCombatManagerComponent</code>. Implement the <b>Combat System Interface</b> and return it from <code>GetCombatManager</code>. Return the character mesh from <code>GetCombatMesh</code> and the animation instance playing the combat montages from <code>GetCombatAnimInstance</code>. With runtime retargeting these can come from different meshes.</p></step>
    <step><p>Set the target mesh or dedicated hit shapes to the <b>Combat</b> collision preset. Add a matching Slot node to the Animation Blueprint so the montages used by your abilities can play.</p></step>
</procedure>

<procedure title="Give both characters starting attributes">
    <step><p>Add <code>NinjaCombatAttributeSet</code> to the ability system. Use an <b>AttributeMetaData</b> table or your usual initialization effect to give each character health, maximum health, and give the attacker a positive Base Damage.</p></step>
    <step><p>With Ninja G.A.S., add the attribute set and its table under <b>Default Attribute Sets</b> in the GAS Setup Data assigned to the Ability System Component. With your own GAS setup, initialize the set and grant abilities on the server.</p></step>
    <step><p>Place a second instance within reach in the level. Give it the same starting health. Keep its movement and attacks idle for the first test.</p></step>
</procedure>

## Initialization Data

The sample includes starting values for attacks, defenses, resources, and recovery. Adjust them to suit your characters.

<code-block lang="json" src="cbt_attributes.json" collapsible="true" collapsed-title="Sample combat attributes"/>

## Try It in Play

Use `showdebug abilitysystem` and inspect both characters. Check that each has its own current and maximum health. Next, [register a weapon and land a melee hit](cbt_guide_melee_attacks.md). If you start with a spellcaster, [launch a projectile](cbt_guide_ranged_attacks.md) from the character's mesh instead.
