# Attack Magnitudes
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

Combat Abilities responsible for applying primary Gameplay Effects, such as **damage**, provide ways to **customize
magnitudes** in their outgoing effects.

## Default Magnitudes
By default, **Attack Abilities** collect relevant data and automatically apply a pre-defined set of magnitude data tags.

| Data Tag                  | Description                                                                  |
|---------------------------|------------------------------------------------------------------------------|
| `Combat.Data.ComboCount`  | Current combo count, which can be used to scale damage across larger combos. |
| `Combat.Data.Damage`      | Base damage, retrieved from the Melee or Projectile interfaces.              |
| `Combat.Data.PoiseDamage` | Poise damage, retrieved from the Melee or Projectile interfaces.             |

**Cast Abilities** follow the same pattern, but only when the effect is applied directly by the ability—such as when 
using `TargetingSystem` or `WaitForConfirmation` targeting modes.

| Data Tag               | Description                             |
|------------------------|-----------------------------------------|
| `Combat.Data.CastHits` | Number of targets affected by the cast. |

## Custom Combat Magnitudes
If you need to introduce new magnitude values into your **Attack** or **Cast** abilities, you can override the
`GetAdditionalCombatMagnitudes` function.

This allows you to extend or modify the set of magnitudes applied to outgoing Gameplay Effects.

> **Override Default Data**
>
> Any magnitudes you set using `GetAdditionalCombatMagnitudes` will **override** the pre-defined values, if they use
> the same data tags.
{style="note"}

<procedure title="Setting Custom Magnitudes" collapsible="true" default-state="expanded">
    <step>Open your <b>Gameplay Ability</b> that extends an <b>Attack</b> or <b>Cast</b> ability.</step>
    <step>
        <p>Implement <code>GetAdditionalCombatMagnitudes</code> and return any magnitudes that should be added or modified in the outgoing effect.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="cbt_advanced_attack_magnitudes_add_data_tag.png" alt="Custom Magnitudes" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="c++" src="cbt_gameplay_effect_magnitudes.cpp" />
            </tab>
        </tabs>
    </step>
</procedure>
