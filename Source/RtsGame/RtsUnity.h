// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Animation/BlendSpace1D.h"
#include "RtsBuildingBatiment.h"
#include "Components/SpotLightComponent.h"
#include "RtsUnityType.h"
#include "RtsUnityAnimInstance.h"
#include "RtsResource.h"
#include "RtsUnity.generated.h"

UCLASS()
class RTSGAME_API ARtsUnity : public ACharacter
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ARtsUnity();

	UStaticMeshComponent* Selected;

	UFUNCTION(BlueprintCallable, Category = "IsMyCharacter")
		bool IsMyCharacter();

public:
	struct {
		float Speed = 10.f;
		float Health = 100.f;
		float MaxHealth = 100.f;
		bool Builder = false;
		float BuildSpeed = 0.f;
		float Attack = 5.f;
		bool Recolter = false;
		float ColectSpeed = 13;
	} BasicStats;

	struct MeshAssets {
		ConstructorHelpers::FObjectFinder<USkeletalMesh> *Skeletal;
		ConstructorHelpers::FClassFinder<URtsUnityAnimInstance>* Animation;
		UTexture2D* TextureImage;

		MeshAssets(const TCHAR* Skeletal, const TCHAR* AnimationBlueprintClass, const TCHAR* TextureImagePath)
		{
			this->Skeletal = new ConstructorHelpers::FObjectFinder<USkeletalMesh>(Skeletal);
			this->Animation = new ConstructorHelpers::FClassFinder<URtsUnityAnimInstance>(AnimationBlueprintClass);
			this->TextureImage = (new ConstructorHelpers::FObjectFinder<UTexture2D>(TextureImagePath))->Object;
		}
	};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialisation")
		bool MainPlayer = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialisation")
		TEnumAsByte<UnityType> Type;

	UTexture2D* GetTextureImage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Select")
	void Build(ARtsBuildingBatiment * Batiment);

	void Recolte(ARtsResource* Resource);

	const float GetXAnimation() const
	{
		if (this->IsMoving) {
			return this->BasicStats.Speed * 5;
		}
		else {
			return 0;
		}
	}

	float GetHealth() const
	{
		return this->BasicStats.Health;
	}

	float GetMaxHealth() const
	{
		return this->BasicStats.MaxHealth;
	}

	bool IsBuilder()
	{
		return this->BasicStats.Builder;
	}

	void UpdateType(UnityType T);

public:
	bool GoTo(FVector Position);


	void Select();

	void Unselect();

	float GetZAnimation() const;

	void Attack(ARtsUnity* UnityToAttack);

	bool BeAttacked(float value);

	void MoveTo();

	float RessourceColected = 0.f;

private:
	void InitAnimation();
	void InitCapsuleComponent();
	void InitStatusTemplate(UnityType T);
	UTexture2D* TextureImage;

	TArray<FVector> PointToGoList;

	bool IsMoving;

private:
	USkeletalMesh* Skeletal = nullptr;
	UClass* AnimationBlueprintClass = nullptr;
	ARtsBuildingBatiment* BatimentToBuild = nullptr;
	ARtsResource* ResourceToColect = nullptr;
	ARtsUnity* UnityToAttack = nullptr;


	void AttackRepeatingFunction();
	void ColectRepeatingFunction();

	float ZAnimation = 50.f;
	FTimerHandle MemberTimerHandleMove;
	FTimerHandle MemberTimerHandleAttack;
	FTimerHandle MemberTimerHandleColect;

	void StopMove();
	bool IsSelected = false;

};
