// Copyright (c) 2025 Erdem Akar

using UnrealBuildTool;
using System.Collections.Generic;

public class ArcaneTarget : TargetRules
{
	public ArcaneTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Arcane" } );
	}
}
