# Proposed Writerside table of contents

## Reading the outline

The site has three entry points: **Getting Started**, **Plugins**, and **Integrations**. Under Plugins, selecting a plugin opens its **Overview**. Its children are **Setup**, **Concepts**, **Guides**, and the existing **Changelog**, in that order. **First Steps** is a page under Setup, so a new user can go directly from enabling a plugin to seeing it work. Setup, Concepts, and Guides are the only section levels within a plugin. List every page directly in its section so opening the section reveals its full catalog. Link related pages in the text. Each bullet below is a proposed page with its writing brief. Each plugin also keeps its Changelog as a leaf for versioned changes and upgrade notes.

Ninja Bot supplies the editorial pattern. Keep its short description, named Unreal assets, illustrated procedures, and links to the next useful task. Use three topic folders per plugin: `setup`, `concepts`, and `guides`. Put First Steps in `setup` and keep the overview and changelog at the plugin root. Keep advanced details close to the feature they explain. Use straight apostrophes in possessives and contractions, such as character's and don't. Preserve the Blueprint events, native delegates, and overrides that readers use to connect their own gameplay. Give their exact names, say when they fire or what to override, and show a practical use.

| Page type | Common Writerside format |
| --- | --- |
| Overview | Use the plugin name as the page title and apply its primary label. Follow the Bot sequence: What It Does, Main Features, Architecture Overview, Integrations. In Architecture Overview, trace one gameplay example through the assets the reader will edit. End with links to Setup and relevant integration recipes. |
| Setup | Open with prerequisites. Use Bot's checklist columns for step, whether required, and guide. Link shared project settings and distinguish engine features, optional Ninja plugins, and C++-only steps. |
| First Steps | Name the playable or inspectable result and starting project. Use named Writerside procedures, Editor paths, and screenshots at the steps where readers must recognize a result. Finish with a Play In Editor check and Next Steps. |
| Concept | Start with the design decision the page helps the reader make. Follow one example from configuration to observed behavior. Use a small diagram or comparison table where it helps, then link the guide that implements it. |
| Guide | Use the plugin primary label and guide secondary label. Open with the outcome and prerequisites. Use ordered procedures and Bot-style tabs for genuinely alternative routes, such as Behavior Tree and State Tree. End with the expected result and one useful check if it fails. |
| Integration | Use the Integrations primary label and participating plugin labels. Identify what each plugin supplies, required settings on both sides, and a reproducible end-to-end check. Link here from each participating overview. |

## Getting Started

- **Getting Started** — Help readers choose a plugin by the feature they want to build. Keep the multi-plugin setup order as guidance for combined projects, alongside the template recommendation and support contacts.
- **Install and Enable Plugins** — Walk through Launcher and project-source installs, enabling plugins and checking they load. Give C++ module dependencies their own conditional step.
- **Register Assets with the Asset Manager** — Show one primary asset type and scan directory in Project Settings, the equivalent configuration entry, and how to recognize an undiscovered asset.
- **Configure Collision** — Organize channels, profiles, and responses by plugin and purpose. Show how to use a project's existing channel assignments and check both sides of a failed trace or overlap.

## Plugins

### Ninja Bot

- **Overview** — Follow one agent from sensing the player to choosing a target and running a behavior. Introduce the two supported tree workflows.
- **Setup** — Cover AI engine settings, perception configuration and plugin defaults. Point to the Gameplay Debugger before the first playtest.
  - **First Steps: Roam, Detect, and Chase** — Keep the existing Idle, Roam, and Chase example. Give Behavior Tree and State Tree users equivalent checkpoints.

**Concepts**

