// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsPlayerController.h"

#include "Engine/LocalPlayer.h"
#include "RtsSpectatorPawn.h"
#include "RtsCameraComponent.h"
#include "AIController.h"


ARtsPlayerController::ARtsPlayerController() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	this->bShowMouseCursor = true;

	this->bReplicates = true;
	this->bAlwaysRelevant = true;
	this->bOnlyRelevantToOwner = false;

}

void ARtsPlayerController::Forward(float value) 
{
	ARtsSpectatorPawn* spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn());

	if (spectatorPawn)
	{
		spectatorPawn->CameraComponent->MoveForward(value*20);
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

	InputComponent->BindAction("MouseLeftClick", EInputEvent::IE_Pressed, this, &ARtsPlayerController::LeftClick);
	InputComponent->BindAction("MouseLeftClick", EInputEvent::IE_Released, this, &ARtsPlayerController::LeftClickReleased);
	InputComponent->BindAction("MouseRightClick", EInputEvent::IE_Pressed, this, &ARtsPlayerController::RightClick);
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



void ARtsPlayerController::LeftClick()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->LeftClick();
	}
}

void ARtsPlayerController::LeftClickReleased()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->LeftClickReleased();
	}
}

void ARtsPlayerController::RightClick()
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->RightClick();
	}
}

void ARtsPlayerController::SelectBatiment(TEnumAsByte<BatimentType> batimentType)
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->SelectBatiment(batimentType.GetValue());
	}
}

void ARtsPlayerController::SelectUnity(int Number)
{
	ARtsSpectatorPawn* spectatorPawn;
	if ((spectatorPawn = Cast<ARtsSpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->StartUnityConstruction(Number);
	}
}