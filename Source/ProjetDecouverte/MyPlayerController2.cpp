// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController2.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AMyPlayerController2::AMyPlayerController2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Visible Component
	/*Visible = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	Visible->SetupAttachment(RootComponent);
	Visible->bHiddenInGame = false;
	*/
	static ConstructorHelpers::FObjectFinder<UForceFeedbackEffect> MyVisualAsset(TEXT("/Game/FeedBack/Haptic01.Haptic01"));

	if (MyVisualAsset.Succeeded())
	{
		haptic1 = MyVisualAsset.Object;
	}
	else
	{
		LOG("Loading Failed");
	}
}

// Called when the game starts or when spawned
void AMyPlayerController2::BeginPlay()
{
	Super::BeginPlay();

	MyController = Cast<APlayerController>(GetController());

	if (MyController)
	{
		MyController->bShowMouseCursor = true;
		MyController->bEnableClickEvents = true;
		MyController->bEnableMouseOverEvents = true;
	}

	TArray<AActor*> FoundMaterials;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMaterials::StaticClass(), FoundMaterials);
	materials = Cast<AMaterials>(FoundMaterials[0]);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Camera")), FoundCameras);
	Camera = FoundCameras[0];

	//TArray<AActor*> FoundPlanets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlanet::StaticClass(), Planets);
	bool sorted = false;
	AActor* temp;
	while (!sorted)
	{
		sorted = true;
		for (size_t i = 0; i < Planets.Num() - 1; i++)
		{
			if (Cast<APlanet>(Planets[i])->Index > Cast<APlanet>(Planets[i + 1])->Index)
			{
				temp = Planets[i];
				Planets[i] = Planets[i + 1];
				Planets[i + 1] = temp;
				sorted = false;
			}
		}
	}

	PlanetSelected = 0;
	ObjectSelected = Planets[PlanetSelected];

	HidePlanet();

	TArray<AActor*> FoundTools;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATools::StaticClass(), FoundTools);
	for(AActor* actorTool : FoundTools)
	{
		if(Cast<ATools>(actorTool)->index == 0)
		{
			currentTool = Cast<ATools>(actorTool);
		}
	}
	currentTool->isActive = true;
	currentTool->upgradeIndex += 1;

	TArray<AActor*> FoundShop;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShop::StaticClass(), FoundShop);
	shop = Cast<AShop>(FoundShop[0]);

	TArray<AActor*> FoundInventory;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInventory::StaticClass(), FoundInventory);
	inventory = Cast<AInventory>(FoundInventory[0]);
}

// Called every frame
void AMyPlayerController2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MyController->GetInputMouseDelta(mouseX, mouseY);

	MyController->GetInputTouchState(ETouchIndex::Touch1, currentTouch.X, currentTouch.Y, onDrag);

	FVector2D deltaTouch;

	if (onDrag)
	{
		deltaTouch = currentTouch - previousTouch;

		previousTouch = currentTouch;
	}

	if(deltaTouch.X >= 2 || deltaTouch.Y >= 2)
	{
		clickHold = false;
	}

	MouseRotation = FRotator(deltaTouch.Y, deltaTouch.X, 0) * 0.1;

	//Un objet est séléctionné est peut donc être manipulé
	if (ObjectSelected != NULL && (pinchDelta == 0 || pinchDelta == -1))
	{
		if (!zoomedOut && Cast<APlanet>(ObjectSelected))
		{
			//Pour pouvoir bouger dans tous les sens l'objet séléctioné
			APlanet* Planet = Cast<APlanet>(ObjectSelected);
			Planet->PlanetRotation.Yaw -= MouseRotation.Yaw;
			Planet->PlanetRotation.Pitch += MouseRotation.Pitch;

			ObjectSelected->SetActorRotation(Planet->PlanetRotation, ETeleportType::None);
		}
		else  if (zoomedOut && Cast<ASolarSystem>(ObjectSelected))
		{
			if (deltaTouch.Y >= 4)
			{
				ASolarSystem* System = Cast<ASolarSystem>(ObjectSelected);
				System->SystemRotation.Yaw += 90;

				if (PlanetSelected + 1 < Planets.Num())
				{
					PlanetSelected += 1;
				}
				else
				{
					PlanetSelected = 0;
				}

				ObjectSelected->SetActorRotation(System->SystemRotation, ETeleportType::None);
				ObjectSelected = NULL;
			}
			else if (deltaTouch.Y <= -4)
			{
				ASolarSystem* System = Cast<ASolarSystem>(ObjectSelected);
				System->SystemRotation.Yaw -= 90;

				if (PlanetSelected - 1 >= 0)
				{
					PlanetSelected -= 1;
				}
				else
				{
					PlanetSelected = Planets.Num() - 1;
				}

				ObjectSelected->SetActorRotation(System->SystemRotation, ETeleportType::None);
				ObjectSelected = NULL;
			}
		}
	}
}

