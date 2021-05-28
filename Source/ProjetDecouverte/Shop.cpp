// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"

// Sets default values
AShop::AShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShop::BeginPlay()
{
	Super::BeginPlay();
	created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();
	shopButton = Cast<UButton>(created_ui->GetWidgetFromName(TEXT("Shop")));
	shopPanel = Cast<UCanvasPanel>(created_ui->GetWidgetFromName(TEXT("ShopPanel")));

	shopPanel->SetVisibility(ESlateVisibility::Collapsed);

	shopButton->OnClicked.AddDynamic(this, &AShop::ActiveShop);
}

// Called every frame
void AShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShop::ActiveShop()
{
	if(shopPanel->GetVisibility() == ESlateVisibility::Collapsed)
	{
		shopPanel->SetVisibility(ESlateVisibility::Visible);
	}
	else if(shopPanel->GetVisibility() == ESlateVisibility::Visible)
	{
		shopPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

