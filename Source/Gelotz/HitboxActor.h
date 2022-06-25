// GG Gaming

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitboxActor.generated.h"

UENUM(BlueprintType)
enum class EHitboxEnum : uint8
{
	HB_PROXIMITY	UMETA(DisplayName = "Proximity"),
	HB_STRIKE		UMETA(DisplayName = "Strike"),
	HB_HURTBOX		UMETA(DisplayName = "Hurtbox")
};

UCLASS()
class GELOTZ_API AHitboxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitboxActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void TriggerVisualizeHitbox();

	UFUNCTION(BlueprintImplementableEvent)
		void VisualizeHitbox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitboxDamage;

	//inisialisasi HitStun Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitstunTime;
	//inisialisasi blockstun Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float blockstunTime;

	//Jumlah Jarak Karakter Terdorong
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float pushbackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		EHitboxEnum hitboxType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FVector hitboxLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
