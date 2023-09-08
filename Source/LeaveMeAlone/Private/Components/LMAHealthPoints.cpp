// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#include "Components/LMAHealthPoints.h"
#include "Math/UnrealMathUtility.h"

ULMAHealthPoints::ULMAHealthPoints()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool ULMAHealthPoints::IsAlive() const
{
	return Health > 0.0f;
}

bool ULMAHealthPoints::AddHealth(float NewHealth) 
{
	if (!IsAlive() || IsHealthFull())
		return false;

	Health = FMath::Clamp(Health + NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	return true;
}
bool ULMAHealthPoints::IsHealthFull() const 
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void ULMAHealthPoints::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
	AActor* OwnerComponent = GetOwner();
	if (OwnerComponent)
	{
		OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &ULMAHealthPoints::OnTakeAnyDamage);
	}
}

void ULMAHealthPoints::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!IsAlive())
		return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);

	if (!IsAlive())
	{
		OnDeath.Broadcast();
	}
}

void ULMAHealthPoints::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}