// Called to bind functionality to input
void AMyPlayerController2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyPlayerController2::OnFingerTouch);

	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AMyPlayerController2::OnFingerRelease);

	InputComponent->BindAxis("UnZoom", this, &AMyPlayerController2::OnFingerPinch);

	//InputComponent->BindGesture(EGestureEvent::, this, &AMyPlayerController2::OnFingerRelease);
}

void AMyPlayerController2::OnFingerTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	MyController->GetInputTouchState(ETouchIndex::Touch1, previousTouch.X, previousTouch.Y, onDrag);
	onDrag = true;
	clickHold = true;

	if (!zoomedOut)
	{
		FHitResult HitResult;
		MyController->GetHitResultUnderFinger(ETouchIndex::Type::Touch1, ECollisionChannel::ECC_Pawn, false, HitResult);
		LOG(FString::SanitizeFloat(HitResult.ImpactPoint.Z));

		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->GetClass()->IsChildOf(ALayerPiece::StaticClass()))
			{
				if (Cast<ALayerPiece>(HitResult.GetActor())->HP > 0 && !Cast<ALayerPiece>(HitResult.GetActor())->indestructible && !Cast<ALayerPiece>(HitResult.GetActor())->lava)
				{
					if(!currentTool->onHold)
					{
						if(Cast<ALayerPiece>(HitResult.GetActor())->liquid == currentTool->onLiquid)
						{
							Cast<ALayerPiece>(HitResult.GetActor())->LooseHP(currentTool->currentDamage * damageBonus, HitResult.ImpactPoint);

							for (size_t i = 0; i < Cast<ALayerPiece>(HitResult.GetActor())->materialsIndex.Num(); i++)
							{
								LOG("gain material");

								if (Cast<ALayerPiece>(HitResult.GetActor())->matIndex == i)
								{
									materials->UpdateMaterial(Cast<ALayerPiece>(HitResult.GetActor())->materialsIndex[i],
										FMath::RandRange(Cast<ALayerPiece>(HitResult.GetActor())->minMat + currentTool->currentProd,
											Cast<ALayerPiece>(HitResult.GetActor())->maxMat + currentTool->currentProd) * materialBonus);
								}
							}

							MyController->ClientPlayForceFeedback(haptic1, false, FName("Haptic1"));

							UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Cast<ALayerPiece>(HitResult.GetActor())->TouchVFX, HitResult.ImpactPoint);
						}
					}
					else
					{
						if (Cast<ALayerPiece>(HitResult.GetActor())->liquid == currentTool->onLiquid)
						{
							HoldDamage(Cast<ALayerPiece>(HitResult.GetActor()));
						}
					}
				}
				ObjectSelected = Planets[PlanetSelected];
			}
		}
	}
	else
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASolarSystem::StaticClass(), FoundActors);
		ObjectSelected = FoundActors[0];
	}
}

void AMyPlayerController2::OnFingerRelease(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	ObjectSelected = NULL;
	onDrag = false;
	clickHold = false;
	currentTouch = FVector2D(0, 0);
	previousTouch = FVector2D(0, 0);
	MouseRotation = FRotator(0, 0, 0);
	currentPinch = 0;
	previousPinch = 0;
	pinchDelta = 0;
}

