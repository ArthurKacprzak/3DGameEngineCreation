// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "RtsBatimentType.h"
#include "RtsUnityType.h"
#include "UObject/ConstructorHelpers.h"
#include "RtsBuildingBatiment.generated.h"

class UImage;

UCLASS()
class RTSGAME_API ARtsBuildingBatiment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARtsBuildingBatiment();

	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialisation")
	bool Camp = true;

	struct {
		float Health = 1.f;
		float MaxHealth = 100.f;
	} BasicStats;

	float GetHealth() const
	{
		return this->BasicStats.Health;
	}

	float GetMaxHealth() const
	{
		return this->BasicStats.MaxHealth;
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	struct CreationUnity {
		int ID;
		UTexture2D* Texture;
		UnityType Type;
	};
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool Build(float Speed);

	bool IsCamp();
	bool CanUpgrade();

	void SetBatimentType(BatimentType BatimentToBuildType);
	void Upgrade();

	BatimentType GetType();

	UTexture2D*GetTextureImage();
	UTexture2D* GetTextureImageUnityByNumber(int Number);
	TArray<CreationUnity*> GetCreationList();
	void AddCreationUnity(UTexture2D* image, int UnityID);

	void UnSelect();
	void Select();

	struct UnityCreation {
		UTexture2D* Texture;
		UnityType Type;
	};

	TArray<UnityCreation*> GetUnityCreateImages();
	TArray<UnityCreation*> UnityCreateImages;
private:
	struct BatimentConstructionStates {
		ConstructorHelpers::FObjectFinder<UStaticMesh>* StateOne;
		ConstructorHelpers::FObjectFinder<UStaticMesh>* StateTwo;
		ConstructorHelpers::FObjectFinder<UStaticMesh>* StateThree;
		ConstructorHelpers::FObjectFinder<UStaticMesh>* UpgradeOne;
		ConstructorHelpers::FObjectFinder<UStaticMesh>* UpgradeTwo;
	};

	int UpgradeLevel = 0;

	TSubclassOf<class AActor> CharacterBlueprint;

	TArray<BatimentConstructionStates*> BatimentsMesh;

	int BuildLvl = 0;
	BatimentType Type;
	int TypeIndex = 0;

	void CreateBatiment(const TCHAR* StateOne, const TCHAR* StateTwo, const TCHAR* StateThree, const TCHAR* UpgradeOne = nullptr, const TCHAR* UpgradeTwo = nullptr);

	void CreateImageAssets(const TCHAR* Path);

	void CreateImageUnityAssets(const TCHAR* Path);

	TArray <UTexture2D*> ImageAssets;
	TArray <UTexture2D*> ImageAssetsUnity;



	void RepeatingFunction();

	FTimerHandle MemberTimerHandle;
	int RepeatingCallsRemaining = 0;

	

	TArray<CreationUnity*> CreationList;
	TArray<int> CreationUnityTime;

	float UnityCreationPercent = 0.f;

	bool Selected = false;
};
