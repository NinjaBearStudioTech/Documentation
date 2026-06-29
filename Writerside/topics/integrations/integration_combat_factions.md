# Combat and Factions
<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="factions-sec"/>

Integrating [**Ninja Combat**](cbt_overview.md) and [**Ninja Factions**](fct_overview.md) allows you to control **friendly
fire** based on the **Faction** and **Alignment** between the Attacker and Target.

This integration is automatically enabled when both plugins are available and active in the project, regardless of whether
they are installed locally or in the engine.

## Modifying Damage

Ninja Combat provides an interface that establishes the contract for damage modification: `CombatDamageModifierInterface`.
It allows damage to be modified or fully cancelled. For more information about damage modification and cancellation,
check the [**Damage and Mitigation**](cbt_concept_damage_and_mitigation.md) page.

This interface is added to the **mitigation pipeline** via the **Modifier Interface** mitigation object. When added to
the pipeline, it evaluates the **Game Mode** and **Game State** for valid implementations of the interface.

The integration with Ninja Factions uses this mechanism by introducing a dedicated component that can check the **Team
Attitude**, as provided by **Ninja Factions**, between the attacker and victim. This component can cancel or modify
damage applied to **friendly actors**.

<procedure title="Configuring the Damage Evaluator" collapsible="true" default-state="expanded">
    <step>Add the <code>CombatDamageModifierInterface</code> to your Game Mode or Game State.</step>
    <step>Add <code>NinjaCombatFactionDamageEvaluator</code> to the same object.</step>
    <step>Route the interface's <code>ShouldCancelDamage</code> function to the component's implementation.</step>
    <step>Route the interface's <code>ModifyDamage</code> function to the component's implementation.</step>
    <step>Make sure that your Combat Mitigation Pipeline asset includes the <b>Modifier Interface</b> mitigation object.</step>
</procedure>

The component offers two settings:

| Property                   | Description                                                                                    |
|----------------------------|------------------------------------------------------------------------------------------------|
| `CancelFriendlyDamage`     | Determines whether friendly damage is fully cancelled. If enabled, the damage is discarded.    |
| `FriendlyDamageMitigation` | If damage is not cancelled, determines how much base damage is mitigated for friendly targets. |

> **Default Game Mode**
>
> Consider using the `NinjaCombatGameMode` class as the base for your Game Mode, if you do not have a hierarchy of your
> own. This class already provides the integration for you.
