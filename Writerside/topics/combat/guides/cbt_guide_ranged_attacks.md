# Configuring Ranged Attacks
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

This guide shows how to create a basic **ranged attack** using an **Gameplay Ability**, an **Animation Montage** and a
**Projectile Actor**.

The setup is agnostic to the ranged source. The same flow works for projectiles launched from the **combatant** and 
for projectiles launched from an equipped **weapon**. The shared pre-requisite is that a projectile source must be a
valid implementation of `ICombatRangedInterface`.

For more information, see the documentation for [**Ranged Attacks**](cbt_concept_ranged_attacks.md).

## Prerequisites

### Collision and Components

Your collision channels, combat components, and base character setup should already be configured. For more information,
see [**Combat Setup**](cbt_setup.md) and [**Combat First Steps**](cbt_first_steps.md).

### Input Handling

Make sure your input setup can activate gameplay abilities. For more information, see
[**Combat and Input Integration**](integration_combat_input.md). Integration with Ninja Input is optional, but input
handling for ability activation should already be configured.

### Weapon Management
<secondary-label ref="optional"/>

If your projectiles originate from **weapons**, make sure to configure them first. For more information, see
[**Weapon Management**](cbt_concept_weapon_management.md).

## Projectile Actor

