// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RtsGameTarget : TargetRules
{
	public RtsGameTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new string[] { "RtsGame", "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "NavigationSystem", "UnrealEd", "UMGEditor", "UMG", "OnlineSubsystemSteam" });
	}
}
