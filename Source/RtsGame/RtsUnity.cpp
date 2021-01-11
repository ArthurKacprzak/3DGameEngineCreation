// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsUnity.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "RtsUnityAnimInstance.h"
#include "NavigationSystem.h"
#include "RtsUnityAnimInstance.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationPath.h"
#include "RtsMainGameHud.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"


// Sets default values
ARtsUnity::ARtsUnity() : Super()
{

	this->InitCapsuleComponent();	
	InitStatusTemplate(this->Type.GetValue());

	this->GetMesh()->SetCollisionProfileName(TEXT("Pawn"));
	this->GetMesh()->SetupAttachment(this->RootComponent);
	this->GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -200.f));
	this->GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));



	float Size = 2.f;
	this->GetMesh()->SetWorldScale3D(FVector(Size, Size, Size));

/*	this->Selected = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshSelected"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SelectedVisualAsset(TEXT("StaticMesh'/Game/RtsGame/Map/Shape/Shape_Torus.Shape_Torus'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInterface> Material_Gold(TEXT("Material'/Game/RtsGame/Map/Materials/M_Ground_Grass.M_Ground_Grass'"));

	if (SelectedVisualAsset.Succeeded() && Material_Gold.Succeeded())
	{
		this->Selected->SetStaticMesh(SelectedVisualAsset.Object);
		this->Selected->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		this->Selected->SetRelativeScale3D(FVector(0.f, 0.f, 0.f));
		this->Selected->SetMaterial(0, Material_Gold.Object);
	}*/
	
//	this->Selected->SetupAttachment(this->RootComponent);
}

void ARtsUnity::InitAnimation()
{
	this->GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	if (this->AnimationBlueprintClass) {
		this->GetMesh()->SetAnimInstanceClass(this->AnimationBlueprintClass);
	}

}

void ARtsUnity::InitCapsuleComponent()
{
	this->GetCapsuleComponent()->InitCapsuleSize(140, 200);
	this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ARtsUnity::BeginPlay()
{
	Super::BeginPlay();
	
//	this->Selected->SetVisibility(false);

	InitStatusTemplate(this->Type.GetValue());
	FTimerHandle UniqueHandle;
//	this->ClearFog();

}

void ARtsUnity::MoveTo()
{
	FVector ToGo = this->PointToGoList[0];
	FVector Location = GetActorLocation();

	this->IsMoving = true;
	if (ToGo.X - this->BasicStats.Speed <= Location.X && ToGo.X + this->BasicStats.Speed >= Location.X &&
		ToGo.Y - this->BasicStats.Speed <= Location.Y && ToGo.Y + this->BasicStats.Speed >= Location.Y) {
		ToGo.Z = Location.Z;
		this->SetActorLocation(ToGo);
		GetWorldTimerManager().ClearTimer(MemberTimerHandleMove);
		this->IsMoving = false;
		this->PointToGoList.RemoveAt(0);

		if (this->PointToGoList.Num()) {
			GetWorldTimerManager().SetTimer(this->MemberTimerHandleMove, this, &ARtsUnity::MoveTo, .02f, true);
		}
	}
	float k = this->BasicStats.Speed / FMath::Sqrt(FMath::Pow(ToGo.X - Location.X, 2) + FMath::Pow(ToGo.Y - Location.Y, 2));
	float X = k * (ToGo.X - Location.X);
	float Y = k * (ToGo.Y - Location.Y);
	
	Location.X += X;
	Location.Y += Y;

	FRotator Rotation = this->GetActorRotation();
	Rotation.Yaw = FMath::RadiansToDegrees(FMath::Atan(Y / X));
	if (X < 0) {
		Rotation.Yaw += 180;
	}

	this->SetActorRotation(Rotation);
	this->SetActorLocation(Location);
}

// Called every frame
void ARtsUnity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	if (this->BatimentToBuild) {
		FVector BatimentLocation = this->BatimentToBuild->GetActorLocation();

		if ((Location - BatimentLocation).Size() <= 1200) {
			ZAnimation = 75.f;
			this->StopMove();
			if (this->BatimentToBuild->Build(this->BasicStats.BuildSpeed * DeltaTime)) {
				this->BatimentToBuild = nullptr;

				ZAnimation = 50.f;
			}
		}
	}

}

