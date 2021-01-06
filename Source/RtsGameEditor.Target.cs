// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RtsGameEditorTarget : TargetRules
{
	public RtsGameEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "RtsGame", "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "NavigationSystem" } );
	}
}
