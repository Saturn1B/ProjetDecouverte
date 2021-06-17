// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorisation.h"

// Sets default values
ATutorisation::ATutorisation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	FString text = "Hey mineur! Bienvenue pour ton premier jour. Le principe est simple, ici on detruit des planetes jusqu'a leur noyau pour en recuperer les ressources. Ne t inquiete pas tout est legal (enfin, tant que tu te fait pas chopper).";
	SetPopup(text, 20.0f, NULL);
}

// Called every frame
void ATutorisation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATutorisation::SetPopup(FString text, float time, UTexture2D* image)
{
	if (image == NULL)
	{
		popupImage->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		popupImage->SetVisibility(ESlateVisibility::Visible);
		popupImage->SetBrushFromTexture(image);
	}

	popup->SetVisibility(ESlateVisibility::Visible);
	popupText->SetText(FText::FromString(text));

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &ATutorisation::ResetPopup, time, false);
}

void ATutorisation::ResetPopup()
{
	popup->SetVisibility(ESlateVisibility::Collapsed);
	popupText->SetText(FText::FromString(""));
	popupImage = NULL;
}

