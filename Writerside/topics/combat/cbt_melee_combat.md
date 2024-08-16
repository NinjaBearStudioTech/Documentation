# Melee Combat
<primary-label ref="combat"/>

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