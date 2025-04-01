# Opportunity Attack Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Uses the <b>Contextual Animation System</b> to synchronize animations between an <b>attacker</b> and a <b>victim</b>.</li>        
        <li>Uses the <b>Gameplay Target System</b> to collect the correct target, even if it is the one with the current <b>target lock</b>.</li>
        <li>Can optionally use <b>Camera Animations</b> and for that, the Combat System provides a <b>Camera Manager</b>.</li>
    </ul>
</tldr>

The Opportunity Attack Ability manages **Actor and Camera animations** to perform an attack with a **cinematic flair**.

## Contextual Animations

The Opportunity Attack uses a **Contextual Animation Asset** to manage the animations and motion warping between an attacker
and a victim. The roles are not strict, but you need a **primary** and **secondary** role in your scene.

The primary role is always meant to be the **victim**, which is collected via the Target Preset assigned to the ability.
The secondary role is always meant to be the **attacker**, which is the Ability Avatar.

### Additional Roles
<secondary-label ref="wip"/>

If you need additional roles in your scene, such as a third actor, or an environment "prop", then you can override the 
`CollectAdditionalSceneActors` function, from the Opportunity Attack Ability.

This function returns a map of **Role Names** and **Actors** that should be provided to the Scene Asset.

## Camera Animations

You can optionally add a **Camera Animation**, usually created using the **Level Sequencer**, to add a cinematic flair 
to your opportunity attacks.

### Camera Anchor

This actor provides the camera that will be used to play the animation. You can extend this actor to adjust how you want
your camera to behave or even to use a different kind of camera, such as the **Cine Camera**.

For camera transitions, you don't need to extend the Camera Anchor. Instead, you can override the 
`BuildCameraAnimationParameters` function, from the Opportunity Attack Ability