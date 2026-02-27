# Release Interaction Handle Task
<primary-label ref="interaction"/>

Deliberately releases the Interaction Handle.

Before releasing the handle it will evaluate if the Smart Object slot is indeed marked as either claimed or occupied. 
If not, the release won't execute, but the state succeeds.

| Property                  | Type      | Description                                                          |
|---------------------------|-----------|----------------------------------------------------------------------|
| Interaction Manager       | Context   | Interaction Manager assigned to the owner.                           |
| Smart Object Claim Handle | Parameter | Handle representing the claim to the slot in the active interaction. |
