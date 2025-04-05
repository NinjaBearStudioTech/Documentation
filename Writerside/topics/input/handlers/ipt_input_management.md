# Input Management
<primary-label ref="input"/>

The Input System was designed to **separate** player input handling logic from Pawn or Character classes. By doing so,
it further enables **reusability** of such logic, even across **different projects**.

## Input Handler

Input Handlers are small objects that will react to certain **Trigger Events**, from specific **Input Actions**. They 
are meant to separate all input handling logic from pawns or characters.

The Input System contains provides many Input Handlers ready to be used. You can also create your own Input Handlers by
extending the `NinjaInputHandler` class.

Input Handlers are bundled along with their respective Mapping Context in an **[Input Setup](ipt_input_setup.md)**. Input
Handlers can also be buffered using the **[Animation-Based Input Buffer](ipt_input_buffer.md)**.

## Input Manager

The **Input Manager** is the backbone of the Input System. It's responsible for initializing and maintaining **Input
Setups** and **routing Input Actions to appropriate Input Handlers**.

> **Chain of Responsibility**
> 
> In OOP terms, the Input Manager implements the **Chain of Responsibility** pattern. It allows all Handlers to evaluate
> incoming Inputs to decide on whether they will execute or ignore them.

The Input Manager can be added to the **Player Controller**, which is recommended, or **Pawn/Character**. Regardless, 
you can always access the Pawn related to the Input Manager by calling `GetPawn`.

The Input Manager is also an implementation of the **Ability System Interface**. It will attempt to retrieve the Ability
System Component from the current **Pawn**.

In an **Input Handler**, the Ability System Component can be obtained from the **Input Manager**, using the 
`GetAbilitySystemComponent` function, available in both Blueprint and C++.

### Component Initialization

During initialization, the Input Manager will bind itself the **Enhanced Input Subsystem** and load any Input Contexts
provided by default, via the appropriate **Input Setups**.

The component will automatically initialize and, if assigned to a **Player Controller** also re-initialize when a new 
**Pawn** is possessed.

### Input Buffering

The Input Manager is a valid implementation of the **[](ipt_input_buffer.md)**. It can capture player inputs 
while the buffer is open, and executing them later on once the buffer closes.
