# State Trees
<primary-label ref="bot"/>

Choose a State Tree when you can describe the bot's actions as a sequence. A guard finds a patrol point, walks to it, looks around, then advances to the next point. A transition can interrupt that sequence when the player appears.

## Read the Target and Change State

Create a tree with the **State Tree AI Component** schema. Add the **Update Perception** evaluator. Bind its **Sensed Actor** to a chase task and use its **Awareness Level** when the guard should wait for confirmation. Give Roam a transition to Chase when the target becomes valid, and give Chase a way back when the target is lost.

## Give Each Guard Its Own Settings

In the **Bot Setup**, expand **State Tree** and choose the main tree. For example, expose an **Attack Range** root parameter in the tree and bind it to your distance check. Enable the override beside that parameter in one guard's setup and enter its range. Other guards keep the tree's default. If you remove a parameter or change its type, compile the tree and review its overrides.

The standard AI schema works for this walkthrough. A project-specific schema can add context, such as an ability system. The project must supply that context when the tree runs. Linked trees must use the main tree's schema or a subclass.

## Change What Happens at a Patrol Stop

A **Linked Asset** state marks a place where another tree can run. Give that state a gameplay tag. In **Linked State Trees** on the Bot Setup, choose the tree and parameter overrides for that tag. A patrol point can supply its own tree and values at the same tag. At a point with no override, the patrol task can restore the setup's linked tree and its values. The main tree keeps control of the route.

If you upgraded an existing project, open and save your setup and patrol-point assets to keep their migrated State Tree settings.

[Build a first State Tree](bot_first_steps.md) or [try a different behavior at one patrol stop](bot_guide_04_create_patrols.md).
