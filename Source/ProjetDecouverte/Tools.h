// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToolSelector.h"
#include "Inventory.h"
#include "Tools.generated.h"

UCLASS()
class PROJETDECOUVERTE_API ATools : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATools();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	//Costs

	UPROPERTY(editanywhere)
		TArray<float> baseCost;

	TArray<float> currentCost;

	UPROPERTY(editanywhere)
		float costCoeff;

	//Damage

	UPROPERTY(editanywhere)
		float baseDamage;

	float currentDamage;

	UPROPERTY(editanywhere)
		float damageCoeff;

	//Bool

	UPROPERTY(editanywhere)
		bool onHold;

	UPROPERTY(editanywhere)
		bool onLiquid;

	//Timer

	UPROPERTY(editanywhere)
		float holdTimer;

	//Stats

	UPROPERTY(editanywhere)
		int index;

	float upgradeIndex;

	UPROPERTY(editanywhere)
		bool isActive;

	void Buy();

	void Upgrade();

	UPROPERTY(editanywhere)
		class AInventory* inventory;
};
