// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#include "Components/LMAHealthComponent.h"
#include "Math/UnrealMathUtility.h"

ULMAHealthComponent::ULMAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool ULMAHealthComponent::IsAlive() const
{
	return Health > 0.0f;
}

void ULMAHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
	AActor* OwnerComponent = GetOwner();
	if (OwnerComponent)
	{
		OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &ULMAHealthComponent::OnTakeAnyDamage);
	}
}

void ULMAHealthComponent::OnTakeAnyDamage(
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