- **Controllers, Bot Data, and Teams** — Explain which choices belong on the reusable setup asset, what the controller owns at runtime, and how team attitude affects detection.
- **Perception and Awareness** — Follow a stimulus through awareness gain, memory, decay, and target selection.
- **Awareness Targets** — Show how the player receives the highest awareness reading across guards. Name the Blueprint event, component override and native delegate, and link to the per-guard UI guide.
- **Threat and Target Priority** — Explain how damage or other gameplay actions add to each actor's threat total, when a new leader is reported, and how threat competes with the other senses.
- **Behavior Trees** — Show how sensed targets reach the blackboard, how a branch selects a behavior, and where an injected subtree fits.
- **State Trees** — Explain schema choice, context, transitions and linked behaviors. Show where setup parameters and per-patrol-point overrides take effect.
- **Movement Modes and Patrol Paths** — Connect a movement profile to roaming, chasing, path traversal, and optional behavior at a patrol point.
- **Awareness Feedback** — Explain whose awareness a tracker displays, where the ViewModel gets updates, and how the indicator behaves after sight is lost.

**Guides**

- **Set Movement Speeds for Roaming and Chasing** — Author a profile, assign it, and observe the speed change on the First Steps agent.
- **Configure Teams and Attitudes** — Set up native team resolution and compare friendly and hostile targets. Link the Factions integration for the provider alternative.
- **Switch Behaviors at Runtime** — Replace a linked behavior, pass its parameters, then restore the original. Show both tree workflows.
- **Build a Patrol Route** — Place points, assign the path, and add a stop with its own behavior. Verify the agent resumes its route.
- **Tune Detection and Awareness** — Complete the existing guide stub with a sight example. Watch the debugger while the player enters view, breaks sight, and is forgotten.
- **Display an Awareness Indicator** — Complete the UI stub with a tracker bound to the example agent. Test filling, decay, and removal.

- **Make a Guard Respond to Threat** — Give two actors competing threat scores, then use the tree debugger to confirm which actor the guard senses when the lead changes.

### Ninja Combat

- **Overview** — Trace a weapon attack from ability activation through contact, mitigation and feedback. Point readers to melee, ranged, or casting entry points.
- **Setup** — Cover required GAS configuration and collision, plus physical materials where used. Identify optional input, inventory, and ability-system providers.
  - **First Steps: Set Up a Combatant** — Assemble the character, grant starter combat data and inspect the active combatant. Link directly to the first attack guide.

**Concepts**

- **Combatants, Abilities, and Attributes** — Explain the manager, supporting components, ability grants, effects and initial attributes through one attacker and defender.
- **Weapons and Attack Types** — Explain weapon registration and when to use melee scans, projectile actors, hitscans or targeted casts. Cover pooling alongside high-volume projectiles and effects.
- **Targeting and Animation Alignment** — Distinguish target selection, lock anchors and motion warping. Show which part controls facing, position and animation timing.
- **Combos and Action Windows** — Explain how animation windows, input events and combo trees determine the next move. Include how an AI agent advances a combo.
- **Damage, Defense, and Recovery** — Trace incoming damage through mitigation, health, reactions and vulnerable states. Explain when a reaction, stagger, knockdown, riposte or death is eligible.
- **Firearms and Ammunition** — Explain firearm data, fire intent, ammo storage and reloads. Link inventory-backed ammunition to Integrations.

**Guides**

- **Register a Weapon and Land a Melee Hit** — Combine weapon setup and the melee guide. Compare weapon-based and owner-based scans and verify contact within the animation window.
- **Launch a Projectile** — Configure the actor, ability and launch notify. Verify a hit applies the intended effect.
- **Build a Targeted Cast** — Select a target, preview or confirm placement, and execute the cast behavior. Include the canceled path.
- **Build a Branching Combo** — Start with two moves, add a branch, and test input inside and outside the combo window.
- **Lock On and Align an Attack** — Configure a target preset, anchor and marker. Test acquisition, release, and the effect of motion warping on approach.
- **Apply Damage, Hit Reactions, and Death** — Configure damage and defense data. Compare a surviving hit with a fatal hit, and show where physical animation can supply feedback.
- **Block, Evade, and Parry** — Turn the unfinished guides into one defensive encounter. Compare a held block, an evade and a timed parry with a riposte opportunity.
- **Handle Knockdown and Recovery** — Set up fall, grounded and recovery stages. Test recovery and give-up outcomes.
- **Create a Paired Finisher** — Assign attacker and victim roles in a contextual animation, gate the opportunity, and verify both actors exit together.
- **Configure a Firearm and Reload It** — Retain the rifle and shotgun examples to explain differences in firing and hitscan setup. Verify ammunition use and reloading.
- **Display Player and Enemy Vitals** — Bind HUD and overhead widgets to their respective combatants and verify both respond to damage.
- **Drive Combat from AI** — Use the built-in tree support to initiate an action and observe completion. Link Bot and Combat for perception-driven target lock.
- **Diagnose a Failed Attack** — Rework Troubleshooting around a missing grant, missed contact and a hit with no damage. Show which ability debug output or log distinguishes them.

