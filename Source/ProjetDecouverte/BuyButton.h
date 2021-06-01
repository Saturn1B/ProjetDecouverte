// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "BuyButton.generated.h"

class Shop;
class Tools;

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
		class AShop* shop;

	UPROPERTY(editanywhere)
		class ATools* tool;

	UPROPERTY(editanywhere)
		class UTextBlock* text;

	UFUNCTION(BlueprintCallable)
		void Clicked();

};
