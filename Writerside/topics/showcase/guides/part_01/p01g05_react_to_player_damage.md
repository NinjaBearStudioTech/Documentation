# React to Player Damage
<secondary-label ref="guide"/>

To make sure that our attacks work, we need an enemy. Using concepts established before, we will create a new enemy
character that properly **reacts to incoming damage** and eventually dies.

<procedure title="Configure hit reaction animations" collapsible="true">
    <step>For the default hit reaction, we will use <b>directional animations</b>. Create an <b>Animation Montage</b> and organize all the sequences.</step>
    <step>Create <b>Montage Sections</b> for each sequence, with appropriate names, based on their directions.</step>
    <step>In the <b>Montage Sections</b> tab, make sure to break the links between all sections, so they won't play in a sequence.</step>
    <img src="p01g05_hit_reaction_montage_default.png" alt="Default Hit Reaction Animation Montage" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure hit reaction animations" collapsible="true">
    <step>Create an <b>Animation Montage</b> for the <b>heavy reaction</b>.</step>
    <img src="p01g05_hit_reaction_montage_strong.png" alt="Knockback Hit Reaction Animation Montage" thumbnail="true" border-effect="line" width="600"/>
    <tip>Even though this step only uses a single Animation Sequence, you could also have directional animations if you have them.</tip>
</procedure>

<procedure title="Configure the hit reaction ability" collapsible="true">
    <img src="p01g05_hit_reaction_ability.png" alt="Hit Reaction Gameplay Ability" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the enemy Blueprint" collapsible="true">
</procedure>

<procedure title="Configure the enemy Ability Data" collapsible="true">
</procedure>

<procedure title="Test your hit reactions" collapsible="true">
</procedure>