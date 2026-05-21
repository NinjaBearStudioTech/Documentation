# Ninja Tokens
<primary-label ref="tokens"/>

![Ninja Tokens](tkn_feature.png "Ninja Tokens")

**Ninja Tokens** is a lightweight AI coordination plugin for Unreal Engine. It helps prevent too many AI agents from 
performing the same action at the same time by giving targets a configurable token budget.

The plugin is designed for combat and encounter scenarios where multiple agents may want to attack, flank, cast, interrupt, 
or perform other coordinated actions around the same target.

## What It Does

- Provides a reusable **token budget** system for AI coordination.
- Prevents groups of agents from overcrowding the same action at the same time.
- Uses **Gameplay Tags** to define independent action channels.
- Supports fair and predictable token queues.
- Integrates with **Behavior Trees** and **State Trees**.
- Avoids ticking and timers by resolving expiration opportunistically.
- Provides diagnostics through **Visual Logger** and **Unreal Insights**.

## Main Features

- **Tag-Based Token Budgets**: Define independent action channels using Gameplay Tags, such as attack, flank, cast, or defend.
- **Per-Target Coordination**: Each target owns its own token budget and queues, allowing agents to coordinate around specific actors.
- **Request and Queue Flow**: Agents can request tokens, receive them immediately when capacity exists, or wait in a queue.
- **Priority and FIFO Resolution**: Higher-priority requests are handled first, while equal-priority requests preserve arrival order.
- **TTL Without Ticking**: Time-to-live policies are enforced during later token interactions, avoiding per-frame overhead.
- **Behavior Tree Support**: Provides tasks and decorators for requesting, returning, and checking tokens.
- **State Tree Support**: Provides tasks and conditions for using token coordination in State Tree workflows.
- **Diagnostics**: Integrates with Visual Logger and Unreal Insights to help inspect token behavior.

## Architecture Overview

Ninja Tokens is organized around targets, token budgets, requests, and queues.

A target owns one or more token budgets, usually separated by Gameplay Tag. Each budget defines how much capacity is available for a type of action. When an AI agent wants to perform an action, it requests a token from the target using the relevant tag and cost.

If enough capacity is available, the request is granted immediately. If not, the request is placed into a queue. When tokens are returned or new requests are processed, the system evaluates queued requests using priority and arrival order, granting access when capacity becomes available.

This approach allows AI agents to coordinate without requiring heavy managers, ticking services, or hardcoded combat rules. Projects can use it for simple attack limits, more advanced role coordination, or as part of a broader AI engagement system.

## Integrations

- **[Ninja Bot](bot_overview.md)** can use tokens after selecting targets through perception and awareness.
- **[Ninja Combat](cbt_overview.md)** can use tokens to coordinate attack windows, ability usage, and enemy pressure.