### Ninja Factions

- **Overview** — Explain how faction membership answers “is this actor friendly?” and how reputation can change the answer.
- **Setup** — Register faction assets and identify the project settings for faction lookup and attitude resolution.
  - **First Steps: Give Two Actors Opposing Factions** — Create player and enemy factions, assign their members, and check the attitude returned between them.

**Concepts**

- **Factions and Memberships** — Cover faction assets, the database, the member component and main faction selection. Explain how a controller gets faction data for its pawn.
- **Reputation and Attitude** — Use one relationship to distinguish reputation amount, tier and resolved attitude. Compare the main-faction and target-reputation solvers.

**Guides**

- **Assign and Change Memberships** — Build on the first two factions. Add or remove a membership at runtime and inspect which faction represents the actor.
- **Change Reputation Through Gameplay** — Define tiers, award reputation, and observe a threshold crossing and its attitude result in the debugger.
- **Use Faction Attitude in AI Decisions** — Use the built-in tree checks to choose between friendly and hostile behaviors. Link Bot-specific perception to Integrations.
- **Save and Restore Faction Progress** — Save a changed membership and reputation value. Reload and compare the results with the pre-save state.

### Ninja G.A.S.

- **Overview** — Show what the plugin adds to Unreal's Gameplay Ability System: reusable initialization, ownership choices and grants from data.
- **Setup** — Register setup assets, explain global initialization, and identify where the project's Attribute Sets come from.
  - **First Steps: Give a Character an Ability System** — Choose character or Player State ownership, assign setup data and inspect the initialized component.

**Concepts**

- **Ownership and Initialization** — Explain the owner and avatar through possession and pawn replacement. Map the provided base classes to those choices.
- **Setup Data, Bundles, and Loading** — Distinguish startup attributes, effects and abilities. Explain when deferred loading affects the point at which grants are usable.

**Guides**

- **Grant Starting Attributes and Abilities** — Use a project-provided Attribute Set, initialization values and an ability. Verify the resulting value and grant on the intended owner.
- **Play a Local Gameplay Cue** — Trigger a cosmetic cue through the supplied local cue support and check which client sees it.
- **Use Ability System Data in AI** — Drive a tree decision with an attribute or tag and exercise the appropriate tree support. Show where to inspect the value used by the decision.

### Ninja Input

- **Overview** — Follow one Enhanced Input action from a mapping context to a handler. Introduce reusable setups, remapping and device-aware controls.
- **Setup** — Cover Enhanced Input settings and removing duplicate template input. Separate optional user settings and Common UI setup from the basic path.
  - **First Steps: Move a Template Character** — Create the setup, attach the manager, and verify movement and look after possession.

**Concepts**

- **Input Setups and Ownership** — Explain controller defaults, pawn-provided setups, mapping priority, forward reference and what changes on possession.
- **Handlers and Trigger Events** — Match handler choice and trigger phase to movement, one-shot actions, held actions and UI events.
- **Input Modes, Remapping, and Preferences** — Distinguish the active device, player-mappable keys and settings such as sensitivity. Explain which settings persist.
- **Input Buffering** — Walk through an early input being stored, consumed or discarded when the action window closes.

**Guides**

