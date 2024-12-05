# Attitude Solver
<primary-label ref="factions"/>

**Attitude Solvers** are used to determine the Attitude between an AI Agent and a given target. 

The Faction System does not expose these directly to designers. Instead, these objects are used internally by the 
Faction Subsystem to determine the attitude between factions.

## Available Solvers

There are two Attitude Solvers provided by the Faction System. Faction Solvers can be set in the Faction Settings page.

| Solver                | Description                                                                                          |
|-----------------------|------------------------------------------------------------------------------------------------------|
| Simple Attitude Check | Determines attitude based on the Main Faction configuration for both actors.                         |
| Target Reputation     | Determines attitude based on the Reputation between the source's Main Faction and the target's tier. |

## Creating Solvers

Projects can use create their own **Attitude Solver** by extending `NinjaFactionAttitudeSolver`. This can be done in 
Blueprints or C++.

In this example, a "Chaotic Solver" will be created, where the attitude is always random.

<tabs group="sample">
     <tab title="Blueprint" group-key="bp">
        <img src="fct_solver_example.png" alt="Faction Solver Example" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="C++" src="fct_chaotic_solver.h"/>
        <br/>
        <code-block lang="C++" src="fct_chaotic_solver.cpp"/>
    </tab>
</tabs>
