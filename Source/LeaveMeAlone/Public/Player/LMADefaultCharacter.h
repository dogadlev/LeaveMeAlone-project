// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;
class UDecalComponent;
class UMaterialInterface;
class ULMAHealthPoints;
class UAnimMontage;
class ULMAWeaponComponent;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALMADefaultCharacter();

	UFUNCTION()
	ULMAHealthPoints* GetHealthComponent() { return HealthComponent; }

	UFUNCTION()
	bool GetSprintState() { return IsSprinting; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthPoints* HealthComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAWeaponComponent* WeaponComponent;
	
	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MaxArmLength = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MinArmLength = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	bool IsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float StaminaDecreaseRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float StaminaIncreaseRate;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;
	float ArmLength = 1400.0f;
	float FOV = 55.0f;

	void MoveForward(float);
	void MoveRight(float);
	void ChangeCameraArmLength(float);

	void OnDeath();
	void OnHealthChanged(float);

	void RotationPlayerOnCursor();

	void StopSprint();
	void StartSprint();
};