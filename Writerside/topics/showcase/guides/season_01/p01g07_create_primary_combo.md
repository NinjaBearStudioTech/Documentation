# Create a Combo
<secondary-label ref="guide"/>

The **Combo System** is used to trigger attack sequences that can even branch out depending on different inputs. In this
guide you will learn more about it and how to mix **Attack** and **Cast** abilities in a combo.

## Create a basic Combo

<video src="https://youtu.be/2dghAUw1v5s" preview-src="sc_thumbnail_p01g07a.png" width="800" />

In this first part of the Combo guide, the default **Attack Ability** created before will be converted into a combo.
This will give you an overview of the combo system, its configuration and main objects.

<procedure title="Configure the Combo Window" collapsible="true">
    <step>Open the Animation Montage used for the <b>Primary Attack</b>.</step>
    <step>Add the <b>Combo Window</b> notify state, covering the frames in the animation that will allow the combo to advance.</step>
</procedure>

<procedure title="Configure additional attack animations" collapsible="true">
    <step>Create Animation Montages for all other attacks that will be used in the combo.</step>
    <step>Add the Combo Window notify state to all these animations.</step>
</procedure>

<procedure title="Create additional attack abilities" collapsible="true">
    <step>As done before, configure all your attack abilities using the new animations.</step>
    <step>Configure the <b>Ability Tags</b> for the attack abilities, following a cohesive pattern, such as: <code>Ability.Attack.Combo.Primary.A</code>, <code>Ability.Attack.Combo.Primary.B</code>, or something similar.</step>
    <step>Remove unnecessary ability tags from the original Attack Ability, since it won't be activated directly from input anymore.</step>
</procedure>

<procedure title="Configure the State Tree" collapsible="true">
    <step>Create a new State Tree, using the <b>CombatComboComponentSchema</b>.</step>
    <step>If you are using Unreal Engine 5.3, add the <b>Combo Component</b> evaluator to the tree and bind the Actor input parameter to the one available in the <b>state tree context</b>.</step>
    <step>Add the <b>Combo State</b> evaluator and bind the Combo Manager input parameter to the one exposed yb the <b>Combo Component evaluator</b> or from the <b>context</b>.</step>
    <step>Create a new child state from the root, and set it as a <b>state</b> and configure the <b>Selection Behavior</b> to <b>Try Select Children in Order</b>. Name it <b>Primary Attacks</b>.</step>
    <step>Create a new child state in the group and name it <b>Primary Attack 01</b>, or any other meaningful name that you prefer. Create all primary attack states for your combo in the same way.</step>
    <step>Add an <b>Integer Compare</b> check to the <b>Entry Conditions</b> list. Set the left side to the <b>Combo Count</b> from the Combo State evaluator and the right value to <b>0</b>, which is the very first possible combo count.</step>
    <step>Add an <b>Activate Combo Ability</b> task to the Task list. Set the activation tag to <code>Ability.Attack.A</code>, as it was set in the Ability Activation Tags. Configure the Task to <b>increment</b> the Combo Count.</step>
    <step>Add an <b>Event Transition</b> to the list of <b>Transitions</b>, based on the <code>Combat.Event.Combo.Attack.Primary</code> tag. Set the transition to go to Attack 02.</step>
    <step>Add a <b>Finished Transition</b> to the list of <b>Transitions</b>, Set this transition to complete the State Tree.</step>
    <step>Repeat steps 6 to 9 for each other attack, ensuring that the Entry Conditions are updated correctly and the Event Transitions move to the correct next step. The last attack only has the "Finished" transition.</step>
    <img src="cbt_combo_light_attacks_state_tree.png" alt="Light Attacks" border-effect="line" thumbnail="true" width="600"/>
</procedure>

<procedure title="Create the combo ability" collapsible="true">
    <step>Create a new Gameplay Ability, using <code>CombatAbility_Combo</code> as the base.</step>
    <step>Set the state tree configured in the previous step.</step>
    <step>Add all abilities used by the combo to the list of abilities.</step>
    <step>Configure the Ability Tags, adding <code>Ability.Combo</code>, so it can be used for activation.</step>
    <step>Configure the Blocked Ability Tags, adding <code>Ability.Attack.Secondary</code>.</step>
    <img src="cbt_combo_ability_01.png" alt="Combo Ability for main attacks" border-effect="line" thumbnail="true" width="600"/>
</procedure>

<procedure title="Update the Ability Setup" collapsible="true">
    <step>Remove previous attacks, that are now part of the combo, and were added to the Ability Setup.</step>
    <step>Add the combo attack do the ability setup.</step>
    <tip>All attacks that are part of the combo will be added by the combo itself.</tip>
</procedure>

<procedure title="Configure combo inputs" collapsible="true">
    <step>Adjust your <b>Primary Attack</b> Input Handler, updating the Activation Tags for the Combo Ability.</step>
    <step>Add a new Input Handler to your list of Handlers, using the <b>GAS: Send Gameplay Event</b>.</step>
    <step>Set the <b>Primary Attack</b> Input Action and <code>Combat.Event.Combo.Attack.Primary</code> tag as the event.</step>
</procedure>

<procedure title="Add the Combo Manager" collapsible="true">
    <step>Open your Character Blueprint and add a <b>Combo Manager</b>.</step>
    <step>Implement the <b>Get Combo Manager</b> function from the Combat System interface, returning the new component.</step>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press play and then press your attack button.</step>
    <step>In the appropriate combo window, continue pressing the attack and the next attacks should follow.</step>
