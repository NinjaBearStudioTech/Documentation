# Configure Input Handlers
<secondary-label ref="guide"/>

<video src="https://youtu.be/6B6VPUPXmK0" preview-src="sc_thumbnail_p01g01.png" width="800" />

Configure **Ninja Input** and replace the default configuration from a project, such as the **Third Person Template**, so
it will use **Input Handlers** and an **Input Setup**.

<procedure title="Add Ninja Input to your project" collapsible="true">
    <step>Follow the steps from the <b><a href="ipt_setup.md"/></b> page. In this guide, we will add the <b>Input Manager Component</b> to the <b>Player Controller</b>.</step>    
    <step>Set your <b>Player Controller</b> to your <b>Game Mode</b> either in your <b>Level Details</b>, or in your <b>Maps and Modes</b> page in the <b>Project Settings</b>.</step>
</procedure>

<procedure title="Remove the original input handling logic" collapsible="true">
    <step>Open your <b>Project Settings</b>, navigate to <b>Enhanced Input</b> and make sure that there are no <b>Default Mapping Contexts</b>.</step>    
    <step>Navigate to your <b>Character Blueprint</b>, open it and go to the <b>Event Graph</b>.</step>
    <step>Remove all input-related nodes, including the ones connected to <b>Begin Play</b>.</step>
</procedure>

<procedure title="Configure the Input Setup" collapsible="true">
    <step>In the <b>Content Browser</b>, navigate to your <b>Input</b> folder.</step>
    <step>Right click to open the <b>Context Menu</b>, navigate to the <b>Input</b> category and select <b>Ninja Input Setup</b>. Name it in a way that it correlates with your <b>Input Mapping Context</b>, for example: <code>IMC_Gameplay</code> &rightarrow; <code>IS_Gameplay</code>.</step>
    <step>Open the new <b>Input Setup</b> and add your <b>Input Mapping Context</b>.</step>
    <step>Add three new entries to the <b>Input Handlers</b> list, selecting: <code>Character: Move</code>, <code>Character: Look</code> and <code>Character: Jump</code>.</step>
    <step>
        <p>For each one of these entries, expand their properties and add the appropriate <b>Input Action</b>.</p>
        <p>By default, they will have Input Actions starting with <code>IA_NI</code>, which are the ones provided by Ninja Input. Make sure to <b>replace them</b> with their counterparts, provided by the project.</p>
        <img src="p01g01_configure_input_setup.png" alt="Configure Input Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <tip>
        <p>If you get a <b>Validation Error</b> while saving your <b>Input Setup</b>, it means that there are Input Actions in your <b>Input Mapping Context</b> that are <b>missing</b> in the list of <b>Input Handlers</b>.</p>
        <p>Check the <b>Message Log Window</b> and you will find which Input Actions are missing an Input Handler. And you can always separate your inputs into <b>multiple setups</b>.</p>
    </tip>
</procedure>

<procedure title="Assign the Input Setup to the Input Manager" collapsible="true">
    <step>Navigate to the <b>Player Controller</b>, where the <b>Input Manager</b> was added.</step>
    <step>Click the <b>Input Manager Component</b> to open its <b>Default Values</b>.</step>
    <step>
        <p>Add the newly-created <b>Input Setup</b> to the list of <b>Input Setups</b>.</p>
        <img src="p01g01_add_input_setup_to_component.png" alt="Add the Input Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Hit <b>Play</b> and all your inputs should work as expected: you should be able to <b>move</b>, <b>look around</b> and <b>jump</b>.</step>
    <img src="p01g01_outcome.gif" alt="Finished initial setup"/>
</procedure>