# Motion Warping
<secondary-label ref="guide"/>

Motion Warping can adjust **root motion animations** to **shorten** or **stretch** their movement, so they will
properly reach targets.

<procedure title="Add the Motion Warping Component" collapsible="true">
    <step>Add the <code>NinjaCombatMotionWarpingComponent</code> to your base Character C++ class or Blueprint.</step>
    <step>Implement the `GetMotionWarpingComponent` function, returning the Motion Warping Component just added.</step>
    <note>You might have already done this before, while configuring Opportunity Attacks. If you did, then you can ignore this step!</note>
</procedure>

<procedure title="Configure Melee Target Presets" collapsible="true">
    <step>Create a new <b>Targeting Preset</b>. It will be used for the warp target selection.</step>
    <step>Add the <b>Current Target</b> Selection Task. This will prioritize any target that is currently selected.</step>
    <step>Add the <b>AOE</b> Selection Task. Use a <b>Sphere</b> shape, add <b>Pawn</b> and <b>World Dynamic</b> as <b>Collision Object Types</b>, set it to <b>ignore the source actor and instigator</b>, and a <b>radius</b> of <b>1600</b>.</step>
    <step>Add the <b>Actor Class</b> Filter Task. Set your <b>base Character Class</b> as the <b>Required Actor Class Filter</b>, or adjust these filters to match your character hierarchy.</step>
    <step>Add the <b>Facing</b> Filter Task. Set the maximum angle to <b>60</b>, or any other value that makes sense to you.</step>
    <step>Add the <b>Dead</b> Filter Task.</step>
    <step>Add the <b>Sort By Distance</b> Filter Task.</step>
</procedure>

<procedure title="Update Initial Attack Abilities" collapsible="true">
    <step>Open your <b>Gameplay Ability</b> for the first Melee Attack in the main combo.</step>
    <step>Enable <b>Motion Warping</b> by checking the appropriate property.</step>
    <step>Leave the default <b>Warp Target Provider</b> unchanged. The first attack will only warp if a target is locked.</step>
    <step>Adjust the <b>Warp Offset</b> as necessary, providing a distance to be kept between attacker and victim.</step>
    <step>Repeat these steps for all _first_ or _single_ attack abilities that you need to use warping.</step>
</procedure>

<procedure title="Update Follow-up Attack Abilities" collapsible="true">
    <step>Open the follow-up <b>Gameplay Abilities</b> that will continue the combo with melee attacks.</step>
    <step>Same as before, enable <b>Motion Warping</b> and adjust the <b>Warp Offset</b>.</step>
    <step>Change the <b>Warp Target Provider</b> to <b>Targeting System</b>. Set the Targeting Preset created in the previous step.</step>
    <step>Repeat these steps for all _follow-up_ attack abilities that you need to use warping.</step>
</procedure>

<procedure title="Add Motion Warping Notify States" collapsible="true">
    <step>Open the <b>Animation Montage</b> for the first Melee Attack in the main combo.</step>
    <step>Add the <b>Motion Warping Anim Notify State</b> at the beginning of the animation, for a reasonable stretch.</step>
    <step>Set the <b>Warp Name</b> in the Notify State to <code>CombatWarp</code>.</step>
    <step>Repeat these steps for other Animation Montages used for other Melee Attacks.</step>
    <note>Make sure to check the <a href="cbt_motion_warping.md"/> page for more information on how to configure your warping.</note>
</procedure>

<procedure title="Test Everything" collapsible="true">
    <step>Hit <b>Play</b> and try to attack the enemy from far, no warp should happen.</step>
    <step>Move closer, within warping range and attack the enemy. Warping should happen.</step>
</procedure>
