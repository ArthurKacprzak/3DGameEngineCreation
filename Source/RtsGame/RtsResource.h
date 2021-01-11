// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "RtsRessourceType.h"
#include "Containers/EnumAsByte.h"
#include "RtsResource.generated.h"

UCLASS()
class RTSGAME_API ARtsResource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARtsResource();


	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialisation")
		TEnumAsByte <RessourceType> Type;


	float Colect(float Value);

	float RessouceColectable = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void CreateMesh(const TCHAR* StateOne);

	void SetRessourceType();

	TArray<UStaticMesh*> ResourceMesh;
	

};
