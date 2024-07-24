// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TestCodeProjectTarget : TargetRules
{
	public TestCodeProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		bWithPushModel = true;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("TestCodeProject");
	}
}