- **Create a Handler and Switch Input Setups** — Add one action for a controllable pawn and swap setups at runtime. Verify the previous mapping stops firing.
- **Build a Key Remapping Menu** — Mark actions as mappable, assemble entries and categories, change a key, save it and restore defaults.
- **Adapt Controls to the Active Device** — Change a prompt when switching between mapped keyboard and gamepad input. Apply a player preference through an input modifier.
- **Buffer an Action** — Open and close a buffer around an unavailable action. Test an early press and a press after the window expires.
- **Diagnose Missing or Duplicate Input** — Trace action, active context, manager and handler with on-screen messages and logs. Include the template double-binding case.

### Ninja Interaction

- **Overview** — Follow a player approaching an object, selecting it and completing its behavior. Introduce the roles of Smart Objects, abilities and State Trees.
- **Setup** — Cover GAS, Smart Objects, collision and the State Tree requirements for authored flows.
  - **First Steps: Interact with a Nearby Object** — Configure one source and target using the provided assets. Detect the target, execute its behavior, and confirm the slot becomes available again.

**Concepts**

- **Sources, Targets, and Selection** — Explain discovery volumes, target eligibility and selection when several objects are in range.
- **Smart Object Slots and Interaction Flow** — Trace claim, approach, alignment, execution and release. Use the relevant State Tree tasks and abilities at each stage.
- **Traits, Duration, and Feedback** — Explain where interaction-specific data lives and how it affects animation choice, timing and prompts.

**Guides**

- **Build an Interaction with a State Tree** — Customize the default flow to reach, face and use a target. Check exit and release on interruption.
- **Show a Prompt and Timed Progress** — Bind an actor or HUD prompt, configure duration and test completion and cancellation.
- **Animate an Interaction** — Choose a montage through a Chooser Table and play it at the appropriate stage of the interaction.
- **Make a Lockable Door** — Configure open, close and unlock behavior, key resolution and cosmetic updates. Try the door with and without a valid key.

### Ninja Inventory

- **Overview** — Follow an item from pickup to storage, use or equipment. Introduce layout and UI choices through that same item.
- **Setup** — Cover asset discovery, GAS requirements and initial inventory attributes.
  - **First Steps: Give a Character a Starting Item** — Initialize an owner, add a default container and item, and verify the result in the Gameplay Debugger.

**Concepts**

- **Owners, Containers, and Layouts** — Explain the inventory owner and avatar, then compare simple slots, equipment slots and spatial footprints with a bag, holster and backpack.
- **Items, Fragments, and Eligibility** — Distinguish shared definitions from per-item state. Use stack size, weight and prerequisites to explain storage and use decisions.
- **Inventory Operations and Events** — Trace an add, move or removal through eligibility, placement and notification. Cover failed placement and stranded items.
- **Equipment and Appearance** — Explain eligibility, instances, attachment, equipped states, animation layers and tag-driven visibility.
- **Shared Inventories and Loot** — Distinguish generating loot, viewing another owner's containers and transferring items through an authorized session.
- **Inventory Widgets and ViewModels** — Map container, item and fragment data to the widgets that display them. Explain how widgets stay current when an item moves.

**Guides**

- **Create a Stackable Item and Pickup** — Author fragments, place a pickup, collect it twice and inspect the resulting stack.
- **Build a Standard Slot-Based Inventory** — Give the First Steps character a six-slot bag using Simple Layout. Bind a slot widget to each entry and collect six distinct items in play. Try a seventh, free a slot, and pick it up again to verify capacity and UI updates.
- **Build a Spatial Grid Inventory** — Give the First Steps character a backpack using Spatial Layout. Set the grid size, define item footprints with the Dimensions Fragment, and display them at the correct size and position. In play, try placing a two-cell item in separated empty cells, then rearrange the contents so it fits. Demonstrate rotation if enabled.
- **Equip an Item and Change Its Appearance** — Add an equipment slot, attach the spawned actor and switch its equipment state. Check visibility on equip and unequip.
- **Use, Store, and Drop Items** — Drive the stock item abilities with a selected item. Show an eligible use, a rejected use, and a drop into the world.
- **Build Tooltips and Drag-and-Drop** — Display fragment-backed values, drag between valid slots and exercise a rejected drop.
- **Open a Shared Loot Container** — Generate loot, open a session, display available items and transfer one. Verify the change on both inventories and close the session.
- **Save and Restore an Inventory** — Round-trip containers, items and their mutable state. Check placement and equipment after loading.

