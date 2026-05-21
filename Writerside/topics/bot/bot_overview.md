# Ninja Bot
<primary-label ref="bot"/>

![Ninja Bot](bot_feature.png "Ninja Bot")

**Ninja Bot** is an AI framework plugin for Unreal Engine that provides a structured layer for perception evaluation, 
awareness, and decision support.

It is designed to sit between Unreal Engine's AI Perception system and higher-level decision logic, turning raw sensed 
data into meaningful information that can be consumed by Behavior Trees, State Trees, UI, and other gameplay systems.

## What It Does

- Adds a reusable framework for **AI perception evaluation** and **awareness modeling**.
- Converts raw perception data into normalized, meaningful awareness information.
- Helps AI agents reason about targets using explicit evaluation rules instead of raw sense data.
- Provides decision-ready data for **Behavior Trees** and **State Trees**.
- Supports UI presentation for awareness, detection, and AI state.
- Includes additional gameplay systems such as **Patrol Points** and optional **Threat Management**.
- Integrates with **Ninja Factions** for attitude-aware perception.

## Main Features

- **Perception Evaluation**: Evaluates sensed actors using reusable rules, scores, and sense-specific data.
- **Awareness Modeling**: Aggregates perception data into continuous awareness states that can drive AI behavior.
- **Behavior Tree Support**: Provides services, tasks, decorators, and blackboard-friendly data for Behavior Tree workflows.
- **State Tree Support**: Provides evaluators and tasks for projects using State Trees as their AI decision model.
- **Patrol Points**: Adds reusable patrol-point support for common AI movement and routing behavior.
- **Threat Management**: Provides an optional module for tracking and selecting relevant threats.
- **UI Presentation**: Includes UMG widgets and ViewModels for presenting awareness and AI state.
- **Faction Integration**: Works with Ninja Factions to evaluate perceived targets using team attitude and faction relationships.

## Architecture Overview

Ninja Bot is organized around a clear separation between sensing, interpretation, decision support, and presentation.

Unreal Engine's AI Perception system detects raw stimuli such as sight, sound, damage, and team information. Ninja Bot 
evaluates that data into normalized perception entries, then interprets those entries into awareness values that can be 
consumed by AI decision systems.

Behavior Trees and State Trees can then use that awareness data to select targets, change behavior, update blackboards, 
trigger tasks, or drive higher-level AI logic. UI systems can observe the same awareness state through ViewModels and 
widgets, allowing player-facing feedback such as detection indicators or awareness meters.

By keeping sensing, evaluation, decision support, and UI presentation separate, Ninja Bot allows multiple AI agents to 
share the same controller structure while changing behavior through data assets, perception settings, awareness profiles, 
and optional faction configuration.

## Integrations

- **[Ninja Factions][1]** can provide team and attitude data used by the perception layer.
- **[Ninja Combat](cbt_overview.md)** can provide combat events, damage stimuli, or target data used by AI behavior.

[1]: fct_overview.md