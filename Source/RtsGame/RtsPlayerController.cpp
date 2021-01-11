// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsPlayerController.h"

#include "Engine/LocalPlayer.h"
#include "RtsSpectatorPawn.h"
#include "RtsCameraComponent.h"
#include "RtsMainGameHud.h"
#include "RtsBuildingTmp.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"


ARtsPlayerController::ARtsPlayerController() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	this->bShowMouseCursor = true;

	this->bReplicates = true;
	this->bAlwaysRelevant = true;
	this->bOnlyRelevantToOwner = false;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), ARtsUnity::StaticClass(), FoundActors);

	for (auto& Actor : FoundActors) {
		ARtsUnity* tmpUnity = Cast<ARtsUnity>(Actor);
		if (tmpUnity) {


			this->AllUnity.Add(tmpUnity);
		}
	}

}

void ARtsPlayerController::Forward(float value) 
{
	ARtsSpectatorPawn* spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn());

	if (spectatorPawn)
	{
		spectatorPawn->CameraComponent->MoveForward(value*20);
	}
}

void ARtsPlayerController::UpgradeBatiment()
{
	for (auto batiment : this->BatimentSelected) {
		if (this->Wood >= batiment->GetWoodPriceUpgrade() && this->Stone >= batiment->GetStonePriceUpgrade()) {
			batiment->Upgrade();

			this->Wood -= batiment->GetWoodPriceUpgrade();
			this->Stone -= batiment->GetStonePriceUpgrade();
			this->UpdateHudRessources();
		}
	}
}

void ARtsPlayerController::Right(float value)
{
	ARtsSpectatorPawn* spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn());

	if (spectatorPawn)
	{
		spectatorPawn->CameraComponent->MoveRight(value * 20);
	}
}

void ARtsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARtsPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARtsPlayerController::ZoomOut);

/*	InputComponent->BindAction("MouseLeftClick", EInputEvent::IE_Pressed, this, &ARtsPlayerController::LeftClick);
	InputComponent->BindAction("MouseLeftClick", EInputEvent::IE_Released, this, &ARtsPlayerController::LeftClickReleased);
	InputComponent->BindAction("MouseRightClick", EInputEvent::IE_Pressed, this, &ARtsPlayerController::RightClick);*/
	InputComponent->BindAxis("Forward", this, &ARtsPlayerController::Forward);
	InputComponent->BindAxis("Right", this, &ARtsPlayerController::Right);
}

void ARtsPlayerController::ProcessPlayerInput(const float deltaTime, const bool bGamePaused)
{
	Super::ProcessPlayerInput(deltaTime, bGamePaused);

	/*{
		const ULocalPlayer* localPlayer = Cast<ULocalPlayer>(Player);
		ARtsSpectatorPawn *spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn());

		if (spectatorPawn && localPlayer)
		{
			if (localPlayer->ViewportClient)
			{
				spectatorPawn->CameraComponent->UpdateCameraMovement(this);
			}
		}
	}*/
}

void ARtsPlayerController::ZoomIn()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->OnMouseScrollUp();
	}
}

void ARtsPlayerController::ZoomOut()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->OnMouseScrollDown();
	}
}

FVector const& ARtsPlayerController::GetSelectionStartPosition() const
{
	return selectionStartPosition_;
}




void ARtsPlayerController::SelectBatiment(TEnumAsByte<BatimentType> batimentType)
{
	this->SelectBatimentServer(batimentType.GetValue());
}

void ARtsPlayerController::SelectBatimentServer(BatimentType batimentType)
{
	if (this->TmpBuilding) {
		this->TmpBuilding->ConditionalBeginDestroy();
		this->TmpBuilding = nullptr;
	}
	this->TmpBuilding = Cast<ARtsBuildingTmp>(this->GetWorld()->SpawnActor<AActor>(ARtsBuildingTmp::StaticClass(), PressPosition, FRotator::ZeroRotator));
	this->TmpBuilding->SetBatimentType(batimentType);
}

void ARtsPlayerController::SelectUnity(int Number)
{
	this->StartUnityConstructionServer(Number);
}

