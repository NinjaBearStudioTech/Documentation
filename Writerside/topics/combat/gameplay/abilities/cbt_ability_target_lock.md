# Target Lock Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Selects a target using the <b>Gameplay Targeting System</b>.</li>        
        <li>Tracks the selected target's <b>Death Delegate</b> so it can deselect the target automatically.</li>
        <li>Can optionally select a <b>new target</b>, after the current one is destroyed.</li>
    </ul>
</tldr>

The **Target Lock Ability** is part of the Target Lock System. It is responsible for collecting
targets, using the **Gameplay Targeting System** and registering them in the **Target Manager**.

Since a target lock can happen at any time, whenever a key is pressed or an event is received, this ability should be
granted to characters by default.

## Targeting Presents

The Target Lock Ability supports two **Targeting Presets**:

- **Targeting Preset**: Main targeting preset used when the ability activates.
- **Next Targeting Preset**: An optional present used, when **Move to Next Targets** is enabled. If set to null, the main preset is used.

## Distance Tracking

You can optionally track the distance between the **avatar** and the **current target**. When tracked, a threshold is
established and if the distance is bigger than that value, the target will be unlocked.

## Event Activation

Normally, a player would activate the Target Lock Ability by pressing a certain key or button. In these cases you can 
activate the ability normally, via its **Gameplay Tags** or **Ability Class**.

But there might be some situations where the Target Lock Ability should be activated as a consequence of another gameplay 
circumstance or event. For example:

- **Automated targeting**, where an incoming attacker is automatically targeted.
- **AI integration**, where the perception system automatically locks on the perceived actor.

For those scenarios, the Target Lock Ability can be activated via a **Gameplay Event**. To that end, this ability will 
always listen to Gameplay Events represented by these gameplay tags:

| Gameplay Tag                    | Description                                              |
|---------------------------------|----------------------------------------------------------|
| `Combat.Event.Target.Acquired`  | Requests the ability to lock on a target in the payload. |
| `Combat.Event.Target.Dismissed` | Requests the ability to unlock from the current target.  |

> **Ninja Perception Integration**
>
> Ninja Perception can automatically send the Gameplay Event to lock and unlock targets obtained via the **Perception System**,
> by utilizing the correct Gameplay Tags.

### Target Acquired Gameplay Event

To lock on a pre-determined, you can send the appropriate Gameplay Event, providing the actor in the **payload**.

<tabs group="sample">
    <tab title="Blueprint">
        <img src="cbt_target_acquired_event.png" alt="Target Acquired Gameplay Event" border-effect="line"/>
    </tab>
    <tab title="C++">
        <code-block lang="c++" src="cbt_target_acquired_payload.cpp"/>
    </tab>
</tabs>

### Target Dismissed Gameplay Event

To dismiss the current target, you can send the appropriate Gameplay Event, without any additional actors. 

<tabs group="sample">
    <tab title="Blueprint">
        <img src="cbt_target_dismissed_event.png" alt="Target Dismissed Gameplay Event" border-effect="line"/>
    </tab>
    <tab title="C++">
        <code-block lang="c++" src="cbt_target_dismissed_payload.cpp"/>
    </tab>
</tabs>

