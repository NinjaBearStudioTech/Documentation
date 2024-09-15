# Faction Database
<primary-label ref="factions"/>

The **Faction Database** determines the original location from where **Faction Data Assets** are obtained. It is used
by the **Faction Subsystem** to retrieve Faction information.

## Available Database

The system provides a Faction Database based on the **Asset Manager**, loading Data Assets available in the project.
This database requires the Faction Data Asset to be properly configured in the Asset Manager, as per the [Setup page](fct_setup.md).

## Creating Databases

Projects can use create their own **Faction Database** by extending `NinjaFactionDatabase`. This can be done in
Blueprints or C++.

In this example, a "List-Based Database" will be created, where assets are loaded from a pre-defined list.

<tabs group="sample">
     <tab title="Blueprint" group-key="bp">
        <img src="fct_database_example.png" alt="Faction Database Example" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="C++" src="fct_list_database.h"/>
        <br/>
        <code-block lang="C++" src="fct_list_database.cpp"/>
    </tab>
</tabs>
