// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsActivation.h"
#define LOG(fstring) GLog->Log(fstring)

void UToolsActivation::SetCurrentTool() 
{
	currentTool->index = index;
	currentTool->tool = tool;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AToolsShop::StaticClass(), FoundActors);
	for (UToolsActivation* activation : Cast<AToolsShop>(FoundActors[0])->toolsActivation)
	{
		if (activation->tool->isActive)
		{
			activation->SetIsEnabled(true);
		}
	}

	SetIsEnabled(false);
}

