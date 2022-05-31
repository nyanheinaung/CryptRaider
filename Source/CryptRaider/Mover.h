// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//	void SetShouldMove(bool NewShouldMove);

//	UFUNCTION(BlueprintCallable)
	void IncrementCurrentTriggerCount();

//	UFUNCTION(BlueprintCallable)
	void DecrementCurrentTriggerCount();

	UPROPERTY(EditAnywhere)
	int32 CurrentTriggerCount = 0;

	UPROPERTY(BlueprintReadOnly)
	bool PermanentlyOpened = false;

private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;

	FVector OriginalLocation;
	FVector CurrentLocation;
	FVector TargetLocation;
	float Speed;

	UPROPERTY(EditAnywhere)
	int32 TotalTriggerToPermanentlyOpen = 2;
	


	UPROPERTY(EditAnywhere)
	int32 MinimumTriggerRequirement = 1;

	void CheckTriggerRequirement();

	UPROPERTY(EditAnywhere)
	bool FlipFlopMover = false;

	bool Sounded = false;

	UPROPERTY(EditAnywhere)
	USoundBase* DoorScrapingSound;

	UAudioComponent* SoundRef;
};
