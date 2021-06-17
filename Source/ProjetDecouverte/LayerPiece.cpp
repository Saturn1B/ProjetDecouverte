// Fill out your copyright notice in the Description page of Project Settings.


#include "LayerPiece.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "MyPlayerController2.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
ALayerPiece::ALayerPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Visible Component
	Visible = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	Visible->SetupAttachment(RootComponent);
	Visible->bHiddenInGame = false;

	static ConstructorHelpers::FObjectFinder<UForceFeedbackEffect> MyVisualAsset1(TEXT("/Game/FeedBack/Haptic02.Haptic02"));
	if (MyVisualAsset1.Succeeded())
	{
		haptic1 = MyVisualAsset1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UForceFeedbackEffect> MyVisualAsset2(TEXT("/Game/FeedBack/Haptic03.Haptic03"));
	if (MyVisualAsset2.Succeeded())
	{
		haptic2 = MyVisualAsset2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MyVisualAsset3(TEXT("/Game/02_Materials/M_Planet/inst/Lave/M_Crame_inst.M_Crame_inst"));
	if (MyVisualAsset1.Succeeded())
	{
		indestructibleMat = MyVisualAsset3.Object;
	}
}

// Called when the game starts or when spawned
void ALayerPiece::BeginPlay()
{
	Super::BeginPlay();

	MyController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	TArray<AActor*> FoundPlayer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController2::StaticClass(), FoundPlayer);
	Player = Cast<AMyPlayerController2>(FoundPlayer[0]);

	if (core)
	{
		dynamicMaterial = UMaterialInstanceDynamic::Create(coreMat, this);
		Visible->SetMaterial(0, dynamicMaterial);
		HPMultiplier = HP / 10;
	}

}

void ALayerPiece::LooseHP(int damageValue, FVector destroyLoc)
{
	HP -= damageValue;
	if (core)
	{
		dynamicMaterial->SetScalarParameterValue(FName("EmissiveMultiplier"), (HP / HPMultiplier) / 10);
	}
	if (HP <= 0)
	{
		if(!liquid)
		{
			Visible->SetSimulatePhysics(true);
			Visible->SetEnableGravity(false);

			Visible->AddImpulse(Visible->GetRelativeLocation() * strength);

			/*if (!Player->tuto1)
			{
				Player->tuto1 = true;
				Tutorisation->ResetPopup();
				FString text = "Hey, bien joue mineur! Belle explosion! Tu peux aller dans l'onglet ressource pour voir ce que t'a récolter. Quoique la roche ça raporte pas grand chose";
				Tutorisation->SetPopup(text, 15.0f, Tutorisation->ressource);
			}*/
		}

		if(core)
		{
			MyController->ClientPlayForceFeedback(haptic2, false, FName("Haptic3"));
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CamShakeBig, 1);
		}
		else
		{
			MyController->ClientPlayForceFeedback(haptic1, false, FName("Haptic2"));
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CamShakeSmall, 1);
		}

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DestroyVFX, destroyLoc);

		if (lavaPiece != NULL && lavaPiece->lava == true)
		{
			lavaPiece->LavaSpread();
		}

		if (liquid)
		{
			Destroy();
		}
		else
		{
			FTimerHandle handle;
			GetWorldTimerManager().SetTimer(handle, this, &ALayerPiece::Kill, 1, false);
		}
	}
}

void ALayerPiece::Kill()
{
	Destroy();
}

void ALayerPiece::LavaSpread()
{
	for(ALayerPiece* spreadPiece : spreadPieces)
	{
		spreadPiece->indestructible = true;
		spreadPiece->Visible->SetMaterial(0, indestructibleMat);
	}
}

