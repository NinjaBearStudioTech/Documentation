# Melee Combat
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The Weapon (or Character) must implement the <b>Melee Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Melee Attacks</b>.</li>
        <li><b>Melee Scans</b> are executed by the Attack Ability. They are started and stopped from <b>Gameplay Events</b>.</li>
        <li>The <b>Damage</b> applied by a melee hit can be customized in many ways.</li>
    </ul>
</tldr>

## Attack Ability

## Melee Scan

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