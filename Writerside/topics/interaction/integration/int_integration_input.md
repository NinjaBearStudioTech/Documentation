# Input Integration
<primary-label ref="interaction"/>

<tldr>
    <ul>
        <li>Use <b>Ninja Input</b> to send <b>gameplay events</b> into the Interaction Source’s <b>Ability</b>.</li>
        <li><b>Pressed</b> → start interaction (e.g., <code>Interaction.Event.RequestInteraction</code>).</li>
        <li><b>Released</b> → attempt to cancel/interrupt (e.g., <code>Interaction.Event.CancelledButtonPress</code>).</li>
        <li>Implement by extending Ninja Input’s <b>Send Gameplay Event</b> handler and mapping it to your Input Action.</li>
        <li><b>Released</b> is optional; only add it for <b>hold-to-activate</b> or <b>cancellable</b> interactions.</li>
    </ul>
</tldr>

Use **Ninja Input** to forward button events to the Interaction pipeline. The handler translates the current input state
into a **gameplay event tag** that your **Interaction Ability** listens for, so a **press** starts an interaction and a
**release** cancels it when applicable.

## Creating the Input Handler

<procedure title="Create and wire the Input Handler" collapsible="true" default-state="expanded">
    <step>
        <b>Create an Input Action</b> (e.g., <code>IA_Interact</code>).
        <ul>
            <li>Add a <b>Pressed</b> trigger.</li>
            <li><i>Optional:</i> Add a <b>Released</b> trigger for hold/cancellable interactions.</li>
        </ul>
    </step>
    <step>
        <b>Create a Handler Blueprint</b> that <b>extends</b> <code>Send Gameplay Event</code> (from Ninja Input), and open
        <code>HandleTriggeredEvent(Manager, Value, InputAction, ElapsedTime)</code>.
    </step>
    <step>
        <b>Convert</b> <code>InputActionValue</code> &rarr; <b>Bool</b> ("pressed?").
        <b>Select</b> the gameplay event tag based on that boolean:
        <ul>
            <li><code>true</code> &rarr; <code>Interaction.Event.RequestInteraction</code> (start)</li>
            <li><code>false</code> &rarr; <code>Interaction.Event.CancelledButtonPress</code> (cancel)</li>
        </ul>
        <note>Use your project’s tags if they differ. The tags above are common defaults shipped with Ninja Interaction.</note>
    </step>
    <step>
        <b>Call</b> <code>Send Gameplay Event</code> with the following parameters:
        <ul>
            <li><b>Manager</b>: Interaction Manager reference</li>
            <li><b>Value</b>: the original input value</li>
            <li><b>Input Action</b>: the <code>IA_Interact</code> action</li>
            <li><b>Gameplay Event Tag</b>: the selected tag from the previous step</li>
        </ul>
    </step>
    <step>
        <b>Bind the Handler</b> in your input setup (mapping context / action bindings) so it runs for <code>IA_Interact</code>.
    </step>
    <img src="int_integration_input_handler.png" alt="Select tag and call Send Gameplay Event" border-effect="line" thumbnail="true"/>
</procedure>
