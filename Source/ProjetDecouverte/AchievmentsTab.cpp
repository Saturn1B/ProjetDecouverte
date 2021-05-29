// Fill out your copyright notice in the Description page of Project Settings.


#include "AchievmentsTab.h"
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
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_05"))));
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_06"))));
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_07"))));
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_08"))));
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_09"))));
	achievmentsUI.Add(Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Achievment_10"))));

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
	achievmentsUI[toRemove->index]->SetVisibility(ESlateVisibility::Collapsed);
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
}

void AAchievmentsTab::AchieveTab()
{
	if (achievments_ui->GetVisibility() == ESlateVisibility::Collapsed)
	{
		achievments_ui->SetVisibility(ESlateVisibility::Visible);
		achieveButton->SetVisibility(ESlateVisibility::Collapsed);
		achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		achievments_ui->SetVisibility(ESlateVisibility::Collapsed);
		achieveButton->SetVisibility(ESlateVisibility::Visible);
		achievmentsPopup->SetVisibility(ESlateVisibility::Collapsed);
	}
}

