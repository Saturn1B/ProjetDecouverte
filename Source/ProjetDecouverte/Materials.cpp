// Fill out your copyright notice in the Description page of Project Settings.


#include "Materials.h"
#include "Shop.h"
#include "Inventory.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AMaterials::AMaterials()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMaterials::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShop::StaticClass(), FoundActor);
	shop = Cast<AShop>(FoundActor[0]);

	/*created_ui = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), bp_ui);
	created_ui->AddToViewport();
	materialsText.Add(Cast<UTextBlock>(created_ui->GetWidgetFromName(TEXT("Mat1"))));*/


	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &AMaterials::CheckMat, 0.2f, false);
}

void AMaterials::UpdateMaterial(int index, int value)
{
	materialsCount[index] += value;
	materialsText[index]->SetText(FText::FromString(FString::FromInt(materialsCount[index])));
	for (UBuyButton* button : shop->buttonArray)
	{
		button->SetIsEnabled(true);
		for (size_t i = 0; i < materialsCount.Num(); i++)
		{
			if (button->tool->currentCost[i] > materialsCount[i])
			{
				button->SetIsEnabled(false);
			}
		}
	}
}

void AMaterials::CheckMat()
{
	for (UBuyButton* button : shop->buttonArray)
	{
		button->SetIsEnabled(true);
		LOG(FString::FromInt(materialsCount.Num()));
		for (size_t i = 0; i < materialsCount.Num(); i++)
		{
			LOG(FString::FromInt(button->tool->baseCost[i]));
			LOG(FString::FromInt(materialsCount[i]));
			if (button->tool->baseCost[i] > materialsCount[i])
			{
				button->SetIsEnabled(false);
			}
		}
	}
}

