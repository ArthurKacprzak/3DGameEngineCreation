// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RtsSpectatorPawn.h"
#include "Engine/ActorChannel.h"
#include "RtsUnity.h"
#include "Net/UnrealNetwork.h"
#include "RtsBatimentType.h"
#include "RtsPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class RTSGAME_API ARtsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARtsPlayerController();
	

	UFUNCTION(BlueprintCallable, Category = "Select")
	void SelectBatiment(TEnumAsByte<BatimentType> batimentType);

	UFUNCTION(BlueprintCallable, Category = "Select")
	void SelectUnity(int Number);

	UFUNCTION(BlueprintCallable, Category = "Select")
	void UpgradeBatiment();

protected:
	virtual void SetupInputComponent() override;
	virtual void ProcessPlayerInput(const float deltaTime, const bool bGamePaused) override;

	void ZoomIn();
	void ZoomOut();
	void Forward(float value);
	void Right(float value);


public:

	FVector const& GetSelectionStartPosition() const;

	bool GetIsSelectionActive() const
	{
		return isSelectionActive_;
	}

	UFUNCTION(BlueprintCallable, Category = "Select")
	void StartSelection()
	{
		FHitResult hit;
		GetHitResultUnderCursor(ECC_Visibility, false, hit);
		selectionStartPosition_ = hit.Location;

		isSelectionActive_ = true;
	}

	void EndSelection()
	{
		FHitResult hit;
		GetHitResultUnderCursor(ECC_Visibility, false, hit);
		selectionEndPosition_ = hit.Location;

		isSelectionActive_ = false;

//		UnitSelection();
	}

public:


	UFUNCTION(BlueprintCallable, Category = "Select")
	virtual void RightClickServer(FHitResult Hit, TArray<ARtsUnity*> Unities);


	UFUNCTION(BlueprintCallable, Category = "Select")
	virtual void LeftClickReleasedServer(FHitResult Hit);

	UFUNCTION(BlueprintCallable, Category = "Select")
	virtual ARtsBuildingBatiment* LeftClickServer(FHitResult Hit, TArray<FString> UnitiesName, BatimentType BatimentToBuildType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitySelected")
	TArray<ARtsUnity*> UnitySelected;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitySelected")
	FVector PressPosition;

	UPROPERTY(VisibleAnywhere)
	TArray<ARtsUnity*> AllUnity;

	UFUNCTION(BlueprintCallable, Category = "Select")
		void ResetBuildingTmp();

	virtual void SelectBatimentServer(BatimentType batimentType);

	virtual void StartUnityConstructionServer(int Number);

	void UpdateWood(int w);
	void UpdateStone(int w);
	void UpdatePopulation(int w);
	void UpdatePopulationMax(int w);

	void UpdateHudRessources();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UnitySelected")
		ARtsBuildingTmp* TmpBuilding = nullptr;
private:
	bool isSelectionActive_ = false;
	FVector selectionStartPosition_;
	FVector selectionEndPosition_;
	bool CheckSelectionBox(float UnityPosX, float one, float two);
	void UnselectAll();

	int Wood = 100;
	int Stone = 100;
	int Population = 3;
	int PopulationMax = 3;

	
	TArray<ARtsBuildingBatiment*> BatimentSelected;
};
