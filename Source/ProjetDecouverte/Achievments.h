// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Achievments.generated.h"

class AchievmentsTab;
class Materials;

UCLASS()
class PROJETDECOUVERTE_API AAchievments : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAchievments();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//class AchievmentsTab* instance;
	//class Materials* instance;

	UPROPERTY(editanywhere)
		int materialToDestroy;

	UPROPERTY(editanywhere)
		int numberToDestroy;

	UPROPERTY(editanywhere)
		int goldGiven;

	UPROPERTY(editanywhere)
		FString Title;

	UPROPERTY(editanywhere)
		FString Paragragh;

	UPROPERTY(editanywhere)
		int index;

	UPROPERTY(editanywhere)
		class AMaterials* materialsTotal;

	UPROPERTY(editanywhere)
		bool isComplete = false;

	void CheckCondition();

	void CompleteAchievment();

};
