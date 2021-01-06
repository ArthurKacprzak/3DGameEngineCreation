// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsCameraComponent.h"

URtsCameraComponent::URtsCameraComponent()
{
	bShouldClampCamera_ = true;

	zoomAlpha_ = 1.f;
	cameraScrollSpeed_ = 3000.f;
	cameraActiveBorder_ = 100.f;
	minZoomLevel_ = 0.4f;
	maxZoomLevel_ = 10.f;
	minCameraOffset_ = 0.f;
	maxCameraOffset_ = 25000.f;
	movementSpeed_ = 10.f;

	fixedCameraAngle_ = FRotator(-40.f, 0.f, 0.f);
}

void URtsCameraComponent::GetCameraView(float deltaTime, FMinimalViewInfo& desiredView)
{
	ARtsPlayerController* playerController = nullptr;
	APawn* owner = GetOwnerPawn();
	if (owner)
	{
		playerController = Cast<ARtsPlayerController>(owner->GetController());
	}
	if (playerController)
	{
		desiredView.FOV = 30.f;
		const float currentOffset = minCameraOffset_ + zoomAlpha_ * (maxCameraOffset_ - minCameraOffset_);
		const FVector focalPos = playerController->GetFocalLocation();
		desiredView.Location = focalPos - fixedCameraAngle_.Vector() * currentOffset;
		desiredView.Rotation = fixedCameraAngle_;
	}
}

void URtsCameraComponent::OnZoomIn()
{
	SetZoomLevel(zoomAlpha_ - 0.1f);
}

void URtsCameraComponent::OnZoomOut()
{
	SetZoomLevel(zoomAlpha_ + 0.1f);
}

void URtsCameraComponent::UpdateCameraMovement(const APlayerController* playerController) const
{
	ULocalPlayer* localPlayer = Cast<ULocalPlayer>(playerController->Player);

	if (localPlayer && localPlayer->ViewportClient && localPlayer->ViewportClient->Viewport) {
		FVector2D mousePosition;
		if (!localPlayer->ViewportClient->GetMousePosition(mousePosition)) {
			return;
		}

		FViewport* viewport = localPlayer->ViewportClient->Viewport;
		const float scrollSpeed = 100.f;
		FIntPoint viewportSize = viewport->GetSizeXY();

		uint32 viewLeft = FMath::TruncToInt(localPlayer->Origin.X * viewportSize.X);
		uint32 viewRight = viewLeft + FMath::TruncToInt(localPlayer->Size.X * viewportSize.X);
		uint32 viewTop = FMath::TruncToInt(localPlayer->Origin.Y * viewportSize.Y);
		uint32 viewBottom = viewTop + FMath::TruncToInt(localPlayer->Size.Y * viewportSize.Y);

		const float maxSpeed = cameraScrollSpeed_ * FMath::Clamp(zoomAlpha_, minZoomLevel_, maxZoomLevel_);

		const uint32 mouseX = mousePosition.X;
		const uint32 mouseY = mousePosition.Y;
		float spectatorCameraSpeed = maxSpeed;
		ARtsSpectatorPawn *spectatorPawn = nullptr;

		if (true) //!bNoScrollZone_
		{
			if (mouseX >= viewLeft && mouseX <= (viewLeft + cameraActiveBorder_))
			{
				const float delta = 1.0f - float(mouseX - viewLeft) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveRight(-scrollSpeed * delta);
			}
			else if (mouseX >= (viewRight - cameraActiveBorder_) && mouseX <= viewRight)
			{
				const float delta = float(mouseX - viewRight + cameraActiveBorder_) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveRight(scrollSpeed * delta);
			}

			if (mouseY >= viewTop && mouseY <= (viewTop + cameraActiveBorder_))
			{
				const float delta = 1.0f - float(mouseY - viewTop) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveForward(scrollSpeed * delta);
			}
			else if (mouseY >= (viewBottom - cameraActiveBorder_) && mouseY <= viewBottom)
			{
				const float delta = float(mouseY - (viewBottom - cameraActiveBorder_)) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveForward(-scrollSpeed * delta);
			}
		}
	}
}

void URtsCameraComponent::MoveForward(const float value) const
{
	APawn* ownerPawn = GetOwnerPawn();

	if (ownerPawn)
	{
		ARtsPlayerController* controller = nullptr;
		APawn* owner = GetOwnerPawn();
		if (owner)
		{
			controller = Cast<ARtsPlayerController>(owner->GetController());
		}

		if (value != 0.f && controller)
		{
			FVector worldSpaceAcc = ownerPawn->GetActorLocation();;
			
			worldSpaceAcc.X += value * movementSpeed_;

			ownerPawn->SetActorLocation(worldSpaceAcc);
		}
	}
}

void URtsCameraComponent::MoveRight(const float value) const
{
	APawn* ownerPawn = GetOwnerPawn();

	if (ownerPawn)
	{
		ARtsPlayerController* controller = nullptr;
		APawn* owner = GetOwnerPawn();
		if (owner)
		{
			controller = Cast<ARtsPlayerController>(owner->GetController());
		}
		if (value != 0.f && controller)
		{
			FVector worldSpaceAcc = ownerPawn->GetActorLocation();;

			worldSpaceAcc.Y += value * movementSpeed_;

			ownerPawn->SetActorLocation(worldSpaceAcc);
		}
	}
}

void URtsCameraComponent::SetZoomLevel(float level)
{
	zoomAlpha_ = FMath::Clamp(level, minZoomLevel_, maxZoomLevel_);
}

APawn* URtsCameraComponent::GetOwnerPawn() const
{
	return Cast<APawn>(GetOwner());
}
