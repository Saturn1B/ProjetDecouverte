// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsButton.h"
#define LOG(fstring) GLog->Log(fstring)

void UToolsButton::ButtonInteract()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutomaticTools::StaticClass(), FoundActors);
	for (AActor* actorTool : FoundActors)
	{
		AAutomaticTools* tool = Cast<AAutomaticTools>(actorTool);
		if (tool->Index == index)
		{
			if (!tool->isActive)
			{
				BuyTool(tool);
			}
			else 
			{
				UpgradeTool(tool);
			}
		}
	}
}

void UToolsButton::BuyTool(AAutomaticTools* tool)
{
	tool->Buy();
	ButtonTextState->SetText(FText::FromString("UPGRADE"));
}

void UToolsButton::UpgradeTool(AAutomaticTools* tool)
{
	tool->Upgrade();
}
