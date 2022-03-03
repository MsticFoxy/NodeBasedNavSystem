// Fill out your copyright notice in the Description page of Project Settings.


#include "DijkstraNavGraphPathfinder.h"
#include "WeightedNavNode.h"

bool UDijkstraNavGraphPathfinder::SetupPathfinder_Implementation(ANavGraph* graph)
{
	return true;
}

void UDijkstraNavGraphPathfinder::WeightNodes(ANavNode* origin)
{
	TArray<ANavNode*> unvis = navGraph->GetNodeArray();
	/*
	for (int i = unvis.Num()-1; i >= 0; i--)
	{
		UNavNode* n = unvis[i];
		unvis.RemoveAt(i);
		if (!n->IsNull())
		{
			int cost = 1;
			if (UWeightedNavNode* wn = dynamic_cast<UWeightedNavNode*>(n))
			{
				
			}
		}
	}*/

	TArray<ANavNode*> visited;

	auto weightSingle = [](ANavNode* node, int prevCost, TArray<ANavNode*>* visited)
	{

	};
}
