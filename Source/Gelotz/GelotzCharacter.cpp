// Copyright Epic Games, Inc. All Rights Reserved.

#include "GelotzCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Gelotz/GelotzGameMode.h>

AGelotzCharacter::AGelotzCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	//CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	//SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	//SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	otherPlayer = nullptr;
	hurtbox = nullptr;
	directionalInput = EDirectionalInput::VE_Default;
	transform = FTransform();
	scale = FVector(0.0f, 0.0f, 0.0f);

	playerHealth = 1.00f;
	maxDistanceApart = 1000.0f;

	wasLightAttackUsed = false;
	wasMediumAttackUsed = false;
	wasHeavyAttackUsed = false;
	wasSpecialAttackUsed = false;
	isFlipped = false;
	hasLandedHit = false;
	canMove = false;
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

//Bind Input Karakter
void AGelotzCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (auto gameMode = Cast<AGelotzGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (gameMode-> player1 == this)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player 1 Has Bound Their Controls . "));
			// set up gameplay key bindings
			PlayerInputComponent->BindAction("JumpP1", IE_Pressed, this, &AGelotzCharacter::Jump);
			PlayerInputComponent->BindAction("JumpP1", IE_Released, this, &AGelotzCharacter::StopJumping);
			PlayerInputComponent->BindAction("CrouchP1", IE_Pressed, this, &AGelotzCharacter::StartCrouching);
			PlayerInputComponent->BindAction("CrouchP1", IE_Released, this, &AGelotzCharacter::StopCrouching);
			PlayerInputComponent->BindAxis("MoveRightP1", this, &AGelotzCharacter::MoveRight);

			PlayerInputComponent->BindAction("Attack1P1", IE_Pressed, this, &AGelotzCharacter::StartAttack1);
			//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ACGelotzharacter::StopAttack1);
			PlayerInputComponent->BindAction("Attack2P1", IE_Pressed, this, &AGelotzCharacter::StartAttack2);
			//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ACGelotzharacter::StopAttack1);
			PlayerInputComponent->BindAction("Attack3P1", IE_Pressed, this, &AGelotzCharacter::StartAttack3);
			//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ACGelotzharacter::StopAttack1);
			PlayerInputComponent->BindAction("Attack4P1", IE_Pressed, this, &AGelotzCharacter::StartAttack4);
			//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ACGelotzharacter::StopAttack1);

			PlayerInputComponent->BindTouch(IE_Pressed, this, &AGelotzCharacter::TouchStarted);
			PlayerInputComponent->BindTouch(IE_Released, this, &AGelotzCharacter::TouchStopped);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player 2 Has Bound Their Controls "));
			// set up gameplay key bindings
			PlayerInputComponent->BindAction("JumpP2", IE_Pressed, this, &AGelotzCharacter::Jump);
			PlayerInputComponent->BindAction("JumpP2", IE_Released, this, &AGelotzCharacter::StopJumping);
			PlayerInputComponent->BindAction("CrouchP2", IE_Pressed, this, &AGelotzCharacter::StartCrouching);
			PlayerInputComponent->BindAction("CrouchP2", IE_Released, this, &AGelotzCharacter::StopCrouching);
			PlayerInputComponent->BindAxis("MoveRightP2", this, &AGelotzCharacter::MoveRight);

			PlayerInputComponent->BindAction("Attack1P2", IE_Pressed, this, &AGelotzCharacter::StartAttack1);
			//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ACGelotzharacter::StopAttack1);
			PlayerInputComponent->BindAction("Attack2P2", IE_Pressed, this, &AGelotzCharacter::StartAttack2);
			//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ACGelotzharacter::StopAttack1);
			PlayerInputComponent->BindAction("Attack3P2", IE_Pressed, this, &AGelotzCharacter::StartAttack3);
			//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ACGelotzharacter::StopAttack1);
			PlayerInputComponent->BindAction("Attack4P2", IE_Pressed, this, &AGelotzCharacter::StartAttack4);
			//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &ACGelotzharacter::StopAttack1);

			PlayerInputComponent->BindTouch(IE_Pressed, this, &AGelotzCharacter::TouchStarted);
			PlayerInputComponent->BindTouch(IE_Released, this, &AGelotzCharacter::TouchStopped);
		}
	}
	
}

// Fungsi Ketika Player Menekan Tombol

