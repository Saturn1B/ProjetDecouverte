// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSelector.h"
#include "Inventory.h"
#include "Tools.h"

void UToolSelector::Clicked()
{
	for(UToolSelector* selector : inventory->toolSelector)
	{
		selector->SetIsEnabled(true);
	}
	TArray<AActor*> FoundTools;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATools::StaticClass(), FoundTools);

	TArray<AActor*> FoundPlayer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerController2::StaticClass(), FoundPlayer);

	for (AActor* toolsActor : FoundTools)
	{
		if (Cast<ATools>(toolsActor)->index == toolIndex)
		{
			Cast<AMyPlayerController2>(FoundPlayer[0])->currentTool = Cast<ATools>(toolsActor);
			break;
		}
	}



	this->SetIsEnabled(false);
}
