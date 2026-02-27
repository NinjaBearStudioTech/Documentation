# Reach Target Task
<primary-label ref="interaction"/>

This task will interpolate the owner's current location to reach the target.

It's a simple alternative to using a "Move To" task (or the Player Counterpart) task, if your interaction radius is not 
too big and just need some adjustments. Once the target is reached, this task will end the state successfully.

| Property           | Type      | Description                                                              |
|--------------------|-----------|--------------------------------------------------------------------------|
| Target Transform   | Input     | The transform being reached. Usually the interaction slot.               |
| Ease In Out        | Parameter | Ease In-Out function for the interpolation, used to smooth the movement. |
| Location Tolerance | Parameter | Tolerance to determine we reached the target location.                   |
| Rotation Tolerance | Parameter | Tolerance to determine we reached the target rotation.                   |
| Max Wait Time      | Parameter | Maximum amount of time the task will wait for the interpolation.         |
