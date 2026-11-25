# Launch a Projectile
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Cast a glowing projectile from a hand socket and make it affect the combatant it hits. Use the [combatant setup](cbt_first_steps.md) for the caster and target.

<procedure title="Create the traveling actor">
    <step><p>Make a Gameplay Effect based on <code>CombatEffect_RangedHit</code>. Create a Blueprint based on <code>NinjaCombatProjectileActor</code> and assign the effect as its <b>Impact Effect Class</b>.</p></step>
    <step><p>Set its scan channel and hit adjustment trace channel to the combat channel your target responds to. Add a trail or mesh so you can see the projectile travel. For a Niagara trail, turn off <b>Auto Activate</b>.</p></step>
</procedure>

<procedure title="Launch from the release frame">
    <step><p>Implement the <b>Combat Ranged Interface</b> on the caster. Return the mesh with the launch socket from <code>GetProjectileSourceMesh</code>. Add a <b>Launch Projectile</b> notify at the release frame of the cast montage. In its <b>Request Data</b>, set the source to <b>Owner</b> and its origin socket to that socket.</p></step>
    <step><p>Create a <code>CombatAbility_LaunchProjectile</code> Blueprint. Set <b>Projectile Trigger</b> to <b>Gameplay Event</b>, assign the montage, and set <b>Fallback Projectile Class</b> to your projectile. Grant the ability and activate it from your test action. For a weapon launch, set the notify source to <b>Weapon</b> and use a query matching the registered weapon.</p></step>
</procedure>

<img src="cbt_guide_projectile_montage_notify.png" alt="Launch Projectile notify on the montage release frame" width="650" border-effect="line"/>

Override the projectile's `LaunchProjectile` and `Exhaust` events to start and stop a trail. Call the parent implementation in both so movement and cleanup still run. C++ subclasses can implement the corresponding `_Implementation` methods. If your game fires many projectiles, add `NinjaCombatActorPoolComponent` to the attacker, include the projectile class in its pool configuration, and return the component from `GetActorPool` on the Combat Pool Provider Interface. Reset per-shot visuals on activation and clear them on deactivation. A class configured in the notify's request can override the ability's fallback projectile.

<code-block lang="c++" src="cbt_add_actor_pool_component.cpp" collapsible="true" collapsed-title="Return the projectile pool from a C++ character"/>

## Try It in Play

Launch toward a stationary target, then past it. Check the socket origin, whether the projectile reaches the target, and whether health changes only on a hit. Fire again and check that a reused trail begins at the new origin.
