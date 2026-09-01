# Unreal Engine Steam Multiplayer Template

A minimal reference project for **Steam multiplayer in Unreal Engine 5.7**.

This repository exists because Unreal Engine's Steam multiplayer setup has seen breaking changes across recent engine versions, while existing documentation and tutorials have not always been updated to reflect those changes. The goal is to keep a known-working implementation that can be reused when starting a new project.

## Scope

This is **not a complete game template** or project starter.

It contains only:

- Minimal main menu logic
- The networking logic required to host and join games through Steam
- The custom `GameInstanceSubsystem` responsible for the multiplayer/session flow
- The required Steam/Online Subsystem configuration
- Minimal gameplay logic for moving around with 3rd person mannequin

Game-specific systems, gameplay, UI, maps, and other project setup are intentionally left out.

## Requirements

- Unreal Engine 5.7
- Online Subsystem Steam
- Steam client

No other online subsystem is supported.

## Supported Features

<!-- TODO: Combine sections Hosting and Joining as they are basically duplicate information -->

### Session types

A player can host a session as:

- **Public** — Discoverable through the session browser
- **Friends Only** — Friends can join the session
- **Invite Only** — Players can only join through Steam invitations

> **NOTE**: Due to limitations of Steam, the following restrictions apply:
>
> - **Friends only** -games don't appear in found sessions. To add friend sessions to some kind of session browser, you have to iterate through friends separately and check whether they have a hosted session ongoing.
> - For some reason, friends can't be invited to **Invite only** -games through Steam overlay. For this you have to open a separate Invite-overlay by calling `USteamMultiplayerSubsystem::ShowInviteUI()`.

## Configuration

1. Enable `Steam Sockets`-plugin and restart the engine.

<!-- TODO: Is PrivateDependencyModuleNames enough? -->

1. Add the following dependencies under `PublicDependencyModuleNames` in `[PROJECT_NAME].Build.cs`-file:
   1. `OnlineSubsystem`
   1. `OnlineSubsystemUtils` (TODO: Is this needed?)

1. Add the following line in `[PROJECT_NAME].Build.cs`-file: `DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");`

1. Add the following lines to `DefaultEngine.ini`:

<!-- TODO: Copy the final config here once everything works -->

```ini
[/Script/Engine.GameEngine]
!NetDriverDefinitions=ClearArray
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="/Script/SteamSockets.SteamSocketsNetDriver",DriverClassNameFallback="/Script/SteamSockets.SteamNetSocketsNetDriver")

[OnlineSubsystem]
DefaultPlatformService=Steam

[OnlineSubsystemSteam]
bEnabled=true
SteamDevAppId=480
; bUsesPresence=true
; bUseLobbiesIfAvailable=true
; ; If using Sessions

[/Script/SteamSockets.SteamSocketsNetDriver]
NetConnectionClassName="/Script/SteamSockets.SteamSocketsNetConnection"
```

1. Copy required code for the custom game instance from `TODO`

## Purpose

This repository is intended to be a small, working reference that can be copied or consulted when starting a new multiplayer project—not a framework to build the entire game from.
