// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsBuildingBatiment.h"
#include "RtsUnity.h"
#include "RtsMainGameHud.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARtsBuildingBatiment::ARtsBuildingBatiment() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->bReplicates = true;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBatiment"));

	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/RtsGame/Unity/MyRtsUnity.MyRtsUnity'"));
	if (ItemBlueprint.Object) {
		CharacterBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}
	
	this->CreateBatiment(
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_TownHall_0.SM_TownHall_0'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_TownHall_1.SM_TownHall_1'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/SM_TownHall.SM_TownHall'"));

	this->CreateBatiment(
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_Barracks_0.SM_Barracks_0'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_Barracks_1.SM_Barracks_1'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/SM_Barracks.SM_Barracks'"));

	this->CreateBatiment(
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_Archery_0.SM_Archery_0'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_Archery_1.SM_Archery_1'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/SM_Archery.SM_Archery'"));

	this->CreateBatiment(
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_Stables_0.SM_Stables_0'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_Stables_1.SM_Stables_1'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/SM_Stables.SM_Stables'"));

	this->CreateBatiment(
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_Tower_A_0.SM_Tower_A_0'"),

		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/Construction/SM_Tower_A_1.SM_Tower_A_1'"),
		TEXT("StaticMesh'/Game/Toony_Tiny_RTS_Set/Meshes/Buildings/SM_Tower_A.SM_Tower_A'"));
	

	
	this->SetRootComponent(this->Mesh);

	this->SetReplicateMovement(true);
	this->SetReplicates(true);
	this->Mesh->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
	this->Mesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	this->Mesh->SetCollisionProfileName(TEXT("Pawn"));

	this->CreateImageAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/buildCamp.buildCamp'"));
	this->CreateImageAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Caserne.Caserne'"));
	this->CreateImageAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Archery.Archery'"));
	this->CreateImageAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Stables.Stables'"));
	this->CreateImageAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Tower.Tower'"));

	this->CreateImageUnityAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/peon.peon'"));
	this->CreateImageUnityAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Infantry.Infantry'"));
	this->CreateImageUnityAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Archer.Archer'"));
	this->CreateImageUnityAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Cavalry.Cavalry'"));
	this->CreateImageUnityAssets(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/Orc.Orc'"));

}

void ARtsBuildingBatiment::CreateImageAssets(const TCHAR* Path)
{
	ConstructorHelpers::FObjectFinder <UTexture2D> ImageFinder(Path);

	ImageAssets.Add(ImageFinder.Object);
}

void ARtsBuildingBatiment::CreateImageUnityAssets(const TCHAR* Path)
{
	ConstructorHelpers::FObjectFinder <UTexture2D> ImageFinder(Path);

	ImageAssetsUnity.Add(ImageFinder.Object);
}

void ARtsBuildingBatiment::CreateBatiment(const TCHAR *StateOne, const TCHAR* StateTwo, const TCHAR* StateThree)
{
	BatimentConstructionStates* BatimentTmp = new BatimentConstructionStates();

	BatimentTmp->StateOne = new ConstructorHelpers::FObjectFinder<UStaticMesh>(StateOne);
	BatimentTmp->StateTwo = new ConstructorHelpers::FObjectFinder<UStaticMesh>(StateTwo);
	BatimentTmp->StateThree = new ConstructorHelpers::FObjectFinder<UStaticMesh>(StateThree);

	this->BatimentsMesh.Add(BatimentTmp);
}

// Called when the game starts or when spawned
void ARtsBuildingBatiment::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARtsBuildingBatiment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->BasicStats.Health > this->BasicStats.MaxHealth / 2 && this->BuildLvl == 0) {
		this->Mesh->SetStaticMesh(this->BatimentsMesh[this->TypeIndex]->StateTwo->Object);
		this->BuildLvl++;
	}
	else if (this->BasicStats.Health == this->BasicStats.MaxHealth && this->BuildLvl == 1) {
		this->Mesh->SetStaticMesh(this->BatimentsMesh[this->TypeIndex]->StateThree->Object);
		this->BuildLvl++;
	}
	
}

void ARtsBuildingBatiment::RepeatingFunction()
{
	AMainGameHud* Hud = Cast<AMainGameHud>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	CreationUnity* creationUnity = *this->CreationList.begin();

	this->UnityCreationPercent += 1.f / this->CreationUnityTime[creationUnity->ID];
	if (this->Selected) {
		Hud->UpdateProgressBar(this->UnityCreationPercent);
	}

	if (--RepeatingCallsRemaining <= 0)
	{
		if (this->CreationList.Num()) {
			this->CreationList.RemoveAt(0, 1, false);
		}


		FVector Location = GetActorLocation();

		Location.Y += 800;
		Location.Z += 200;

		AActor* NewActor = this->GetWorld()->SpawnActor<AActor>(CharacterBlueprint, Location, FRotator::ZeroRotator);
		if (!NewActor) {
			return;
		}
		ARtsUnity* NewUnity = Cast<ARtsUnity>(NewActor);
		if (NewUnity) {
			NewUnity->UpdateType(creationUnity->Type);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("ERROR"));
		}
		Hud->UpdateCreationUnities(this->CreationList);

		this->UnityCreationPercent = 0;
		if (this->Selected) {
			Hud->UpdateProgressBar(this->UnityCreationPercent);
		}

		if (!this->CreationList.Num()) {
			GetWorldTimerManager().ClearTimer(MemberTimerHandle);
		}
		else {
			creationUnity = *this->CreationList.begin();
			this->RepeatingCallsRemaining = CreationUnityTime[creationUnity->ID];
		}
	}
}

void ARtsBuildingBatiment::UnSelect()
{
	this->Selected = false;
}

void ARtsBuildingBatiment::Select()
{
	AMainGameHud* Hud = Cast<AMainGameHud>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	this->Selected = true;
	Hud->UpdateProgressBar(this->UnityCreationPercent);
}

bool ARtsBuildingBatiment::Build(float Speed)
{
	if (this->BasicStats.Health < this->BasicStats.MaxHealth) {
		this->BasicStats.Health += Speed;
		return false;
	}
	else {
		this->BasicStats.Health = this->BasicStats.MaxHealth;
		return true;
	}
}

bool ARtsBuildingBatiment::IsCamp()
{
	return Camp;
}

void ARtsBuildingBatiment::SetBatimentType(BatimentType BatimentToBuildType)
{
	this->Mesh->SetStaticMesh(this->BatimentsMesh[0]->StateOne->Object);

	ARtsBuildingBatiment::UnityCreation* UnityCanCreate = new ARtsBuildingBatiment::UnityCreation();
	ARtsBuildingBatiment::UnityCreation* Orc = new ARtsBuildingBatiment::UnityCreation();

	switch (BatimentToBuildType)
	{
	case BatimentType::CAMP:
		this->Mesh->SetStaticMesh(this->BatimentsMesh[CAMP_INDEX]->StateOne->Object);
		this->TypeIndex = CAMP_INDEX;

		UnityCanCreate->Texture = ImageAssetsUnity[0];
		UnityCanCreate->Type = UnityType::PEASANT;
		this->CreationUnityTime.Add(10);
		this->UnityCreateImages.Add(UnityCanCreate);


		Orc->Texture = ImageAssetsUnity[4];
		Orc->Type = UnityType::ORC;
		this->CreationUnityTime.Add(50);
		this->UnityCreateImages.Add(Orc);
		break;
	case BatimentType::CASERNE:
		this->Mesh->SetStaticMesh(this->BatimentsMesh[CASERNE_INDEX]->StateOne->Object);
		this->TypeIndex = CASERNE_INDEX;

		UnityCanCreate->Texture = ImageAssetsUnity[1];
		UnityCanCreate->Type = UnityType::INFANTRY;
		this->CreationUnityTime.Add(20);
		this->UnityCreateImages.Add(UnityCanCreate);

		break;
	case BatimentType::ARCHERY:
		this->Mesh->SetStaticMesh(this->BatimentsMesh[ARCHERY_INDEX]->StateOne->Object);
		this->TypeIndex = ARCHERY_INDEX;

		UnityCanCreate->Texture = ImageAssetsUnity[2];
		UnityCanCreate->Type = UnityType::ARCHER;
		this->CreationUnityTime.Add(20);
		this->UnityCreateImages.Add(UnityCanCreate);
		break;
	case BatimentType::STABLES:
		this->Mesh->SetStaticMesh(this->BatimentsMesh[STABLES_INDEX]->StateOne->Object);
		this->TypeIndex = STABLES_INDEX;

		UnityCanCreate->Texture = ImageAssetsUnity[3];
		UnityCanCreate->Type = UnityType::CAVALRY;
		this->CreationUnityTime.Add(30);
		this->UnityCreateImages.Add(UnityCanCreate);
		break;
	case BatimentType::TOWER:
		this->Mesh->SetStaticMesh(this->BatimentsMesh[TOWER_INDEX]->StateOne->Object);
		this->TypeIndex = TOWER_INDEX;
		break;
	default:
		break;
	}
	this->Type = BatimentToBuildType;
}

TArray<ARtsBuildingBatiment::UnityCreation*> ARtsBuildingBatiment::GetUnityCreateImages()
{
	return this->UnityCreateImages;
}

BatimentType ARtsBuildingBatiment::GetType()
{
	return this->Type;
}

UTexture2D*ARtsBuildingBatiment::GetTextureImage()
{
	return this->ImageAssets[this->TypeIndex];
}

UTexture2D* ARtsBuildingBatiment::GetTextureImageUnityByNumber(int Number)
{
	return this->UnityCreateImages[Number]->Texture;
}

TArray<ARtsBuildingBatiment::CreationUnity*> ARtsBuildingBatiment::GetCreationList()
{
	return this->CreationList;
}

void ARtsBuildingBatiment::AddCreationUnity(UTexture2D* Image, int UnityID)
{
	CreationUnity* creationUnity = new CreationUnity();

	creationUnity->ID = UnityID;
	creationUnity->Texture = Image;
	creationUnity->Type = this->UnityCreateImages[UnityID]->Type;
	this->CreationList.Add(creationUnity);
	if (this->RepeatingCallsRemaining <= 0) {
		this->RepeatingCallsRemaining = CreationUnityTime[UnityID];
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ARtsBuildingBatiment::RepeatingFunction, 1.0f, true);
	}
}