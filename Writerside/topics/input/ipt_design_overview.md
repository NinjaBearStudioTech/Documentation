# Input Design Overview
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>The Input System introduces three new input objects: <b>Input Handlers</b>, <b>Input Setups</b> and the <b>Input Manager</b> component.</li>
        <li><b>Input Handlers</b> are objects that will react to specific <b>Input Actions</b>, from the <b>Enhanced Input</b> subsystem.</li>
        <li><b>Input Setups</b> bundle <b>Input Mapping Contexts</b> to their appropriate <b>Input Handlers</b>.</li>
        <li>The <b>Input Manager</b> processes all <b>Input Setups</b>, so it can <b>route Input Actions to the appropriate Input Handlers</b>.</li>
    </ul>
</tldr>

The Input System was designed to **separate** player input handling logic from Pawn or Character classes. By doing so,
it further enables **reusability** of such logic, even across **different projects**.

## Input Handler

Input Handlers are small objects that will react to certain **Trigger Events**, from specific **Input Actions**. They 
are meant to separate all input handling logic from pawns or characters.

The Input System contains provides many Input Handlers ready to be used. You can also create your own Input Handlers by
extending the `NinjaInputHandler` class.

## Input Setup

Input Setups are **Data Assets** used to bundle an **Input Mapping Context** to all appropriate **Input Handlers**. 
These bundles are provided to the Input Manager either as **default setups** or managed during **runtime**.  

> **Input Setup Management**
> 
> You will find more information regarding the organization and management of Input Setups in the 
> **[Managing Input Setups](ipt_managing_input_setups.md)** page.

## Input Manager

The **Input Manager** is the backbone of the Input System. It's responsible for initializing and maintaining **Input
Setups** and **routing Input Actions to appropriate Input Handlers**.

> **Chain of Responsibility**
> 
> In OOP terms, the Input Manager implements the **Chain of Responsibility** pattern. It allows all Handlers to evaluate
> incoming Inputs to decide on whether they will execute or ignore them.

The Input Manager is also an implementation of the **Ability System Interface**. It will attempt to retrieve the Ability
System Component from the current **Pawn** (regardless if the Input Manager is added to a Pawn or Controller).

This also means that within an **Input Handler**, you can always access the Ability System Component from the Input
Manager provided to all functions.

### Component Initialization

During initialization, the Input Manager will bind itself the **Enhanced Input Subsystem** and load any Input Contexts
provided by default, via the appropriate **Input Setups**.

The component will automatically initialize and, if assigned to a **Player Controller** also re-initialize when a new 
**Pawn** is possessed.

### Input Buffering

The Input Manager can also work as an **Input Buffer**, capturing player inputs while the buffer is open, and executing 
them later on once the buffer closes.

> **Animation-Based Input Buffer**
>
> You will find more information regarding the Input Buffer and its Animation Notify State in the 
> **[Animation-Based Input Buffer](ipt_input_buffer.md)** page.

