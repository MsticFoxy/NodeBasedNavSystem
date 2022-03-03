// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NavNode.h"
#include "NavGraphRow.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class NBNAVSYSTEM_API ANavGraphRow : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TArray<ANavNode*> posNodes;
	UPROPERTY(EditAnywhere)
		TArray<ANavNode*> negNodes;

	int validNum;
public:
	
	ANavNode* operator [](int i);

	ANavGraphRow();

	/*
	* Sets the node at index [i] in this row. Adds null nodes if the graph is too small
	*/
	UFUNCTION(BlueprintCallable)
	void Set(int i, ANavNode* node);

	/*
	* @return the number of nodes excluding nullptr
	*/
	UFUNCTION(BlueprintCallable)
	int ValidNum();

	/*
	* @return the number of nodes including nullptr
	*/
	UFUNCTION(BlueprintCallable)
	int Num();

	/*
	* @return if the row is empty
	*/
	UFUNCTION(BlueprintCallable)
	bool IsEmpty();


public:
	friend class ANavGraph;
};
