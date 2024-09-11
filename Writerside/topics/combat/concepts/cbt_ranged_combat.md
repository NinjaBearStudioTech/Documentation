# Ranged Combat
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The Weapon (or Character) must implement the <b>Ranged Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Ranged Attacks</b>.</li>
        <li>A <b>Projectile</b> is launched by the Attack Ability, from a <b>Gameplay Event</b>.</li>
        <li>The <b>Damage</b> applied by the projectile can be customized in many ways.</li>
    </ul>
</tldr>

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

## Projectiles

### Launch Projectile Notify

### Projectile Request Transfer Object

### Projectile Definition

## Ranged Weapon Interface
