// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "AutomaticTools.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "ToolsButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJETDECOUVERTE_API UToolsButton : public UButton
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void ButtonInteract();

	UFUNCTION(BlueprintCallable)
		void BuyTool(AAutomaticTools* tool);

	UFUNCTION(BlueprintCallable)
		void UpgradeTool(AAutomaticTools* tool);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int index = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTextBlock* ButtonTextState;

};
