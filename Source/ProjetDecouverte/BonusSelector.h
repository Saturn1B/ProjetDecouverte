// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MyPlayerController2.h"
#include "Kismet/GameplayStatics.h"
#include "BonusSelector.generated.h"

/**
 *
 */
UCLASS()
class PROJETDECOUVERTE_API UBonusSelector : public UButton
{
	GENERATED_BODY()

public :

	UPROPERTY(editanywhere)
		int damageBonus;

	UPROPERTY(editanywhere)
		int materialBonus;

	UPROPERTY(editanywhere)
		int index;

	UPROPERTY(editanywhere)
		bool damage;

	UFUNCTION(BlueprintCallable)
		void Clicked();

	UFUNCTION(BlueprintCallable)
		void RestoreValue();

	UFUNCTION(BlueprintCallable)
		void RestoreButton();
};
