// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	TargetLocation = OriginalLocation + MoveOffset;
	Speed = FVector::Distance(TargetLocation, OriginalLocation) / MoveTime;
	SoundRef = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DoorScrapingSound, GetOwner()->GetActorLocation(), UE::Math::TRotator<double>::ZeroRotator, 1.0F, 1.0F, 0.0F, (USoundAttenuation*)nullptr, (USoundConcurrency*)nullptr, false);
//	if(SoundRef!=nullptr)
//	{
		SoundRef->Stop();
//	}
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ShouldMove)
	{
		CurrentLocation = GetOwner()->GetActorLocation();
		GetOwner()->SetActorLocation(FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed));
	}
	else
	{
		CurrentLocation = GetOwner()->GetActorLocation();
		GetOwner()->SetActorLocation(FMath::VInterpConstantTo(CurrentLocation, OriginalLocation, DeltaTime, Speed));
	}
	
	if(CurrentLocation != OriginalLocation && CurrentLocation != TargetLocation)
	{
	
		if(!Sounded)
		{
			Sounded = true;
	//		if(SoundRef!=nullptr)
	//		{
				SoundRef->Play();
	//		}
			UE_LOG(LogTemp, Warning, TEXT("Playsound"));
		}
		
	}
	else
	{
		if(Sounded)
		{
			Sounded = false;
	//		if(SoundRef!=nullptr)
	//		{
				SoundRef->Stop();
	//		}
			UE_LOG(LogTemp, Warning, TEXT("PauseSound"));
		}
		
	}
	

}

void UMover::IncrementCurrentTriggerCount()
{
	if(!FlipFlopMover)
	{
		CurrentTriggerCount++;
		CheckTriggerRequirement();
	}
	else
	{
		ShouldMove = !ShouldMove;
	}
}

void UMover::DecrementCurrentTriggerCount()
{
	if(!FlipFlopMover)
	{
		CurrentTriggerCount--;
		CheckTriggerRequirement();
	}
	else
	{
		ShouldMove = !ShouldMove;
	}
}

void UMover::CheckTriggerRequirement()
{
	if(!PermanentlyOpened)
	{
		PermanentlyOpened = CurrentTriggerCount >= TotalTriggerToPermanentlyOpen;
		ShouldMove = CurrentTriggerCount>=MinimumTriggerRequirement;
	}
	else
	{
		ShouldMove = true;
	}
}