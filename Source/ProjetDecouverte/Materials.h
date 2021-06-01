// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "BuyButton.h"
#include "Materials.generated.h"

class Shop;

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

	UPROPERTY(editanywhere)
		TArray<int> materialsCount;

	UPROPERTY(editanywhere)
		TArray<class UTextBlock*> materialsText;

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AShop* shop;

	void UpdateMaterial(int index, int value);

};
