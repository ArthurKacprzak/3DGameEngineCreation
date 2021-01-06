// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RtsUnityType.generated.h"

UENUM(BlueprintType)
enum UnityType
{
	PEASANT		UMETA(DisplayName = "PEASANT"),
	ORC			UMETA(DisplayName = "ORC"),
	INFANTRY	UMETA(DisplayName = "INFANTRY"),
	ARCHER		UMETA(DisplayName = "ARCHER"),
	CAVALRY		UMETA(DisplayName = "CAVALRY")
};