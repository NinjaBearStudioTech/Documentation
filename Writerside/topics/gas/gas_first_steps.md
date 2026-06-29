# First Steps with Ninja G.A.S.
<primary-label ref="gas"/>

This page guides you through the first steps for **Ninja G.A.S.** Make sure to check the [**G.A.S. Setup**](gas_setup.md)
instructions before continuing.

The following steps aim to provide **a character that has access to an Ability System Component**. We will cover both
common ownership models: one where the Ability System Component is owned by the **Character**, and another where it is
owned by the **Player State**.

## G.A.S. Setup Data

The **G.A.S. Setup Data Asset** defines the initial Attribute Sets, Gameplay Effects, and Gameplay Abilities granted to
an actor during Ability System initialization.

<procedure title="Create a G.A.S. Setup Data Asset" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new <b>G.A.S. Setup Data Asset</b>.</p>
        <p>You can do so by right-clicking an empty area in the <b>Content Browser</b>, then navigating to <b>Ninja Bear Studio</b> &rarr; <b>Ninja G.A.S.</b> &rarr; <b>G.A.S. Setup</b>.</p>
    </step>
    <step>Add any <b>Attribute Sets</b> required by your project. For example, you can use the one provided by <a href="cbt_concept_attributes.md"><b>Ninja Combat</b></a>.</step>
    <step>Add any startup <b>Gameplay Effects</b> required by your project.</step>
    <step>Add any startup <b>Gameplay Abilities</b> required by your project.</step>
</procedure>

> **Attribute Sets**
>
> Ninja G.A.S. does not provide Attribute Sets by itself. You can create your own Attribute Sets or use Attribute Sets
> provided by other plugins, such as **Ninja Combat** or **Ninja Inventory**.
{style="tip"}

## Character Base Class

Ninja G.A.S. provides [**base character classes**](gas_base_classes.md) for common Gameplay Ability System setups. The 
main decision is where the **Ability System Component** should live.

| Base Class                | ASC Owner    | Common Use                                                                      |
|---------------------------|--------------|---------------------------------------------------------------------------------|
| `NinjaGASCharacter`       | Character    | AI characters, NPCs, single-player characters, or simpler player setups.        |
| `NinjaGASPlayerCharacter` | Player State | Multiplayer player characters where the ASC should persist beyond pawn changes. |

### Character-Owned ASC

Use this setup when the Ability System Component should live directly in the **character**.

<procedure title="Create a Character-Owned ASC Setup" collapsible="true" default-state="expanded">
    <step>Create a new <b>Character</b> using <code>NinjaGASCharacter</code> as the <b>base class</b>.</step>
    <step>Use this class for AI agents, NPCs, or player characters where the ASC does not need to persist across pawn changes.</step>
    <step>Configure the character's <b>Ability System Component</b> using the <b>G.A.S. Setup Data Asset</b>.</step>
</procedure>

### Player State-Owned ASC

Use this setup when the Ability System Component should live in the **Player State**.

<procedure title="Create a Player State-Owned ASC Setup" collapsible="true" default-state="expanded">
    <step>Create a new <b>Player State</b> using the Ninja G.A.S. Player State base class, <code>NinjaGASPlayerState</code>.</step>
    <step>Create a new <b>Character</b> using <code>NinjaGASPlayerCharacter</code> as the <b>base class</b>.</step>
    <step>Set your <b>Game Mode</b> to use the new Player State class.</step>
    <step>Use this setup for projects where the ASC should persist across pawn changes.</step>
    <step>Configure the Player State's <b>Ability System Component</b> using the <b>G.A.S. Setup Data Asset</b>.</step>
</procedure>

## Next Steps

At this point, you have a character that can access an **Ability System Component** and initialize it through a
**G.A.S. Setup Data Asset**.

From here, you can:

- Learn more about [**Lazy Loading**](gas_lazy_loading.md) for the Ability System Component.
- Learn more about [**Batch Activation**](gas_batch_activation.md) in the Ability System Component.
- Learn how to [**adopt Ability Bundles from possessed pawns**](gas_data_asset.md), allowing one Player State to work with different pawns.
