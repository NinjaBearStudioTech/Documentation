# Execute Interaction
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li>Main ability that <b>executes</b> an interaction on the selected target.</li>
        <li>Activated by a <b>Gameplay Event</b> that carries the Smart Object plus Behavior (from an Interaction Request).</li>
        <li>Grant it to the <b>Interaction Source</b> (player) by default; pairs with the Scan ability that sends the "Request Interaction" event.</li>
        <li>Orchestrates the Smart Object's <b>Gameplay Behavior</b> with the configured <b>State Tree</b> during execution.</li>
    </ul>
</tldr>

The **Main Interaction Ability** for the system. It is designed to be activated by a **Gameplay Event** that contains 
the **Smart Object** and the desired **Behavior** (selected from a slot inside an **Interaction Request**). 

It should be present on the **Interaction Source** by default, so when the **Request Interaction** event is triggered
(by the Scan/Find ability plus input), this ability begins execution.

## Functions

You can introduce custom logic at key points by overriding these functions (Blueprint or C++):

| Function                    | Description                                                                                                                                                           |
|-----------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `HandleInteractionStarted`  | Called when the interaction actually starts. This is a proper location to play animations (if not using the dedicated Animation Ability), and apply gameplay effects. |
| `HandleInteractionFinished` | Called when the interaction completes or is cancelled. This is a proper location to clean-up anything that has been done during by the "Started" event.               |
| `HandleInteractionEvent`    | Handle additional custom interaction events you emit during execution.                                                                                                |
