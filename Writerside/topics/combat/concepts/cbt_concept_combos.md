# Combos and Action Windows
<primary-label ref="combat"/>

Think of a three-move combo as a choice after the first move. A second press can continue the light chain, a different press can start a heavy follow-up, and waiting lets the first animation finish.

The **Combo Ability** owns the Combo Tree and grants its supporting abilities. The **Combo Manager** runs that tree. Each move has a state that activates an ability by tag. Event transitions connect it to the possible next moves.

## Decide When a Press Counts

Put a **Combo Window** notify state on the current move's montage. While it is open, send the gameplay event named by the transition. An input buffer can retain an earlier press and deliver it when the window opens. A melee scan window belongs on the frames where contact can occur and can have different timing.

Use `BindToComboWindowChangedDelegate` to show a training prompt and `BindToComboFinishedDelegate` to clear it. `GetComboCount` tells a branching rule how far the character has progressed. [Build a branching combo](cbt_guide_combos.md) to set up the transitions, or [drive the same combo from AI](cbt_guide_ai.md).
