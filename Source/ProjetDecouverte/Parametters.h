// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Parametters.generated.h"

class Shop;
class Materials;
class Inventory;
class AchievmentsTab;

UCLASS()
class PROJETDECOUVERTE_API AParametters : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParametters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;

	UPROPERTY(editanywhere)
		class UCanvasPanel* paramettersPanel;

	UPROPERTY(editanywhere)
		class UButton* paramettersButton;

	UPROPERTY(editanywhere)
		class UButton* backButton;

	UFUNCTION()
		void AchieveTab();

	UPROPERTY(editanywhere, Category = "UI")
		class AInventory* inventory;
	UPROPERTY(editanywhere, Category = "UI")
		class AShop* shop;
	UPROPERTY(editanywhere, Category = "UI")
		class AMaterials* material;
	UPROPERTY(editanywhere, Category = "UI")
		class AAchievmentsTab* achievmentsTab;
};
