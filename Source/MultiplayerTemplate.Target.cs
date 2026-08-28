// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MultiplayerTemplateTarget : TargetRules
{
	public MultiplayerTemplateTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("MultiplayerTemplate");
	}
}
