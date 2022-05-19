// Fill out your copyright notice in the Description page of Project Settings.


#include "TinaCharacter.h"

ATinaCharacter::ATinaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATinaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATinaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATinaCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
}
