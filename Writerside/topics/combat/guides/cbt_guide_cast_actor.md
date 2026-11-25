# Leave a Frost Field That Applies an Effect on Contact
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Give a caster a frost field they can leave behind. A combatant that enters the field gains a `Status.Frosted` gameplay tag. Leaving the field clears the tag. The cast actor handles entry and exit, so the spell can keep working after the caster finishes the animation.

<procedure title="Build the field and its effect">
    <step><p>Register <code>Status.Frosted</code> in your project's gameplay tags. Create a Gameplay Effect with an <b>Infinite</b> duration and grant that tag to the target while the effect is active.</p></step>
    <step><p>Create a Blueprint based on <code>NinjaCombatCastActor_Sphere</code>. In its class defaults, set <b>Cast Effect Class</b> to the frost effect. On the root sphere, set a radius of 300, enable query collision and <b>Generate Overlap Events</b>, and set the response to the target's collision object type to <b>Overlap</b>. Enable overlap events on the target's collision component too.</p></step>
    <step><p>On the <b>Cast Behavior</b> component, open the existing <b>Cast Effect</b> behavior. Enable <b>Manage Effect Removal</b> so the infinite effect ends on exit. Keep <b>Should Ignore Source</b> enabled. Turn off <b>Reinforce Hit Results</b> so touching the sphere is enough to gain the tag.</p></step>
    <step><p>In <b>Floor Alignment</b>, choose a <b>Floor Trace Channel</b> that your floor blocks and the caster ignores. In the <b>Dissipation</b> behavior, enable <b>Auto Dissipate</b> and set <b>Active Duration</b> to five seconds. Add a visible ring or particle effect matching the sphere so the player can see where to step.</p></step>
</procedure>

To let frost-resistant characters walk through safely, make a child of <code>NinjaCombatCastEffectBehavior</code> and use it in place of the field's default effect behavior. Override <code>PassesCastFilter</code> in Blueprint, or <code>PassesCastFilter_Implementation</code> in C++, and return false for targets with your resistance tag. The built-in behavior still handles application and removal.

<procedure title="Let the caster leave the field behind">
    <step><p>Create a <code>CombatAbility_Cast</code> Blueprint. Choose <b>Ability Activation</b> for <b>Cast Trigger</b> and <b>Spawn Actor</b> for <b>Targeting</b>. Set <b>Cast Actor Class</b> to the frost field. The actor owns the frost effect.</p></step>
    <step><p>Assign a short casting montage, grant the ability, and activate it on your character. The default spawn location is the caster's position. Walk away as the animation finishes.</p></step>
</procedure>

## Try It in Play

Move a second combatant into the field after the caster walks away. Watch its owned tags in the Gameplay Debugger. <code>Status.Frosted</code> should appear on entry and disappear on exit. Enter again and stay until the field expires. The tag should clear then too.
