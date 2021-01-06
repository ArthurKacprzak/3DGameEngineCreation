// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsUserWidget.h"
#include "UMG/Public/Components/Button.h"
#include "UMG/Public/Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Widget.h"
#include "Blueprint/WidgetTree.h"

void URtsUserWidget::NativeConstruct()
{
    this->Super::NativeConstruct();


}

void URtsUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void URtsUserWidget::OnClick()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("click!"));
}