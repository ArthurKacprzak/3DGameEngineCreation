// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RtsUnityAIController.generated.h"

/**
 * 
 */
UCLASS()
class RTSGAME_API ARtsUnityAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ARtsUnityAIController(): Super()
	{
		this->bReplicates = true;
		this->bOnlyRelevantToOwner = false;
	}
};
