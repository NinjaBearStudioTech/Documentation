# Equipment System
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Equipment System</b></p>
    <br/>
    <ul>
        <li>The <b>Equipment Manager</b> manages all in-world representations of equipment, such as actors and meshes.</li>
        <li>Only add an Equipment Manager to actors that are expected to visually represent equipment.</li>
        <li>Add the Equipment Manager to the <b>Inventory Avatar</b> (e.g., Player Character).</li>
        <li>Optionally implement <code>EquipmentSystemInterface</code> for faster and direct access to the manager.</li>
    </ul>
</tldr>

The Equipment System manages **Equipment**, providing a flexible way to handle items that require in-world representation, 
such as **spawned actors**, **mesh components**, and **loaded assets** via the **Asset Manager**. 

This system should be added to the **Avatar Actor**, usually the Player Character or controlled Pawn.

> **Conditional Component**
> 
> Actors that won't interact with **Item Presences** (e.g., equippable weapons or visible gear), such as chests, vendors 
> and static enemies **do not require an Equipment Manager**.
{style="note"}

## Equipment Manager Component
The Equipment Manager Component should be added to any actor expected to show equipment in the world. This is typically 
your **Inventory Avatar** (e.g., the Player Character).

<procedure title="Add the Equipment Manager Component" collapsible="true" default-state="expanded">
    <step>
        <p>In your <b>Inventory Avatar Actor</b> (i.e., the Player Character), add the <b>Equipment Manager Component</b>.</p>
        <p>The component can be added using either Blueprint or C++:</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="inv_setup_equipment_manager.png" alt="Add the Equipment Manager Component" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p><b>Header</b></p>
                <code-block lang="c++" src="inv_setup_equipment_manager_component.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="inv_setup_equipment_manager_component.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

The Equipment Manager provides important **key settings** that can be used to adjust its behavior.

| Property                    | Description                                                                                   |
|-----------------------------|-----------------------------------------------------------------------------------------------|
| Equipment Container Query   | A query used to select all Equipment Containers in the Inventory Manager.                     |
| Default Attach Finder Class | Default strategy used to select attachment parent components for Equipment Actors and Meshes. |

### Inventory Component Binding
The Equipment Manager Component will automatically bind to an Inventory System Component. When that happens, it will
automatically process any necessary **equipment instance** for all **eligible items**.

## Equipment System Interface
The recommended way to retrieve the Equipment Manager is through the `GetEquipmentManager` function provided in `NinjaInventoryEquipmentFunctionLibrary`.

This function searches common ownership chains—such as Actor → Controller → Player State—to locate the Equipment Manager.

To avoid repeated lookups, you can optionally implement `EquipmentSystemInterface` on the actor that owns the Equipment 
Manager. This allows the system to retrieve the component directly.

<procedure title="Add the Equipment System Interface" collapsible="true" default-state="expanded">
    <step>In your <b>Inventory Avatar</b>, add the <code>EquipmentSystemInterface</code>.</step>
    <step>Implement the <code>GetEquipmentManager</code> function so it returns the <b>Equipment Manager Component</b>.</step>
    <tabs group="sample">
        <tab title="Blueprint" group-key="bp">
            <img src="inv_setup_equipment_interface.png" alt="Add the Equipment System Interface" width="800" thumbnail="true" border-effect="line"/>
        </tab>
        <tab title="C++" group-key="cpp">
            <p><b>Header</b></p>
            <code-block lang="c++" src="inv_setup_equipment_system_interface.h"/>
            <p><b>Implementation</b></p>
            <code-block lang="c++" src="inv_setup_equipment_system_interface.cpp"/>
        </tab>
    </tabs>
</procedure>
