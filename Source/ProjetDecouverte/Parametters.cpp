// Fill out your copyright notice in the Description page of Project Settings.


#include "Parametters.h"

// Sets default values
AParametters::AParametters()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParametters::BeginPlay()
{
	Super::BeginPlay();

	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();

	paramettersPanel = Cast<UCanvasPanel>(created_ui->GetWidgetFromName(TEXT("Options")));
	paramettersButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_1")));
	backButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_2")));

	paramettersPanel->SetVisibility(ESlateVisibility::Collapsed);

	paramettersButton->OnClicked.AddDynamic(this, &AParametters::AchieveTab);
	backButton->OnClicked.AddDynamic(this, &AParametters::AchieveTab);
}

// Called every frame
void AParametters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParametters::AchieveTab()
{
	if (paramettersPanel->GetVisibility() == ESlateVisibility::Collapsed)
	{
		paramettersPanel->SetVisibility(ESlateVisibility::Visible);
		paramettersButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		paramettersPanel->SetVisibility(ESlateVisibility::Collapsed);
		paramettersButton->SetVisibility(ESlateVisibility::Visible);
	}
}

