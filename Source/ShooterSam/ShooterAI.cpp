// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAI::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterAI::StartBehaviorTree(AShooterSamCharacter* Player)
{
	if (!EnemyAIBehaviorTree)
	{
		return;
	}

	MyCharacter = Cast<AShooterSamCharacter>(GetPawn());
	if (!MyCharacter)
	{
		return;
	}

	if (Player)
	{
		PlayerCharacter = Player;
	}

	RunBehaviorTree(EnemyAIBehaviorTree);

	// Store spawn point for patrol/return behavior
	UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
	if (MyBlackboard && PlayerCharacter)
	{
		MyBlackboard->SetValueAsVector("StartLocation", MyCharacter->GetActorLocation());
	}
}
