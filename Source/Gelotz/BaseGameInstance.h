// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	VE_Default	UMETA(DisplayName = "Mannequin"),
	VE_Tina		UMETA(DisplayName = "Tina"),
	VE_Grayfox	UMETA(DisplayName = "Grayfox")
};

UCLASS()
class GELOTZ_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	ECharacterClass characterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance Settings")
		float roundTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance Settings")
		int numRounds;
};
