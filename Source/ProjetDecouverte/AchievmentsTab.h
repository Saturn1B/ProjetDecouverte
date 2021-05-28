// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Achievments.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "AchievmentsTab.generated.h"

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	UPROPERTY(editanywhere)
		class UCanvasPanel* achievments_ui;

	UPROPERTY(editanywhere)
		UUserWidget* created_ui;
};
