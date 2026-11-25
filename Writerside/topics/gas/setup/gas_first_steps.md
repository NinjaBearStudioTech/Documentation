# First Steps: Give a Character an Ability System
<primary-label ref="gas"/>

Choose who should keep the abilities when the pawn goes away. For a guard that starts fresh each time it spawns, use the character-owned setup. For a player who keeps abilities across respawns, use the Player State setup.

## Create a Setup Asset

In the folder you registered during [setup](gas_setup.md), choose **Add → Ninja Bear Studio → Ninja G.A.S. → G.A.S. Setup**. Name the asset `DA_StarterAbilities`. To make the first grant easy to spot, create a Gameplay Ability Blueprint named `GA_Wave` and add it to **Default Gameplay Abilities** at level 1. You can inspect a grant before wiring it to input.

## Character-Owned ASC

<procedure title="Give the guard its own abilities">
    <step><p>Create a Blueprint based on <code>NinjaGASCharacter</code>. Select its Ability System Component (ASC) and assign <code>DA_StarterAbilities</code> to <b>Default Ability Setup</b>. Leave the character's separate setup field empty for this example.</p></step>
    <step><p>Place the guard in your test level. Its component initializes on Begin Play. The guard is both the owner of the ability and the avatar that performs it.</p></step>
</procedure>

## Player State-Owned ASC

<procedure title="Keep the player's abilities across pawns">
    <step><p>Create a Blueprint based on <code>NinjaGASPlayerState</code>. Select its Ability System Component and assign <code>DA_StarterAbilities</code> to <b>Default Ability Setup</b>.</p></step>
    <step><p>Create a character based on <code>NinjaGASPlayerCharacter</code>. In the active Game Mode, set <b>Player State Class</b> to your new Player State and <b>Default Pawn Class</b> to your new character. Start play and let the player possess it.</p></step>
    <step><p>For a move tied to this pawn, create a second setup asset containing that move and assign it to <b>Default Ability Setup</b> on the character's class defaults. The Player State supplies the shared abilities and the pawn supplies its own moves.</p></step>
</procedure>

## Try It in Play

Run `showdebug abilitysystem` and select the test character as the debug target. Look for `GA_Wave` in the abilities list. For the guard, owner and avatar should identify the guard. For the player, the owner should be the Player State and the avatar should be the possessed pawn. Possess a second player pawn with a different setup on the same Player State and check that the shared ability remains while the pawn-specific move changes.

To connect a widget that opens before possession finishes, use the Blueprint node **Wait For Ability System** on the pawn. On **Completed**, resolve the component and read the values. Use **Timed Out** to show an unavailable state and **Cancelled** to discard a pending update. For possession changes on an existing component, bind to `OnAbilitySystemAvatarChanged` and refresh the widget's pawn reference.

Next, [give the character a starting value and an ability that changes it](gas_guide_starting_abilities.md).
