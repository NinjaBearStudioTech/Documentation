# Ranged Combat
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The weapon or character must implement the <b>Ranged Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Ranged Attacks</b>. Once it activates, it will listen to many <b>Gameplay Events</b>.</li>
        <li>A <b>projectile</b> is launched by the Attack Ability, from a <b>Gameplay Event</b>, and it can be obtained from the <b>Actor Pool</b>.</li>
        <li><b>Damage</b> is applied by the projectile, and does not need the source to be available anymore.</li>
    </ul>
</tldr>

The **Ranged Combat** functionality is designed to connect animations, launching projectiles and applying their damage
regardless of the owner's Ability System Component. This functionality is also related to the [Actor Pool](cbt_actor_pooling.md).

<code-block lang="mermaid">
sequenceDiagram
    ASC->>AttackAbility: activate
    activate AttackAbility
        AttackAbility->>AttackAbility: listen for events
        AttackAbility->>Animation: play
        activate Animation
            Animation->>LaunchProjectileNotify: begin
            activate LaunchProjectileNotify
                LaunchProjectileNotify->>ProjectileRequestInstance: initialize
                activate ProjectileRequestInstance
                    ProjectileRequestInstance-->>LaunchProjectileNotify: instance
                deactivate ProjectileRequestInstance
                LaunchProjectileNotify->>AttackAbility: gameplay event
                Animation->>LaunchProjectileNotify: end
            deactivate Animation
            deactivate LaunchProjectileNotify
            AttackAbility->>SpawnProjectileTask: initialize
            activate SpawnProjectileTask
                SpawnProjectileTask-->>AttackAbility: instance
            deactivate SpawnProjectileTask
            AttackAbility->>SpawnProjectileTask: activate
            activate SpawnProjectileTask
                SpawnProjectileTask->>ProjectileRequestInstance: spawn
                activate ProjectileRequestInstance
                    ProjectileRequestInstance->>Projectile: spawn
                    activate Projectile
                    ProjectileRequestInstance-->>SpawnProjectileTask: Projectile
                deactivate ProjectileRequestInstance
            SpawnProjectileTask-->>AttackAbility: Projectile
            deactivate SpawnProjectileTask
            AttackAbility->>Projectile: set GE Spec
            AttackAbility->>Projectile: launch
            deactivate Projectile
    deactivate AttackAbility
</code-block>

## Attack Ability

A Ranged Attack starts with the **Attack Ability**.

<img src="cbt_melee_ability.png" alt="Ranged Ability" border-effect="line" thumbnail="true"/>

## Projectiles

### Launch Projectile Notify

### Projectile Request Transfer Object

### Projectile Definition

## Ranged Weapon Interface
