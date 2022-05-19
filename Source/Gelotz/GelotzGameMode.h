// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GelotzCharacter.h"
#include "GelotzGameMode.generated.h"


UCLASS(minimalapi)
class AGelotzGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGelotzGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		AGelotzCharacter* player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		AGelotzCharacter* player2;
};