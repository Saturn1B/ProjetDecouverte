// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "BonusSelector.h"
#include "Tutorisation.h"
#include "BuyButton.generated.h"

class Shop;
class Tools;
class Inventory;

/**
 *
 */
UCLASS()
class PROJETDECOUVERTE_API UBuyButton : public UButton
{
	GENERATED_BODY()

public :

	UBuyButton();

	UPROPERTY(editanywhere)
		int toolIndex;

	UPROPERTY(editanywhere)
		bool isBonus;

	UPROPERTY(editanywhere)
		bool isBought;

	UPROPERTY(editanywhere)
		class AShop* shop;

	UPROPERTY(editanywhere)
		class ATools* tool;

	UPROPERTY(editanywhere)
		class UBonusSelector* bonus;

	UPROPERTY(editanywhere)
		class UTextBlock* text;

	UPROPERTY(editanywhere)
		class UTextBlock* price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATutorisation* Tutorisation;

	UPROPERTY(editanywhere, Category = "Sound")
		USoundBase* buySound;

	UFUNCTION(BlueprintCallable)
		void Clicked();

};
