# Combat Attributes
<primary-label ref="combat"/>

The Combat Framework includes its own Attribute Set, represented by the `NinjaCombatAttributeSet` class.

This Attribute Set provides dozens of combat-related attributes used by the framework, including **Vitals**,
**Damage**, **Defense**, **Block**, **Evade**, **Poise**, **Stagger**, and other combat systems.

Make sure to add this Attribute Set to the Ability System Component assigned to your Character or Player State. You can
use [**Ninja G.A.S.**](gas_overview.md) to register and initialize attribute sets.

## Attribute Design

Combat Attributes are not only raw values. Some of them are used by the framework as part of important combat
operations, such as applying damage, calculating mitigation, spending resources, and deriving final vital values.

### Pending Damage and Mitigation Costs

`PendingDamage` and `PendingMitigationCost` are meta attributes processed by the Attribute Set.

They represent temporary values that are received by the Attribute Set and then distributed to their actual
destinations.

For example, incoming `PendingDamage` is processed by the damage mitigation flow and eventually applied to `Health`.
Likewise, `PendingMitigationCost` is processed and applied to the appropriate resource used by the mitigation result.

### Vitals

The main vitals provided by Combat are **Health**, **Stamina** and **Mana**. Each vital has a set of support attributes 
used to calculate and manage its final value:

| Attribute Type    | Description                                                                               |
|-------------------|-------------------------------------------------------------------------------------------|
| Current Value     | The current amount available, such as `Health`, `Stamina`, or `Mana`.                     |
| Max Total         | Meta attribute containing the final maximum value after base, add, and percent modifiers. |
| Max Add           | Flat amount added to the maximum value.                                                   |
| Max Percent       | Multiplier applied to the maximum value.                                                  |
| Regeneration Rate | A value that is regenerated over a period of time.                                        |

For example, Health uses: `Health`, `MaxHealth`, `MaxHealthTotal`, `MaxHealthAdd`, `MaxHealthPercent`. The same pattern 
is used by Stamina and Mana.

### Damage

Combat provides damage attributes used by the framework when building and applying damage.

The main damage attributes include:

| Attribute               | Description                                     |
|-------------------------|-------------------------------------------------|
| `BaseDamage`            | Base damage applied by the character.           |
| `CriticalHitChance`     | Chance to apply a critical hit.                 |
| `CriticalHitMultiplier` | Multiplier used when a critical hit is applied. |
| `BaseDamageBonus`       | Dynamic bonus added to base damage.             |
| `BaseDamageReduction`   | Dynamic reduction applied to base damage.       |

These attributes can be used by abilities, effects, equipment, or other systems that need to affect outgoing damage.

### Mitigation Attributes

Mitigation attributes are used by the [**damage mitigation pipeline**](cbt_concept_damage_and_mitigation.md).

These include attributes related to systems such as **blocking**, **defense**, **armor**, and any other combat rules that
participate in reducing, redirecting, or reacting to incoming damage.

Attributes are only considered by the mitigation pipeline when they are deliberately exposed to it. To do that, an
Attribute Set must implement `CombatMitigationAttributeSetInterface` and return the relevant attributes from
`GetAttributesRelevantForDamageMitigation`.

> **Exposing Custom Attribute Sets**
>
> Any Attribute Set present in the owner's Ability System Component will be evaluated for the interface. All
> implementations can provide attributes to be exposed to the mitigation pipeline.

> **Gameplay Debugger**
>
> You can always track your character's attributes and their current values using the Gameplay Ability System debugger.

## Initialization Data

You can use this JSON to create and populate Data Table used to initialize the Combat Attributes.

The Data Table Row type used to create the Attribute Set Data for initialization, `AttributeMetaData`, is provided by
the **Gameplay Ability System**. Once your Data Table is created, you can import the following JSON to have an initial,
complete set of attribute values.

<code-block lang="json" src="cbt_attributes.json" collapsible="true" collapsed-title="Combat Attributes"/>