# Create a Melee Weapon
<primary-label ref="combat"/>
<secondary-label ref="how-to"/>

This how-to will show you how to create your first **Melee Weapon** and assign it to the default **Weapon Manager**.

<procedure title="Create your Sword Weapon actor" collapsible="true">
    <step>Create a new <b>Actor</b> extending from <code>NinjaCombatWeaponActor</code> and name it <code>BP_Weapon_Sword</code>.</step>
    <step></step>
    <step>
        <p>Add <code>Inventory.Item.Type.Sword</code> to the <b>Weapon Tags</b> container.</p>
        <img src="cbt_create_weapon_tags.png" alt="Create the Weapon Tags" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Create a <b>Static Mesh Component</b> and set the mesh for your Weapon.</p>
        <img src="cbt_create_weapon_mesh.png" alt="Create the Weapon Mesh" border-effect="line" thumbnail="true"/>
    </step>
    <step>Set the Weapon Collision to <b>Overlap All</b>, since the system uses traces to scan for targets.</step>
    <step>Add the <code>Combat.Component.MeleeScanSource</code> tag to your Static Mesh Component, so the Weapon Actor will be able to find the <b>Weapon Mesh</b>.</step>
</procedure>

<procedure title="Create your Shield Weapon actor" collapsible="true">
    <step>Create a new <b>Actor</b> extending from <code>NinjaCombatWeaponActor</code> and name it <code>BP_Weapon_Shield</code>.</step>
    <step></step>
    <step>
        <p>Add <code>Inventory.Item.Type.Shield</code> to the <b>Weapon Tags</b> container.</p>
        <img src="cbt_create_weapon_shield.png" alt="Create the Shield" border-effect="line" thumbnail="true"/>
    </step>
    <step>Repeat the same steps as before, setting the <b>Weapon Collision</b> and tagging the <b>Static Mesh Component</b>.</step>
</procedure>

<procedure title="Configure the Weapon Manager" collapsible="true">
    <step>
        <p>Implement the <b>Combat System Interface</b> along with the <code>GetCombatMesh</code> and <code>GetWeaponManager</code> functions.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <p>In the <b>Components</b> tab, search for <code>weapon</code> and select the <b>Ninja Combat Weapon Manager</b> component.</p>
                <br/>
                <img src="cbt_add_weapon_manager_component.png" alt="Weapon Manager Component" border-effect="line"/>
                <br/>
                <p>In the <b>Class Settings</b> view, add the <b>Combat System Interface</b>.</p>
                <br/>
                <img src="cbt_add_weapon_system_interface.png" alt="Combat System Interface" border-effect="line"/>
                <br/>
                <p>In the <b>Blueprints</b> tab, expand the <b>Combat System Interface</b> and double-click <code>Get Weapon Manager Component</code>. Implement it returning the Weapon Manager.</p>
                <br/>
                <img src="cbt_add_combat_system_weapon_manager.png" alt="Weapon Manager in the Combat System Interface" border-effect="line"/>
                <p>Still in the <b>Blueprints</b> tab, double-click <code>Get Combat Mesh</code>. Implement it returning the main Character Mesh for your Blueprint.</p>
                <br/>
                <img src="cbt_add_combat_system_combat_mesh.png" alt="Combat Mesh in the Combat System Interface" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p>Add <code>CombatSystemInterface</code> to your header and create a pointer to the <b>Weapon Manager</b>.</p>
                <p>Override the <code>GetCombatMesh</code> and <code>GetWeaponManagerComponent</code> functions.</p>
                <br/>
                <code-block lang="c++" src="cbt_weapon_manager_setup.h" />
                <br/>
                <p>Initialize the <b>Weapon Manager</b> instance and return it from the appropriate function. Do the same for the <b>Character Mesh</b>.</p>
                <br/>
                <code-block lang="c++" src="cbt_weapon_manager_setup.cpp" />
            </tab>
        </tabs>
    </step>
    <step>
        <p>Add your weapons to the Weapon Manager's <b>Details Tab</b> and configure them to the correct sockets in your <b>Character's Mesh Skeleton</b>.</p>
        <img src="cbt_add_weapons_to_manager.png" alt="Adding Weapons to the Weapon Manager" border-effect="line"/>
    </step>
</procedure>

<procedure title="Check the Weapon Manager configuration" collapsible="true">
    <step>Click the <b>Play</b> button.</step>
    <step>
        <p>Your character should start with the <b>both weapons</b> attached to the <b>correct sockets</b>.</p>
        <img src="cbt_weapon_manager_results.png" alt="Combatant with attached weapons" border-effect="line"/>
    </step>
</procedure>