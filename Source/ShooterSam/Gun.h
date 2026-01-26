// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Gun.generated.h"

UCLASS()
class SHOOTERSAM_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* MuzzleFlashParticleSystem;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ImpactParticleSystem;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000.0f;

	UPROPERTY(EditAnywhere)
	float BulletDamage = 10.0f;

	UPROPERTY(EditAnywhere)
	USoundBase* ShootSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	// Controller that owns this gun - used for line traces and damage attribution
	UPROPERTY()
	AController* OwnerController;

	void PullTrigger();
};
