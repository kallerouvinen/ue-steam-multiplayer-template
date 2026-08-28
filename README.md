# Unreal Engine Steam Multiplayer Template

A minimal reference project for **Steam multiplayer in Unreal Engine 5.7**.

This repository exists because Unreal Engine's Steam multiplayer setup has seen breaking changes across recent engine versions, while existing documentation and tutorials have not always been updated to reflect those changes. The goal is to keep a known-working implementation that can be reused when starting a new project.

## Scope

This is **not a complete game template** or project starter.

It contains only:

* Minimal main menu logic
* The networking logic required to host and join games through Steam
* The custom `GameInstance` responsible for the multiplayer/session flow
* The required Steam/Online Subsystem configuration

Game-specific systems, gameplay, UI, maps, and other project setup are intentionally left out.

## Requirements

* Unreal Engine 5.7
* Online Subsystem Steam
* Steam client

No other online subsystem is supported.

## Supported Features

### Hosting

A player can host a session as:

* **Public** — discoverable through the session browser
* **Friends Only** — friends can find/join the session
* **Invite Only** — players can join through Steam invitations

### Joining

Players can join through:

* **Session browser**
* Accepting a **Steam overlay invite**
* Selecting **Join Game** directly from a friend's Steam profile/overlay

## Configuration

The Steam setup is kept as minimal as possible and is primarily contained in:

```text
Config/DefaultEngine.ini
Config/DefaultGame.ini
```

The exact configuration in this repository should be treated as the known-working baseline for **UE 5.7** rather than copied from older Unreal Engine/Steam tutorials.

## Purpose

This repository is intended to be a small, working reference that can be copied or consulted when starting a new multiplayer project—not a framework to build the entire game from.
