# Target Lock Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Selects a target using the <b>Gameplay Targeting System</b>.</li>        
        <li>Tracks the selected target's <b>Death Delegate</b> so it can deselect the target automatically.</li>
        <li>Can optionally select a <b>new target</b>, after the current one is destroyed.</li>
    </ul>
</tldr>

The **Target Lock Ability** is part of the [Target Lock System](cbt_target_locking.md). It is responsible for collecting
targets, using the **Gameplay Targeting System** and registering them in the **Target Manager**.

## Targeting Presents

The Target Lock Ability supports two **Targeting Presets**:

- **Targeting Preset**: Main targeting preset used when the ability activates.
- **Next Targeting Preset**: An optional present used, when **Move to Next Targets** is enabled. If set to null, the main preset is used.

## Distance Tracking

You can optionally track the distance between the **avatar** and the **current target**. When tracked, a threshold is
established and if the distance is bigger than that value, the target will be unlocked.