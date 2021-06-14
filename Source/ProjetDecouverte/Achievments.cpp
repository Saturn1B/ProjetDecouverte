// Fill out your copyright notice in the Description page of Project Settings.


#include "Achievments.h"
#include "Materials.h"
#include "AchievmentsTab.h"
#define LOG(fstring) GLog->Log(fstring)

// Sets default values
AAchievments::AAchievments()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAchievments::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMaterials::StaticClass(), FoundActors);
	materialsTotal = Cast<AMaterials>(FoundActors[0]);
}

// Called every frame
void AAchievments::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckCondition();
}

void AAchievments::CheckCondition()
{
	if(materialsTotal->materialsCount[materialToDestroy] >= numberToDestroy && !isComplete)
	{
		CompleteAchievment();
		isComplete = true;
	}
	//Check conditon each tick
	//Check condition value in MPC2 array of destroyed material type
}

void AAchievments::CompleteAchievment()
{
	isComplete = true;
	materialsTotal->UpdateMaterial(3, goldGiven);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAchievmentsTab::StaticClass(), FoundActors);
	Cast<AAchievmentsTab>(FoundActors[0])->RemoveAchievment(this);
	//spawn popup
}

