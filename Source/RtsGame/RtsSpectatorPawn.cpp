// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsSpectatorPawn.h"
#include "RtsCameraComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RtsUnity.h"
#include "RtsBuildingTmp.h"
#include "AIController.h"
#include "RtsMainGameHud.h"
#include "RtsPlayerController.h"
#include "RtsResource.h"
#include "Kismet/GameplayStatics.h"
#include "RtsBuildingBatiment.h"

ARtsSpectatorPawn::ARtsSpectatorPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	bAddDefaultMovementBindings = false;

	CameraComponent = CreateDefaultSubobject<URtsCameraComponent>(TEXT("Camera Component"));
	


	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), ARtsUnity::StaticClass(), FoundActors);

	for (auto& Actor : FoundActors) {
		ARtsUnity* tmpUnity = Cast<ARtsUnity>(Actor);
		if (tmpUnity) {

			
			this->AllUnity.Add(tmpUnity);
		}
	}

	this->CameraComponent->SetupAttachment(this->RootComponent);
}

void ARtsSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector::ZeroVector);
}

void ARtsSpectatorPawn::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ARtsSpectatorPawn::OnMouseScrollUp()
{
	CameraComponent->OnZoomIn();
}

void ARtsSpectatorPawn::OnMouseScrollDown()
{
	CameraComponent->OnZoomOut();
}

void ARtsSpectatorPawn::SelectBatiment(BatimentType batimentType)
{
	if (this->TmpBuilding) {
		this->TmpBuilding->ConditionalBeginDestroy();
		this->TmpBuilding = nullptr;
	}
	this->TmpBuilding = Cast<ARtsBuildingTmp>(this->GetWorld()->SpawnActor<AActor>(ARtsBuildingTmp::StaticClass(), PressPosition, FRotator::ZeroRotator));
	this->TmpBuilding->SetBatimentType(batimentType);
}

void ARtsSpectatorPawn::LeftClick()
{
	FHitResult Hit;
	Cast<APlayerController>(Controller)->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit) {
		if (Hit.Actor.IsValid()) {


			this->PressPosition = Hit.ImpactPoint;

			if (this->TmpBuilding) {
				BatimentType BatimentToBuildType = this->TmpBuilding->GetBatimentToBuildType();
				this->TmpBuilding->ConditionalBeginDestroy();
				this->TmpBuilding = nullptr;
				AActor *NewActor = this->GetWorld()->SpawnActor<AActor>(ARtsBuildingBatiment::StaticClass(), PressPosition, FRotator::ZeroRotator);
				ARtsBuildingBatiment* NewBatiment = Cast<ARtsBuildingBatiment>(NewActor);
				NewBatiment->SetBatimentType(BatimentToBuildType);
				if (NewBatiment) {
					for (auto Unity : this->UnitySelected) {
						Unity->Build(NewBatiment);
					}
				}

			}

			this->UnselectAll();

			ARtsPlayerController* pc = Cast<ARtsPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			pc->StartSelection();
		}
	}
}

void ARtsSpectatorPawn::LeftClickReleased()
{
	FHitResult Hit;
	Cast<APlayerController>(Controller)->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit) {
		if (Hit.Actor.IsValid()) {
			if (this->PressPosition != FVector(0.f, 0.f, 0.f)) {
				this->UnselectAll();


				ARtsUnity* UnityTmp = Cast<ARtsUnity>(Hit.GetActor());

				if (UnityTmp) {
					this->UnitySelected.Add(UnityTmp);
					UnityTmp->Select();
				}


				ARtsBuildingBatiment* Batiment = Cast<ARtsBuildingBatiment>(Hit.GetActor());

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

			ARtsPlayerController* pc = Cast<ARtsPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			pc->EndSelection();


			AMainGameHud* Hud = Cast<AMainGameHud>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
			Hud->NewUnitySelection(this->UnitySelected);
			Hud->NewBatimentSelection(this->BatimentSelected);
			if (this->UnitySelected.Num()) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ok"));
				UTexture2D* Image;

				Image = this->UnitySelected[0]->GetTextureImage();
				Hud->UpdateSelectionHud(Image);
			}

		}
	}
}

bool ARtsSpectatorPawn::CheckSelectionBox(float UnityPosX, float one, float two)
{
	return UnityPosX > two && UnityPosX < one;
}

void ARtsSpectatorPawn::RightClick()
{
	FHitResult Hit;
	Cast<APlayerController>(Controller)->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	
	if (Hit.bBlockingHit) {
		if (Hit.Actor.IsValid()) {

			if (Hit.GetActor()->GetName().Find("Landscape") != -1) {
				int UnitySelectedNum = this->UnitySelected.Num();
				if (UnitySelectedNum) {
					for (auto& Unity : this->UnitySelected) {
						Unity->GoTo(FVector(Hit.ImpactPoint.X, Hit.ImpactPoint.Y, Hit.ImpactPoint.Z));
					}
				}
				return;
			}

			ARtsBuildingBatiment* BuildingBatiment = Cast<ARtsBuildingBatiment>(Hit.Actor);
			if (BuildingBatiment) {
				if (this->UnitySelected.Num()) {
					for (auto& Unity : this->UnitySelected) {
						Unity->Build(BuildingBatiment);
					}
				}
				return;
			}

			ARtsUnity* UnityToAttack = Cast<ARtsUnity>(Hit.Actor);
			if (UnityToAttack) {
				if (this->UnitySelected.Num()) {
					for (auto& Unity : this->UnitySelected) {
						Unity->Attack(UnityToAttack);
					}
				}
				return;
			}

			ARtsResource* Resource = Cast<ARtsResource>(Hit.Actor);
			if (Resource) {
				if (this->UnitySelected.Num()) {
					for (auto& Unity : this->UnitySelected) {

						Unity->Recolte(Resource);
					}
				}
			}
		}
	}
}

void ARtsSpectatorPawn::UnselectAll()
{
	if (this->UnitySelected.Num()) {
		for (auto& Unity : this->UnitySelected) {
			Unity->Unselect();
		}
		this->UnitySelected.Empty();
	}
}

void ARtsSpectatorPawn::StartUnityConstruction(int Number)
{
	if (!this->BatimentSelected.Num()) {
		return;
	}

	for (auto& Batiment : this->BatimentSelected) {
		AMainGameHud* Hud = Cast<AMainGameHud>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		UTexture2D* Image;

		Image = Batiment->GetTextureImageUnityByNumber(Number);
		Batiment->AddCreationUnity(Image, Number);

		TArray<ARtsBuildingBatiment::CreationUnity*> ImagesUnities;

		ImagesUnities = Batiment->GetCreationList();
		Hud->UpdateCreationUnities(ImagesUnities);
	}
}