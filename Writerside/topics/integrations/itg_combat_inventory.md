# Inventory Integration
<primary-label ref="integrations"/>

Combat and Inventory can be integrated via the Weapon Manager and Weapon classes. You can do so using Blueprints or C++.
This guide will walk you through the steps necessary to integrate both systems. 

<procedure title="Turn Weapons into Equipment Actors" collapsible="true">
    <step>Create a base <b>Weapon Actor</b>, extending from <code>ANinjaCombatWeaponActor</code>.</step>
    <step>Add <code>NinjaEquipmentReceiverComponent</code> to this base Weapon Actor.</step>
    <step>Add the <code>EquipmentActorInterface</code> to the list of implemented interfaces.</step>
    <step>
        <p>Implement the <code>GetWeaponOwner</code> function, from the <code>WeaponInterface</code>, to provide the Equipment Owner.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="cbt_integration_inventory_get_weapon_owner.png" alt="Get Weapon Owner" thumbnail="true"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="c++" src="cbt_integration_inventory_weapon_actor.h"/>
                <br/>
                <code-block lang="c++" src="cbt_integration_inventory_weapon_actor.cpp"/>
            </tab>
        </tabs>
    </step>
    <step>
        <p>Implement the <code>GetHitEffectLevel</code> function, from the <code>WeaponInterface</code>, to provide the Equipment Level.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="cbt_integration_inventory_get_hit_effect_level.png" alt="Get Hit Effect Level" thumbnail="true"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="c++" src="cbt_integration_inventory_weapon_actor_pt2.h"/>
                <br/>
                <code-block lang="c++" src="cbt_integration_inventory_weapon_actor_pt2.cpp"/>
            </tab>
        </tabs>
        <note>
            <p><b>Default Level</b></p>
            <p>Make sure to set the value of <b>Default Level</b> to <code>1</code> as a fallback! Otherwise, items without levels will apply an effect with level zero!</p>
            <p>The <b>Base Weapon Class</b> already provides a variable for the effect level, which you can use as a fallback.</p>
        </note>
    </step>
</procedure>

<procedure title="Create the Equipment Weapon Manager" collapsible="true">
    <step>Create a new <b>Actor Component</b>, extending from <code>ActorComponent</code>.</step>
    <step>Add the <code>CombatWeaponManagerInterface</code> to the list of implemented interfaces.</step>
    <step>
        <p>Implement the <code>GetWeapon</code> function, to retrieve the weapon using the <b>Equipment Manager</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="cbt_integration_inventory_get_weapon.png" alt="Get Weapon" thumbnail="true"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="c++" src="cbt_integration_inventory_weapon_manager.h"/>
                <br/>
                <code-block lang="c++" src="cbt_integration_inventory_weapon_manager.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

<procedure title="Set the Equipment Weapon Manager" collapsible="true">
    <step>Add the new Actor Component created in the previous step to the base Character.</step>
    <step>Make sure that this Character has an <b>Equipment Manager</b> properly configured.</step>
    <step>
        <p>Implement the <code>GetWeaponManager</code> function, to provide the new component.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="cbt_integration_inventory_get_weapon_manager.png" alt="Get Weapon Manager" thumbnail="true"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="c++" src="cbt_integration_inventory_character.h"/>
                <br/>
                <code-block lang="c++" src="cbt_integration_inventory_character.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

