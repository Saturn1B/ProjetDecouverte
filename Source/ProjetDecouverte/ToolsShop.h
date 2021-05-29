// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Materials.h"
#include "MyPlayerController2.h"
#include "AchievmentsTab.h"
#include "ToolsShop.generated.h"

UCLASS()
class PROJETDECOUVERTE_API AToolsShop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToolsShop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(editanywhere)
		TSubclassOf<UUserWidget> bp_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;

	UPROPERTY(editanywhere)
		class UButton* mapButton;
	/*UPROPERTY(editanywhere)
		class UButton* achieveButton;
	UPROPERTY(editanywhere)
		class UButton* achieveBackButton;*/

	UPROPERTY(editanywhere)
		class AActor* camera;

	/*UPROPERTY(editanywhere)
		class AAchievmentsTab* achievmentsTab;*/

	UFUNCTION()
		void ZoomInOut();

	/*UFUNCTION()
		void AchieveTab();*/
};
