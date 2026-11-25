# Targeting and Animation Alignment
<primary-label ref="combat"/>

A lock marker, a character facing an opponent, and a step that brings a strike into reach use related settings. Each answers a different question.

| What the player sees | What to configure |
| --- | --- |
| The intended opponent is selected | A **Targeting Preset** gathers candidates, filters them, and sorts them. The Target Lock ability uses the result. |
| A marker follows the opponent | Give the target a **lock anchor** where the marker belongs. The manager stores the current target. |
| The attacker faces the opponent | Use movement settings that respond to target lock. `GetCombatForwardReference` provides a stable direction for abilities that need one. |
| A moving attack reaches the right position | **Motion Warping** adjusts the root motion of a montage toward a named target over a chosen interval. |

Use `BindToCombatTargetChangedDelegate` on the target manager for a HUD or camera that needs the old and new targets. Clear the display on release. For the steps from target selection to a warped approach, see [Lock On and Align an Attack](cbt_guide_target_lock.md).
