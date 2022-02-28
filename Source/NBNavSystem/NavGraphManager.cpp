// Fill out your copyright notice in the Description page of Project Settings.


#include "NavGraphManager.h"

// Sets default values
ANavGraphManager::ANavGraphManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANavGraphManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANavGraphManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

