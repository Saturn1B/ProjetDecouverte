// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSelector.h"
#include "Inventory.h"
#include "MyPlayerController2.h"
#include "Tools.h"

void UToolSelector::Clicked()
{
	for(UToolSelector* selector : inventory->toolSelector)
	{
		selector->SetIsEnabled(true);
	}

	TArray<AActor*> FoundPlayer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController2::StaticClass(), FoundPlayer);

	Cast<AMyPlayerController2>(FoundPlayer[0])->currentTool = tool;

	this->SetIsEnabled(false);
}
