# React to Fatal Damage
<secondary-label ref="guide"/>

<video src="https://youtu.be/koGpsk_2F-s" preview-src="sc_thumbnail_p01g06.png" width="800" />

Continuing the damage handling, we will handle fatal damage, which starts the death flow and activates the
**Death Ability**.

<procedure title="Configure the default death reaction animation" collapsible="true">
    <step>For the default hit reaction, we will use <b>directional animations</b>. Create an <b>Animation Montage</b> and organize all the sequences.</step>
    <step>Create <b>Montage Sections</b> for each sequence, with appropriate names, based on their directions.</step>
    <step>In the <b>Montage Sections</b> tab, make sure to break the links between all sections, so they won't play in a sequence.</step>
    <img src="p01g05_hit_reaction_montage_default.png" alt="Default Hit Reaction Animation Montage" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the Death Gameplay Ability" collapsible="true">
</procedure>

<procedure title="Update the Damage Data Asset" collapsible="true">
</procedure>

<procedure title="Test everything" collapsible="true">
</procedure>