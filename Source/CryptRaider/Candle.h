// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mover.h"
#include "Candle.generated.h"

UCLASS()
class CRYPTRAIDER_API ACandle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* NewMover);
	
private:
	UMover* Mover;

	UPROPERTY(EditAnywhere)
	int32 TriggerNumber=1;

	UPROPERTY(VisibleAnywhere, Category = "CandleFire")
	class UParticleSystemComponent* CandleFire;
};
