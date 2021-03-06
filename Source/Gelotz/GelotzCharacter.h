// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GelotzCharacter.generated.h"

UENUM(BlueprintType)
// Inisialasasi Untuk Tombol Arah
enum class ECharacterState : uint8
{
	VE_Default		UMETA(DisplayName = "NOT_MOVING"),
	VE_MovingRight	UMETA(DisplayName = "MOVING_RIGHT"),
	VE_MovingLeft	UMETA(DisplayName = "MOVING_LEFT"),
	VE_Jumping		UMETA(DisplayName =	"JUMPING"),
	VE_Stunned		UMETA(DisplayName = "STUNNED"),
	VE_Blocking		UMETA(DisplayName = "BLOCKING"),
	VE_Crouching	UMETA(DisplayName = "CROUCHING"),
	VE_Launched		UMETA(DisplayName = "LAUNCHED")
};

UCLASS(config = Game)
class AGelotzCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	void StartAttack1();
	void StartAttack2();
	void StartAttack3();
	void StartAttack4();
	void StartExceptionalAttack();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardAttack1();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardAttack2();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardAttack3();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardAttack4();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardJump();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardStopJumping();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardMoveRight(float _value);

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void Tick(float DeltaTime) override;

	// Fungsi Untuk Melompat
	virtual void Jump() override;
	virtual void StopJumping() override;
	virtual void Landed(const FHitResult& Hit) override;

	//Membuat Karakter Jongkok
	UFUNCTION(BlueprintCallable)
	void StartCrouching();

	//Membuat Karakter Berhenti Jongkok
	UFUNCTION(BlueprintCallable)
	void StopCrouching();

	//Membuat Karakter Menangkis
	UFUNCTION(BlueprintCallable)
	void StartBlocking();

	//Membuat Karakter Berhenti Menangkis
	UFUNCTION(BlueprintCallable)
	void StopBlocking();

	//Menentukan Apa Yang Harus Karakter Lakukan Jika bertabrakan dengan hitbox
	UFUNCTION(BlueprintCallable)
	void CollidedWithProximityHitbox();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float _damageAmount, float _hitstunTime, float _blockstunTime, float _pushbackAmount, float _launchAmount);

	//Menentukan Karakter Terdorong Berapa Jauh
	void PerformPushback(float _pushbackAmount, float _launchAmount, bool _hasBlocked);
	
	//Fungsi Karakter Masuk Ke Animasi Stun
	void BeginStun();

	//Fungsi Karakter Mengakhiri Animasi Stun
	void EndStun();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayDamageSoundEffect();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeToDamageMaterial();

	UFUNCTION(BlueprintCallable)
		void WinRound();

	UFUNCTION(BlueprintCallable)
		void WinMatch();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void NotifyRoundStart();

	UFUNCTION(BlueprintImplementableEvent)
		void NotifyRoundEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
		AGelotzCharacter* otherPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* hurtbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		ECharacterState characterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FTransform transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FVector scale;

	//Untuk Mengatur Durasi Stun
	FTimerHandle stunTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float playerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float maxDistanceApart;

	//Durasi Jika Karakter Terkena Stun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float stunTime;

	//Nilai Gravitasi (Tergantung Berapa lama Karakter Di Udara)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float gravityScale;

	//Jumlah Super Meter Karakter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Super Meter")
		float superMeterAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logic")
		int roundsWon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasLightAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasMediumAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasHeavyAttackUsed;

	// Apakah Player Menggunakan Jurus?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasSuperUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasLightExAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasMediumExAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasHeavyExAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		bool isFlipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool hasLandedHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool canMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
		bool isDeviceForMultiplayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool hasLostRound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool hasWonMatch;


	// End of APawn interface


public:
	AGelotzCharacter();

	

	/** Returns SideViewCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
