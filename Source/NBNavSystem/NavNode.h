// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NavNode.generated.h"

class ANavGraph;

USTRUCT(BlueprintType)
struct FNeighCoord
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int y;
};

USTRUCT(BlueprintType)
struct FNeighborRule
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNeighCoord> reach;
};

/**
 * 
 */
UCLASS(BlueprintType)
class NBNAVSYSTEM_API UNavNode : public UObject
{
	GENERATED_BODY()
private:
	//static UNavNode* nullNode;
	bool isNullBool;

	int x;
	int y;

	ANavGraph* parent;

	FNeighborRule neighborRule;
public:
	/*
	* @return a custom Null object
	*/
	static UNavNode* Null();

	/*
	* @return if this object is a null object
	*/
	UFUNCTION(BlueprintCallable)
	bool IsNull();

	/*
	* @return the x coordinate of this node relative to the parent NavGraph
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int X();
	/*
	* @return the y coordinate of this node relative to the parent NavGraph
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int Y();
	/*
	* @return the parent NavGraph
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ANavGraph* Parent();

	/*
	* Sets the NeighborRule for this Node
	*/
	UFUNCTION(BlueprintCallable)
	void SetNeighborRule(FNeighborRule rule);

	/*
	* @return the NeighborRule for this Node
	*/
	UFUNCTION(BlueprintCallable)
	FNeighborRule GetNeighborRule();

	/*
	* @return all neighbors of this node depending on the NeighborRule excluding Null Nodes
	*/
	UFUNCTION(BlueprintCallable)
	TArray<UNavNode*> GetNeighbors();

	friend class ANavGraph;
};
