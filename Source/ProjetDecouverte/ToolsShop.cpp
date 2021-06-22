// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsShop.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AToolsShop::AToolsShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AToolsShop::BeginPlay()
{
	Super::BeginPlay();
	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();
	//toolsButton.Add(Cast<UToolsButton>(created_ui->GetWidgetFromName(TEXT("ToolsButton_1"))));
	//toolsActivation.Add(Cast<UToolsActivation>(created_ui->GetWidgetFromName(TEXT("ToolsActivation_1"))));
	//toolsButton.Add(Cast<UToolsButton>(created_ui->GetWidgetFromName(TEXT("ToolsButton_2"))));
	//toolsActivation.Add(Cast<UToolsActivation>(created_ui->GetWidgetFromName(TEXT("ToolsActivation_2"))));
	//toolsButton.Add(Cast<UToolsButton>(created_ui->GetWidgetFromName(TEXT("ToolsButton_3"))));
	//toolsActivation.Add(Cast<UToolsActivation>(created_ui->GetWidgetFromName(TEXT("ToolsActivation_3"))));

	//achievmentsTab->achievments_ui = Cast<UCanvasPanel>(created_ui->GetWidgetFromName(TEXT("Achievments")));
	//->achievmentsPopup = Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("AchievmentPopup")));
	//->created_ui = created_ui;

	//achievmentsTab->achievments_ui->SetVisibility(ESlateVisibility::Collapsed);
	//achievmentsTab->achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);

	mapButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_0")));
	//achieveButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_1")));
	//achieveBackButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_2")));
	mapButton->OnClicked.AddDynamic(this, &AToolsShop::ZoomInOut);
	//achieveButton->OnClicked.AddDynamic(this, &AToolsShop::AchieveTab);
	//achieveBackButton->OnClicked.AddDynamic(this, &AToolsShop::AchieveTab);

	/*for (UToolsButton* button : toolsButton)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutomaticTools::StaticClass(), FoundActors);
		for (AActor* actorTool : FoundActors)
		{
			AAutomaticTools* tool = Cast<AAutomaticTools>(actorTool);
			if (tool->Index == button->index)
			{
				button->tool = tool;
			}
		}
	}*/

	/*for (UToolsActivation* activation : toolsActivation)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutomaticTools::StaticClass(), FoundActors);
		for (AActor* actorTool : FoundActors)
		{
			AAutomaticTools* tool = Cast<AAutomaticTools>(actorTool);
			if (tool->Index == activation->index)
			{
				activation->tool = tool;
			}
		}

		activation->SetIsEnabled(false);

		//TArray<AActor*> FoundActors2;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), UToolsUse::StaticClass(), FoundActors2);
		//activation->currentTool = Cast<UToolsUse>(FoundActors2[0]);

	}*/
}

void AToolsShop::ZoomInOut()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController2::StaticClass(), FoundActors);
	if (Cast<AMyPlayerController2>(FoundActors[0])->zoomedOut)
	{
		//camera->SetActorLocation(FVector(camera->GetActorLocation().X, camera->GetActorLocation().Y, camera->GetActorLocation().Z - 100));
		//Cast<AMyPlayerController2>(FoundActors[0])->zoomedOut = false;
		Cast<AMyPlayerController2>(FoundActors[0])->Camera->SetActorLocation(FVector(-90, Cast<AMyPlayerController2>(FoundActors[0])->Camera->GetActorLocation().Y, 40));
		Cast<AMyPlayerController2>(FoundActors[0])->Camera->SetActorRotation(FRotator(-20, 0, 0));
		Cast<AMyPlayerController2>(FoundActors[0])->zoomedOut = false;
		Cast<AMyPlayerController2>(FoundActors[0])->shop->created_ui->RemoveFromViewport();
		Cast<AMyPlayerController2>(FoundActors[0])->inventory->created_ui->AddToViewport();
		for (AActor* atmos : Cast<AMyPlayerController2>(FoundActors[0])->Atmos)
		{
			if (atmos)
			{
				atmos->SetActorHiddenInGame(true);
				atmos->SetActorEnableCollision(false);
				atmos->SetActorTickEnabled(false);
			}
		}
		Cast<AMyPlayerController2>(FoundActors[0])->HidePlanet();
	}
	else
	{
		//camera->SetActorLocation(FVector(camera->GetActorLocation().X, camera->GetActorLocation().Y, camera->GetActorLocation().Z + 100));
		//Cast<AMyPlayerController2>(FoundActors[0])->zoomedOut = true;
		Cast<AMyPlayerController2>(FoundActors[0])->Camera->SetActorLocation(FVector(-160, Cast<AMyPlayerController2>(FoundActors[0])->Camera->GetActorLocation().Y, 70));
		Cast<AMyPlayerController2>(FoundActors[0])->Camera->SetActorRotation(FRotator(-20, 0, 0));
		Cast<AMyPlayerController2>(FoundActors[0])->zoomedOut = true;
		Cast<AMyPlayerController2>(FoundActors[0])->shop->created_ui->AddToViewport();
		Cast<AMyPlayerController2>(FoundActors[0])->inventory->created_ui->RemoveFromViewport();
		for (AActor* atmos : Cast<AMyPlayerController2>(FoundActors[0])->Atmos)
		{
			if (atmos)
			{
				atmos->SetActorHiddenInGame(false);
				atmos->SetActorEnableCollision(true);
				atmos->SetActorTickEnabled(true);
			}
		}
		Cast<AMyPlayerController2>(FoundActors[0])->ShowPlanet();
	}
}

