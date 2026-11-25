# Configure a Firearm and Reload It
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Give the player two game weapons with different controls. The rifle keeps firing while the button is held and reloads a magazine. The shotgun fires once per press and reloads one shell on each animation loop.

<procedure title="Register a firearm and supply reserve ammo">
    <step><p>Create a <code>NinjaCombatWeaponActor</code> Blueprint with a weapon mesh and a <code>NinjaCombatFirearmComponent</code>. Add a muzzle socket to the mesh and return that mesh from <code>GetProjectileSourceMesh</code> on the ranged interface. Give each weapon an identifying tag. Register it and map its attachment socket as in the <a href="cbt_guide_melee_attacks.md">weapon setup</a>. Test one equipped firearm at a time.</p></step>
    <step><p>Create a <b>Firearm Definition</b> from the Ninja Combat menu and assign it to the component. Set the muzzle socket and a hitscan channel that reaches the test target. Assign the firearm damage effect and set a positive <b>Base Pellet Damage</b> if each hit should reduce health. Assign shooting and reloading montages on the component. Add an <b>Ammo Storage Component</b> to the character and give it starting reserve ammo whose tags match the definition's ammo query.</p></step>
</procedure>

| Setting                      | Rifle example                                    | Shotgun example                                                                                                 |
|------------------------------|--------------------------------------------------|-----------------------------------------------------------------------------------------------------------------|
| Implementation and fire mode | Hit Scan, Automatic                              | Hit Scan, Single Shot                                                                                           |
| Pellets per shot             | One                                              | Several, with spread so the traces can separate                                                                 |
| Ammo Limit and Initial Ammo  | 30                                               | 8                                                                                                               |
| Reload Mode                  | Clip                                             | Single, with Ammo Added set to 1                                                                                |
| Reload montage               | A Reload section with one **Reload Ammo** notify | Reload, Loop, and End sections. Put **Reload Ammo** in Loop and match the loop and end names in the definition. |

<procedure title="Connect fire and reload">
    <step><p>Grant abilities based on <code>CombatAbility_Shoot</code> and <code>CombatAbility_Reload</code>. Use their firearm Shoot and Reload animation providers. Match the shooting section name in the ability to the montage and set the reload section to <b>Reload</b>. Set the reload policy to <b>Gameplay Event</b> and its weapon query to match the active firearm.</p></step>
    <step><p>From the fire input call <code>TryOpenFire</code> on press and <code>TryCeaseFire</code> on release on the active Firearm Component. The component requests the Shoot ability. Activate the granted Reload ability from the reload action.</p></step>
</procedure>

<img src="cbt_guide_firearm_animation_reload_shotgun.png" alt="Reload Ammo notify inside the shotgun montage loop" width="650" border-effect="line"/>

For camera or AI aiming, implement `GetAimIntent` on the controller's **Combat Aim Intent Provider Interface**. For a custom reserve, implement `GetAvailableAmmo` and `TakeAmmo` on the ammo storage interface. To show different effects on wood and stone, use a **Combat Impact Cosmetics** table with entries for the surfaces and assign it to the firearm. See [Combat and Inventory](integration_combat_inventory.md) for equipment and reserve items.

## Try It in Play

Fire three rifle rounds, release, then reload. Check that the loaded count increases at the notify and the reserve falls by the same amount. With the shotgun, hold fire once and check for one shot. Reload from several shells down and watch each loop add one until capacity or reserve runs out.
