# Factions Integration
<primary-label ref="bot"/>
<secondary-label ref="advanced"/>

[**Ninja Factions**](fct_overview.md) is a plugin that allows designers to **define factions** for pawns and determine how 
those factions relate to each other. Attitudes can be expressed using either a **direct faction matrix** or **reputation-based 
relationships**, depending on project needs.

Ninja Bot integrates with Ninja Factions by delegating team membership and attitude resolution to that system, allowing 
a **single, authoritative source of truth** for team logic.

## Team Provider Integration

Ninja Bot includes a **Team Provider implementation** that is compatible with Ninja Factions. When a pawn is sensed by 
the perception system:

1. The pawn's faction and alignment are resolved via **Ninja Factions**
2. The **resulting attitude** (friendly, hostile, neutral) is used by Ninja Bot
3. Perception, awareness, and targeting **decisions rely on this resolved attitude**

This ensures that AI perception logic remains consistent with faction rules defined elsewhere in the project.

## Automatic Detection

If the Ninja Factions module is present in the project, Ninja Bot **automatically enables the corresponding Team Provider**.

You can then select the Ninja Factions Team Provider from the **Ninja Bot Settings page**. Once selected, all team and 
attitude queries performed by Ninja Bot will be routed through Ninja Factions.

<img src="bot_advanced_integration_factions.png" alt="Ninja Factions Integration" width="800" border-effect="line"/>
