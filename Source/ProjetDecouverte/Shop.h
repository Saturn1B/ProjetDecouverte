// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Tools.h"
#include "BuyButton.h"
#include "BonusSelector.h"
#include "Tutorisation.h"
#include "Shop.generated.h"

class Parametters;
class Materials;
class Inventory;
class AchievmentsTab;

UCLASS()
class PROJETDECOUVERTE_API AShop : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;

	UPROPERTY(editanywhere)
		class UButton* shopButton;

	UPROPERTY(editanywhere)
		class UCanvasPanel* shopPanel;

	UPROPERTY(editanywhere)
		TArray<class ATools*> toolsArray;

	UPROPERTY(editanywhere)
		TArray<class UBuyButton*> buttonArray;

	UPROPERTY(editanywhere)
		TArray<class UBuyButton*> bonusArray;

	void SetButton();

	UFUNCTION()
		void ActiveShop();

	UPROPERTY(editanywhere, Category = "UI")
		class AInventory* inventory;
	UPROPERTY(editanywhere, Category = "UI")
		class AParametters* parametters;
	UPROPERTY(editanywhere, Category = "UI")
		class AMaterials* material;
	UPROPERTY(editanywhere, Category = "UI")
		class AAchievmentsTab* achievmentsTab;
	UPROPERTY(EditAnywhere, Category = "UI")
		class ATutorisation* Tutorisation;

};