## Integrations

Keep this section at site root, alongside Plugins. Keep the existing topic filenames so inbound links keep working. The proposed additions below each solve a configuration problem spanning two or more plugins.

**Existing pages**

- **Bot and Combat: Lock On to a Sensed Target** — Match acquired and dismissed gameplay event tags between controller and ability. Test acquisition and loss.
- **Bot and Factions: Resolve Teams for Perception** — Configure the faction-aware provider, explain automatic detection and check attitudes for two known memberships.
- **Combat and Factions: Configure Friendly Fire** — Connect faction attitude to damage mitigation. Repeat the same hit against an ally and an enemy.
- **Combat and Input: Drive Combat Abilities** — Bind attacks, combos, targeting and fire intent. Put buffering and temporary input suppression beside the actions they affect.
- **Combat and Inventory: Fight with Equipped Weapons** — Connect equipped actors to the weapon manager and ammunition storage. Test switching weapons, firing and reloading.
- **Input and Interaction: Start and Cancel an Interaction** — Bind one action to an eligible target and check release before a timed interaction commits.
- **Input and G.A.S.: Activate an Ability from an Action** — Connect a handler to the actor's ability system. Show press, release or cancellation as appropriate, then reuse the pattern for an inventory action.

**Additional pages**

- **G.A.S. with Combat and Inventory: Initialize Plugin Attributes** — Move the existing G.A.S. attributes guide here, preserving its initialization tables and ability bundles. Provide independent Combat and Inventory paths and verify a value on each.
- **Interaction and Inventory: Collect an Item from an Interactable** — Proposed worked example. Connect successful interaction to pickup transfer and test a full inventory before deciding when the world pickup disappears.

## Regeneration notes

| Block | What to reuse and what needs writing |
| --- | --- |
| Bot | Preserve the existing walkthroughs, diagrams and tree alternatives. List Awareness Targets beside Perception and Awareness in Concepts so readers can find its notifications. Use the completed awareness setup and UI guides as examples of how to connect those hooks to gameplay. |
| Combat | Retain the existing weapon, attack, casting, combo, damage, finisher, firearm and widget procedures. Block, evade, parry, and hit reactions/death are commented out of the tree and need authored examples. Use the Showcase reaction and fatal-damage examples as starting material. |
| Factions | The How-To branch is hidden and its pages are placeholders. Build the visible guides from the membership, reputation, save/load and debugger pages. Fold database and solver choices into Concepts. |
| G.A.S. | Split Architecture by ownership and authoring decisions. Move the plugin-specific attributes example to Integrations. The batch activation stub needs a demonstrated user workflow before it earns a page. |
| Input | The Input block has four concepts and five guides. Keep the handler overrides, pawn interfaces, buffer controls, device-change delegate, and save notifications with the workflows that use them. |
| Interaction | Use the individual ability, task and evaluator pages as source material for the lifecycle and worked State Tree. Retain useful node names as procedure steps or compact lookup tables. Link to the Input and Interaction walkthrough under Integrations. |
| Inventory | All four existing Guides entries are stubs. Use the populated layout, equipment, operation, ability and UI pages to supply the examples. Keep Mutable equipment out of the proposed tree pending a worked example. |
| Showcase | The unlisted Showcase series contains worked examples for input, attributes, attacks, reactions, UI and inventory. Reuse current steps and screenshots under the corresponding guides or integrations. Preserve credits with reused sample assets and verify older examples against the version being documented. |

**Suggested review order.** Approve the Bot block and shared page format first. Regenerate Factions next to test the format on a small plugin with unfinished guides. Use Inventory as the test for a larger block, especially the separation between concepts, playable examples and cross-plugin instructions. During implementation, reuse existing topic filenames for surviving pages and redirect retired links to the page or section that takes over their content.
