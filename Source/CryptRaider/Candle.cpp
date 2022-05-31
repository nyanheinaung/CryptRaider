// Fill out your copyright notice in the Description page of Project Settings.

#include "Candle.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ACandle::ACandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CandleFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("CandleFire"));
	CandleFire->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACandle::BeginPlay()
{
	Super::BeginPlay();
	//CandleFire->SetVisibility(false);
}

// Called every frame
void ACandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	if(!(Mover->PermanentlyOpened))
//	{
		if(Mover->CurrentTriggerCount>=TriggerNumber)
		{
			CandleFire->SetVisibility(true);
		}
		else
		{
			if(!(Mover->PermanentlyOpened))
			{
				CandleFire->SetVisibility(false);
			}
			
		}
//	}
	

}

void ACandle::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}