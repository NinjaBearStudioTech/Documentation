# Gameplay Attributes
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Add the <code>NinjaCombatAttributeSet</code> to your Ability System Component.</li>
        <li>Initialize the Attribute Set with a <b>Data Table</b> that uses <code>AttributeMetaData</code> as the <b>row type</b>.</li>
        <li>The Combat Attribute Set has many attributes, both regular and meta attributes.</li> 
        <li>Use the <b>initialization sample</b> below to avoid missing attributes.</li>
    </ul>
</tldr>

The Combat Framework includes its own Attribute Set, containing multiple relevant categories such as **Vitals**,
**Damage** and **Defense**.

The Attribute Set is represented by the `NinjaCombatAttributeSet` class, make sure to add it to the Ability System
Component assigned to your Character or Player State.

## Available Attributes

The following table contains all attributes available in the Combat System's Attribute Set.

| Attribute                | Description                                              | Category          |
|--------------------------|----------------------------------------------------------|-------------------|
| `PendingDamage`          | Damage that must be applied to the owner.                | Meta Attributes   |
| `PendingMitigationCost`  | Mitigation cost that must be subtracted from the owner.  | Meta Attributes   |
| `MaxHealthTotal`         | Total health available, including base/add/percent.      | Meta Attributes   |
| `MaxStaminaTotal`        | Total stamina available, including base/add/percent.     | Meta Attributes   |
| `MaxMagicTotal`          | Total magic available, including base/add/percent.       | Meta Attributes   |
| `Health`                 | Current amount of health available.                      | Health            |
| `MaxHealth`              | Base maximum health available.                           | Health            |
| `MaxHealthAdd`           | Health added to the maximum.                             | Health            |
| `MaxHealthPercent`       | Percent multiplier to health in {0, 1} range.            | Health            |
| `HealthRegenRate`        | Health regeneration rate.                                | Health            |
| `Stamina`                | Current amount of stamina available.                     | Stamina           |
| `MaxStamina`             | Base maximum amount of stamina available.                | Stamina           |
| `MaxStaminaAdd`          | Stamina added to the maximum.                            | Stamina           |
| `MaxStaminaPercent`      | Percent multiplier to stamina in {0, 1} range.           | Stamina           |
| `StaminaCost`            | Base cost for stamina that can be used by abilities.     | Stamina           |
| `StaminaRegenRate`       | Stamina regeneration rate.                               | Stamina           |
| `Magic`                  | Current amount of magic available.                       | Magic             |
| `MaxMagic`               | Base maximum amount of magic available.                  | Magic             |
| `MaxMagicAdd`            | Magic added to the maximum.                              | Magic             |
| `MagicCost`              | Base cost for magic that can be used by abilities.       | Magic             |
| `MaxMagicPercent`        | Percent multiplier to magic in {0, 1} range.             | Magic             |
| `MagicRegenRate`         | Magic regeneration rate.                                 | Magic             |
| `BaseDamage`             | Base damage applied by the character.                    | Damage            |
| `CriticalHitChance`      | Critical Hit Chance for applied damage.                  | Damage            |
| `CriticalHitMultiplier`  | Critical Hit Multiplier for applied damage.              | Damage            |
| `BlockChance`            | Chance to block an incoming attack in {0, 1} range.      | Block             |
| `BlockMitigation`        | Amount of damage mitigated by blocking, in {0, 1} range. | Block             |
| `BlockAngle`             | Maximum angle where block is effective.                  | Block             |
| `BlockLimit`             | Flat limit of damage that can be mitigated.              | Block             |
| `BlockStaminaCostRate`   | The cost in stamina, to block each point of damage.      | Block             |
| `BlockCooldown`          | Block cooldown, usually as penalty from a breaker hit.   | Block             |
| `EvadeStaminaCost`       | Stamina cost to perform an evade.                        | Evade             |
| `EvadeCooldown`          | Cooldown applied before a new evade can be performed.    | Evade             |
| `DefenseChance`          | Chance to defend an incoming attack in {0, 1} range.     | Defense           |
| `DefenseMitigation`      | Amount of damage passively mitigated, in {0, 1} range.   | Defense           |
| `DefenseStaminaCostRate` | The cost in stamina, to defend each point of damage.     | Defense           |
| `ArmorReduction`         | Flat damage reduction for incoming damage.               | Armor             |
| `LastStandCount`         | Chances for the character to revert fatal damage.        | Last Stand        |
| `LastStandHealthPercent` | Amount health granted when fatal damage is reverted.     | Last Stand        |
| `Poise`                  | Current poise. At zero, triggers a stagger.              | Poise and Stagger |
| `MaxPoise`               | Maximum poise for a character.                           | Poise and Stagger |
| `StaggerDuration`        | Duration of the Stagger effect.                          | Poise and Stagger |

> You can always track your character's Attributes and their current values using the Gameplay Ability System debugger.

## Initialization Data

You can use this Json to facilitate the creation the Data Table used to initialize the Combat Attributes.

The Data Table Row type used to create the Attribute Set Data for initialization, `AttributeMetaData`, is provided by
the **Gameplay Ability System**. Once your Data Table is created, you can import the following Json to have an initial,
complete, set of attribute values.

<code-block lang="json" src="cbt_attributes.json" collapsible="true" collapsed-title="Combat Attributes"/>
