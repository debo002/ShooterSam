// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"
#include "ShooterSam.h"
#include "TimerManager.h"

AShooterSamGameMode::AShooterSamGameMode()
{
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(World, 0));
	if (!Player)
	{
		UE_LOG(LogShooterSam, Warning, TEXT("Player pawn not found at BeginPlay - AI will not track player"));
	}

	TArray<AActor*> ShooterAIActors;
	UGameplayStatics::GetAllActorsOfClass(World, AShooterAI::StaticClass(), ShooterAIActors);

	for (AActor* ShooterAIActor : ShooterAIActors)
	{
		AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);
		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(Player);
		}
	}
}

void AShooterSamGameMode::OnPlayerDeath()
{
	if (bGameEnded)
	{
		return;
	}

	bGameEnded = true;
	UE_LOG(LogShooterSam, Display, TEXT("Player died! Restarting in %.1f seconds..."), RestartDelay);

	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(RestartTimerHandle, this, &AShooterSamGameMode::RestartLevel, RestartDelay, false);
	}
}

void AShooterSamGameMode::OnPlayerWin()
{
	if (bGameEnded)
	{
		return;
	}

	bGameEnded = true;
	UE_LOG(LogShooterSam, Display, TEXT("Victory! All enemies defeated. Restarting in %.1f seconds..."), RestartDelay);

	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(RestartTimerHandle, this, &AShooterSamGameMode::RestartLevel, RestartDelay, false);
	}
}

void AShooterSamGameMode::RestartLevel()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	FName LevelName = MapToRestart;
	
	// If no map specified, get current level name
	if (LevelName == NAME_None)
	{
		FString CurrentLevelName = World->GetMapName();
		// Remove "UEDPIE_0_" prefix if in PIE mode
		CurrentLevelName.RemoveFromStart(World->StreamingLevelsPrefix);
		LevelName = FName(*CurrentLevelName);
	}

	UE_LOG(LogShooterSam, Display, TEXT("Restarting level: %s"), *LevelName.ToString());
	UGameplayStatics::OpenLevel(World, LevelName, false);
}

void AShooterSamGameMode::CheckWinCondition()
{
	if (bGameEnded)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	TArray<AActor*> AIActors;
	UGameplayStatics::GetAllActorsOfClass(World, AShooterAI::StaticClass(), AIActors);

	// Check if all AI are dead
	bool bAllAIDead = true;
	for (AActor* AIActor : AIActors)
	{
		AShooterAI* AIController = Cast<AShooterAI>(AIActor);
		if (AIController && AIController->MyCharacter && AIController->MyCharacter->bIsAlive)
		{
			bAllAIDead = false;
			break;
		}
	}

	if (bAllAIDead && AIActors.Num() > 0)
	{
		OnPlayerWin();
	}
}

