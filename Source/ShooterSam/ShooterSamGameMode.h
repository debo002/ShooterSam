// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterSamGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AShooterSamGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	AShooterSamGameMode();

	// Delay before restarting level on win/lose
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
	float RestartDelay = 2.0f;

	// Map name to reload (e.g., "Map1"). Leave empty to reload current map.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
	FName MapToRestart = NAME_None;

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void OnPlayerDeath();

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void OnPlayerWin();

	UFUNCTION(BlueprintCallable, Category = "Game Rules")
	void CheckWinCondition();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle RestartTimerHandle;
	bool bGameEnded = false;

	void RestartLevel();
};



