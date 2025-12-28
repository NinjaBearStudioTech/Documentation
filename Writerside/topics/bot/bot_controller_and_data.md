# AI Controller and Data
<primary-label ref="bot"/>

<tldr>
    <p><b>Summary: AI Controller and Data</b></p>
    <br/>
    <ul>
        <li>Ninja Bot defines AI behavior through a shared controller and reusable data assets.<</li>
        <li>Perception, awareness, and bot-specific behavior are configured through data, not code.</li>
        <li>Bot pawns remain fully project-defined and unconstrained.</li>
    </ul>
</tldr>

Once the [perception and awareness models](bot_perception_and_awareness.md) are established, the next step is to **define 
bots through data**. 

In Ninja Bot, AI agents are assembled by combining a **shared AI controller**, a **data asset that aggregates bot configuration**, 
the **decision asset** (Behavior Tree, State Tree or other solutions) and a project-specific pawn class.

This approach allows multiple bots to **share the same controller logic** while expressing their differences entirely through 
data. Ninja Bot does not impose requirements on the pawn class, allowing projects to use any character, creature, or actor 
setup that fits their needs.

## Bot Controller

The Ninja Bot AI Controller is responsible for **initializing** and **orchestrating** the decision and perception components. 
It provides a consistent runtime environment for all bots, ensuring that all components are set up correctly.

## Bot Data Asset

The Bot Data Asset defines how an individual bot behaves within the Ninja Bot framework. It aggregates perception profiles, 
awareness profiles, and other bot-specific configuration into a reusable data-driven definition.