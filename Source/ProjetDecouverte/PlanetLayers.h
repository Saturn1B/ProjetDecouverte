// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutomaticTools.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PlanetLayers.generated.h"

UENUM(BlueprintType)
enum class ELayers : uint8
{
	Litosphere		UMETA(Displayname, "Litosphere"),
	Asthenosphere	UMETA(Displayname, "Asthenosphere"),
	Mesosphere		UMETA(Displayname, "Mesosphere"),
	ExternCore		UMETA(Displayname, "ExternCore"),
	InternCore		UMETA(Displayname, "InternCore")
};

UCLASS()
class PROJETDECOUVERTE_API APlanetLayers : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlanetLayers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(editanywhere)
		UStaticMeshComponent* Visible;

	UPROPERTY(editanywhere)
		int HP;

	UPROPERTY(editanywhere)
		ELayers Layer;

	void LooseHP(int damageValue);

	UPROPERTY(editanywhere)
		class APlanetLayers* NextLayer;
};
