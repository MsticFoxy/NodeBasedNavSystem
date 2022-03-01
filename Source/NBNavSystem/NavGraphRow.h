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
class NBNAVSYSTEM_API UNavGraphRow : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TArray<UNavNode*> posNodes;
	UPROPERTY(EditAnywhere)
		TArray<UNavNode*> negNodes;

	int validNum;
public:
	
	UNavNode* operator [](int i);

	/*
	* Sets the node at index [i] in this row. Adds null nodes if the graph is too small
	*/
	UFUNCTION(BlueprintCallable)
	void Set(int i, UNavNode* node);

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
