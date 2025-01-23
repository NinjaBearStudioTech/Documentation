# Input Buffer
<primary-label ref="input"/>
<secondary-label ref="advanced"/>

<tldr>
    <ul>
        <li>The <b>Input Buffer</b> is an <b>animation-based</b> mechanism, used to store player input, while the buffer is <b>open</b>, and trigger it later when it <b>closes</b>.</li>
        <li>The <b>Input Buffer</b> uses <b>channels</b> that can store different types of actions, such as <i>movement</i> and <i>combat</i>.</li>
        <li>It is defined by the <code>InputBufferInterface</code>. The <b>Input Manager Component</b> is a valid implementation of this interface.</li>
        <li>You can control the buffer state using the <b>Input Buffer</b> Animation Notify State, on <b>Animation Montages</b>.</li>
        <li>The <b>Input Manager Component</b> allows you to decide if you want to capture the <b>first</b> or the <b>last</b> player input.</li>
    </ul>
</tldr>

The Input System offers an **Input Buffer** that allows deferring the execution of Input Handlers to a **later moment**.

This is particularly useful in combat systems where players might press keys during animations that cannot be interrupted, 
yet the game should still register these inputs to ensure responsiveness.

> **Animation Compatibility**
>
> The Input Buffer Anim Notify State can only be used in **Animation Montages**. This ensures full compatibility with 
> the Ability System Component, and montages that might be played, and also scaled by it.
{style="note"}

## Input Buffer Design

The buffer is implemented using the _Command_ design pattern: Inputs that cannot be handled immediately are encapsulated 
in a **Command** structure, which can be executed later when the buffer is closed.

> **Command**
>
> In OOP terms, the Input Buffer implements the **Command** pattern. Incoming Input Actions and their values are 
> converted into a command structure that can be executed later on.

The Input Buffer is _Animation-Based_, meaning it is opened and closed at specific points during an animation, controlled 
through an Animation Notify State.

Although the Input Manager Component manages the buffer by default, the Input Buffer functionality is defined by the 
`InputBufferInterface`. Any component that implements this interface can be engaged by the animation, provided it is
enabled.

You can also disable the Input Manager's buffer if you wish to replace it with your own custom Buffer Component, 
making the system highly flexible.

> **Buffer, not Queue**
>
> The default Input Buffer provided by the system is a **Buffer**, not a **Queue**. This means only one command will be 
> executed when the buffer closes, rather than processing all commands in the order they were received.

## Using the Input Buffer

To buffer actions, follow these steps:

1. Enable the `Can Be Buffered` property on any Input Handlers you wish to add to the Input Buffer.
2. Define the correct **Channel** for the buffer. If you don't need multiple channels, just use the default one.
3. Add the Notify State to an animation that supports buffering inputs.

### Enabling Input Handlers for Buffering

To allow an Input Handler to be buffered, enable its `Can Be Buffered` property when registering the Input Handler to a 
`UNinjaInputSetupDataAsset`.

![Activating the buffer on Handlers](ipt_input_buffer_enable_handler.png "Activating the buffer on Handlers")

> **You are buffering Input Actions**
>
> Although you mark **Input Handlers** as "_buffered_", conceptually, it is the **Input Action** that gets buffered by 
> the Input Manager Component. This means the Input Manager Component will collect all buffer-able handlers triggered by 
> an Input Action while the buffer is active and invoke them later when the buffer is closed.

### Opening and Closing the Input Buffer in Animations

The most straightforward way to open and close the Input Buffer is by using the **Input Buffer** Animation Notify State. 
Make sure to define the correct **channel** in the Animation Notify State.

![Placing the Buffer AnimNotifyState](ipt_input_buffer_animation.gif "Placing the Buffer AnimNotifyState")

> **Scrubbing Animations**
>
> When placing the Input Buffer Animation Notify State, hold the **shift** key to smooth scroll and preview the animation 
> simultaneously.

Once the state **Begins**, the Input Buffer will open, and the Input Manager Component will stop routing Input Actions 
to Handlers. Instead, it will store any handlers that would have been triggered, along with their current Input Action 
Values, based on the buffering policy in place.

Once the state **Ends**, the Input Buffer will close, and any stored Input Handlers related to a saved Action will be 
invoked using the previously saved values.

> **Avoid the first or last frames**
>
> Notifies and Notify States may occasionally fail to be invoked when placed on the very first or last frame of an 
> animation. It's recommended to place them a couple of frames before the end.
{style="warning"}

### Externally Opening and Closing the Buffer

While the method above is the primary way to interact with the Buffer, you can open and close the buffer in other ways 
using the `InputBufferInterface`.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_input_buffer_blueprint.png" alt="Add a container to the inventory" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="ipt_use_input_buffer.h"/>
        <br/>
        <code-block lang="c++" src="ipt_use_input_buffer.cpp"/>
    </tab>
</tabs>

## Default Input Buffer Implementation

The `UNinjaInputBufferComponent` is the default implementation of the `InputBufferInterface` and provides an additional 
feature: the **Buffering Policy**.

There are three possible values for this policy:

- **Last Command**: All Input Actions will be processed until the buffer is closed. When that happens, the **last Action** processed will be the one executed. This is the default mode.
- **First Command**: Once the first valid Input Action is saved, no other Actions will be kept, and this **first Action** will be the one executed.
- **Disabled**: Disables the Ninja Input Buffer and allows another custom buffer to take over.

> **Supporting policies in custom buffers**
>
> If you want to support the same policies in your custom Input Buffer implementation, you can use the `EInputBufferMode` 
> enumeration.

## Creating New Input Buffers

You can create your own Input Buffer by creating an Actor Component that implements the `InputBufferInterface`.

If you choose this route, ensure that the Input Manager Component's Buffer is **disabled** and that your custom component 
is **enabled** using the appropriate interface method.

Another option is to create your component as a subclass of the `NinjaInputBufferComponent`, which already implements 
the necessary interface and provides additional utility methods.

This approach allows you to implement only the functions relevant to your scenario, such as `BufferInputCommands`, which 
decides if a command should be buffered.

### The FBufferedInputCommand Struct

Commands stored in the buffer are represented by the `FBufferedInputCommand` struct.

The main Input Manager Component creates these instances when input handlers are routed to the buffer instead of being 
processed immediately. The `BufferInputCommands` function receives an array of commands because all the commands in that 
array were triggered by the same Action and Event, so they represent a **single** player input.
