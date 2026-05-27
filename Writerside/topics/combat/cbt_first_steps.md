# First Steps with Ninja Combat
<primary-label ref="combat"/>

This page guides you through the first steps for **Ninja Combat**. Make sure to check the [**Combat Setup**](cbt_setup.md)
instructions before continuing. This page assumes that [**Ninja G.A.S.**](gas_overview.md) is also installed, but all 
concepts related to the Gameplay Ability System can easily transfer to other G.A.S. setups.

The following steps aim to provide **a player character class, fully configured as a combatant**. This includes optional
steps to ensure compatibility with the **melee** and **ranged** combat capabilities.

## Combatant Class
Before creating the combatant class, choose which Ninja GAS character base class you want to use. This [page from Ninja G.A.S. documentation](gas_base_classes.md) 
provides details to help you choose your base hierarchy. 

For this example, we'll use the `ANinjaGASCharacter` class. This means our Ability System Component will live in the 
character, and this combatant class is **compatible with both Players and AI**.

<procedure title="Create a Combatant Character" collapsible="true" default-state="expanded">
    <step>Create a new <b>Character</b> using <code>NinjaGASCharacter</code> as the <b>base class</b>.</step>
    <step>Add the <b>Combat Manager component</b>, <code>NinjaCombatManagerComponent</code>.</step>
    <step>Add the <b>Combat System interface</b>, <code>CombatSystemInterface</code>.</step>
    <step>Implement/override the interface function, <code>GetCombatManager</code>, so it returns the <b>Combat Manager component</b>.</step>
    <step>Implement/override the interface function, <code>GetCombatMesh</code>, so it returns the relevant <b>mesh</b>. See note below for modular, multi-mesh characters.</step>
    <step>Implement/override the interface function, <code>GetCombatAnimInstance</code>, so it returns the relevant <b>animation instance</b>. See note below for characters retargeted during runtime.</step>
    <step>Set the relevant mesh's <b>Collision Preset</b> to <code>Combat</code>. See note below for hit detection collision.</step>
</procedure>

> **Modular Characters**
>
> It's common to have characters with multiple meshes, using **Leader Pose Components** or **Mutable**.
> Either way, the combat system only needs to know about the **primary mesh**, which is used for **collisions**
> and **attachments** (when not using the Ninja Inventory).
{style="tip"}

> **Runtime Retargeting**
>
> In some scenarios, such as the GASP sample, the **primary mesh** is hidden, running the animation and a
> **visible mesh** actually represents the character, using a runtime retargeter to transfer animations.
>
> In this scenario, the **visible mesh** is the one relevant to the Combat System, but the animation instance
> should be obtained from the **primary mesh** instead.
{style="tip"}

> **Hit Detection Collision**
>
> Instead of setting the relevant mesh's Collision Preset, for more precise hit detection, you can use **dedicated
> collision components** instead of the full mesh.
{style="tip"}

### Forward Reference
<secondary-label ref="optional"/>
<secondary-label ref="recommended"/>

Certain features, such as the **Evade Ability**, need a global forward reference: a Scene Component that always points 
forward, usually an Arrow Component with **Absolute Rotation** enabled.

> **Automatic Creation**
>
> The Combat Manager component will **automatically create a Forward Reference**, if no reference is found, but one is 
> required. You can also modify the default creation logic, by overriding the <code>CreateForwardReference</code> function.
> 
> When using [**Ninja Input](ipt_overview.md) it is recommended to create your own component that adheres to the 
> requirements from both systems. 
{style="tip"}

<procedure title="Add a Forward Reference component" collapsible="true" default-state="expanded">
    <step>In the <b>Character Class</b>, create a new <b>Arrow Component</b>, parented to the <b>Root Component</b>, the character's <b>Capsule Component</b>.</step>
    <step>Add the <code>Combat.Component.ForwardReference</code> tag to the list of <b>Component Tags</b>.</step>
    <step>Set the <b>Transform</b> to use <b>Absolute Rotation</b>, so it always points forward.</step>
    <step>Implement/override the Combat System interface function, <code>GetCombatForwardReference</code>, so it returns the <b>Arrow Component</b>.</step>
</procedure>

### Melee Combat
<secondary-label ref="optional"/>

Combatants may perform melee attacks directly, without a weapon. To support that, the character must implement the **Melee Interface**.
When added to a combatant, the Melee System offers two implementations listed below. You can use one or both.

1. **Traces and Sweeps**: Collects targets by performing line traces or sweeps, during specific animation frames. This is also used by melee weapons.
2. **Component Overlaps**: Collects targets overlapping a component, during specific animation frames. Useful for simpler collision scenarios.

<procedure title="Enable Scans for Melee Combat" collapsible="true" default-state="expanded">
    <step>If not done yet, add the <b>Melee interface</b>, <code>CombatMeleeInterface</code>.</step>
    <step>Implement/override the interface function, <code>GetMeleeMesh</code>, so it returns the <b>relevant Mesh</b>. See notes above regarding modular characters.</step>
    <step>Optionally, implement/override the interface function, <code>GetMeleeMeshByTag</code>, so it returns the <b>relevant Mesh</b> for a given <b>Gameplay Tag</b>.</step>
</procedure>

