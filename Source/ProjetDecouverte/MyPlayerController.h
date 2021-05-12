// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlanetLayers.h"
#include "AutomaticTools.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.generated.h"

UCLASS()
class PROJETDECOUVERTE_API AMyPlayerController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class APlayerController* MyController;

	void OnMouseClick();

	void OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location);

	/*UPROPERTY(editanywhere)
		UStaticMeshComponent* Visible;*/

	UPROPERTY(editanywhere)
		class APlanetLayers* currentLayer;
};