void AGelotzCharacter::Jump()
{
	ACharacter::Jump(); // Ketika Pemain Menekan Tombol Melompat Maka Character Akan Melompat
	directionalInput = EDirectionalInput::VE_Jumping;
}

void AGelotzCharacter::StopJumping()
{
	ACharacter::StopJumping(); // Ketika Pemain Melepas Tombol Melompat Maka Character Akan Turun
}

void AGelotzCharacter::Landed(const FHitResult& Hit)
{
	//ACharacter::Landed(Hit)
	directionalInput = EDirectionalInput::VE_Default; //Ketikan Character Telah Menyentuh Permukaan Maka Character Akan Idle
}

void AGelotzCharacter::StartCrouching()
{
	isCrouching = true; // Ketika Pemain Menekan Tombol Jongkok Maka Character Akan Jongkok
}

void AGelotzCharacter::StopCrouching()
{
	isCrouching = false; // Ketika Pemain Tidak Menekan Tombol Jongkok Maka Character Akan Idle
}

void AGelotzCharacter::MoveRight(float Value)
{
	 
	

		UE_LOG(LogTemp, Warning, TEXT("The directional input is: %f "), Value);

		if (directionalInput != EDirectionalInput::VE_Jumping)
		{
			if (Value > 0.20f)
			{
				directionalInput = EDirectionalInput::VE_MovingRight;
			}
			else if (Value < -0.20f)
			{
				directionalInput = EDirectionalInput::VE_MovingLeft;

			}
			else
			{
				directionalInput = EDirectionalInput::VE_Default;
			}
		}

		float currentDistanceApart = abs(otherPlayer->GetActorLocation().Y - GetActorLocation().Y);

		if (currentDistanceApart >= maxDistanceApart)
		{
			if ((currentDistanceApart + Value < currentDistanceApart && !isFlipped) || (currentDistanceApart - Value < currentDistanceApart && isFlipped))
			{
				// add movement in that direction
				AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
			}
		}
		else
		{
			// add movement in that direction
			AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
		}

	
}

void AGelotzCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AGelotzCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AGelotzCharacter::StartAttack1()
{
	UE_LOG(LogTemp, Warning, TEXT("Menggunakan Attack 1"));
	wasLightAttackUsed = true;
}

void AGelotzCharacter::StartAttack2()
{
	UE_LOG(LogTemp, Warning, TEXT("Menggunakan Attack 2"));
	wasMediumAttackUsed = true;
}

void AGelotzCharacter::StartAttack3()
{
	UE_LOG(LogTemp, Warning, TEXT("Menggunakan Attack 3"));
	wasHeavyAttackUsed = true;
}

void AGelotzCharacter::StartAttack4()
{
	UE_LOG(LogTemp, Warning, TEXT("Menggunakan Attack 4"));
	wasSpecialAttackUsed = true;
}

void AGelotzCharacter::P2KeyboardAttack1()
{
	StartAttack1();
}

void AGelotzCharacter::P2KeyboardAttack2()
{
	StartAttack2();
}

void AGelotzCharacter::P2KeyboardAttack3()
{
	StartAttack3();
}

void AGelotzCharacter::P2KeyboardAttack4()
{
	StartAttack4();
}

void AGelotzCharacter::P2KeyboardJump()
{
	Jump();
}

void AGelotzCharacter::P2KeyboardStopJumping()
{
	StopJumping();
}

void AGelotzCharacter::P2KeyboardMoveRight(float _value)
{
	MoveRight(_value);
}

void AGelotzCharacter::TakeDamage(float _damageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Menerima Damage Sebesar %f poin."), _damageAmount);
	playerHealth -= _damageAmount;
	if (otherPlayer)
	{
		otherPlayer->hasLandedHit = true;
	}

	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}



void AGelotzCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (otherPlayer)
	{
		if (auto characterMovement = GetCharacterMovement())
		{
			if (auto enemyMovement = otherPlayer->GetCharacterMovement())
			{
				if (enemyMovement->GetActorLocation().Y >= characterMovement->GetActorLocation().Y)
				{
					if (isFlipped)
					{
						if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = mesh->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = 1;
							transform.SetScale3D(scale);
							mesh->SetRelativeTransform(transform);
						}
						isFlipped = false;
					}
				}
				else
				{
					if (!isFlipped)
					{
						if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = mesh->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = -1;
							transform.SetScale3D(scale);
							mesh->SetRelativeTransform(transform);
						}
						isFlipped = true;
					}
				}
			}
		}
	}
}

