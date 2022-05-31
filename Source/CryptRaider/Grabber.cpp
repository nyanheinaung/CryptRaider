// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * MaxGrabDistance;
		GetPhysicsHandle()->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Released()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
		
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	if(HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add("Grabbed");
		HitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		GetPhysicsHandle()->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			HitResult.GetComponent()->GetComponentRotation()
		);
		UE_LOG(LogTemp, Display, TEXT("Grabbed %s"), *HitResult.GetActor()->GetActorNameOrLabel());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Hitting Anything"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber requires Physics Handle Component!!"));
	}
	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

//	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 1);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
		);
}