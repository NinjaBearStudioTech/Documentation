# Threat and Target Priority
<primary-label ref="bot"/>
<secondary-label ref="experimental"/>

Give a guard a **Threat Manager** when you want actions such as dealing damage or healing an ally to draw its attention. Each guard tracks its own threat totals. A healer can become one guard's highest threat while another guard still focuses on the fighter.

## How Threat Reaches the Guard

The **Threat Manager** on the AI Controller keeps a running total for each source actor. When the lead changes, the manager sends the new leader to that guard's **Threat Sense**. For example, if the fighter has 10 threat and the healer has 6, another 6 from the healer puts the healer ahead.

The Sense Profile decides how that signal competes with sight, hearing, and other senses. Your tree still decides what action to take with the selected actor. If the guard must become **Aware** before it pursues anyone, its awareness settings and chase condition still apply.

## Ways to Generate Threat

| What should draw attention?                                    | What to use                                                                                                                                                                                                                |
|----------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Damage the guard perceives                                     | Add Damage to its Sense Profile and enable **Bind to Damage Sense** on the manager. A successfully perceived damage event adds its strength to the attacker's total.                                                       |
| A gameplay action such as healing                              | Call **Register Threat Source** (`RegisterThreatSource`) on that guard's Threat Manager on the server. Pass the actor that should draw attention and the amount to add.                                                    |
| A role or buff that changes how much threat an actor generates | Implement `IBotThreatModifierInterface` on the source actor and override **Modify Threat Score** (`ModifyThreatScore`). Return the adjusted amount for this action.                                                        |
| A single perception signal, such as a scripted distraction     | Call **Report Threat Event** (`ReportThreatEvent`) with the receiving guard's controller, the actor to sense, and a normalized strength. This sends a stimulus directly and leaves the manager's running totals unchanged. |

[Set up a guard and test two competing threat sources](bot_guide_07_threat.md).
