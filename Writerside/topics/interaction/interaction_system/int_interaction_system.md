# Interaction System
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li>Interactions start at the <b>Interaction Source</b>, which detects and evaluates viable <b>Interaction Targets</b>.</li>
        <li>Targets accept a source only when they expose a compatible interaction.</li>
        <li>Once the first target is registered, the source <b>scans</b> for the best candidate (e.g., by distance or camera aim) and applies <b>focus</b>; scanning stops when no targets are available.</li>
        <li>When the player interacts, a <b>Gameplay Ability</b> on the source executes the interaction using the target's <b>Smart Object</b> and its <b>Gameplay Behavior</b>.</li>
        <li>The source runs a <b>State Tree</b> (move/rotate, play animation, etc.), which then triggers the final behavior on the target and produces an outcome.</li>
    </ul>
</tldr>

The Interaction System coordinates how an **Interaction Source** (player or AI) discovers and engages **Interaction Targets** 
placed in the world. Targets declare available interactions via **Smart Objects** and **Gameplay Behaviors**, while the source 
detects/maintains candidates, applies focus using strategies like **distance to the instigator** or **camera aim**.

Eventually, the Interaction Source fires a Gameplay Ability that retrieves the target's Smart Object and selected behavior. 
The source then runs a **State Tree** that supports multiple possible behaviors, such as orchestrate movement/rotation, 
animation, timing, and effects, ultimately triggering the behavior on the target and **producing a clear interaction outcome**.

## Key Participants
The system is built around two roles: the **Interaction Source** and the **Interaction Target**.

**[](int_interaction_source.md)**
: The **Interaction Source** captures and stores available **Interaction Targets** for a pawn or character. Once captured,
these targets can be **focused**, making them eligible for the **Interaction Flow**.

**[](int_interaction_targets.md)**
: The **Interaction Target** is built on two frameworks: **Smart Objects** and **Gameplay Behaviors**. It introduces
specialized logic and flows, integrated with other parts of the Interaction System.

## Flow Overview
The following steps are involved in the **interaction flow**:

1. **Detect:** The Interaction Source registers nearby targets and becomes aware of potential interactions.
2. **Accept:** A target accepts the source only if it offers a compatible interaction.
3. **Scan & Focus:** When the first target is registered, the source begins scanning and applies **focus** to the best candidate. If no targets remain, scanning halts.
4. **Request:** From an appropriate Gameplay Event, the source sends an interaction **request** to a Gameplay Ability, packaging the chosen target's **Smart Object** and the desired **Behavior**.
5. **Execute:** The **Execute Interaction** ability bridges the source and target, retrieving the correct behavior configuration from the Smart Object.
6. **State Tree Orchestration:** The source runs a **State Tree** to handle movement/rotation, animation, timing, and other orchestration steps, including actually triggering the interaction behavior.
7. **Outcome:** The target's behavior logic runs to completion (or cancellation), producing the interaction outcome.


