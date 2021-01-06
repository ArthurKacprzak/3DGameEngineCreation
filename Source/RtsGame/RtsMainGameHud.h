// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RtsPlayerController.h"
#include "RtsMainGameHud.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API AMainGameHud : public AHUD
{
	GENERATED_BODY()
public:
	AMainGameHud();

	void BeginPlay() override;
	void Tick(float deltaSeconds) override;

	void NewUnitySelection(TArray<ARtsUnity*> UnitySelected);
	void NewBatimentSelection(TArray<ARtsBuildingBatiment*> BatimentSelected);

	void UpdateSelectionHud(UTexture2D* Image);
	void UpdateCreationUnities(TArray<ARtsBuildingBatiment::CreationUnity*> Images);

	void UpdateProgressBar(float PercentValue);

	void UpdateStateByName(float Value, FName Name, float Max = 0);

private:
	// Main drawing function
	virtual void DrawHUD() override;
	ARtsPlayerController *GetPlayerController() const;

	void DrawCampHud(ARtsBuildingBatiment*Batiment);

	void DrawHealthBars() const;
	void DrawHealth(AActor* Character, float Health, float MaxHealth, float Radius, FLinearColor Color) const;
	void DrawSelectionGrid(FVector2D gridStartPos);
	void DrawConstructionItem();

	void DrawCampHud(ESlateVisibility);
	void DrawBatimentHud(ESlateVisibility slateVisibility);
	void DrawSelectionHud(ESlateVisibility slateVisibility);

	void DrawUnityStatsHud(ESlateVisibility slateVisibility, ARtsUnity *Unity);
	void DrawUnityStatsHud(ESlateVisibility slateVisibility);

	float UiScale;

private:

	struct HUDWidget {
		TSubclassOf<class UUserWidget> HUDWidgetClass;

		class UUserWidget* Widget;
	};

	HUDWidget WidgetBP;
	
	struct HUDConstructionItem {

	};
	HUDConstructionItem ConstructionItem;

	UTexture2D* EmptyUnityCreationAsset;
};
