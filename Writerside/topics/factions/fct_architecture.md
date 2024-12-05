# Architecture
<primary-label ref="factions"/>

This section includes **deep dive** on important **technical aspects** of the Faction System.

**[](fct_faction_database.md)**
: By default, the Faction System uses the **Asset Manager** to load all available in the game. But you can extend or 
modify this strategy, by creating your own **Faction Database**.

**[](fct_attitude_solver.md)**
: The Unreal Engine's Perception System uses the concept of **attitude** to determine how agents should react to their
perceived targets. You can use **Attitude Solvers** to provide the attitude logic between Factions.

**[](fct_bots.md)**
: If your AI agents must react to Faction Data, they can use the appropriate objects provided by the Framework, both for
**Behavior and State Trees**.

**[](fct_save_load.md)**
: The Faction System might have data that can change over time, such as **Reputation**. Therefore, the ability to save
and load this data is important to resume gameplay sessions without loss of progress.

**[](fct_gameplay_debugger.md)**
: You can query Faction Information regarding an AI agent using the **Gameplay Debugger**. A dedicated Faction Category
is available, showing Memberships and Reputation. 
