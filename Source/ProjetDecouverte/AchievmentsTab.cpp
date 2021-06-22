// Fill out your copyright notice in the Description page of Project Settings.


#include "AchievmentsTab.h"
#include "Parametters.h"
#include "Shop.h"
#include "Materials.h"
#include "Inventory.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AAchievmentsTab::AAchievmentsTab()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAchievmentsTab::BeginPlay()
{
	Super::BeginPlay();

	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();

	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_01"))));
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_02"))));
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_03"))));
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_04"))));

	popupTitle = Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("PopupTitle")));
	popupPara = Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("PopupPara")));

	achievments_ui = Cast<UCanvasPanel>(created_ui->GetWidgetFromName(TEXT("Achievments")));
	achievmentsPopup = Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("AchievmentPopup")));

	achievments_ui->SetVisibility(ESlateVisibility::Collapsed);
	achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);

	achieveButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_1")));
	achieveBackButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Button_2")));

	achieveButton->OnClicked.AddDynamic(this, &AAchievmentsTab::AchieveTab);
	achieveBackButton->OnClicked.AddDynamic(this, &AAchievmentsTab::AchieveTab);
}

void AAchievmentsTab::RemoveAchievment(AAchievments* toRemove)
{
	created_ui->RemoveFromViewport();
	created_ui->AddToViewport();
	currentIndex = toRemove->index;

	achievmentsUI[currentIndex]->SetVisibility(ESlateVisibility::Collapsed);
	achievments.Remove(toRemove);

	popupTitle->SetText(FText::FromString(toRemove->Title));
	popupPara->SetText(FText::FromString(toRemove->Paragragh));

	achievmentsPopup->SetVisibility(ESlateVisibility::Visible);

	LOG(popupTitle->Text);

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &AAchievmentsTab::HidePopup, 2.0f, false);
}

void AAchievmentsTab::HidePopup()
{

	achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);
	if (currentIndex == 1)
	{
		Tutorisation->ResetPopup();
		FString text = "Jolie mon petit, t'a le coup de main. Passe sur la carte galactique en dezoomant. La tu pourra, choisir une autre planete, je te conseille de partir vers celle de glace (y a des trucs interessant)";
		Tutorisation->SetPopup(text, 20.0f, 0);
	}
}

void AAchievmentsTab::AchieveTab()
{
	material->matPanel->SetVisibility(ESlateVisibility::Collapsed);
	shop->shopPanel->SetVisibility(ESlateVisibility::Collapsed);
	parametters->paramettersPanel->SetVisibility(ESlateVisibility::Collapsed);
	inventory->toolInventory->SetVisibility(ESlateVisibility::Collapsed);

	if (achievments_ui->GetVisibility() == ESlateVisibility::Collapsed)
	{
		achievments_ui->SetVisibility(ESlateVisibility::Visible);
		achieveButton->SetVisibility(ESlateVisibility::Collapsed);
		achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);
		Tutorisation->ResetPopup();

		material->matButton->SetVisibility(ESlateVisibility::Hidden);
		shop->shopButton->SetVisibility(ESlateVisibility::Hidden);
		parametters->paramettersButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		achievments_ui->SetVisibility(ESlateVisibility::Collapsed);
		achieveButton->SetVisibility(ESlateVisibility::Visible);
		achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);

		material->matButton->SetVisibility(ESlateVisibility::Visible);
		shop->shopButton->SetVisibility(ESlateVisibility::Visible);
		parametters->paramettersButton->SetVisibility(ESlateVisibility::Visible);
	}
}

