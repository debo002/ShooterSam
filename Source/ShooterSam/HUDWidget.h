// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"

#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERSAM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Auto-binds to widget named "HealthBar" in UMG designer (optional)
	UPROPERTY(EditAnywhere, meta = (BindWidgetOptional))
	UProgressBar* HealthBar;

	// Smoothing speed for health bar animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
	float HealthBarInterpSpeed = 5.0f;

	void SetHealthBarPercent(float NewPercent);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	float CurrentHealthPercent = 1.0f;
	float TargetHealthPercent = 1.0f;
};
