# Collision Settings

Unreal Engine uses **collision channels** and **collision presets** to determine how objects detect, block, overlap, or 
ignore each other.

Some Ninja Bear Studio plugins require custom collision settings so they can perform gameplay queries consistently. These 
queries are used for features such as **line-of-sight checks**, **melee and projectile traces**, and other gameplay-specific 
detection.

This page lists the shared collision setup used by Ninja Bear Studio plugins. **Configure only the channels and presets 
required by the plugins enabled in your project**.

**Collision settings** are configured in **Edit** &rarr; **Project Settings** &rarr; **Engine** &rarr; **Collision**.

## Object Channels
**Object Channels** represent the **type of object** being queried. These are commonly assigned through Collision Presets.

<procedure title="Adding Object Channels" collapsible="true" default-state="expanded">
    <step>Open <b>Edit</b> &rarr; <b>Project Settings</b>.</step>
    <step>Navigate to <b>Engine</b> &rarr; <b>Collision</b>.</step>
    <step>In <b>Object Channels</b>, add the object channels required by the plugins you are using.</step>
    <step>Set each channel's <b>Default Response</b> according to the tables below.</step>
    <step>Save the project settings and restart the editor if requested.</step>
</procedure>

| Plugin            | Channel             | Default Response | Purpose                                                                                                               |
|-------------------|---------------------|------------------|-----------------------------------------------------------------------------------------------------------------------|
| Combat            | `CombatObject`      | Ignore           | Represents objects that can be detected by combat traces, weapons, projectiles, aiming checks, or opportunity checks. |
| Interaction       | `InteractionObject` | Ignore           | Represents objects used by interaction sources and targets.                                                           |
| Combat, Inventory | `FloorObject`       | Ignore           | Optional object type for floor actors used by floor-specific traces or top-down targeting.                            |

## Trace Channels
**Trace Channels** represent specific **query types** used by gameplay systems.

<procedure title="Adding Trace Channels" collapsible="true" default-state="expanded">
    <step>Open <b>Edit</b> &rarr; <b>Project Settings</b>.</step>
    <step>Navigate to <b>Engine</b> &rarr; <b>Collision</b>.</step>
    <step>In <b>Trace Channels</b>, add the trace channels required by the plugins you are using.</step>
    <step>Set each channel's <b>Default Response</b> according to the tables below.</step>
    <step>Save the project settings and restart the editor if requested.</step>
</procedure>

| Plugin            | Channel            | Default Response | Purpose                                                                                                     |
|-------------------|--------------------|------------------|-------------------------------------------------------------------------------------------------------------|
| Interaction       | `InteractionSight` | Ignore           | Used to validate line of sight between an interaction source and an interaction target. **See note below!** |
| Combat            | `Projectile`       | Block            | Used by projectile traces, hit-scan traces, and projectile-style collision checks.                          |
| Combat            | `Opportunity`      | Ignore           | Used by opportunity checks, such as opportunity attacks or combat line-of-sight validation.                 |
| Combat            | `Evade`            | Block            | Used for evade checks or movement-space validation.                                                         |
| Combat            | `Aim`              | Ignore           | Used for aiming traces or target validation.                                                                |
| Combat, Inventory | `Floor`            | Ignore           | Used for floor traces, mouse targeting, or ground detection.                                                |

### Line of Sight for Interactions
Interaction line-of-sight checks use the `InteractionSight` channel to detect blocking geometry between the scanner and 
the interaction target.

For common blocking geometry, make sure relevant presets block `InteractionSight`. This usually includes presets such as:

- `BlockAll`
- `BlockAllDynamic`
- Any project-specific wall, prop, door, obstacle, or blocking-volume preset

<tip>
    <p><b>Blocking Objects vs. Tracing Interaction Targets</b></p>
    <p>In Ninja Interaction, <b>line-of-sight</b> traces are meant to detect <b>blocking geometry</b>, not confirm a hit on the interaction target.</p>
    <p>Interaction should <b>succeed</b> when nothing physically blocks the line of sight. It should <b>fail</b> because something blocks it, not because the interaction target failed to respond to the trace.</p>
</tip>

