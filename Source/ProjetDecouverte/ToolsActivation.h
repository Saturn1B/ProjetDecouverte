// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "ToolsUse.h"
#include "ToolsShop.h"
#include "ToolsActivation.generated.h"

/**
 * 
 */
UCLASS()
class PROJETDECOUVERTE_API UToolsActivation : public UButton
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void SetCurrentTool();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int index = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UToolsUse* currentTool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AAutomaticTools* tool;
	
};
