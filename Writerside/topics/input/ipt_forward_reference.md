# Forward Reference
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>For inputs that require a global reference, such as top-down movement, a <b>Forward Reference</b> is required.</li>
        <li>The Input Manager can <b>automatically create</b> a Forward Reference or use a predefined <b>Scene Component</b>.</li>
    </ul>
</tldr>

Certain usage scenarios, such as a **top-down game with WASD movement** will require an anchor that can be used as a 
reference to the movement inputs. For such cases a **Forward Reference** is necessary. 

The Forward Reference is a <b>Scene Component</b> that always points _North_ (or _Positive X_), instead of following the
**character rotation**. This means it has <b>absolute rotation</b>.

The most common Scene Components for this are a **Camera** or an **Arrow Component**.

## Providing the Forward Reference

You can provide your own Forward Reference by **tagging** a Scene Component with `InputForwardReference`. By doing so,
the Input Manager Component will acquire and store this reference, when the Pawn is possessed.

<tabs group="sample">
    <tab title="Blueprint">
        <img src="ipt_forward_arrow.png" alt="Forward Arrow Reference" border-effect="line"/>
    </tab>
    <tab title="C++">
        <code-block lang="c++" src="ipt_forward_arrow.h"/>
        <br/>
        <code-block lang="c++" src="ipt_forward_arrow.cpp"/>
    </tab>
</tabs>

## Automatic Creation

The **Input Manager** can create a Forward Reference automatically. For that, you need to mark the appropriate option,
`bShouldCreateForwardReference`. 

When that property is enabled, the Input Manager will attempt to find a Forward Reference first and if none was found,
it will create an **Arrow Component**.

### Overriding the Default Scene Component

If you need to modify or completely change the **Scene Component** created by the Input Manger, override the 
`CreateForwardReference` function, either in Blueprints or C++.