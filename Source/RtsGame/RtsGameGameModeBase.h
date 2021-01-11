// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RtsPlayerController.h"
#include "RtsMainGameHud.h"
#include "RtsSpectatorPawn.h"
#include "RtsGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ARtsGameGameModeBase : public AGameMode
{
	GENERATED_BODY()

	ARtsGameGameModeBase()
	{
//		this->DefaultPawnClass = AMain::StaticClass();
		this->PlayerControllerClass = ARtsPlayerController::StaticClass();
		this->HUDClass = AMainGameHud::StaticClass();
		this->DefaultPawnClass = ARtsSpectatorPawn::StaticClass();
	}
	
};
