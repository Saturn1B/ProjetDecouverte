// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomaticTools.h"

// Sets default values
AAutomaticTools::AAutomaticTools()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAutomaticTools::BeginPlay()
{
	Super::BeginPlay();

	currentCost = baseCost;
	currentProd = baseProd;
	currentDamage = baseDamage;
	upgradeIndex = 0;

	isActive = false;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController::StaticClass(), FoundActors);
	currentLayer = Cast<AMyPlayerController>(FoundActors[0])->currentLayer;
}

// Called every frame
void AAutomaticTools::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAutomaticTools::Upgrade()
{
	currentCost = baseCost * FMath::Pow(costCoeff, upgradeIndex);
	currentProd = (baseProd * upgradeIndex) * prodCoeff;
	currentDamage = (baseDamage * upgradeIndex) * damageCoeff;
}

