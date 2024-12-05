# Concepts
<primary-label ref="combat"/>

This section includes **high-level concepts** for the Combat System. These elements are provided by an aggregation of 
multiple technical elements, such as **components** and **gameplay classes**.

**[](cbt_melee_combat.md)**
: Melee combat can be executed by a combatant (hand-to-hand combat) or using weapons. The process is the same for both 
scenarios and includes scanning, applying damage effects, and triggering impact cosmetics.

**[](cbt_ranged_combat.md)**
: Ranged combat can be executed by a combatant or using ranged weapons. In both cases, projectiles are spawned in the 
world and can apply damage independently of their owner's Ability System Component.

**[](cbt_combo_system.md)**
: Attack Abilities for both Melee and Ranged Combat can be orchestrated by the Combo System. This is a State Tree-based
solution that can manage combo states, transitions, and damage multipliers.

**[](cbt_opportunity_system.md)**
: This system handles attacks that can only be triggered from certain opportunities, such as a Backstab or a Riposte.
This system takes care of gathering eligible targets, pairing animations between participants, and animating the camera.

**[](cbt_damage_and_defense.md)**
: Every successful hit or impact triggers the Damage and Defense system, where things like Critical Damage, Armor, 
Blocking, and Invincibility are considered to determine the final damage output.

**[](cbt_poise_and_stagger.md)**
: A system that works in tandem with the Damage system, but can be enabled or disabled as needed. It is commonly used in 
conjunction with the Opportunity System.

**[](cbt_target_locking.md)**
: The Target Locking functionality allows combatants, players or AI, to lock on a target, which helps with Motion Warping
and targeting, plus it can also notify current targets, so they can be considered _in combat_.

**[](cbt_forward_reference.md)**
: The Target Locking functionality allows combatants, players or AI, to lock on a target, which helps with Motion Warping
and targeting, plus  it can also notify current targets, so they can be considered _in combat_.