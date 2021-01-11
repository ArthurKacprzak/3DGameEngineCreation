// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "AIController.h"
#include "RtsBatimentType.h"
#include "RtsSpectatorPawn.generated.h"

class URtsCameraComponent;
class ARtsUnity;
class ARtsBuildingBatiment;
class ARtsPlayerController;
class ARtsBuildingTmp;



/**
 * 
 */
UCLASS()
class RTSGAME_API ARtsSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	ARtsSpectatorPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

public:
	void OnMouseScrollUp();
	void OnMouseScrollDown();

public:
	URtsCameraComponent* CameraComponent;
};
