# Configure Collision

Set up collision for the feature you are testing. A combat trace needs a target it can hit. An interaction scan needs two shapes that overlap. A dropped item may need a floor trace. Start with the matching section below.

Open **Edit → Project Settings → Engine → Collision**. An **Object Channel** identifies a kind of object. A **Trace Channel** is what a query tests. A **Preset** saves the object type, collision mode, and responses so you can apply them to a component. In an existing project, keep channel assignments that other assets already use. Select the corresponding named channel on the plugin's query or trace setting.

## Combat

<procedure title="Make the character visible to combat traces">
    <step><p>Under <b>Object Channels</b>, create <code>CombatObject</code> with default response <b>Ignore</b>. Under <b>Preset</b>, create <code>Combat</code>, set <b>Collision Enabled</b> to <b>Query Only</b>, choose <code>CombatObject</code> as its object type, and set its response to <code>CombatObject</code> to <b>Block</b>.</p></step>
    <step><p>Apply the preset to the character mesh or dedicated hit shapes. Let those shapes ignore <b>Pawn</b>, <b>Camera</b>, and <b>Vehicle</b> where the movement capsule already handles physical contact. Keep the capsule's movement preset.</p></step>
    <step><p>In your attack's scan settings, select the channel that matches your target setup. For an object query, include the target's object type. For a trace by channel, set the target's response to that channel to <b>Block</b>.</p></step>
</procedure>

[Set up a combatant](cbt_first_steps.md), then [land a melee hit](cbt_guide_melee_attacks.md). If the swing passes through the target, check which component the trace crosses, its assigned preset, and the channel selected by the attack.

### Additional Combat Traces

Add these trace channels when the move calls for them. The default response sets the starting behavior for components in the project. Adjust individual presets for the objects the move should hit.

| Trace channel | Default response | What to configure |
| --- | --- | --- |
| `Projectile` | Block | Let the target and any cover that should stop a shot block the trace. Have trigger volumes ignore it. |
| `Opportunity` | Ignore | Let eligible target shapes block an opportunity check. |
| `Aim` | Ignore | Let the shapes you want to aim at block the trace. |
| `Evade` | Block | Let obstacles that should stop an evade block the trace. |

## Interaction

<procedure title="Let a pawn detect a switch">
    <step><p>Create an <b>Object Channel</b> named <code>InteractionObject</code> with default response <b>Ignore</b>. Create the two presets below. Both use <b>Query Only</b> and the <code>InteractionObject</code> object type.</p></step>
    <step><p>Assign <code>InteractionSource</code> to the pawn's scan and focus shapes. Assign <code>InteractionTarget</code> to the collision box around the switch. Enable <b>Generate Overlap Events</b> on both sides.</p></step>
</procedure>

| Preset | Response to `InteractionObject` | Other channels |
| --- | --- | --- |
| `InteractionSource` | Overlap | Ignore |
| `InteractionTarget` | Block | Ignore |

The source's **Overlap** response lets it detect the target without physically stopping the pawn. [Interact with a Nearby Object](int_first_steps.md) sets up the sphere, focus box, abilities, and switch. If the switch never registers, check both shapes' responses and overlap events. If it registers but never becomes selectable, check the focus shape and the find ability.

### Line of Sight for Interactions

If a wall should hide the switch, enable the line-of-sight check on your targeting task. Ninja Interaction defaults to **Visibility**. To control interaction sight separately, create the `InteractionSight` trace channel with default response **Ignore**, then select it as the **Line of Sight Channel** in Ninja Interaction settings. Make walls and other opaque obstacles **Block** that channel, including the **BlockAll** and **BlockAllDynamic** presets where appropriate. Let trigger volumes ignore it.

Test with the switch in range, first with a clear view, then with a blocking wall between the pawn and switch. The wall should prevent selection while the sight check is active.

## Floor

For a cast actor that settles on the floor or an inventory pickup placed on the ground, use a trace channel your walkable surface blocks. If you want a dedicated channel, add **Floor** under **Trace Channels** with default response **Ignore**.

On the floor mesh's existing preset, set **Floor** to **Block** and keep the responses that let the character stand on it. If you create a separate floor preset, use **WorldStatic** and **Query and Physics** for a solid level floor. For a cast actor, select that channel under **Floor Alignment → Floor Trace Channel**. For inventory drops, the Drop fragment's **Placement Query** chooses where the pickup appears. If that query traces for the ground, select the floor channel in the query. Set **Projectile** or **Evade** to **Ignore** on the floor only if those queries should pass through it. If a query selects floors by object type, you can also define **FloorObject** as an object channel and assign it to the surfaces that query should find.

A first inventory with a fixed-size bag only needs its [item and container setup](inv_first_steps.md). Check floor collision when you [drop an item into the level](inv_gameplay_abilities.md) or [place a cast effect](cbt_guide_cast_actor.md).
