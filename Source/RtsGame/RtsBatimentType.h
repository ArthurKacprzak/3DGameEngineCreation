// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RtsBatimentType.generated.h"

UENUM(BlueprintType)
enum BatimentType
{
	CAMP		UMETA(DisplayName = "CAMP"),
	CASERNE		UMETA(DisplayName = "CASERNE"),
	ARCHERY		UMETA(DisplayName = "ARCHERY"),
	STABLES		UMETA(DisplayName = "STABLES"),
	TOWER		UMETA(DisplayName = "TOWER")
};

static const int CAMP_INDEX = 0;
static const int CASERNE_INDEX = 1;
static const int ARCHERY_INDEX = 2;
static const int STABLES_INDEX = 3;
static const int TOWER_INDEX = 4;