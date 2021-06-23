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
	if (MyVisualAsset3.Succeeded())
	{
		indestructibleMat = MyVisualAsset3.Object;
	}

	// find sound

	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset1(TEXT("/Game/06_SFX/Sound/SFX_Pickaxe1.SFX_Pickaxe1"));
	if (MyAudioAsset1.Succeeded())
	{
		pickaxeSound.Add(MyAudioAsset1.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset2(TEXT("/Game/06_SFX/Sound/SFX_Pickaxe2.SFX_Pickaxe2"));
	if (MyAudioAsset2.Succeeded())
	{
		pickaxeSound.Add(MyAudioAsset2.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset3(TEXT("/Game/06_SFX/Sound/SFX_Pickaxe2.SFX_Pickaxe2"));
	if (MyAudioAsset3.Succeeded())
	{
		pickaxeSound.Add(MyAudioAsset3.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset4(TEXT("/Game/06_SFX/Sound/SFX_Pump2.SFX_Pump2"));
	if (MyAudioAsset4.Succeeded())
	{
		liquidSound = MyAudioAsset4.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset5(TEXT("/Game/06_SFX/Sound/SFX_Explosion1.SFX_Explosion1"));
	if (MyAudioAsset5.Succeeded())
	{
		explosionSound.Add(MyAudioAsset5.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset6(TEXT("/Game/06_SFX/Sound/SFX_Explosion2.SFX_Explosion2"));
	if (MyAudioAsset6.Succeeded())
	{
		explosionSound.Add(MyAudioAsset6.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset7(TEXT("/Game/06_SFX/Sound/SFX_Explosion3.SFX_Explosion3"));
	if (MyAudioAsset7.Succeeded())
	{
		explosionSound.Add(MyAudioAsset7.Object);
	}
}

// Called when the game starts or when spawned
void ALayerPiece::BeginPlay()
{
	Super::BeginPlay();

	HP = LayerHp + PieceHP;

	MyController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	TArray<AActor*> FoundPlayer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController2::StaticClass(), FoundPlayer);
	Player = Cast<AMyPlayerController2>(FoundPlayer[0]);

	if (core)
	{
		dynamicMaterial = UMaterialInstanceDynamic::Create(coreMat, this);
		Visible->SetMaterial(0, dynamicMaterial);
		HPMultiplier = HP / 10;

		TArray<AActor*> FoundChildren2;
		Planet->GetAttachedActors(FoundChildren);
		int layersFound = FoundChildren.Num();
		LOG(FString::FromInt(FoundChildren.Num()) + "part found");
		for (size_t j = 0; j < layersFound; j++)
		{
			FoundChildren[j]->GetAttachedActors(FoundChildren2);
			FoundChildren += FoundChildren2;
			FoundChildren2.Empty();
		}
	}
}

void ALayerPiece::LooseHP(int damageValue, FVector destroyLoc)
{
	HP -= damageValue;

	if (liquid)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), liquidSound);
	}
	else
	{
		int r = FMath::RandRange(0, pickaxeSound.Num() - 1);
		UGameplayStatics::PlaySound2D(GetWorld(), pickaxeSound[r]);
	}

	if (core)
	{
		dynamicMaterial->SetScalarParameterValue(FName("EmissiveMultiplier"), (HP / HPMultiplier) / 10);
	}
	if (HP <= 0)
	{
		if(!liquid && !core)
		{
			Visible->SetSimulatePhysics(true);
			Visible->SetEnableGravity(false);

			Visible->AddImpulse(Visible->GetRelativeLocation() * strength);

			if (!Player->tuto1 && Tutorisation != NULL)
			{
				Player->tuto1 = true;
				Tutorisation->ResetPopup();
				FString text = "Hey, bien joue pilleur! Belle explosion! Va dans l'onglet ressource pour voir ce que t'as recolte.";
				Tutorisation->SetPopup(text, 15.0f, 1);
			}
			else if (Player->tuto1 && !Player->tuto2 && Tutorisation != NULL)
			{
				Player->tuto2 = true;
				Tutorisation->ResetPopup();
				FString text = "Tiens on dirait qu'il y a de l'eau la dessous, il te faut peut etre un autre outil pour l'enlever. Va dans la carte galactique, il y a la boutique, tu pourras y trouver de nouveaux outils.";
				Tutorisation->SetPopup(text, 15.0f, 0);
			}
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
			lavaPiece->LavaSpread(destroyLoc);
		}

		if (liquid)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), explosionSound[2]);
		}
		else if (core)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), explosionSound[1]);
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), explosionSound[0]);
		}

		if (liquid)
		{
			Kill();
		}
		else if (core)
		{
			FTimerHandle handle;
			GetWorldTimerManager().SetTimer(handle, this, &ALayerPiece::Kill, 0.1f, false);
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
	if (core)
	{
		Player->tuto2 = false;

		if (CoreAchieve != NULL)
		{
			CoreAchieve->CompleteAchievment();
		}
		for (AActor* piece : FoundChildren)
		{
			if (piece != NULL && Cast<ALayerPiece>(piece) && !Cast<ALayerPiece>(piece)->core)
			{
				piece->Destroy();
			}
			else if (piece != NULL && !Cast<ALayerPiece>(piece))
			{
				piece->Destroy();
			}
		}
		//FoundChildren.Empty();
		Destroy();
		/*if (FoundChildren.Num() > 1)
		{
			DestroyPiece(0);
		}*/
	}
	else
	{
		Destroy();
	}
}

void ALayerPiece::DestroyPiece(int i)
{
	if (FoundChildren[i] != NULL && Cast<ALayerPiece>(FoundChildren[i]) && !Cast<ALayerPiece>(FoundChildren[i])->core)
	{
		FoundChildren[i]->Destroy();
	}

	if (i + 1 < FoundChildren.Num())
	{
		FTimerHandle handle;
		FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this, &ALayerPiece::DestroyPiece, i+1);
		GetWorldTimerManager().SetTimer(handle, TimerDel, 0.1f, false);
	}
	else
	{
		Destroy();
	}
}

void ALayerPiece::LavaSpread(FVector destroyLoc)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), LavaSpreadFX, destroyLoc);

	for(ALayerPiece* spreadPiece : spreadPieces)
	{
		spreadPiece->indestructible = true;
		spreadPiece->Visible->SetMaterial(0, indestructibleMat);
	}
}

