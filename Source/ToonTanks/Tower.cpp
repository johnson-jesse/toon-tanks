// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Tank) return;
		
	if (const float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation()); Distance <= FireRange)
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
