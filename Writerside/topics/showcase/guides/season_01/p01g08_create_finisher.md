# Create a Finisher
<secondary-label ref="guide"/>

Let's take a look at the **Opportunity System** by creating a finishing move, that will replace the primary attack,
whenever the enemy's health is low.

## Contextual Animations

<video src="https://youtu.be/wGhL1PvRGJ0" preview-src="sc_thumbnail_p01g08a.png" width="800" />

The **Contextual Animation** functionality from the Unreal Engine allows you to synchronize animation montages between 
multiple actors and fine tune how their positions.

<procedure title="Add the Required Components" collapsible="true">
</procedure>

<procedure title="Create the Animation Montages" collapsible="true">
</procedure>

<procedure title="Create the Roles Data Asset" collapsible="true">
</procedure>

<procedure title="Create the Contextual Animation Data Asset" collapsible="true">
</procedure>

## Opportunity Attack

<video src="https://youtu.be/nYNB3UsEUFo" preview-src="sc_thumbnail_p01g08b.png" width="800" />

Continuing the Opportunity System, let's check the Gameplay Targeting System and then the Opportunity Attack Ability. 
We'll go through a finisher move executed when the enemy is low on health.

<procedure title="Create the Targeting System Data Asset" collapsible="true">
</procedure>

<procedure title="Create the Finisher Ability" collapsible="true">
</procedure>

<procedure title="Configure the Input Handler" collapsible="true">
</procedure>

## Camera Animations

<video src="https://youtu.be/fC72Re8_7Aw" preview-src="sc_thumbnail_p01g08c.png" width="800" />

Opportunity Attacks can optionally use Camera Animations. Let's take a look how to configure the **Player Camera Manager**
and how to create **Camera Animations** for these attacks, using the **Level Sequencer**.

<procedure title="Configure the Player Camera Manager" collapsible="true">
    <step>Set <code>NinjaCombatPlayerCameraManager</code> as the Camera Manager in your <b>Player Controller</b>.</step>
</procedure>

<procedure title="Create Camera Shakes for hits" collapsible="true">
</procedure>

<procedure title="Create the Camera Animation in the Sequencer" collapsible="true">
</procedure>

<procedure title="Test Everything" collapsible="true">
</procedure>
