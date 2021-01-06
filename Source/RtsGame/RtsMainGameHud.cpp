// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsMainGameHud.h"

#include "Components/CapsuleComponent.h"
#include "Components/Button.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "RtsUnity.h"
#include "RtsBuildingBatiment.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Styling/SlateBrush.h"

AMainGameHud::AMainGameHud() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> ObjBP(TEXT("WidgetBlueprint'/Game/RtsGame/Map/Hud/RtsWidgetsHudBP.RtsWidgetsHudBP_C'"));
	this->WidgetBP.HUDWidgetClass = ObjBP.Class;
	static ConstructorHelpers::FObjectFinder <UTexture2D> ImageFinder(TEXT("Texture2D'/Game/RtsGame/Map/Hud/Textures/EmptyUnityCreation.EmptyUnityCreation'"));
	EmptyUnityCreationAsset = ImageFinder.Object;
}

void AMainGameHud::BeginPlay()
{
	Super::BeginPlay();

	if (this->WidgetBP.HUDWidgetClass != nullptr) {
		this->WidgetBP.Widget = CreateWidget<UUserWidget>(GetWorld(), this->WidgetBP.HUDWidgetClass);
		if (this->WidgetBP.Widget) {
			this->WidgetBP.Widget->AddToViewport();
			this->DrawBatimentHud(ESlateVisibility::Hidden);
			this->DrawCampHud(ESlateVisibility::Hidden);
			this->DrawSelectionHud(ESlateVisibility::Hidden);
			this->DrawUnityStatsHud(ESlateVisibility::Hidden);
		}
	}
}

void AMainGameHud::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

}

void AMainGameHud::DrawHUD()
{
	Super::DrawHUD();

	if (GEngine && GEngine->GameViewport) {
		FVector2D viewportSize;
		GEngine->GameViewport->GetViewportSize(viewportSize);
		this->UiScale = viewportSize.X / 2048.f;
	}

	this->DrawHealthBars();

	if (GetPlayerController()->GetIsSelectionActive())
	{
		const FVector selectionStartPosition = Canvas->Project(GetPlayerController()->GetSelectionStartPosition());

		this->DrawSelectionGrid(FVector2D(selectionStartPosition));
	}
	this->DrawConstructionItem();
}

void AMainGameHud::DrawHealthBars() const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AActor::StaticClass(), FoundActors);


	for (auto *Actor : FoundActors)
	{
		ARtsUnity* Character = Cast<ARtsUnity>(Actor);
		ARtsBuildingBatiment* CharacterBatiment = Cast<ARtsBuildingBatiment>(Actor);

		if (Character && Character->GetHealth() > 0) {
			if (Character->GetRemoteRole() != ROLE_Authority) {
				if (Character->MainPlayer) {
					this->DrawHealth(Character, Character->GetHealth(), Character->GetMaxHealth(), Character->GetCapsuleComponent()->GetScaledCapsuleRadius(), FLinearColor(0.f, 1.0f, 0.f, 0.7f));
				}
				else {
					this->DrawHealth(Character, Character->GetHealth(), Character->GetMaxHealth(), Character->GetCapsuleComponent()->GetScaledCapsuleRadius(), FLinearColor(1.f, 0.0f, 0.f, 0.7f));
				}
			}
			else {
				if (!Character->MainPlayer) {
					this->DrawHealth(Character, Character->GetHealth(), Character->GetMaxHealth(), Character->GetCapsuleComponent()->GetScaledCapsuleRadius(), FLinearColor(0.f, 1.0f, 0.f, 0.7f));
				}
				else {
					this->DrawHealth(Character, Character->GetHealth(), Character->GetMaxHealth(), Character->GetCapsuleComponent()->GetScaledCapsuleRadius(), FLinearColor(1.f, 0.0f, 0.f, 0.7f));
				}
			}
			continue;
		}

		if (CharacterBatiment && CharacterBatiment->GetHealth() > 0) {
			this->DrawHealth(CharacterBatiment, CharacterBatiment->GetHealth(), CharacterBatiment->GetMaxHealth(), 200, FLinearColor(0.f, 1.0f, 0.f, 0.7f));
		}
	}
}

