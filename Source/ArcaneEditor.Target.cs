// Copyright (c) 2025 Erdem Akar

using UnrealBuildTool;
using System.Collections.Generic;

public class ArcaneEditorTarget : TargetRules
{
	public ArcaneEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Arcane" } );
	}
}
