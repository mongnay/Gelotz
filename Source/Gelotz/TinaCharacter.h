// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GelotzCharacter.h"
#include "TinaCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GELOTZ_API ATinaCharacter : public AGelotzCharacter
{
	GENERATED_BODY()
	

public:
	ATinaCharacter();

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