<procedure title="Enable Overlaps for Melee Combat" collapsible="true" default-state="expanded">
    <step>If not done yet, add the <b>Melee interface</b>, <code>CombatMeleeInterface</code>.</step>
    <step>Create a <b>Shape Component</b> (e.g. a Sphere Component) and set its <b>Collision Preset</b> to <code>Combat</code>.</step>
    <step>Implement/override the interface function, <code>GetMeleeOverlap</code>, so it returns the <b>shape component</b> that collects overlapping melee targets.</step>
    <step>Optionally, implement/override the interface function, <code>GetMeleeOverlapByTag</code>, so it returns the <b>shape component</b> for a given <b>Gameplay Tag</b>.</step>
</procedure>

### Ranged Combat
<secondary-label ref="optional"/>

Combatants may perform ranged attacks directly, without a weapon. To support that, the character must implement the **Ranged Interface**.

<procedure title="Configure the Projectile Source" collapsible="true" default-state="expanded">
    <step>Add the <b>Ranged interface</b>, <code>CombatRangedInterface</code>.</step>
    <step>Implement/override the interface function, <code>GetProjectileSourceMesh</code>, so it returns the <b>relevant Mesh</b>. See notes above regarding modular characters.</step>
</procedure>

### Additional Components
<secondary-label ref="optional"/>

Ninja Combat provides many components that can enhance the combatant's capabilities. They are **optional**, but at this
point, feel free to add the ones you might find relevant. These components should also be returned by the **Combat System
interface**.

| Component                               | Purpose                                                                                                                                                             | Interface Function              |
|-----------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------|
| `NinjaCombatComboManagerComponent`      | Allows the combatant to perform **combos**                                                                                                                          | `GetComboManagerComponent`      |
| `NinjaCombatMotionWarpingComponent`     | Manages warping targets. **Overrides other Motion Warping Components**.                                                                                             | `GetMotionWarpingComponent`     |
| `NinjaCombatPhysicalAnimationComponent` | Manages physical animations.                                                                                                                                        | `GetPhysicalAnimationComponent` |
| `NinjaCombatWeaponManagerComponent`     | Provides combat weapons. When using the Inventory System, should be replaced by the **Equipment Adapter**. See the Combat/Inventory integration page for more info. | `GetWeaponManager`              |

## Gameplay Ability System
We won't create Gameplay Abilities just yet, but each combatant should have their **Combat Attributes** and optionally 
some **Gameplay Effects** to replenish certain attributes.

### Combat Attributes
Ninja Combat provides its own **Attribute Set**, which should be added to each combatant.

<procedure title="Add Combat Attributes using Ninja G.A.S." collapsible="true" default-state="expanded">
    <step>Create a new <b>Data Table</b> for your Combat Attributes, using <code>AttributeMetaData</code> as the table row structure.</step>
    <step>Download the <b><a href="cbt_attributes.md#initialization-data">Sample Initialization Data</a></b> and use it as the table data.</step>
    <step>
        <p>Create a new <b>G.A.S. Setup Data Asset</b> and add a new <b>Default Attribute Set</b> entry.</p> 
        <p>You can do so by right-clicking an empty area in the <b>Content Browser</b>, then navigating to <b>Ninja Bear Studio</b> &rarr; <b>Ninja G.A.S.</b> &rarr; <b>G.A.S. Setup</b>.</p>
    </step>
    <step>Add the <b>Ninja Combat Attribute Set</b>, <code>NinjaCombatAttributeSet</code>, and the data table as the <b>Attribute Table</b>.</step>
    <step>Set the new GAS Setup Data to the character's <b>Ability System Component</b>.</step>
</procedure>

### Regeneration Effects
<secondary-label ref="optional"/>

You may want to use **Regeneration Effects** for attributes like Stamina, Mana or even Health. The Combat System provides
these effects, which operate based on the combatant's attributes.

<procedure title="Add Regeneration Effects" collapsible="true" default-state="expanded">
    <step>Create a <b>Blueprint</b>, based on <code>CombatEffect_ReplenishMana</code> and name it <code>GE_Regeneration_Mana</code>.</step>
    <step>Create a <b>Blueprint</b>, based on <code>CombatEffect_ReplenishStamina</code> and name it <code>GE_Regeneration_Stamina</code>.</step>
    <step>Open the GAS Setup Data created in the previous section.</step>
    <step>Add both Gameplay Effects to the list of <b>Gameplay Effects</b> in the data asset.</step>
</procedure>

## Next Steps
At this point, you have a complete base **Combatant Class** that can be used as a foundation for **Players** and **AI**.
This character has the following features:

1. The **core combat system configuration**.
2. A **forward reference** used by certain abilities.
3. Optionally, the character can perform **melee attacks**.
4. Optionally, the character can perform **ranged attacks**.
5. Optionally, the character includes **additional components**, such as the Combo Manager.
6. The character has the **Combat Attributes** added and properly initialized.
7. Optionally, the character **regenerates certain attributes**, such as Stamina and Mana.

From here, you can:

- Learn more about [**combat components**](cbt_concepts_components.md) and other important parts of the system.
- Create [**combat abilities**](cbt_abilities.md) to be used by the character directly, including [**Combos**](cbt_concepts_combos.md). 
- Configure [**weapon management**](cbt_weapon_management.md).