# React to Player Damage
<secondary-label ref="guide"/>

<video src="https://youtu.be/e0ehcUX92v8" preview-src="sc_thumbnail_p01g05.png" width="800" />

To make sure that our attacks work, we need an enemy. Using concepts established before, we will create a new enemy
character that properly **reacts to incoming damage** and eventually dies.

<procedure title="Configure the default hit reaction animation" collapsible="true">
    <step>For the default hit reaction, we will use <b>directional animations</b>. Create an <b>Animation Montage</b> and organize all the sequences.</step>
    <step>Create <b>Montage Sections</b> for each sequence, with appropriate names, based on their directions.</step>
    <step>In the <b>Montage Sections</b> tab, make sure to break the links between all sections, so they won't play in a sequence.</step>
    <img src="p01g05_hit_reaction_montage_default.png" alt="Default Hit Reaction Animation Montage" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the strong hit reaction animation" collapsible="true">
    <step>Create an <b>Animation Montage</b> for the <b>heavy hit reaction</b>.</step>
    <img src="p01g05_hit_reaction_montage_strong.png" alt="Knockback Hit Reaction Animation Montage" thumbnail="true" border-effect="line" width="600"/>
    <tip>Even though this step only shows a single Animation Sequence, you could also use directional animations here.</tip>
</procedure>

<procedure title="Configure the hit reaction ability" collapsible="true">
    <step>Create a Gameplay Ability from <code>CombatAbility_HitReaction</code>.</step>
    <step>Add a new entry to <b>Hit Reaction Contexts</b> for <code>Combat.Effect.Damage.Knockback</code>. Add the <b>heavy hit</b> animation to it.</step>
    <step>Add a new entry to <b>Hit Reaction Contexts</b> for <code>Combat.Effect.Damage.Stagger</code>. Add the <b>heavy hit</b> animation to it.</step>
    <step>Adjust the animation directions, so they use the appropriate montage sections.</step>
    <step>Set the <b>Default Animation Montage</b> and <b>Default Section Name</b> that will be used when no direction is set, or a direction entry cannot be found.</step>
    <img src="p01g05_hit_reaction_ability.png" alt="Hit Reaction Gameplay Ability" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the enemy Ability Data" collapsible="true">
    <step><a href="p01g02_configure_gas.md">As done before</a>, create a new <b>Attribute Set Data Table</b> that will be used to initialize the <b>Combat Attribute Set</b>.</step>
    <step>Create a new <b>GAS Setup Data Asset</b> for the enemy.</step>
    <step>Add the <b>Combat Attribute Set</b> and initialize it with the <b>Attribute Table</b>.</step>
    <step>Add the <b>Hit Reaction Ability</b> to the list of <b>Default Gameplay Abilities</b>.</step>
    <img src="p01g05_ability_data.png" alt="Hit Reaction Gameplay Ability" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the enemy Damage Data" collapsible="true">
    <step>Create a new <b>Data Asset</b> based on <code>NinjaCombatDamageDataAsset</code>.</step>
    <step>Set the <b>Death Time Limit</b> to <code>5.0</code>, to accommodate longer animations.</step>
    <step>Add a new entry to the list of <code>Damage Handlers</code> and register a <b>Combat Interfaces</b> handler. It will trigger reactions in the weapons, such as their sound and particles.</step>
    <img src="p01g05_damage_data.png" alt="Hit Reaction Gameplay Ability" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the enemy Blueprint" collapsible="true">
    <step>Create a new blueprint for the <b>enemy</b>. This blueprint should inherit from <code>NinjaGASCharacter</code>.</step>
    <step><a href="p01g03_create_melee_weapons.md">As done before</a>, Add the <b>Combat Manager Component</b> as before, implementing the appropriate interface methods.</step>
    <step>Add the <b>Damage Data</b> to the Combat Manager.</step>
    <step>Add the <b>Ability Data</b> to the Ability System Component.</step>
    <step>Make sure that the enemy's <b>capsule collision</b> is set to ignore the <b>weapon channel</b> Also make sure that the enemy's <b>mesh</b> is set to <b>block</b> it.</step>
    <img src="p01g05_enemy_blueprint.png" alt="Enemy Blueprint" thumbnail="true" border-effect="line" width="600"/>
    <note>When setting the <b>Animation Blueprint</b>, make sure to add a slot that can play the <b>Animation Montages</b>.</note>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Place your enemy blueprint in the map.</step>    
    <step>Press <b>play</b> and attack the enemy, your hit reactions should be played.</step>
    <img src="p01g05_results.gif" alt="Enemy Blueprint" thumbnail="true" border-effect="line" width="600"/>
    <note>If you enable the <b>Debug Mode</b> in your <b>Attack Ability</b>, you should see a green sphere where the collision happens, and a description of enemies being hit.</note>
</procedure>