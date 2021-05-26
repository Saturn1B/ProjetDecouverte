// Fill out your copyright notice in the Description page of Project Settings.


#include "LayerPiece.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
ALayerPiece::ALayerPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Visible Component
	Visible = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	Visible->SetupAttachment(RootComponent);
	Visible->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void ALayerPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALayerPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALayerPiece::LooseHP(int damageValue)
{
	HP -= damageValue;
	if (HP <= 0)
	{
		Visible->SetSimulatePhysics(true);
		Visible->SetEnableGravity(false);

		Visible->AddImpulse(Visible->GetRelativeLocation() * strength);

		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &ALayerPiece::Kill, 1, false);
	}
}

void ALayerPiece::Kill()
{
	if(lavaPiece != NULL && lavaPiece->lava == true)
	{
		lavaPiece->LavaSpread();
	}
	Destroy();
}

void ALayerPiece::LavaSpread()
{
	for(ALayerPiece* spreadPiece : spreadPieces)
	{
		spreadPiece->indestructible = true;
	}
}

