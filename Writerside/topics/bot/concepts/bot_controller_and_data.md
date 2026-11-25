# Controllers, Bot Data, and Teams
<primary-label ref="bot"/>

Two guards can share a Character Blueprint and still behave differently. Give each a **Bot Setup** asset. One setup might use a short sight radius and a patrol route, while the other spots targets farther away and roams.

## What Goes Where

| Where                        | What you choose                                                                                                                                                                      |
|------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Character Blueprint          | Set **AI Controller Class** to `NinjaBotAIController` and implement **Get Bot Setup Data** through the **Bot Setup Provider Interface**. Return the setup this character should use. |
| Bot Setup                    | Choose the brain type and its tree. Assign a Sense Profile, an optional Awareness Profile, and a movement adapter if the tree changes speed.                                         |
| Project Settings → Ninja Bot | Choose how the project decides whether two actors are friendly, neutral, or hostile.                                                                                                 |

For everyday decisions, choose a [Behavior Tree](bot_behavior_trees.md) to prioritize branches or a [State Tree](bot_state_trees.md) to move between named states. If your project already has a custom brain component, choose **Custom** and assign its class.

When the controller takes possession of the character, it loads the setup and starts the tree. Editing a shared setup affects every character using it. Duplicate the setup when you want a variation for just one group.

## Who Counts as an Enemy?

The team provider determines the attitude between the bot and the sensed actor. The sense uses **Detection by Affiliation** to decide which attitudes to accept. If a bot ignores a visible player, check both the player's team and the attitudes enabled for Sight.

[Set up native teams](bot_guide_02_team_setup.md) or [use Ninja Factions](integration_bot_factions.md).

## React When the Bot Is Ready

If a widget or gameplay component depends on the guard's senses, check **Has Completed Bot Setup** (`HasCompletedBotSetup`) on its Ninja Bot AI Controller. If it is ready, initialize your component immediately. Otherwise, bind to **On Bot Setup Complete** (`OnBotSetupComplete`) and initialize it when the event fires. This also works for a widget added after the guard has spawned.

## Use Your Own Team or Focus Rules

If your game already tracks teams, create a **Ninja Bot Team Provider** subclass and override `GetTeamId` and `GetTeamAttitude`. The first identifies the actor's team. The second decides how the observing actor regards the target. Select your subclass under **Project Settings → Ninja Bot → Team Provider Class**.

On the controller, **Apply Focus to Perception Target** makes the guard face its selected target. A C++ controller subclass can override `GetFocusPriorityForPerceptionTarget` to choose the priority. To start or end an ability when the selected target changes, use the controller's acquired and dismissed gameplay event tags. See [Bot and Combat](integration_bot_combat.md) for a target-lock example.