void AMainGameHud::DrawHealth(AActor *Character, float Health, float MaxHealth, float Radius, FLinearColor Color) const
{
	// Select the center point of the bar as the character's location
	FVector Center = Character->GetActorLocation();

	// Offsets of the bar
	FVector extent = FVector(60.f, 34.f, 131.75f);

	// Project function of Canvas translates a world position to the screen position
	FVector2D Center2D = FVector2D(Canvas->Project(FVector(Center.X, Center.Y, Center.Z + extent.Z)));

	float ActorExtent = 50.f;
	float HealthPercentage = 0.5f;
	float YOffset = 10.f;

	HealthPercentage = Health / MaxHealth;
	ActorExtent = Radius;

	FVector Pos1 = Canvas->Project(FVector(Center.X, Center.Y - ActorExtent * 2, Center.Z + extent.Z));
	FVector Pos2 = Canvas->Project(FVector(Center.X, Center.Y + ActorExtent * 2, Center.Z + extent.Z));

	float BarWidth = (Pos2 - Pos1).Size2D();
	float BarHeight = BarWidth / 10;


	float x = Center2D.X - BarWidth * 0.5f;
	float y = Center2D.Y;

	x = Center2D.X - BarWidth * 0.5f;
	y = Center2D.Y - 1.f;
	FCanvasTileItem TileItem(FVector2D(x, y), FVector2D(BarWidth * HealthPercentage, BarHeight), Color);
	TileItem.BlendMode = SE_BLEND_Translucent;


	Canvas->DrawItem(TileItem);
}

void AMainGameHud::DrawSelectionGrid(FVector2D GridStartPos)
{
	FVector2D MousePosition;
	GetPlayerController()->GetMousePosition(MousePosition.X, MousePosition.Y);

	float GridWidth = MousePosition.X - GridStartPos.X;
	float GridHeight = MousePosition.Y - GridStartPos.Y;

	FCanvasTileItem fillTileItem(GridStartPos, FVector2D(GridWidth, GridHeight), FLinearColor(1.0f, 1.0f, 1.0f, 0.2f));
	fillTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(fillTileItem);

	FCanvasTileItem TileItem(GridStartPos, FVector2D(GridWidth, 1.f), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.UV1 = FVector2D(GridWidth * 0.1f, 1.f);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos + FVector2D(0.f, GridHeight);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos;
	TileItem.Size = FVector2D(1.f, GridHeight);
	TileItem.UV1 = FVector2D(1.f, GridHeight * 0.1f);
	Canvas->DrawItem(TileItem);

	TileItem.Position = GridStartPos + FVector2D(GridWidth, 0.f);
	Canvas->DrawItem(TileItem);
}

void AMainGameHud::DrawConstructionItem()
{

}

ARtsPlayerController *AMainGameHud::GetPlayerController() const
{
	return Cast<ARtsPlayerController>(PlayerOwner);
}

void AMainGameHud::NewUnitySelection(TArray<ARtsUnity*> UnitySelected)
{
	if (!UnitySelected.Num()) {
		this->DrawBatimentHud(ESlateVisibility::Hidden);
		this->DrawUnityStatsHud(ESlateVisibility::Hidden);
		return;
	}

	this->DrawUnityStatsHud(ESlateVisibility::Hidden);
	if (UnitySelected.Num() == 1) {
		this->DrawUnityStatsHud(ESlateVisibility::Visible, UnitySelected[0]);
	}

	bool Builder = true;

	for (auto Unity : UnitySelected) {
		if (Unity->IsBuilder() && Builder != false) {
			if (Unity->GetRemoteRole() != ROLE_Authority) {
				Builder = true;
			}
		}
		else {
			Builder = false;
		}
	}
	if (Builder) {
		this->DrawBatimentHud(ESlateVisibility::Visible);
	}
	else {
		this->DrawBatimentHud(ESlateVisibility::Hidden);
	}
}

void AMainGameHud::NewBatimentSelection(TArray<ARtsBuildingBatiment*> BatimentSelected)
{
	if (!BatimentSelected.Num()) {
		this->DrawCampHud(ESlateVisibility::Hidden);
		this->DrawSelectionHud(ESlateVisibility::Hidden);
		return;
	}

	for (auto Batiment : BatimentSelected) {
		this->DrawCampHud(Batiment);
		this->DrawSelectionHud(ESlateVisibility::Visible);
		return;
	}
	this->DrawCampHud(ESlateVisibility::Hidden);
	this->DrawSelectionHud(ESlateVisibility::Hidden);
}

void AMainGameHud::DrawCampHud(ESlateVisibility slateVisibility)
{
	this->WidgetBP.Widget->GetWidgetFromName("ButtonAction_1")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonAction_2")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonAction_3")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonAction_4")->SetVisibility(slateVisibility);
}

void AMainGameHud::DrawCampHud(ARtsBuildingBatiment* Batiment)
{
	TArray<ARtsBuildingBatiment::UnityCreation*> CreationList = Batiment->GetUnityCreateImages();
	int tmp = 1;

	this->DrawCampHud(ESlateVisibility::Hidden);
	for (auto Creation : CreationList) {
		FString base = "ImageAction_";
		base += FString::FromInt(tmp);
		UImage* Image = Cast<UImage>(this->WidgetBP.Widget->GetWidgetFromName(*base));

		if (Image) {

			FString baseButton = "ButtonAction_";
			baseButton += FString::FromInt(tmp);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, baseButton);
			this->WidgetBP.Widget->GetWidgetFromName(*baseButton)->SetVisibility(ESlateVisibility::Visible);
			Image->SetBrushFromTexture(Creation->Texture);
		}
		tmp++;
	}
}

