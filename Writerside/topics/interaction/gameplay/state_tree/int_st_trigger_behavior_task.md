# Trigger Behavior Task
<primary-label ref="interaction"/>

Triggers the Interaction Behavior on the target.

This task transfers control to the **Interaction Target**, allowing its **custom behavior to execute**.

Optionally, this task can release the associated Smart Object claim handle. If enabled, it verifies whether the Smart 
Object slot related to the interaction is currently claimed or occupied before releasing it.

> **Mandatory State Tree Task**
>
> Among the tasks provided for Interaction State Trees, this is the most critical one, as it ultimately triggers the 
> behavior configured on the Interaction Target. You should **always include this task**, or provide an equivalent 
> implementation that performs the same responsibility.
{style=note}

| Property                     | Type      | Description                                                           |
|------------------------------|-----------|-----------------------------------------------------------------------|
| Interaction Manager          | Context   | Interaction Manager assigned to the owner.                            |
| Target Actor                 | Input     | Target actor participating in this interaction.                       |
| Smart Object Claim Handle    | Input     | Handle representing the claim to the slot in the active interaction.  |
| Release Handle Automatically | Parameter | If true, releases the provided handle when the state ends.            |
