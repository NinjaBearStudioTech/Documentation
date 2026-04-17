# Casting Spells
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

<procedure title="Create the Cast Actor" collapsible="true" default-state="collapsed">
<step>
    <p>In your Blueprints folder, create a new <b>Cast Actor Blueprint</b> using <code>NinjaCombatCastActor</code> as the base class.</p>
</step>
<step>
    <p>Add two components to the <b>Cast Sphere</b>, a <b>Niagara Component</b> and an <b>Audio Component</b>. Set <b>Auto Activate</b> to <code>false</code> in both of them.</p>
    <note>You can set particles and sound assets to these components, or keep this Blueprint as an Abstract parent for specific Cast types.</note>
</step>
<step>
    <p>In the <b>My Blueprint</b> tab, expand the list of <b>Overridable Functions</b> and select <code>StartCast</code>. This will add this event to the <b>Event Graph</b>.</p>
</step>
<step>
    <p>Right-click the new node and select <b>Add Call to Parent Function</b>. Connect that node to the event.</p>
    <note>Always call the <b>Parent Function</b> in your base <b>Cast Actors</b>, since the base class runs important logic in there.</note>
</step>
<step>
    <p>Bind a new event to the VFX's <b>System Finished</b> delegate, activate the <b>VFX</b> and <b>Audio</b> components, making sure that both are set to <b>reset</b> and then <b>Play</b> the audio.</p>
</step>
<step>
    <p>In the <b>System Finished Event</b>, unbind the callback and <b>deactivate the Poolable Actor</b>, using the <b>Poolable Actor Component</b>.</p>
</step>
<img src="cbt_guide_cast_actor_graph.png" alt="Cast Actor Graph" width="780" border-effect="line"/>
</procedure>


