# Input Integration
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li>Use <b>Ninja Input</b> to invoke the appropriate interaction functions on the <b>Interaction Manager</b>.</li>
        <li>The <b>Pressed</b> trigger should attempt to <b>start</b> an interaction with the current eligible target.</li>
        <li>If timed interactions are supported, the <b>Released</b> trigger should attempt to <b>interrupt</b> any ongoing interaction.</li>
    </ul>
</tldr>

Use **Ninja Input** to forward button events to the **Interaction Manager**, so it attempts to start an interaction with
an eligible target and, optionally, interrupt an ongoing interaction that hasn’t been **committed** yet.

## Creating the Input Handler
<procedure title="Creating the Input Handler" collapsible="true" default-state="expanded">
    <step>
        <b>Create an Input Action</b> (e.g., <code>IA_Interact</code>).
        <ul>
            <li>Add a <b>Pressed</b> trigger.</li>
            <li><i>Optional:</i> add a <b>Released</b> trigger for hold-to-activate / cancellable interactions.</li>
        </ul>
    </step>
    <step>
        <b>Create an Input Handler</b> that <b>extends</b> <code>NinjaInputHandler</code> (from Ninja Input), and implement
        <code>HandleTriggeredEvent</code>.
    </step>
    <step>
        Retrieve the <b>Interaction Manager</b> from the pawn associated with the <b>Input Manager</b>, and verify it is valid.
    </step>
    <step>
        <p>Branch on the incoming <b>Input Action Value</b> (convert to bool):</p>
        <ul>
            <li><code>true</code> &rarr; call <code>TryInitializeInteractionWithCurrentTarget</code></li>
            <li><code>false</code> &rarr; call <code>TryCancelCurrentInteraction</code> with reason tag <code>Interaction.Event.CancelledButtonPress</code></li>
        </ul>
    </step>
    <step>
        <b>Bind the handler</b> in your input setup (mapping context / action bindings) so it runs for <code>IA_Interact</code>.
    </step>
    <p><img src="int_integration_input_handler.png" alt="Input handler branching to start/cancel via Interaction Manager" border-effect="line" thumbnail="true"/></p>
</procedure>
