# Reputation and Attitude
<primary-label ref="factions"/>

A player might have **12 reputation** with the Town Watch. If scores from 10 to 99 earn the **Trusted** tier, and that tier is **Friendly**, a guard can welcome the player. The number records progress, the tier gives that progress a name, and the attitude is the answer your game can act on.

## Choose How the Observer Judges a Target

The **Faction Solver Class** in **Project Settings → Ninja Factions** controls what **Get Attitude** returns. Put the actor making the decision on **Source**. Asking how the guard sees the player can give a different answer from asking how the player sees the guard.

| Solver | What the guard checks |
| --- | --- |
| **Simple Attitude Check** | Compares the guard's and player's main faction tags. Matching tags use the guard faction's attitude toward its own faction. For different tags, the guard looks for an exception in its faction's attitude matrix, then falls back to its attitude toward other factions. |
| **Target Reputation** | Looks for the player's membership in the guard's main faction. If found, it uses the attitude of the tier for the player's reputation there. If the player has no such membership, the guard uses its faction's default attitude toward other factions. |

In a dialogue or interaction Blueprint, use **Is Friendly**, **Is Neutral**, or **Is Hostile** to test just the attitude your branch needs. For Unreal Gameplay Effects, the built-in **Friendly Attitude** and **Hostile Attitude** application requirements can use that same relationship to limit who receives a heal or a harmful effect.

## Give One Faction an Exception

Suppose the Watch is neutral toward outsiders but hostile to Zombies. Create a Data Table with the row type **Faction Alignment Table Row** (`FFactionAlignmentTableRow`). Add a row, put the Zombies faction's exact tag in **Faction Tags**, and set **Attitude** to **Hostile**. Assign the table to the Watch asset's **Attitude Matrix**. With **Simple Attitude Check**, other outsiders still receive the Watch's usual neutral response. Set up the Zombies asset separately if you want the reverse relationship.

## Define Reputation Tiers

**Target Reputation** uses one project-wide **Reputation Table**. Each row has a name, a minimum and maximum score, and an attitude. Both endpoints count. Start the first range at zero and make each score belong to exactly one row. The row's display name and color can represent that standing in your UI.

[Change Reputation Through Gameplay](fct_add_reputation.md) walks through creating the table and crossing a threshold. For a longer progression, the following sample has five tiers.

<code-block lang="json" src="fct_reputation_tiers.json" collapsible="true" collapsed-title="Five example reputation tiers"/>

## Add a Project-Specific Rule

For a truce that makes two rival factions friendly, create a Blueprint or C++ subclass of the **Simple Attitude Check** solver. Override **Solve Attitude** (`SolveAttitude`), return Friendly while the truce applies, and call the parent implementation for other encounters. Select your subclass as **Faction Solver Class**. If all you want to change is which groups count as the same faction, override **Is Same Faction** (`IsSameFaction`) on that solver.

The example below shows where to return a custom attitude in a solver derived directly from `NinjaFactionAttitudeSolver`. It picks a random result on each query.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp"><img src="fct_solver_example.png" alt="Blueprint overriding Solve Attitude" width="780" border-effect="line"/></tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="C++" src="fct_chaotic_solver.h"/>
        <code-block lang="C++" src="fct_chaotic_solver.cpp"/>
    </tab>
</tabs>
