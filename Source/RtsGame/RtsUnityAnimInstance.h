// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RtsUnityAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API URtsUnityAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CharacterMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CharacterAnimZ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isCharacterAttacking_;

	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();
};
