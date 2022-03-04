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
class NBNAVSYSTEM_API ANavNode : public AActor
{
	GENERATED_BODY()
private:
	//static UNavNode* nullNode;
	UPROPERTY(EditAnywhere)
	bool isNullBool;

	UPROPERTY(EditAnywhere)
	int h_x;
	UPROPERTY(EditAnywhere)
	int h_y;

	UPROPERTY(EditAnywhere)
	ANavGraph* h_parent;

	UPROPERTY(EditAnywhere)
	FNeighborRule h_neighborRule;
public:

	ANavNode();

	/*
	* @return a custom Null object
	*/
	static ANavNode* Null(UWorld* world);

	/*
	* @return if this object is a null object
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
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
	TArray<ANavNode*> GetNeighbors();

	/*
	* @return one neighbor of this node depending on the given direction
	* @param direction The direction of the neighbor node
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ANavNode* GetNeighbor(FNeighCoord direction);

	friend class ANavGraph;
};
