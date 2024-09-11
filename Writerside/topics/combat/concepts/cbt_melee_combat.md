# Melee Combat
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The Weapon or Character must implement the <b>Melee Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Melee Attacks</b>. Once it activates, it will listen to many <b>Gameplay Events</b>.</li>
        <li><b>Melee Scans</b> events are sent usually by the <b>Melee Scan Notify</b> and will initiate a per-frame <b>Scan</b>.</li>
        <li>At the end of each frame, the <b>Damage Gameplay Effect</b> is applied to all targets collected by the <b>Melee Scan</b>.</li>
    </ul>
</tldr>

The **Melee Combat** functionality is designed to connect animations, scans and targeting in a cohesive way so that 
Melee Attacks can be configured in multiple ways, for many types of combat systems.

<code-block lang="mermaid">
sequenceDiagram
    ASC->>AttackAbility: activate
    activate AttackAbility
        AttackAbility->>AttackAbility: listen for events
        AttackAbility->>Animation: play
        activate Animation
            Animation->>MeleeScanNotifyState: begin
            activate MeleeScanNotifyState
                MeleeScanNotifyState->>MeleeScanInstance: initialize
                activate MeleeScanInstance
                    MeleeScanInstance-->>MeleeScanNotifyState: instance
                deactivate MeleeScanInstance
                MeleeScanNotifyState->>AttackAbility: gameplay event
                Animation->>MeleeScanNotifyState: end
            deactivate Animation
            deactivate MeleeScanNotifyState
            AttackAbility->>MeleeScanTask: initialize
            activate MeleeScanTask
                MeleeScanTask-->>AttackAbility: instance
            deactivate MeleeScanTask
            AttackAbility->>MeleeScanTask: activate
            activate MeleeScanTask
                MeleeScanTask->>MeleeScanInstance: scan
                activate MeleeScanInstance
                    MeleeScanInstance->>MeleeScan: scan
                    MeleeScanInstance-->>MeleeScanTask: targets
                deactivate MeleeScanInstance
            MeleeScanTask-->>AttackAbility: targets
            deactivate MeleeScanTask
            loop each Target
                AttackAbility->>Target: apply GE
            end
    deactivate AttackAbility
</code-block>

## Attack Ability

A Melee Combat starts with the **Attack Ability**. This Ability defines important elements for a **Melee Attack**. 

<img src="cbt_melee_ability.png" alt="Melee Ability" border-effect="line" thumbnail="true"/>

First, the **Animation Provider** determines which animation should be played during the Attack. The default animation
provider uses a single Animation Montage and a Section Name, but you could create other Animation Providers that will
pick certain animations using any **criteria**, such as the type of Weapon currently in use.

The next section, **Motion Warping**, allows you to define a way to collect targets, via the **Targeting Preset** to 
warp the animation. **Motion Warping** is a technique where the animation's **Root Motion** is scaled enough to travel a 
specific distance and/or to rotate to a certain target. You can also apply a **Warp Offset** that will reduce the 
distance to travel between the attacker and the target.

## Melee Scan

Once the selected Animation starts, it will listen for certain **Gameplay Events**. The ones relevant to Melee Attacks
are:

| Gameplay Event                 | Description                                                                                                                 |
|--------------------------------|-----------------------------------------------------------------------------------------------------------------------------|
| `Combat.Event.MeleeScan.Start` | Starts the Melee Scan Task. The Melee Scan instance must be present in the **Payload**, as one of its **Optional Objects**. |
| `Combat.Event.MeleeScan.Stop`  | Stops the Melee Scan Task.                                                                                                  |

These Gameplay Events can be triggered by any object in the system, the only requirement is having a valid **Melee Scan
Transfer Object** in the payload.

The most common way to trigger these events is via the **Melee Scan Notify State**, which can be added to the **Animation
Montage** played by the Attack Ability.

### Melee Scan Notify State



### Melee Scan Transfer Object

## Melee Weapon Interface

### Melee Hit Cosmetics

In the Damage Handling flow, you can have a **Damage Handler** to invoke **Combat Interfaces** on the **Damage Causer**,
which may likely be a **Weapon**. This triggers the `HandleMeleeDamageCosmetics` function, meant to play cosmetics like
**Sounds** and **Particles**.

The Default Weapon Actor will provide a preliminary structure to handle these assets, allowing you to set them in the
weapon's **Details Tab**. They are stored as **soft references** load on-demand.

> **Niagara Parameters**
>
> If you need to set parameters to the Niagara Component, override the `ModifyMeleeHitComponent` function. By default,
> this function will set: **Target**, **Hit Location** and **Hit Normal**.
{style="note"}