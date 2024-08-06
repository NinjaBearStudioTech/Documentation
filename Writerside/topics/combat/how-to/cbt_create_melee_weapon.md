# Create a Melee Weapon
<primary-label ref="combat"/>
<secondary-label ref="how-to"/>

This how-to will show you how to create your first `Melee Weapon` and assign it to the default `Weapon Manager` that
will be configured in the player character as well.

At the end, you will create a simple `Weapon Query` to make sure that your weapon was properly assigned.

<procedure title="Create your Melee Weapon actor" collapsible="true">
    <step>Create a new <b>Actor</b> and name it <code>BP_Weapon_Sword</code>.</step>
    <step>
        <p>Add the <code>Combat Weapon Interface</code> to the new actor.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <p>In <b>Blueprints</b>, go to your <b>Class Settings</b> and under <b>Implemented Interfaces</b>, add <code>CombatWeaponInterface</code>.</p>
                <br/>
                <img src="cbt_add_weapon_interface.png" alt="Add the Combat Weapon Interface"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p>In <b>C++</b>, add the interface in your header <code>CombatWeaponInterface</code>.</p>
                <br/>
                <code-block lang="c++" src="cbt_add_weapon_interface_header.cpp" />
            </tab>
        </tabs>
    </step>
    <step>
        <p>Create a <b>Gameplay Tag Container</b> for your <b>Weapon Tags</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <p>Create a new <b>Gameplay Tag Container</b> named <code>WeaponTags</code> and set it to be <b>replicated</b>.</p>
                <br/>
                <img src="cbt_create_weapon_tags.png" alt="Create the Weapon Tags"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p>Add your <b>Constructor</b>, override <code>GetLifetimeReplicatedProps</code> and add a <b>Gameplay Tag Container</b> named <code>WeaponTags</code>.</p>
                <br/>
                <code-block lang="c++" src="cbt_add_weapon_tag_container_header.cpp" />
                <br/>
                <p>In your <b>implementation</b> configure the <b>replication</b> of the weapon and its tags.</p>
                <br/>
                <code-block lang="c++" src="cbt_add_weapon_tag_container_impl.cpp" />
            </tab>
        </tabs>        
    </step>
    <step>
        <p>Create a <b>Static Mesh</b> (or <b>Skeletal Mesh</b>, if that's more appropriate to your scenario) and</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <p>Add the <b>Component Tag</b> <code>Combat.Component.MeleeScanSource</code> and set its <b>Collision</b> to <b>Overlap All</b>.</p>
                <img src="cbt_create_weapon_mesh.png" alt="Create the Weapon Mesh"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p>Declare your <b>Mesh Component</b> in your <b>header</b>.</p>
                <br/>
                <code-block lang="c++" src="cbt_add_weapon_mesh_header.cpp" />
                <br/>
                <p>Initialize your <b>Mesh Component</b> in your constructor.</p>
                <br/>
                <code-block lang="c++" src="cbt_add_weapon_tag_container_impl.cpp" />
            </tab>
        </tabs>    
    </step>
</procedure>

<procedure title="Add your weapon to your Weapon Manager" collapsible="true">
</procedure>

<procedure title="Check your progress" collapsible="true">
</procedure>