## Adding Collision Presets
Collision Presets make it easier to apply the correct channel responses to actors and components without configuring 
each one manually.

<procedure title="Adding Collision Presets" collapsible="true" default-state="expanded">
    <step>Open <b>Edit</b> &rarr; <b>Project Settings</b>.</step>
    <step>Navigate to <b>Engine</b> &rarr; <b>Collision</b>.</step>
    <step>In <b>Preset</b>, add each preset required by the plugins you are using.</step>
    <step>Set <b>Collision Enabled</b>, <b>Object Type</b>, and <b>Collision Responses</b> according to the tables below.</step>
    <step>Save the project settings and restart the editor if requested.</step>
</procedure>

## Collision Presets
The following presets provide reusable collision configurations for common Ninja Bear Studio gameplay components. Add only 
the presets required by the plugins enabled in your project, then assign them to the relevant actors or components.

| Plugin            | Preset              | Collision Enabled | Object Type         | Purpose                                                                      |
|-------------------|---------------------|-------------------|---------------------|------------------------------------------------------------------------------|
| Interaction       | `InteractionSource` | Query Only        | `InteractionObject` | Used by scanner components that detect interaction targets.                  |
| Interaction       | `InteractionTarget` | Query Only        | `InteractionObject` | Used by interactable actors that can be detected by interaction scans.       |
| Combat            | `Combat`            | Query Only        | `CombatObject`      | Used by actors or components that should be detected by combat traces.       |
| Combat, Inventory | `Floor`             | Query and Physics | `WorldStatic`       | Used by floor actors that should support floor traces or top-down targeting. |

## Preset Details
Use the following entries as a reference for each **Preset** being added to your project.

### InteractionSource
<secondary-label ref="interaction-sec"/>
Use this preset for scanning components attached to actors that can look for interactable targets.

| Setting             | Value               |
|---------------------|---------------------|
| Collision Enabled   | Query Only          |
| Object Type         | `InteractionObject` |
| `InteractionObject` | Overlap             |
| All other channels  | Ignore              |

### InteractionTarget
<secondary-label ref="interaction-sec"/>
Use this preset for actors or components that should be detected by interaction scans.

| Setting             | Value               |
|---------------------|---------------------|
| Collision Enabled   | Query Only          |
| Object Type         | `InteractionObject` |
| `InteractionObject` | Block               |
| All other channels  | Ignore              |

### Floor
<secondary-label ref="combat-sec"/>
<secondary-label ref="inventory-sec"/>
Use this preset for floor actors that should participate in floor-specific queries, such as the placement of <b>Cast Actors</b> (combat)
or <b>Dropped Items</b> (inventory).

| Setting           | Value             |
|-------------------|-------------------|
| Collision Enabled | Query and Physics |
| Object Type       | `WorldStatic`     |
| `Floor`           | Block             |
| `FloorObject`     | Block             |
| `Projectile`      | Ignore            |
| `Evade`           | Ignore            |
| Other channels    | Project-specific  |

### Combat
<secondary-label ref="combat-sec"/>
Use this preset for components that should be detected by combat-related traces. Combat Objects are usually the <b>mesh</b>
that represents the pawn or character, or dedicated <b>collision components</b> added along the skeleton.

| Setting            | Value            |
|--------------------|------------------|
| Collision Enabled  | Query Only       |
| Object Type        | `CombatObject`   |
| `CombatObject`     | Block            |
| `Opportunity`      | Block            |
| `Aim`              | Block            |
| `Pawn`             | Ignore           |
| `Camera`           | Ignore           |
| `Vehicle`          | Ignore           |
| `InteractionSight` | Ignore           |
| Other channels     | Project-specific |

## Collision Parity
As you introduce new traces and channels, you might need to review other **predefined channels** to ensure their parity
with the new instructions.

| Profile           | Changes                                                |
|-------------------|--------------------------------------------------------|
| `Trigger`         | Should **ignore** `Projectile` and `InteractionSight`. |
| `NoCollision`     | Should **ignore** `Projectile` and `InteractionSight`. |
| `BlockAll`        | Should **block** `InteractionSight`.                   |
| `BlockAllDynamic` | Should **block** `InteractionSight`.                   |