</procedure>

## Cast Ability and Combo Branching

<video src="https://youtu.be/-la0XirPPyc" preview-src="sc_thumbnail_p01g07b.png" width="800" />

In this second part of the Combo guide, a new **Cast Ability** will be created to show different kinds of abilities 
being added to the combo. Then we can use it to **branch** between **primary** and **heavy** attacks.

<procedure title="Create the damage effect for the Heavy Attack" collapsible="true">
    <step>Create a Gameplay Effect based on <code>CombatEffect_MeleeHit</code>.</step>
    <step>Add a <b>Calculation Modifier</b> to the list of <b>Executions</b>.</step>
    <step>
        <p>Set <code>Combat.Data.Damage.Multiplier</code> as the <b>Backing Data</b> and a higher magnitude. In this example, we are using <code>2.0</code>.</p>
        <img src="cbt_combo_heavy_damage.png" alt="Cast Damage" border-effect="line" thumbnail="true" width="600"/>
    </step>
</procedure>

<procedure title="Create the damage effect for the Cast Attack" collapsible="true">
    <step>Create a Gameplay Effect based on <code>CombatEffect_MeleeHit</code>.</step>
    <step>Add a <b>Calculation Modifier</b> to the list of <b>Executions</b>.</step>
    <step>
        <p>Set <code>Combat.Data.Damage.Multiplier</code> as the <b>Backing Data</b> and a higher magnitude. In this example, we are using <code>5.0</code>.</p>
        <img src="cbt_combo_cast_damage.png" alt="Cast Damage" border-effect="line" thumbnail="true" width="600"/>
    </step>
</procedure>

<procedure title="Create the additional attack ability" collapsible="true">
    <step>Following the same steps as before, create a new attack that will be used as a Heavy Attack.</step>
    <step>Set the Melee Damage Effect to the one created above, for the <b>Heavy Attack</b>.</step>
</procedure>

<procedure title="Configure the cast attack animation" collapsible="true">
    <step>We also need an <b>Animation Montage</b> for a Cast Attack, where the character will perform an explosive attack.</step>
    <step>At the appropriate frame, we'll add the <b>Cast</b> Animation Notify, which is used by the Cast Ability to spawn the Cast Actor.</step>
</procedure>

<procedure title="Create a Cast Actor" collapsible="true">
    <step>Create a new Blueprint based on <code>NinjaCombatCastActor</code>. This actor will be spawned by the Cast Ability.</step>
    <step>Set the original <b>Cast Sphere</b> radius to <code>200</code>. This is the area of the effect, where targets will be collected.</step>
    <step>Set the <b>Time To Live Outside Pool</b> property to <code>5.0</code>. This will be used later on when we configure the <b>Actor Pool</b> component.</step>
    <step>Add a <b>Niagara Particle System Component</b>, used to represent the effect. Set the desired effect asset.</step>
    <step>Add an <b>Audio Component</b>, to play the effect sound. Set the desired sound asset.</step>    
    <step>
        <p>Create a <b>function</b> called <code>SetLocationFromShieldLocation</code>. It will be used to place this Cast Actor where the shield currently is.</p>
        <img src="cbt_create_cast_actor_01.png" alt="Set Location From Shield Location" border-effect="line" thumbnail="true" width="600"/>
    </step>
    <step>
        <p>In the <b>Event Graph</b>, implement the <code>StartCast</code> event, defined by the base class. The goal is to adjust the location using the function from the previous step, track when the VFX is finished so we can eventually return the actor to the pool, and activate all systems.</p>
        <img src="cbt_create_cast_actor_02.png" alt="Cast Event Graph" border-effect="line" thumbnail="true" width="600"/>
    </step>
    <tip>For better gameplay results, make sure that your <b>particle effect size</b> and <b>collision radius</b> are compatible!</tip>
    <note>When implementing the <code>StartCast</code> event in the <b>Event Graph</b>, make sure to always call the parent implementation!</note>
    <note>If all your Cast Actors will include VFX and SFX, you can create a base Blueprint or C++ with those components, and always extend from this version instead.</note>
</procedure>

<procedure title="Create a Cast Ability" collapsible="true">
    <img src="cbt_combo_cast_ability.png" alt="Combo Cast Ability" border-effect="line" thumbnail="true" width="600"/>
</procedure>

<procedure title="Update the Combo Ability" collapsible="true">
    <step>Add the new heavy abilities - Attack and Cast - to the Combo Ability, so they are automatically added along with the Combo Ability itself.</step>
    <img src="cbt_combo_ability_02.png" alt="Combo Ability for heavy attacks" border-effect="line" thumbnail="true" width="600"/>
</procedure>

<procedure title="Update the State Tree" collapsible="true">
    <step>Following the same steps as before, add the Heavy Attack state and appropriate specific states to the <b>State Tree</b>.</step>
    <img src="cbt_combo_heavy_attacks_state_tree.png" alt="Light Attacks" border-effect="line" thumbnail="true" width="600"/>
</procedure>

<procedure title="Configure combo inputs" collapsible="true">
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press play and start your combo.</step>
    <step>After two light attacks, press the secondary attack button. The combo will branch to the first heavy attack.</step>
    <step>Start your combo again and after three light attacks, press the secondary button. The combo will branch to the cast attack.</step>
</procedure>