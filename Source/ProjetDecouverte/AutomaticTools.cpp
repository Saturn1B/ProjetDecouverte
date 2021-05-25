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
	//Mine();
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
	currentProd = FMath::RoundHalfToEven((baseProd * upgradeIndex) * prodCoeff);
	currentDamage = FMath::RoundHalfToEven((baseDamage * upgradeIndex) * damageCoeff);
}

void AAutomaticTools::Mine()
{
	if (isMining)
	{
		if (currentLayer != NULL)
		{
			currentLayer->LooseHP(currentDamage);

			for (size_t i = 0; i < currentLayer->materialsIndex.Num(); i++)
			{
				materials->UpdateMaterial(currentLayer->materialsIndex[i], currentProd);
			}

			if (currentLayer->HP > 0)
			{
				FTimerHandle handle;
				GetWorldTimerManager().SetTimer(handle, this, &AAutomaticTools::Mine, baseTime, false);
			}
			else
			{
				currentLayer = NULL;
			}
		}
		else if (currentPiece != NULL)
		{
			currentPiece->LooseHP(currentDamage);

			for (size_t i = 0; i < currentPiece->materialsIndex.Num(); i++)
			{
				materials->UpdateMaterial(currentPiece->materialsIndex[i], currentProd);
			}

			if (currentPiece->HP > 0)
			{
				FTimerHandle handle;
				GetWorldTimerManager().SetTimer(handle, this, &AAutomaticTools::Mine, baseTime, false);
			}
			else
			{
				currentPiece = NULL;
				EndMining();
			}
		}
	}
	
}

void AAutomaticTools::StartMining()
{
	isMining = true;
	Mine();
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &AAutomaticTools::EndMining, stayTime, false);
}

void AAutomaticTools::EndMining()
{
	isMining = false;
}

