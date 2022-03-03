// Fill out your copyright notice in the Description page of Project Settings.


#include "NavGraphPathfinder.h"

bool UNavGraphPathfinder::SetupPathfinder_Implementation(ANavGraph* graph)
{
	graph->OnGraphChanged.AddDynamic(this, &UNavGraphPathfinder::OnGraphChanged);
	navGraph = graph;
	return true;
}

void UNavGraphPathfinder::OnGraphChanged_Implementation()
{
}

TArray<ANavNode*> UNavGraphPathfinder::FindPath_Implementation(ANavNode* start, ANavNode* end)
{
	return TArray<ANavNode*>();
}

void UNavGraphPathfinder::EndPathfinder_Implementation()
{
	navGraph->OnGraphChanged.RemoveDynamic(this, &UNavGraphPathfinder::OnGraphChanged);
}
