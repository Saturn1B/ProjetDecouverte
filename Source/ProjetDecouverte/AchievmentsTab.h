// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Achievments.h"
#include "Tutorisation.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "AchievmentsTab.generated.h"

class Shop;
class Parametters;
class Materials;
class Inventory;

UCLASS()
class PROJETDECOUVERTE_API AAchievmentsTab : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAchievmentsTab();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	int currentIndex;

	UPROPERTY(editanywhere)
		TArray<class AAchievments*> achievments;

	UPROPERTY(editanywhere)
		TArray<class UBorder*> achievmentsUI;

	UPROPERTY(editanywhere)
		class UBorder* achievmentsPopup;

	UPROPERTY(editanywhere)
		class UTextBlock* popupTitle;
	UPROPERTY(editanywhere)
		class UTextBlock* popupPara;

	void RemoveAchievment(AAchievments* toRemove);

	void HidePopup();

	UFUNCTION()
		void AchieveTab();

	UPROPERTY(editanywhere)
		class UCanvasPanel* achievments_ui;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATutorisation* Tutorisation;

	UPROPERTY(editanywhere)
		class UButton* achieveButton;
	UPROPERTY(editanywhere)
		class UButton* achieveBackButton;

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;

	UPROPERTY(editanywhere, Category = "UI")
		class AParametters* parametters;
	UPROPERTY(editanywhere, Category = "UI")
		class AShop* shop;
	UPROPERTY(editanywhere, Category = "UI")
		class AMaterials* material;
	UPROPERTY(editanywhere, Category = "UI")
		class AInventory* inventory;
};
