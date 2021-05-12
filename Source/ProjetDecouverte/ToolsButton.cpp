// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolsButton.h"
#define LOG(fstring) GLog->Log(fstring)

void UToolsButton::BuyTool()
{
	LOG(FString::FromInt(index));

	/*TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAutomaticTools::StaticClass(), FoundActors);
	for (AActor* actorTool : FoundActors)
	{
		AAutomaticTools* tool = Cast<AAutomaticTools>(actorTool);
		if (!tool->isActive == false)
		{
			if (tool->Index == index)
			{
				tool->isActive = true;
				//TO DO désactiver le bouton acheter
				//TO DO activer le bouton améliorer
				//OR REBIND BUTTON AND CHANGE TEXT
				//TO DO retirer le montant de minéraux défini
			}
		}
	}*/
}