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
	UPROPERTY(VisibleAnywhere)
	TArray<ARtsUnity*> UnitySelected;

	UPROPERTY(VisibleAnywhere)
	TArray<ARtsUnity*> AllUnity;

	UPROPERTY(VisibleAnywhere)
	FVector PressPosition;

	
	
public:
	ARtsSpectatorPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

public:
	void OnMouseScrollUp();
	void OnMouseScrollDown();

public:
	URtsCameraComponent* CameraComponent;

public:

	void LeftClick();

	void SelectBatiment(BatimentType batimentType = BatimentType::CAMP);

	void LeftClickReleased();

	void RightClick();

	void StartUnityConstruction(int Number);

private:
	void UnselectAll();

	bool CheckSelectionBox(float UnityPosX, float one, float two);

private:
	ARtsBuildingTmp* TmpBuilding = nullptr;
	TArray<ARtsBuildingBatiment*> BatimentSelected;
};
