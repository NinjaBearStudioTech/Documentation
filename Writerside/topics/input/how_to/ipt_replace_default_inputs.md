# Replace Default Inputs
<primary-label ref="input"/>
<secondary-label ref="how-to"/>

This how-to will show you how to replace all inputs from the default **Third Person Template** with the equivalent
**Input Handlers** provided by Ninja Input.

<procedure title="Remove the original input handling" collapsible="true">
    <step>Open your <b>Project Settings</b>, navigate to <b>Enhanced Input</b> and make sure that there are no <b>Default Mapping Contexts</b>.</step>    
    <step>Navigate to your <b>Character Blueprint</b>, open it and go to the <b>Event Graph</b>.</step>
    <step>You'll see many events related to <b>input handling</b>, including <b>Begin Play</b>. Select and <b>remove</b> all nodes.</step>
</procedure>

<procedure title="Configure the Input Setup" collapsible="true">
    <step>In the <b>Content Browser</b>, navigate to your <b>Input</b> folder.</step>
    <step>Right click to open the <b>Context Menu</b>, navigate to the <b>Input</b> category and select <b>Ninja Input Setup</b>. Name it in a way that it correlates with your <b>Input Mapping Context</b>, for example: <code>IMC_SciFi</code> &rightarrow; <code>IS_SciFi</code>.</step>
    <step>Open the new <b>Input Setup</b> and add your <b>Input Mapping Context</b>.</step>
    <step>Add three new entries to the <b>Input Handlers</b> list, selecting: <code>Character: Move</code>, <code>Character: Look</code> and <code>Character: Jump</code>.</step>
    <step>For each one of these entries, expand their properties and add the appropriate <b>Input Action</b>.</step>
    <img src="ipt_basic_input_setup.png" alt="Basic Input Setup"/>
</procedure>

<procedure title="Assign the Input Setup to the Input Manager" collapsible="true">
    <step>Navigate to the Actor, <b>Character</b> or <b>Player Controller</b>, where the <b>Input Manager</b> was added.</step>
    <step>Click the <b>Input Manager</b> to open its <b>Default Values</b>.</step>
    <step>Add the newly-created <b>Input Setup</b> to the list of <b>Input Setups</b>.</step>
    <img src="ipt_add_setup_defaults.png" alt="Adding the Input Setup"/>
</procedure>

<procedure title="Check your progress" collapsible="true">
    <step>If you created a new <b>Player Controller</b>, then make sure to configure it in your <b>Game Mode</b>, so it will use the correct object.</step>
    <step>Hit <b>Play</b> and all your inputs should work as expected: you should be able to <b>move</b>, <b>look around</b> and <b>jump</b>.</step>
    <img src="ipt_completed_initial_setup.gif" alt="Finished initial setup"/>
</procedure>