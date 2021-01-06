// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsUnityAnimInstance.h"
#include "RtsUnity.h"

void URtsUnityAnimInstance::UpdateAnimationProperties()
{
	const APawn* character = TryGetPawnOwner();
	const ARtsUnity* Unity;

	if (character && (Unity = Cast<ARtsUnity>(character)) != nullptr)
	{
//		isCharacterAttacking_ = Unity->GetIsAttacking();
		CharacterMovementSpeed = Unity->GetXAnimation();
		CharacterAnimZ = Unity->GetZAnimation();
	}
}