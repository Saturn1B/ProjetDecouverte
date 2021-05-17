// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetLayers.h"
#include "MyPlayerController.h"
#include "Materials.h"
#include "Kismet/GameplayStatics.h"
#include "AutomaticTools.generated.h"

UCLASS()
class PROJETDECOUVERTE_API AAutomaticTools : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAutomaticTools();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Costs

	UPROPERTY(editanywhere)
		TArray<float> baseCost;
	UPROPERTY(editanywhere)
	TArray<float> currentCost;

	UPROPERTY(editanywhere)
		float costCoeff;

	//Prod

	UPROPERTY(editanywhere)
		TArray<float> baseProd;

	TArray<float> currentProd;

	UPROPERTY(editanywhere)
		float prodCoeff;

	//Time

	UPROPERTY(editanywhere)
		float baseTime;

	//Damage

	UPROPERTY(editanywhere)
		float baseDamage;

	float currentDamage;

	UPROPERTY(editanywhere)
		float damageCoeff;

	//UpgradeStats

	float upgradeIndex;

	void Buy();

	void Upgrade();

	void Mine();

	UPROPERTY(editanywhere)
		class APlanetLayers* currentLayer;

	UPROPERTY(editanywhere)
		bool isActive;

	UPROPERTY(editanywhere)
		int Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMaterials* materials;
};