void ARtsPlayerController::StartUnityConstructionServer(int Number)
{
	if (!this->BatimentSelected.Num()) {
		return;
	}

	for (auto& Batiment : this->BatimentSelected) {
		AMainGameHud* Hud = Cast<AMainGameHud>(this->GetHUD());
		UTexture2D* Image;

		Image = Batiment->GetTextureImageUnityByNumber(Number);
		Batiment->AddCreationUnity(Image, Number);

		TArray<ARtsBuildingBatiment::CreationUnity*> ImagesUnities;

		ImagesUnities = Batiment->GetCreationList();
		Hud->UpdateCreationUnities(ImagesUnities);
	}
}

void ARtsPlayerController::RightClickServer(FHitResult Hit, TArray<ARtsUnity*> Unities)
{
	int UnitySelectedNum = Unities.Num();
	if (Hit.GetActor()->GetName().Find("Landscape") != -1) {
		if (UnitySelectedNum) {
			for (auto& Unity : Unities) {

				Unity->GoTo(FVector(Hit.ImpactPoint.X, Hit.ImpactPoint.Y, Hit.ImpactPoint.Z));

			}
		}
		return;
	}

	ARtsBuildingBatiment* BuildingBatiment = Cast<ARtsBuildingBatiment>(Hit.Actor);
	if (BuildingBatiment) {
		if (UnitySelectedNum) {
			for (auto& Unity : Unities) {
				Unity->Build(BuildingBatiment);
			}
		}
		return;
	}

	ARtsUnity* UnityToAttack = Cast<ARtsUnity>(Hit.Actor);
	if (UnityToAttack) {
		if (UnitySelectedNum) {
			for (auto& Unity : Unities) {
				Unity->Attack(UnityToAttack);
			}
		}
		return;
	}

	ARtsResource* Resource = Cast<ARtsResource>(Hit.Actor);
	if (Resource) {
		if (UnitySelectedNum) {
			for (auto& Unity : Unities) {

				Unity->Recolte(Resource);
			}
		}
	}
}

void ARtsPlayerController::LeftClickReleasedServer(FHitResult Hit)
{
	if (this->PressPosition != FVector(0.f, 0.f, 0.f)) {
		this->UnselectAll();

		ARtsUnity* UnityTmp = Cast<ARtsUnity>(Hit.GetActor());

		if (UnityTmp) {
			this->UnitySelected.Add(UnityTmp);
			UnityTmp->Select();
		}


		ARtsBuildingBatiment* Batiment = Cast<ARtsBuildingBatiment>(Hit.GetActor());
		
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Hit.GetActor()->GetName());
		if (Batiment) {
			for (ARtsBuildingBatiment* PrevBatiment : this->BatimentSelected) {
				PrevBatiment->UnSelect();
			}
			this->BatimentSelected.Empty();
			AMainGameHud* Hud = Cast<AMainGameHud>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
			UTexture2D* Image;

			Image = Batiment->GetTextureImage();
			Hud->UpdateSelectionHud(Image);

			TArray<ARtsBuildingBatiment::CreationUnity*> ImagesUnities;

			ImagesUnities = Batiment->GetCreationList();
			Hud->UpdateCreationUnities(ImagesUnities);
			Batiment->Select();
			this->BatimentSelected.Add(Batiment);

		}
		else {
			for (ARtsBuildingBatiment* PrevBatiment : this->BatimentSelected) {
				PrevBatiment->UnSelect();
			}
			this->BatimentSelected.Empty();
		}
		FVector ImpactPoint = Hit.ImpactPoint;
		bool SelectedBoxUp = false;
		bool SelectedBoxRight = false;

		if (this->PressPosition.X < ImpactPoint.X) {
			SelectedBoxUp = true;
		}
		if (this->PressPosition.Y < ImpactPoint.Y) {
			SelectedBoxRight = true;
		}
		for (auto& Unity : this->AllUnity) {
			if (SelectedBoxUp && SelectedBoxRight
				&& this->CheckSelectionBox(Unity->GetActorLocation().X, ImpactPoint.X, this->PressPosition.X)
				&& this->CheckSelectionBox(Unity->GetActorLocation().Y, ImpactPoint.Y, this->PressPosition.Y)) {
				this->UnitySelected.Add(Unity);
				Unity->Select();
			}

			if (SelectedBoxUp && !SelectedBoxRight
				&& this->CheckSelectionBox(Unity->GetActorLocation().X, ImpactPoint.X, this->PressPosition.X)
				&& this->CheckSelectionBox(Unity->GetActorLocation().Y, this->PressPosition.Y, ImpactPoint.Y)) {
				this->UnitySelected.Add(Unity);
				Unity->Select();
			}

			if (!SelectedBoxUp && SelectedBoxRight
				&& this->CheckSelectionBox(Unity->GetActorLocation().X, this->PressPosition.X, ImpactPoint.X)
				&& this->CheckSelectionBox(Unity->GetActorLocation().Y, ImpactPoint.Y, this->PressPosition.Y)) {
				this->UnitySelected.Add(Unity);
				Unity->Select();
			}

			if (!SelectedBoxUp && !SelectedBoxRight
				&& this->CheckSelectionBox(Unity->GetActorLocation().X, this->PressPosition.X, ImpactPoint.X)
				&& this->CheckSelectionBox(Unity->GetActorLocation().Y, this->PressPosition.Y, ImpactPoint.Y)) {
				this->UnitySelected.Add(Unity);
				Unity->Select();
			}

		}
	}

	this->EndSelection();


	AMainGameHud* Hud = Cast<AMainGameHud>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	Hud->NewUnitySelection(this->UnitySelected);
	Hud->NewBatimentSelection(this->BatimentSelected);
	if (this->UnitySelected.Num()) {
		UTexture2D* Image;

		Image = this->UnitySelected[0]->GetTextureImage();
		Hud->UpdateSelectionHud(Image);
	}
}

