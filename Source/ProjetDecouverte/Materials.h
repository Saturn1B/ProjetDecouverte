// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "BuyButton.h"
#include "Tutorisation.h"
#include "Materials.generated.h"

class Shop;
class Parametters;
class Inventory;
class AchievmentsTab;

UCLASS()
class PROJETDECOUVERTE_API AMaterials : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMaterials();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	int matUse = 0;

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;

	UPROPERTY(editanywhere)
		TArray<int> materialsCount;

	UPROPERTY(editanywhere)
		TArray<class UTextBlock*> materialsText;

	UPROPERTY(editanywhere)
		class UCanvasPanel* matPanel;

	UPROPERTY(editanywhere)
		class UButton* matButton;

	UPROPERTY(editanywhere)
		class UButton* backButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATutorisation* Tutorisation;

	void UpdateMaterial(int index, int value);

	void CheckMat();

	UFUNCTION()
		void MatTab();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class AShop* shop;
	UPROPERTY(editanywhere, Category = "UI")
		class AParametters* parametters;
	UPROPERTY(editanywhere, Category = "UI")
		class AInventory* inventory;
	UPROPERTY(editanywhere, Category = "UI")
		class AAchievmentsTab* achievmentsTab;
};
