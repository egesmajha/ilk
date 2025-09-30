// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants/Public/APotActor.h"

// Sets default values
AAPotActor::AAPotActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAPotActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPotActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

