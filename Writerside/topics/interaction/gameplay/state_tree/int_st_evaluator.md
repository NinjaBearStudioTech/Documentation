# Interaction Context Evaluator
<primary-label ref="interaction"/>

Provides information related to the *current interaction**.

| Property                  | Type    | Description                                                          |
|---------------------------|---------|----------------------------------------------------------------------|
| Interaction Manager       | Context | Interaction Manager assigned to the owner.                           |
| Summary ID                | Output  | ID for the active interaction summary.                               |
| Interaction Type Tag      | Output  | Gameplay Tag that identifies the Interaction Type.                   |
| Smart Object Claim Handle | Output  | Handle representing the claim to the slot in the active interaction. |
| Duration                  | Output  | Duration of the interaction, set in the Interaction Definition.      |
| Total Elapsed Time        | Output  | Total time elapsed in this interaction.                              |
| Relevant Elapsed Time     | Output  | Relevant time elapsed in this interaction.                           |
| Reached Duration          | Output  | Informs when the Elapsed Time reaches the duration.                  |
| Slot Transform            | Output  | The transform associated with the Interaction Slot.                  |
| Target Actor              | Output  | Target actor participating in this interaction.                      |
| Target Component          | Output  | Target component participating in this interaction.                  |