void AMyPlayerController2::OnFingerPinch(float AxisValue)
{
	previousPinch = currentPinch;
	currentPinch = AxisValue;
	//pinchDelta = currentPinch - previousPinch;

	if (currentPinch > previousPinch)
	{
		pinchDelta = FMath::Clamp(previousPinch / currentPinch, 0.0f, 1.0f);
		pinchDelta = pinchDelta - 1;
	}
	else if (currentPinch < previousPinch)
	{
		pinchDelta = FMath::Clamp(currentPinch / previousPinch, 0.0f, 1.0f);
		pinchDelta = 1 - pinchDelta;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ZoomPinch %f"), pinchDelta));

	if (pinchDelta > -1 && pinchDelta < 0)
	{
		if (zoomedOut && PlanetSelected == 0)
		{
			Camera->SetActorLocation(FVector(-60, Camera->GetActorLocation().Y, 30));
			Camera->SetActorRotation(FRotator(-20, 0, 0));
			zoomedOut = false;
			shop->created_ui->SetVisibility(ESlateVisibility::Collapsed);
			inventory->created_ui->SetVisibility(ESlateVisibility::Visible);
			HidePlanet();
		}
	}
	else if (pinchDelta < 1 && pinchDelta > 0)
	{
		if (!zoomedOut)
		{
			Camera->SetActorLocation(FVector(-60, Camera->GetActorLocation().Y, 120));
			Camera->SetActorRotation(FRotator(-40, 0, 0));
			zoomedOut = true;
			shop->created_ui->SetVisibility(ESlateVisibility::Visible);
			inventory->created_ui->SetVisibility(ESlateVisibility::Collapsed);
			ShowPlanet();
		}
	}
}

void AMyPlayerController2::HoldDamage(class ALayerPiece* layerPiece)
{
	FHitResult HitResult;
	MyController->GetHitResultUnderFinger(ETouchIndex::Type::Touch1, ECollisionChannel::ECC_Pawn, false, HitResult);

	if (HitResult.GetActor() && HitResult.GetActor()->GetClass()->IsChildOf(ALayerPiece::StaticClass()))
	{
		layerPiece = Cast<ALayerPiece>(HitResult.GetActor());
	}

	if (clickHold && layerPiece->liquid == currentTool->onLiquid)
	{
		LOG(layerPiece->GetName());

		layerPiece->LooseHP(currentTool->currentDamage * damageBonus, HitResult.ImpactPoint);

		for (size_t i = 0; i < layerPiece->materialsIndex.Num(); i++)
		{
			if (layerPiece->matIndex == i)
			{
				materials->UpdateMaterial(layerPiece->materialsIndex[i],
					FMath::RandRange(layerPiece->minMat + currentTool->currentProd,
						layerPiece->maxMat + currentTool->currentProd) * materialBonus);
			}
		}

		MyController->ClientPlayForceFeedback(haptic1, false, FName("Haptic1"));

		FTimerHandle handle;
		FTimerDelegate HoldDamageDel = FTimerDelegate::CreateUObject(this, &AMyPlayerController2::HoldDamage, layerPiece);
		//HoldDamageDel.BindUFunction(this, &AMyPlayerController2::HoldDamage, layerPiece);
		GetWorldTimerManager().SetTimer(handle, HoldDamageDel, currentTool->holdTimer, false);
	}
}

void AMyPlayerController2::HidePlanet()
{
	for (size_t i = 0; i < Planets.Num(); i++)
	{
		if (i != PlanetSelected)
		{
			TArray<AActor*> FoundChildren;
			TArray<AActor*> FoundChildren2;
			Planets[i]->GetAttachedActors(FoundChildren);
			int layersFound = FoundChildren.Num();
			//LOG(FString::FromInt(FoundChildren.Num()) + "part found");
			for (size_t j = 0; j < layersFound; j++)
			{
				FoundChildren[j]->GetAttachedActors(FoundChildren2);
				FoundChildren += FoundChildren2;
				FoundChildren2.Empty();
			}
			LOG(FString::FromInt(FoundChildren.Num()) + "part found");
			for (AActor* piece : FoundChildren)
			{
				piece->SetActorHiddenInGame(true);
				piece->SetActorEnableCollision(false);
				piece->SetActorTickEnabled(false);
			}
		}
	}
}

void AMyPlayerController2::ShowPlanet()
{
	for (size_t i = 0; i < Planets.Num(); i++)
	{
		if (i != PlanetSelected)
		{
			TArray<AActor*> FoundChildren;
			TArray<AActor*> FoundChildren2;
			Planets[i]->GetAttachedActors(FoundChildren);
			int layersFound = FoundChildren.Num();
			LOG(FString::FromInt(FoundChildren.Num()) + "part found");
			for (size_t j = 0; j < layersFound; j++)
			{
				FoundChildren[j]->GetAttachedActors(FoundChildren2);
				FoundChildren += FoundChildren2;
				FoundChildren2.Empty();
			}
			LOG(FString::FromInt(FoundChildren.Num()) + "part found");
			for (AActor* piece : FoundChildren)
			{
				piece->SetActorHiddenInGame(false);
				piece->SetActorEnableCollision(true);
				piece->SetActorTickEnabled(true);
			}
		}
	}
}

