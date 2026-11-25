# Weapons and Attack Types
<primary-label ref="combat"/>

A weapon supplies the mesh, socket, and settings for an attack. The ability tells it when to act. A character can also supply those directly, for a punch or a spell cast from the hand.

## Weapon Actors

Give the weapon an identifying gameplay tag. A sword and a wand can then use different meshes and effects while the character activates attacks through the same ability system. On a melee weapon, `GetMeleeMesh` supplies the mesh with scan sockets. On a ranged source, `GetProjectileSourceMesh` supplies the mesh with the launch socket.

## Weapon Manager

The default manager finds registered actors by matching their weapon tags to the ability or notify's **Weapon Query**. Set **Default Weapon Classes** for starting gear and **Weapon Socket Mapping** for attachments. Use `AddWeapon` for an actor you already have or `AddWeaponClass` to spawn and register one. If equipment comes from Inventory, follow [Combat and Inventory](integration_combat_inventory.md).

## Choose How Contact Happens

| Move | How the target is found |
| --- | --- |
| [Swing or punch](cbt_guide_melee_attacks.md) | Scan a weapon or character socket during selected animation frames. An overlap shape can also supply targets. |
| [Traveling projectile](cbt_guide_ranged_attacks.md) | Launch an actor from a socket and apply its effect when it reaches a target. |
| [Hitscan](cbt_guide_firearms.md) | Trace the shot when it fires. Use an impact cue or surface cosmetic to show where it landed. |
| [Shockwave](cbt_guide_cast_preset.md) | A targeting preset gathers everyone in range when the spell fires. |
| [Lingering field](cbt_guide_cast_actor.md) | A spawned cast actor applies its effect when a combatant overlaps its collision shape. |
| [Aimed spell](cbt_guide_cast_flows.md) | A GAS Target Actor previews the blast and sends the selection when the player confirms. |

For frequently spawned projectiles or cast effects, use an actor pool on the owner. Configure the classes you expect to reuse, reset trails and other per-use visuals at launch, and return the actor when its effects finish. The [projectile guide](cbt_guide_ranged_attacks.md) covers the launch and exhaust hooks.
