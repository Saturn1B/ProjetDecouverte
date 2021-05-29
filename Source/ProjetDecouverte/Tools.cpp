// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools.h"

// Sets default values
ATools::ATools()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATools::BeginPlay()
{
	Super::BeginPlay();
	
	currentCost = baseCost;
	currentDamage = baseDamage;
	upgradeIndex = 0;
	isActive = false;
}

void ATools::Buy()
{
	/*for (size_t i = 0; i < currentCost.Num(); i++)
	{
		materials->UpdateMaterial(i, -currentCost[i]);
	}*/

	upgradeIndex += 1;

	for (size_t i = 0; i < currentCost.Num(); i++)
	{
		currentCost[i] = FMath::RoundHalfToEven(baseCost[i] * FMath::Pow(costCoeff, upgradeIndex));
	}

	isActive = true;
}

void ATools::Upgrade()
{
	/*for (size_t i = 0; i < currentCost.Num(); i++)
	{
		materials->UpdateMaterial(i, -currentCost[i]);
	}*/

	upgradeIndex += 1;

	for (size_t i = 0; i < currentCost.Num(); i++)
	{
		currentCost[i] = FMath::RoundHalfToEven(baseCost[i] * FMath::Pow(costCoeff, upgradeIndex));
	}
	//currentProd = FMath::RoundHalfToEven((baseProd * upgradeIndex) * prodCoeff);
	currentDamage = FMath::RoundHalfToEven((baseDamage * upgradeIndex) * damageCoeff);
}

