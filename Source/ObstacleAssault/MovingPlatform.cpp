// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}


void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += PlatformVelocity * DeltaTime;
	SetActorLocation(CurrentLocation);

	ShowDistance = GetDistanceMoved(CurrentLocation);

	if(ShouldPlatformReturn())
	{
		StartLocation += PlatformVelocity.GetSafeNormal() * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
}

float AMovingPlatform::GetDistanceMoved(FVector CurrentLocation) const
{
	return FVector::Dist(StartLocation, CurrentLocation);
}


bool AMovingPlatform::ShouldPlatformReturn() const
{
	return ShowDistance > MoveDistance;
}


