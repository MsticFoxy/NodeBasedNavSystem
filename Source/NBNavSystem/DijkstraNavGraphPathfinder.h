// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavGraphPathfinder.h"
#include "Containers/Map.h"
#include "DijkstraNavGraphPathfinder.generated.h"

/**
 * 
 */
UCLASS()
class NBNAVSYSTEM_API UDijkstraNavGraphPathfinder : public UNavGraphPathfinder
{
	GENERATED_BODY()
private:
	TMultiMap<int, UNavNode*> weightNodeMap;
	TMap<UNavNode*, int> currentWeight;

public:
	virtual bool SetupPathfinder_Implementation(ANavGraph* graph) override;

	void WeightNodes(UNavNode* origin);
};
