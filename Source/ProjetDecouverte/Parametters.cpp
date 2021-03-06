// Fill out your copyright notice in the Description page of Project Settings.


#include "Parametters.h"
#include "Shop.h"
#include "Materials.h"
#include "Inventory.h"
#include "AchievmentsTab.h"

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
	inventory->toolInventory->SetVisibility(ESlateVisibility::Collapsed);
	shop->shopPanel->SetVisibility(ESlateVisibility::Collapsed);
	material->matPanel->SetVisibility(ESlateVisibility::Collapsed);
	achievmentsTab->achievments_ui->SetVisibility(ESlateVisibility::Collapsed);
	achievmentsTab->achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);

	if (paramettersPanel->GetVisibility() == ESlateVisibility::Collapsed)
	{
		paramettersPanel->SetVisibility(ESlateVisibility::Visible);
		paramettersButton->SetVisibility(ESlateVisibility::Collapsed);
		Tutorisation->ResetPopup();

		shop->shopButton->SetVisibility(ESlateVisibility::Hidden);
		material->matButton->SetVisibility(ESlateVisibility::Hidden);
		achievmentsTab->achieveButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		paramettersPanel->SetVisibility(ESlateVisibility::Collapsed);
		paramettersButton->SetVisibility(ESlateVisibility::Visible);

		shop->shopButton->SetVisibility(ESlateVisibility::Visible);
		material->matButton->SetVisibility(ESlateVisibility::Visible);
		achievmentsTab->achieveButton->SetVisibility(ESlateVisibility::Visible);
	}
}

