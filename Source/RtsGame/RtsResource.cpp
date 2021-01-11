// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsResource.h"

// Sets default values
ARtsResource::ARtsResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bReplicates = true;

	int nbr = FMath::RandRange(1, 5);

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshRessource"));

	this->CreateMesh(
		TEXT("StaticMesh'/Game/AdvancedVillagePack/Meshes/SM_Tree_Var01.SM_Tree_Var01'"));

	this->CreateMesh(
		TEXT("StaticMesh'/Game/AdvancedVillagePack/Meshes/SM_Stone_Big_Var01.SM_Stone_Big_Var01'"));

	this->SetRootComponent(this->Mesh);

	this->Mesh->SetStaticMesh(this->ResourceMesh[0]);
}

void ARtsResource::CreateMesh(const TCHAR* MeshPath)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> *VisualAsset = new ConstructorHelpers::FObjectFinder<UStaticMesh>(MeshPath);

	if (VisualAsset->Succeeded()) {
		ResourceMesh.Add(VisualAsset->Object);
	}
}

// Called when the game starts or when spawned
void ARtsResource::BeginPlay()
{
	Super::BeginPlay();
	
	this->SetRessourceType();
}

void ARtsResource::SetRessourceType()
{
	this->Mesh->SetStaticMesh(this->ResourceMesh[0]);

	switch (this->Type.GetValue())
	{
	case RessourceType::THREE:
		this->Mesh->SetStaticMesh(this->ResourceMesh[0]);
		break;
	case RessourceType::STONE:
		this->Mesh->SetStaticMesh(this->ResourceMesh[1]);
		break;
	}
}

// Called every frame
void ARtsResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ARtsResource::Colect(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(this->RessouceColectable));
	if (this->RessouceColectable - Value <= 0) {
		float tmp =  this->RessouceColectable;
		this->RessouceColectable = 0;
		return tmp;
	}
	this->RessouceColectable -= Value;
	return Value;
}
