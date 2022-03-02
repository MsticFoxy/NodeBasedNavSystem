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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int X();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int Y();

	friend class ANavGraph;
};
