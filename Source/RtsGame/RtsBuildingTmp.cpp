// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsBuildingTmp.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARtsBuildingTmp::ARtsBuildingTmp() : Super()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssetTownHall(TEXT("StaticMesh'/Game/RtsGame/Building/SM_TownHall.SM_TownHall'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssetCaserne(TEXT("StaticMesh'/Game/RtsGame/Building/SM_Barracks.SM_Barracks'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssetArchery(TEXT("StaticMesh'/Game/RtsGame/Building/SM_Archery.SM_Archery'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssetStables(TEXT("StaticMesh'/Game/RtsGame/Building/SM_Stables.SM_Stables'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssetTower(TEXT("StaticMesh'/Game/RtsGame/Building/SM_Tower_A.SM_Tower_A'"));

	if (MeshAssetTownHall.Succeeded()
		&& MeshAssetArchery.Succeeded()
		&& MeshAssetCaserne.Succeeded()
		&& MeshAssetStables.Succeeded()
		&& MeshAssetTower.Succeeded())
	{
		this->MeshMap.Add(MeshAssetTownHall.Object);
		this->MeshMap.Add(MeshAssetCaserne.Object);
		this->MeshMap.Add(MeshAssetArchery.Object);
		this->MeshMap.Add(MeshAssetStables.Object);
		this->MeshMap.Add(MeshAssetTower.Object);
	}
	this->Mesh->SetStaticMesh(this->MeshMap[0]);

	this->Mesh->SetupAttachment(this->RootComponent);
	this->Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	this->Mesh->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
}

void ARtsBuildingTmp::SetBatimentType(BatimentType BatimentType)
{
	switch (BatimentType)
	{
	case BatimentType::CAMP:
		this->Mesh->SetStaticMesh(this->MeshMap[CAMP_INDEX]);
		break;
	case BatimentType::CASERNE:
		this->Mesh->SetStaticMesh(this->MeshMap[CASERNE_INDEX]);
		break;
	case BatimentType::ARCHERY:
		this->Mesh->SetStaticMesh(this->MeshMap[ARCHERY_INDEX]);
		break;
	case BatimentType::STABLES:
		this->Mesh->SetStaticMesh(this->MeshMap[STABLES_INDEX]);
		break;
	case BatimentType::TOWER:
		this->Mesh->SetStaticMesh(this->MeshMap[TOWER_INDEX]);
		break;
	default:
		break;
	}
	this->BatimentToBuildType = BatimentType;
}

BatimentType ARtsBuildingTmp::GetBatimentToBuildType()
{
	return this->BatimentToBuildType;
}

// Called when the game starts or when spawned
void ARtsBuildingTmp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARtsBuildingTmp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AController* Controller = UGameplayStatics::GetPlayerController(this, 0);

	if (!Controller) {
		return;
	}
	
	FHitResult Hit;
	Controller->CastToPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit) {
		if (Hit.Actor.IsValid()) {
			this->SetActorLocation(Hit.ImpactPoint);
		}
	}
}