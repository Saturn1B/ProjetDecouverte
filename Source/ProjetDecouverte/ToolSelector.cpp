// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSelector.h"
#include "Inventory.h"
#include "MyPlayerController2.h"
#include "Tools.h"

UToolSelector::UToolSelector()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> MyAudioAsset1(TEXT("/Game/06_SFX/Sound/SFX_Switch.SFX_Switch"));
	if (MyAudioAsset1.Succeeded())
	{
		selectSound = MyAudioAsset1.Object;
	}
}

void UToolSelector::Clicked()
{
	UGameplayStatics::PlaySound2D(GetWorld(), selectSound);
	for(UToolSelector* selector : inventory->toolSelector)
	{
		selector->SetIsEnabled(true);
	}

	TArray<AActor*> FoundPlayer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController2::StaticClass(), FoundPlayer);

	Cast<AMyPlayerController2>(FoundPlayer[0])->currentTool = tool;

	this->SetIsEnabled(false);
}
