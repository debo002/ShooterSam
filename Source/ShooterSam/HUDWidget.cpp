// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"

void UHUDWidget::SetHealthBarPercent(float NewPercent)
{
	if (NewPercent >= 0.0f && NewPercent <= 1.0f)
	{
		TargetHealthPercent = NewPercent;
	}
}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (HealthBar)
	{
		// Smooth interpolation towards target health
		CurrentHealthPercent = FMath::FInterpTo(CurrentHealthPercent, TargetHealthPercent, InDeltaTime, HealthBarInterpSpeed);
		HealthBar->SetPercent(CurrentHealthPercent);
	}
}
