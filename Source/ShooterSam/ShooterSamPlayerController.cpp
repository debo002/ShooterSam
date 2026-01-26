// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterSamPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "ShooterSam.h"
#include "Widgets/Input/SVirtualJoystick.h"

void AShooterSamPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Touch-only: spawn mobile controls widget
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// Z-order 0 = behind gameplay UI
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogShooterSam, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}

	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}
}

void AShooterSamPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			// Priority 0 = base layer, higher priorities override
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// Mouse/keyboard contexts excluded on touch devices
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}
