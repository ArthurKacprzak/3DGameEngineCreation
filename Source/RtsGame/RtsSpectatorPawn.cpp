// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsSpectatorPawn.h"
#include "RtsCameraComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "RtsUnity.h"
#include "AIController.h"
#include "RtsMainGameHud.h"
#include "RtsPlayerController.h"
#include "RtsResource.h"
#include "Kismet/GameplayStatics.h"
#include "RtsGameGameModeBase.h"
#include "RtsBuildingBatiment.h"

ARtsSpectatorPawn::ARtsSpectatorPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	bAddDefaultMovementBindings = false;

	CameraComponent = CreateDefaultSubobject<URtsCameraComponent>(TEXT("Camera Component"));
	

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
