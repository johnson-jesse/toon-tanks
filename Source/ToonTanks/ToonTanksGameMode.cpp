// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (Tank->GetTankPlayerController())
		{
			Tank->DisableInput(Tank->GetTankPlayerController());
			Tank->GetTankPlayerController()->bShowMouseCursor = false;
		}
		GameOver(false);
	}

	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		if (--TargetTowers <= 0) GameOver(true);
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		const FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnabledTimerDelegate, StartDelay, false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}