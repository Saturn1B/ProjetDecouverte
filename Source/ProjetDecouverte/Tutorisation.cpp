// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorisation.h"

// Sets default values
ATutorisation::ATutorisation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset1(TEXT("/Game/06_SFX/Sound/SFX_Achievment.SFX_Achievment"));
	if (MyAudioAsset1.Succeeded())
	{
		achieveSound = MyAudioAsset1.Object;
	}
}

// Called when the game starts or when spawned
void ATutorisation::BeginPlay()
{
	Super::BeginPlay();

	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();

	popup = Cast<UBorder>(created_ui->GetWidgetFromName(TEXT("Popup")));
	popupImage = Cast<UImage>(created_ui->GetWidgetFromName(TEXT("PopupImage")));
	popupText = Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("PopupText")));
	popup->SetVisibility(ESlateVisibility::Collapsed);

	FString text = "Hey mineur! Bienvenue pour ton premier jour. Le principe est simple, ici on detruit des planetes jusqu'a leur noyau pour en recuperer les ressources. Ne t'inquiete pas tout est legal (enfin, tant que tu te fait pas chopper).";
	SetPopup(text, 20.0f, 0);
}

// Called every frame
void ATutorisation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutorisation::SetPopup(FString text, float time, int imageIndex)
{
	switch (imageIndex)
	{
		case 0:
			popupImage->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case 1:
			popupImage->SetVisibility(ESlateVisibility::Visible);
			popupImage->SetBrushFromTexture(ressource);
			break;
		case 2 :
			popupImage->SetVisibility(ESlateVisibility::Visible);
			popupImage->SetBrushFromTexture(mission);
			break;
		case 3 :
			popupImage->SetVisibility(ESlateVisibility::Visible);
			popupImage->SetBrushFromTexture(shop);
			break;
		case 4 :
			popupImage->SetVisibility(ESlateVisibility::Visible);
			popupImage->SetBrushFromTexture(inventory);
			break;
		default :
			break;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), achieveSound);

	popup->SetVisibility(ESlateVisibility::Visible);
	popupText->SetText(FText::FromString(text));

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &ATutorisation::ResetPopup, time, false);
}

void ATutorisation::ResetPopup()
{
	popup->SetVisibility(ESlateVisibility::Collapsed);
	popupText->SetText(FText::FromString(""));
	popupImage->SetBrushFromTexture(NULL);
}