ARtsBuildingBatiment *ARtsPlayerController::LeftClickServer(FHitResult Hit, TArray<FString> UnitiesName, BatimentType BatimentToBuildType)
{
	AActor* NewActor = this->GetWorld()->SpawnActor<AActor>(ARtsBuildingBatiment::StaticClass(), Hit.ImpactPoint, FRotator::ZeroRotator);
	ARtsBuildingBatiment* NewBatiment = Cast<ARtsBuildingBatiment>(NewActor);



	NewBatiment->SetBatimentType(BatimentToBuildType);



	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), ARtsUnity::StaticClass(), FoundActors);

	TArray<ARtsUnity*> UnitySelect;

	for (auto& Actor : FoundActors) {
		ARtsUnity* tmpUnity = Cast<ARtsUnity>(Actor);
		if (tmpUnity) {
			for (auto name:  UnitiesName) {
				if (name == tmpUnity->GetName()) {
					UnitySelect.Add(tmpUnity);
				}
			}
		}
	}


	if (NewBatiment) {
		for (auto Unity : UnitySelect) {
			Unity->Build(NewBatiment);
		}
	}
	this->UnselectAll();
	return NewBatiment;
}


bool ARtsPlayerController::CheckSelectionBox(float UnityPosX, float one, float two)
{
	return UnityPosX > two && UnityPosX < one;
}

void ARtsPlayerController::UnselectAll()
{
	if (this->UnitySelected.Num()) {
		for (auto& Unity : this->UnitySelected) {
			Unity->Unselect();
		}
		this->UnitySelected.Empty();
	}
}
void ARtsPlayerController::ResetBuildingTmp()
{

	if (this->TmpBuilding) {

		this->TmpBuilding->ConditionalBeginDestroy();
	}
	this->TmpBuilding = nullptr;
}

void ARtsPlayerController::UpdateWood(int w)
{
	this->Wood += w;
	this->UpdateHudRessources();
}

void ARtsPlayerController::UpdateStone(int w)
{
	this->Stone += w;
	this->UpdateHudRessources();
}

void ARtsPlayerController::UpdatePopulation(int w)
{
	this->Population += w;
	this->UpdateHudRessources();
}
void ARtsPlayerController::UpdatePopulationMax(int w)
{
	this->PopulationMax += w;
	this->UpdateHudRessources();
}

void ARtsPlayerController::UpdateHudRessources()
{
	AMainGameHud* Hud = Cast<AMainGameHud>(this->GetHUD());
	Hud->UpdateStateByName(this->Wood, "Woods");
	Hud->UpdateStateByName(this->Stone, "Stones");
	Hud->UpdateStateByName(this->Population, "Populations", this->PopulationMax);
}