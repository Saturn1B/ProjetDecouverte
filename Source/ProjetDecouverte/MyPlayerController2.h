// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlanetLayers.h"
#include "LayerPiece.h"
#include "Planet.h"
#include "SolarSystem.h"
#include "AutomaticTools.h"
#include "Materials.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController2.generated.h"

UCLASS()
class PROJETDECOUVERTE_API AMyPlayerController2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayerController2();

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

	void OnFingerRelease(const ETouchIndex::Type FingerIndex, const FVector Location);

	/*UPROPERTY(editanywhere)
		UStaticMeshComponent* Visible;*/

	UPROPERTY(editanywhere)
		class AActor* ObjectSelected;

	UPROPERTY(editanywhere)
		int PlanetSelected;

	UPROPERTY(editanywhere)
		TArray<class AActor*> Planets;

	UPROPERTY(editanywhere)
		bool onDrag;

	UPROPERTY(editanywhere)
		bool zoomedOut;

	UPROPERTY(editanywhere)
		FVector2D currentTouch;

	UPROPERTY(editanywhere)
		FVector2D previousTouch;

	UPROPERTY(editanywhere)
		FRotator MouseRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMaterials* materials;
};
