// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsInRange()) RotateTurret(Tank->GetActorLocation());
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (IsInRange()) Fire();
}

bool ATower::InFireRange() const
{
	if (!Tank) return false;
	const float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	return Distance <= FireRange;
}

