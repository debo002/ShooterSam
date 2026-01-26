// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_PlayerLocationIfSeen.h"
#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update PlayerLocation If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	if (!OwnerController)
	{
		return;
	}

	AShooterSamCharacter* Player = OwnerController->PlayerCharacter;
	UBlackboardComponent* Blackboard = OwnerController->GetBlackboardComponent();

	if (!Player || !Blackboard)
	{
		return;
	}

	// Prevent AI from tracking corpses
	if (!Player->bIsAlive)
	{
		Blackboard->ClearValue(GetSelectedBlackboardKey());
		OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		return;
	}

	if (OwnerController->LineOfSightTo(Player))
	{
		Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
		OwnerController->SetFocus(Player);
	}
	else
	{
		Blackboard->ClearValue(GetSelectedBlackboardKey());
		OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
	}
}
