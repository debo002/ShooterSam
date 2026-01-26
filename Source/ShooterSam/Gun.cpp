// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"

void AGun::BeginPlay()
{
	Super::BeginPlay();

	if (MuzzleFlashParticleSystem)
	{
		MuzzleFlashParticleSystem->Deactivate();
	}
}

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Muzzle Flash"));
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);
}

void AGun::PullTrigger()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	if (MuzzleFlashParticleSystem)
	{
		MuzzleFlashParticleSystem->Activate(true);
	}
	
	if (ShootSound)
	{
		UGameplayStatics::PlaySoundAtLocation(World, ShootSound, GetActorLocation());
	}

	if (OwnerController)
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

		FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		// ECC_GameTraceChannel2 = Weapon trace (ignores triggers, hit detection only)
		bool bIsHit = World->LineTraceSingleByChannel(HitResult, ViewPointLocation, EndLocation, ECC_GameTraceChannel2, Params);
		if (bIsHit)
		{
			if (ImpactParticleSystem)
			{
				// Orient impact VFX along surface normal
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, ImpactParticleSystem, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
			}
			
			if (ImpactSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, ImpactSound, HitResult.ImpactPoint);
			}

			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UGameplayStatics::ApplyDamage(HitActor, BulletDamage, OwnerController, this, UDamageType::StaticClass());
			}
		}
	}
}

