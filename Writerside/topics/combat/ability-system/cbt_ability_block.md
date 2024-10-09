# Block Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Applies the <b>Block Gameplay Effect</b>, which typically modifies attributes such as <b>Block Chance</b> and <b>Block Amount</b>.</li>
        <li>Optionally checks for a <b>cost</b>, such as a <b>stamina cost</b>, required to initiate blocking.</li>
        <li>Blocking events may trigger changes in the <b>Animation</b> and <b>Movement</b> systems.</li>
    </ul>
</tldr>

In the Combat System, blocking is handled using a **blocking state**, represented by a Gameplay Effect and an **effective
angle**. This means the blocking system does not rely on actual **collisions** but instead uses gameplay attributes to 
determine success.

When the **Block Ability** is activated, it applies the appropriate **Blocking Gameplay Effect**. The blocking logic in 
the **Defense Component** (usually, the Combat Manager) then activates, handling the core blocking functionality.

## Blocking Calculation

When blocking is activated, several **Gameplay Attributes** become relevant. These attributes control the effectiveness 
of the block and its limitations.

| Attribute              | Description                                                             |
|------------------------|-------------------------------------------------------------------------|
| `BlockChance`          | Chance to block an incoming attack, in a {0, 1} range.                  |
| `BlockMitigation`      | Amount of damage mitigated by blocking, in a {0, 1} range.              |
| `BlockAngle`           | Maximum angle within which blocking is effective.                       |
| `BlockLimit`           | Flat limit of damage that can be mitigated while blocking.              |
| `BlockStaminaCostRate` | Stamina cost required to block each point of damage.                    |
| `BlockCooldown`        | Cooldown applied after a successful block or when a breaker hit occurs. |

The Block Ability will always check the **Stamina Cost Rate** before activating, ensuring the combatant has the minimum 
required stamina (or other relevant resources) to block effectively.

## Integrations

Blocking is frequently integrated with other systems within the Combat System, such as **Movement**, **Animation**, and 
**Hit Reactions**.

### Movement

Blocking can affect movement, often reducing the character's movement speed to a _walking speed_. You can implement this 
by listening to the Defense Component's **Blocking State Changed** delegate, or by using the provided 
`NinjaCombatCharacterMovementComponent`, which automatically handles movement adjustments during blocking.

### Animation

When blocking, characters may switch to a different movement state, reflecting the defensive stance. You can track this 
state through the same delegate or by using the `NinjaCombatAnimInstance`, which includes a `Blocking` property to 
represent the current blocking state.

Here's an example showing how to use the 'Blocking' property to switch between animation sequences.

<img src="cbt_blocking_anim_blend_bool.png" alt="Blending by Bool" thumbnail="true" border-effect="line" />

Here's another example, using a **Chooser Table** to select the correct **Motion Matching** database.

<img src="cbt_blocking_anim_chooser_table.png" alt="Chooser Table for Blocking" thumbnail="true" border-effect="line" />

### Hit Reactions

You can define custom hit reactions for blocked hits by creating a specific Animation Montage for when a character 
blocks incoming damage. Similarly, a different reaction can be triggered for **breaker hits** (when a block is 
interrupted).

| Gameplay Tag                   | Context                              |
|--------------------------------|--------------------------------------|
| `Combat.Effect.Damage.Blocked` | The hit was blocked.                 |
| `Combat.Effect.Damage.Breaker` | The blocking stance was interrupted. |

Here's an example of a **Hit Reaction Ability** that includes **blocked** and **breaker** hits.

<img src="cbt_blocking_hit_reaction.png" alt="Hit Reaction with Blocking" thumbnail="true" border-effect="line" />

<seealso style="cards">
    <category ref="external">
        <a href="https://dev.epicgames.com/community/learning/tutorials/lwlG/unreal-engine-your-first-60-minutes-with-motion-matching" summary="Official documentation for Motion Matching and Chooser Tables.">Motion Matching</a>
    </category>
</seealso>
