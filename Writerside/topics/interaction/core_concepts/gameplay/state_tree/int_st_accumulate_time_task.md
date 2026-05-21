# Start Time Accumulation Task
<primary-label ref="interaction"/>

Enables time accumulation for the current interaction.

This task is intended for interactions where time should only begin accumulating **after a deliberate event occurs**. For 
example, the time taken for the instigator to reach the target should not be accounted for as part of the interaction. 
Once the instigator reaches the target, **time accumulation can begin**.

This task works in conjunction with the Interaction Manager's `TimeAccumulationMode` setting, which determines whether 
time accumulation happens **automatically** (default) or only after an **explicit event** is triggered, which is the purpose 
of this task.

| Property            | Type    | Description                                                                                                         |
|---------------------|---------|---------------------------------------------------------------------------------------------------------------------|
| Interaction Manager | Context | Interaction Manager that will receive the request to start accumulating time, for its currently active interaction. |