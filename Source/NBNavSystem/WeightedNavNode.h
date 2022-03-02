// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavNode.h"
#include "WeightedNavNode.generated.h"

/**
 * 
 */
UCLASS()
class NBNAVSYSTEM_API UWeightedNavNode : public UNavNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int weight = 1;
};
