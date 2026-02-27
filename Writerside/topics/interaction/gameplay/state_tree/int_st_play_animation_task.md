# Play Animation Task
<primary-label ref="interaction"/>

Plays an animation on the interaction source actor.

Animations are played via Gameplay Events used to trigger a Gameplay Ability designed to play animations. Any ability
configuring `Interaction.Event.AnimationRequested` as its event trigger will be activated.

Additionally, you can optionally set a specific Animation Montage that will be sent in the **Gameplay Event Payload**,
so the Animation Ability can use that as an override. 

Playing an Animation Montage from the Interaction System potentially cancels any other Animation Montage also being 
played from the same system.

| Property            | Type      | Description                                                                                    |
|---------------------|-----------|------------------------------------------------------------------------------------------------|
| Interaction Manager | Context   | Interaction Manager assigned to the owner.                                                     |
| Montage To Play     | Parameter | An optional Animation Montage sent with the payload, meant to override the default resolution. |
