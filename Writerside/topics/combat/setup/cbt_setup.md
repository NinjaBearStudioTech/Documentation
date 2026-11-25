# Set Up Ninja Combat
<primary-label ref="combat"/>

Enable Ninja Combat and Unreal's Gameplay Ability System (GAS). You can use your project's existing Ability System Component. Ninja G.A.S., Ninja Input, and Ninja Inventory are optional.

## Setup Checklist

| Step | Why it matters |
| --- | --- |
| [Install the plugin](installing_plugins.md). In C++, add the modules whose public classes you use. | Blueprint projects can configure combat directly in the editor. |
| Set the GAS globals and Gameplay Cue Manager below. | Damage effects need Combat's effect context, and cues provide hit feedback. |
| Apply the [collision settings](collision_settings.md) and configure the target mesh or hit shapes to use the **Combat** preset. | Melee scans and projectile queries need a target they can detect. |
| [Set up a combatant](cbt_first_steps.md) and initialize its attributes. | A visible character needs a working ability system and health before you can test damage. |

<procedure title="Configure the Gameplay Ability System">
    <step><p>In <b>Project Settings → Gameplay Ability Settings</b>, use <code>NinjaCombatAbilitySystemGlobals</code> for the globals class and <code>NinjaCombatGameplayCueManager</code> for the cue manager. If your project provides its own versions, derive them from the Combat classes.</p></step>
    <step><p>Include the folders containing your Gameplay Cues in the Gameplay Cue scan paths. Restart the editor after changing the globals.</p></step>
</procedure>

You can also set the classes in **Config/DefaultGame.ini** using the project configuration below.

<code-block lang="ini" src="cbt_gas_global_settings.ini"/>

## Surface-Specific Impacts

If hitting wood should sound different from hitting stone, define the surfaces in **Project Settings → Physics → Physical Surface**. Create a Physical Material for each, select its surface type, and assign it to the material or collision body the trace hits. Use those surfaces as entries in the [firearm impact table](cbt_guide_firearms.md).
