# Create Melee Weapons
<secondary-label ref="guide"/>

<video src="https://youtu.be/IGUBRVY6MAM" preview-src="sc_thumbnail_p01g03.png" width="800" />

After configuring the initial **Combat Components**, the first step in Ninja Combat is to prepare your character for
**Melee Attacks** using a **Melee Weapon**, which must be registered with the **Weapon Manager**.

<procedure title="Create a sword" collapsible="true">
    <step>
        <p>Create a new <b>Actor</b> extending from <code>NinjaCombatWeaponActor</code>. This will be our <b>sword</b>.</p>
        <tip>If you want to create a <b>base Blueprint</b> for your <b>melee weapons</b>, you can also do that. Then, extend this Blueprint to create the sword Actor.</tip>
    </step>
    <step>
        <p>Set <code>Inventory.Item.Type.Sword</code> to the <b>Weapon Tags</b> container.</p>
        <img src="p01g03_sword_item_tag.png" alt="Sword Tags" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Add a <b>Static Mesh</b> to this Actor, set your sword mesh to it, and add the Component Tag <code>Combat.Component.MeleeScanSource</code>.</p>
        <img src="p01g03_sword_weapon_mesh.png" alt="Sword Mesh" thumbnail="true" border-effect="line" width="600"/>
        <tip>
            <p>You can also implement <code>GetMeleeMesh</code>, from the <b>Melee Interface</b> and return your Static Mesh from it. In that case, you do not need to tag your weapon meshes.</p>
            <img src="p01g03_get_mesh_interface.png" alt="Sword Mesh" thumbnail="true" border-effect="line" width="600"/>
        </tip>
    </step>
    <step>
        <p>Set the mesh's collision to <b>Overlap All</b>. The system uses traces to collect targets, and we do not want the weapon colliding with other objects.</p>
        <img src="p01g03_melee_mesh_collision.png" alt="Sword Mesh Collisions" thumbnail="true" border-effect="line" width="600"/>
        <tip>If you created a base <b>Melee Weapon Blueprint</b>, then make sure to configure collisions in the <b>base Blueprint</b>, so it can be applied to any actual Melee Weapon Actors!</tip>
    </step>
</procedure>

<procedure title="Create a shield" collapsible="true">
    <step>Create a new <b>Actor</b> extending from <code>NinjaCombatWeaponActor</code>, or from your <b>base Blueprint</b>. This will be our <b>shield</b>.</step>
    <step>
        <p>Set <code>Inventory.Item.Type.Shield</code> to the <b>Weapon Tags</b> container.</p>
        <img src="p01g03_shield_item_tag.png" alt="shield Tags" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Repeat the same steps as before, setting the <b>Weapon Collision</b> and tagging the <b>Static Mesh Component</b>.</p>
        <tip>You only need to tag your meshes if you have not implemented <code>GetMeleeMesh</code>, from the <b>Melee Interface</b>.</tip>
    </step>
</procedure>

<procedure title="Configure the Combat Components" collapsible="true">
    <step>
        <p>In your <b>Player Character</b>, add the <b>Combat Manager Component</b>, <b>Weapon Manager Component</b> and implement the <b>Combat System Interface</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <p>In the <b>Components</b> tab, search for <code>combat manager</code> and select the <b>Ninja Combat Manager</b> component.</p>
                <br/>
                <img src="p01g03_add_combat_manager.png" alt="Combat Manager Component" thumbnail="true" border-effect="line" width="600"/>
                <br/>
                <p>In the <b>Components</b> tab, search for <code>weapon manager</code> and select the <b>Ninja Combat Weapon Manager</b> component.</p>
                <br/>
                <img src="p01g03_add_weapon_manager.png" alt="Weapon Manager Component" thumbnail="true" border-effect="line" width="600"/>
                <br/>
                <p>In the <b>Class Settings</b> view, add the <b>Combat System Interface</b>.</p>
                <br/>
                <img src="p01g03_weapon_system_interface.png" alt="Combat System Interface" thumbnail="true" border-effect="line" width="600"/>
                <br/>
                <p>In the <b>My Blueprint</b> tab, under <b>Interfaces</b>, expand the <b>Combat System Interface</b>:</p>
                <ul>
                    <li>Double-click <code>GetCombatManagerComponent</code> and return the <b>Combat Manager</b> component.</li>
                    <li>Double-click <code>GetWeaponManagerComponent</code> and return the <b>Weapon Manager</b> component.</li>
                    <li>Double-click <code>GetCombatMesh</code> and return the <b>Character Mesh</b>.</li>
                </ul>
            </tab>
            <tab title="C++" group-key="cpp">
                <ul>
                    <li>Add <code>CombatSystemInterface</code> to your Player Character class.</li>
                    <li>Create an instance of <code>UNinjaCombatManagerComponent</code> and return it from <code>GetCombatManager_Implementation</code></li>
                    <li>Create an instance of <code>UNinjaCombatWeaponManagerComponent</code> and return it from <code>GetWeaponManagerComponent_Implementation</code></li>
                    <li>Return the character's mesh from <code>GetCombatMesh_Implementation</code></li>                        
                </ul>
                <br/>
                <code-block lang="c++" src="cbt_weapon_manager_setup.h" />
                <br/>
                <code-block lang="c++" src="cbt_weapon_manager_setup.cpp" />
            </tab>
        </tabs>
    </step>
</procedure>

<procedure title="Configure the Weapon Manager" collapsible="true">
    <step>Open your character's <b>Skeleton</b> and add sockets for the <b>sword</b> and <b>shield</b>.</step>
    <step>
        <p>Add your weapons to the Weapon Manager's <b>Details Tab</b> and configure them to the appropriate sockets in your <b>Character's Mesh Skeleton</b>.</p>
        <img src="p01g03_add_weapons_to_weapon_manager.png" alt="Adding Weapons to the Weapon Manager" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press <b>play</b>, you should see your <b>Player Character</b>, as usual.</step>
    <step>Your character should have a sword and a shield attacked to the correct sockets.</step>
    <img src="p01g03_results.png" alt="Weapons added to the character" thumbnail="true" border-effect="line" width="600"/>
</procedure>