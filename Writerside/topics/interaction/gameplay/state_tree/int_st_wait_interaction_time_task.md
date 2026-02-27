# Wait Interaction Time Task
<primary-label ref="interaction"/>

Waits for the interaction timer to complete, which means **elapsed == duration**. 

**Elapsed time** starts accumulating automatically or when the [**Time Accumulation Task**](int_st_accumulate_time_task.md) 
executes, depending on the Interaction Manager's setting. As for the **duration**, it is set in the Interaction Behavior.

This task is also compatible with **interactions without a set duration**, so it can be used by generic interaction trees 
that must accommodate both interaction types.

| Property                     | Type      | Description                                                           |
|------------------------------|-----------|-----------------------------------------------------------------------|
| Interaction Manager          | Context   | Interaction Manager assigned to the owner.                            |
| Target Actor                 | Input     | Target actor participating in this interaction.                       |
| Smart Object Claim Handle    | Input     | Handle representing the claim to the slot in the active interaction.  |
| Release Handle Automatically | Parameter | If true, releases the provided handle when the state ends.            |