void AMainGameHud::DrawBatimentHud(ESlateVisibility slateVisibility)
{
	this->WidgetBP.Widget->GetWidgetFromName("ButtonBatimentOne")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonBatimentTwo")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonBatimentThree")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonBatimentFour")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonBatimentFive")->SetVisibility(slateVisibility);

}

void AMainGameHud::DrawSelectionHud(ESlateVisibility slateVisibility)
{
	this->WidgetBP.Widget->GetWidgetFromName("ImageSelected")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ProgressBarCreateUnity")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonUnityFIleList1")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonUnityFIleList2")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonUnityFIleList3")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonUnityFIleList4")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonUnityFIleList5")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ButtonUnityFIleList6")->SetVisibility(slateVisibility);
}

void AMainGameHud::DrawUnityStatsHud(ESlateVisibility slateVisibility, ARtsUnity* Unity)
{

	this->WidgetBP.Widget->GetWidgetFromName("ImageStateHeart")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ImageStateAttack")->SetVisibility(slateVisibility);

	this->WidgetBP.Widget->GetWidgetFromName("TextStateAttack")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("TextStateHeart")->SetVisibility(slateVisibility);
	
	this->UpdateStateByName(Unity->BasicStats.Attack, "TextStateAttack");
	this->UpdateStateByName(Unity->BasicStats.Health, "TextStateHeart", Unity->BasicStats.MaxHealth);

	if (Unity->BasicStats.Builder) {
		this->WidgetBP.Widget->GetWidgetFromName("ImageStateMine")->SetVisibility(slateVisibility);
		this->WidgetBP.Widget->GetWidgetFromName("TextStateMine")->SetVisibility(slateVisibility);
		this->UpdateStateByName(Unity->RessourceColected, "TextStateMine");
	}
}

void AMainGameHud::UpdateStateByName(float Value, FName Name, float Max)
{
	UTextBlock* TextHeart = Cast<UTextBlock>(this->WidgetBP.Widget->GetWidgetFromName(Name));

	FString Text = "";
	Text += FString::SanitizeFloat(Value);
	if (Max) {
		Text += " / ";
		Text += FString::SanitizeFloat(Max);
	}
	TextHeart->SetText(FText::FromString(Text));
}

void AMainGameHud::DrawUnityStatsHud(ESlateVisibility slateVisibility)
{

	this->WidgetBP.Widget->GetWidgetFromName("ImageStateMine")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ImageStateHeart")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("ImageStateAttack")->SetVisibility(slateVisibility); 

	this->WidgetBP.Widget->GetWidgetFromName("TextStateMine")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("TextStateHeart")->SetVisibility(slateVisibility);
	this->WidgetBP.Widget->GetWidgetFromName("TextStateAttack")->SetVisibility(slateVisibility);
}

void AMainGameHud::UpdateSelectionHud(UTexture2D* Image)
{
	this->WidgetBP.Widget->GetWidgetFromName("ImageSelected")->SetVisibility(ESlateVisibility::Visible);
	UImage *i = Cast<UImage>(this->WidgetBP.Widget->GetWidgetFromName("ImageSelected"));

	i->SetBrushFromTexture(Image);
}

void AMainGameHud::UpdateCreationUnities(TArray<ARtsBuildingBatiment::CreationUnity*> Images)
{
	int i = 0;
	int n = 0;

	while (n != 6) {
		n++;
		FString base = "ButtonUnityFileList";
		base += FString::FromInt(n);
		UImage* Button = Cast<UImage>(this->WidgetBP.Widget->GetWidgetFromName(*base));
		if (Button) {
			Button->SetBrushFromTexture(this->EmptyUnityCreationAsset);
		}
	}

	for (auto Image : Images) {
		i++;
		FString base = "ButtonUnityFileList";
		base += FString::FromInt(i);
		UImage* Button = Cast<UImage>(this->WidgetBP.Widget->GetWidgetFromName(*base));
		if (Button) {
			Button->SetBrushFromTexture(Image->Texture);
		}
	}
}

void AMainGameHud::UpdateProgressBar(float PercentValue)
{
	UProgressBar* ProgressBar = Cast<UProgressBar>(this->WidgetBP.Widget->GetWidgetFromName(TEXT("ProgressBarCreateUnity")));

	ProgressBar->SetPercent(PercentValue);
}