bool ARtsUnity::GoTo(FVector Position)
{
	FVector Location = this->GetActorLocation();
	UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	UNavigationPath* path = navSys->FindPathToLocationSynchronously(GetWorld(), Location, Position, this);

	if (path && path->IsValid()) {
		this->PointToGoList = path->PathPoints;

		ZAnimation = 50.f;
		GetWorldTimerManager().SetTimer(this->MemberTimerHandleMove, this, &ARtsUnity::MoveTo, .02f, true);
		return true;
	}
	return false;
}

void ARtsUnity::Select()
{
	IsSelected = true;
//	this->Selected->SetVisibility(true);
}

void ARtsUnity::Unselect()
{
	IsSelected = false;
//	this->Selected->SetVisibility(false);
}

void ARtsUnity::UpdateType(UnityType T)
{
	InitStatusTemplate(T);
}

void ARtsUnity::InitStatusTemplate(UnityType T)
{
	static MeshAssets Orc(
		TEXT("SkeletalMesh'/Game/ParagonNarbash/Characters/Heroes/Narbash/Meshes/Narbash.Narbash'"),
		TEXT("AnimBlueprint'/Game/RtsGame/HeroOrc/Basic/UnityAnimBP.UnityAnimBP_C'"),
		TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Orc.Orc'"));

	static MeshAssets Peasant(
		TEXT("SkeletalMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Characters_Prebuilt/Units/SK_Peasant.SK_Peasant'"),
		TEXT("AnimBlueprint'/Game/RtsGame/Unity/Peasant/PeasantAnimBlueprint.PeasantAnimBlueprint_C'"),
		TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/peon.peon'"));

	static MeshAssets Infantry(
		TEXT("SkeletalMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Characters_Prebuilt/Units/SK_Light_Infantry.SK_Light_Infantry'"),
		TEXT("AnimBlueprint'/Game/RtsGame/Unity/Peasant/PeasantAnimBlueprint.PeasantAnimBlueprint_C'"),
		TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Infantry.Infantry'"));

	static MeshAssets Archer(
		TEXT("SkeletalMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Characters_Prebuilt/Units/SK_Archer.SK_Archer'"),
		TEXT("AnimBlueprint'/Game/RtsGame/Unity/Peasant/PeasantAnimBlueprint.PeasantAnimBlueprint_C'"),
		TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Archer.Archer'"));

	static MeshAssets Cavalry(
		TEXT("SkeletalMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Characters_Prebuilt/Cavalry/SK_Light_Cavalry.SK_Light_Cavalry'"),
		TEXT("AnimBlueprint'/Game/RtsGame/Unity/Cavalry/CavalryAnimBlueprint.CavalryAnimBlueprint_C'"),
		TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Cavalry.Cavalry'"));

	this->BasicStats.Builder = false;
	switch (T)
	{
	case UnityType::ORC:
		this->Skeletal = Orc.Skeletal->Object;
		this->AnimationBlueprintClass = Orc.Animation->Class;
		this->TextureImage = Orc.TextureImage;
		break;

	case UnityType::PEASANT:
		this->Skeletal = Peasant.Skeletal->Object;
		this->AnimationBlueprintClass = Peasant.Animation->Class;
		this->BasicStats.Builder = true;
		this->BasicStats.Recolter = true;
		this->BasicStats.BuildSpeed = 50.f;
		this->TextureImage = Peasant.TextureImage;
		break;
	case UnityType::INFANTRY:
		this->Skeletal = Infantry.Skeletal->Object;
		this->AnimationBlueprintClass = Infantry.Animation->Class;
		this->TextureImage = Infantry.TextureImage;
		break;
	case UnityType::ARCHER:
		this->Skeletal = Archer.Skeletal->Object;
		this->AnimationBlueprintClass = Archer.Animation->Class;
		this->TextureImage = Archer.TextureImage;
		break;

	case UnityType::CAVALRY:
		this->Skeletal = Cavalry.Skeletal->Object;
		this->AnimationBlueprintClass = Cavalry.Animation->Class;
		this->BasicStats.Speed = 25;
		this->TextureImage = Cavalry.TextureImage;
		break;
	default:
		break;
	}

	GetMesh()->SetSkeletalMesh(this->Skeletal);
	this->InitAnimation();
}

void ARtsUnity::Build(ARtsBuildingBatiment* Batiment)
{
	if (!this->BasicStats.Builder) {
		return;
	}

	if (this->GoTo(Batiment->GetActorLocation())) {
		this->BatimentToBuild = Batiment;
	}
}

void ARtsUnity::Recolte(ARtsResource* Resource)
{
	if (!this->BasicStats.Recolter) {
		return;
	}

	if (this->GoTo(Resource->GetActorLocation())) {
		this->ResourceToColect = Resource;
		GetWorldTimerManager().SetTimer(this->MemberTimerHandleColect, this, &ARtsUnity::ColectRepeatingFunction, .5f, true);
	}
}

void ARtsUnity::ColectRepeatingFunction()
{
	if (this->ResourceToColect) {
		FVector Location = GetActorLocation();
		FVector RessourceLocation = this->ResourceToColect->GetActorLocation();

		if ((Location - RessourceLocation).Size() <= 500) {
			ZAnimation = 75.f;
			this->StopMove();
			float Value = 0.f;
			if ((Value = this->ResourceToColect->Colect(this->BasicStats.ColectSpeed)) == 0.f) {
				this->ResourceToColect->ConditionalBeginDestroy();
				this->ResourceToColect = nullptr;
				ZAnimation = 50.f;
				GetWorldTimerManager().ClearTimer(MemberTimerHandleColect);
			}
			else {
				this->RessourceColected += Value;
				ARtsPlayerController * PC = Cast<ARtsPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				if (this->ResourceToColect->Type == RessourceType::THREE) {
					PC->UpdateWood(Value);
				}
				else {
					PC->UpdateStone(Value);
				}
			}
		}
	}
}

void ARtsUnity::Attack(ARtsUnity* UnityToAttackTmp)
{
	if (this->GoTo(UnityToAttackTmp->GetActorLocation())) {
		this->UnityToAttack = UnityToAttackTmp;
		GetWorldTimerManager().SetTimer(this->MemberTimerHandleAttack, this, &ARtsUnity::AttackRepeatingFunction, .5f, true);
	}
}

void ARtsUnity::AttackRepeatingFunction()
{
	if (this->UnityToAttack) {
		FVector Location = GetActorLocation();
		FVector BatimentLocation = this->UnityToAttack->GetActorLocation();

		if ((Location - BatimentLocation).Size() <= 500) {
			ZAnimation = 75.f;
			this->StopMove();
			if (this->UnityToAttack->BeAttacked(this->BasicStats.Attack)) {
				this->UnityToAttack = nullptr;
				ZAnimation = 50.f;
				GetWorldTimerManager().ClearTimer(MemberTimerHandleAttack);

			}
		}
		else {
			ZAnimation = 50.f;
		}
	}
}

bool ARtsUnity::BeAttacked(float Value)
{
	if (this->BasicStats.Health > 0) {
		this->BasicStats.Health -= Value;
		if (this->IsSelected) {
			AMainGameHud* Hud = Cast<AMainGameHud>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
			Hud->UpdateStateByName(this->BasicStats.Health, "TextStateHeart", this->BasicStats.MaxHealth);
		}
		return false;
	}
	else {
		// IM DEAD
		ZAnimation = 25.f;
		return true;
	}
}

float ARtsUnity::GetZAnimation() const
{
	return this->ZAnimation;
}

void ARtsUnity::StopMove()
{
	GetWorldTimerManager().ClearTimer(MemberTimerHandleMove);
	this->IsMoving = false;
}

bool ARtsUnity::IsMyCharacter()
{
	if (this->GetRemoteRole() != ROLE_Authority && this->MainPlayer) {
		return true;
	}
	if (this->GetRemoteRole() == ROLE_Authority && !this->MainPlayer) {
		return true;
	}
	return false;
}

UTexture2D* ARtsUnity::GetTextureImage()
{
	return this->TextureImage;
}