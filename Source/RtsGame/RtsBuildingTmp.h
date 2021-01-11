// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RtsBatimentType.h"
#include "RtsBuildingTmp.generated.h"

UCLASS()
class RTSGAME_API ARtsBuildingTmp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARtsBuildingTmp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialisation")
		TArray<UStaticMesh*> MeshMap;

	UStaticMeshComponent* Mesh;

	void SetBatimentType(BatimentType batimentType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Select")
	BatimentType GetBatimentToBuildType();

private:
	BatimentType BatimentToBuildType;

};
