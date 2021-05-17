// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomaticTools.h"
#define LOG(fstring) GLog->Log(fstring)

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
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanetLayers::StaticClass(), FoundActors);
	for (AActor* layerActor : FoundActors)
	{
		APlanetLayers* layer = Cast<APlanetLayers>(layerActor);
		if (layer->isTopLayer)
		{
			currentLayer = layer;
		}
	}

	TArray<AActor*> FoundMaterials;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMaterials::StaticClass(), FoundMaterials);
	materials = Cast<AMaterials>(FoundMaterials[0]);
}

// Called every frame
void AAutomaticTools::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAutomaticTools::Buy()
{
	for (size_t i = 0; i < currentCost.Num(); i++)
	{
		materials->UpdateMaterial(i, -currentCost[i]);
	}

	upgradeIndex += 1;

	for (size_t i = 0; i < currentCost.Num(); i++)
	{
		currentCost[i] = FMath::RoundHalfToEven(baseCost[i] * FMath::Pow(costCoeff, upgradeIndex));
	}

	isActive = true;
	Mine();
	//TO DO retirer le montant de min�raux d�fini
}

void AAutomaticTools::Upgrade()
{
	for (size_t i = 0; i < currentCost.Num(); i++)
	{
		materials->UpdateMaterial(i, -currentCost[i]);
	}

	upgradeIndex += 1;

	for (size_t i = 0; i < currentCost.Num(); i++)
	{
		currentCost[i] = FMath::RoundHalfToEven(baseCost[i] * FMath::Pow(costCoeff, upgradeIndex));
	}
	for (size_t i = 0; i < currentProd.Num(); i++)
	{
		currentProd[i] = FMath::RoundHalfToEven((baseProd[i] * upgradeIndex) * prodCoeff);
	}
	currentDamage = FMath::RoundHalfToEven((baseDamage * upgradeIndex) * damageCoeff);
	//TO DO retirer le montant de min�raux d�fini
}

void AAutomaticTools::Mine()
{
	if (currentLayer != NULL)
	{
		currentLayer->LooseHP(currentDamage);

		for (size_t i = 0; i < currentProd.Num(); i++)
		{
			materials->UpdateMaterial(i, currentProd[i]);
		}
		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &AAutomaticTools::Mine, baseTime, false);
	}
}

