# Behavior Trees
<primary-label ref="bot"/>

Choose a Behavior Tree when your bot should repeatedly pick the highest-priority action it can perform. A guard can chase a target, roam when it has none, and wait if it cannot find anywhere to go.

## Give Branches the Information They Need

Add the **Update Perception** service to the top selector so it runs while any branch is active. Map its **Sensed Actor** output to an Actor object key in the Blackboard. A chase branch can check that key and feed it to **Move To**. Use **Last Known Location** for a search and **Awareness Level** if a glimpse should only make the guard suspicious.

Place Chase to the left of Roam. Set the chase condition's **Observer Aborts** to **Both** so acquiring a target interrupts roaming and losing the target ends the chase. Watch the active branch and Blackboard together during play.

## Share a Branch Across Bots

Use **Run Behavior Dynamic** where a branch varies by guard. Give the task a gameplay tag and choose its fallback tree. In **Bot Setup → Dynamic Behavior Trees**, assign the same tag to a different tree for a specialist guard. Keep the Blackboard compatible across the trees.

[Build the first tree](bot_first_steps.md) or [switch behaviors at runtime](bot_guide_03_dynamic_behaviors.md).
