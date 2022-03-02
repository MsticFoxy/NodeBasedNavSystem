// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavGraphRow.h"
#include "NavNode.h"
#include "NavGraph.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGraphChangedDelegate);

USTRUCT(BlueprintType)
struct FNodeVis
{
	GENERATED_BODY()
public:
	FNodeVis();
	FNodeVis(int _x, int _y, bool _isNull);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isNull;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int y;
};

UCLASS(BlueprintType)
class NBNAVSYSTEM_API ANavGraph : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavGraph();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<UNavGraphRow*> posRows;
	UPROPERTY(EditAnywhere)
	TArray<UNavGraphRow*> negRows;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UNavGraphRow* operator [](int i);

	/* 
	* Sets the node at index [x][y]. Adds null nodes if the graph is too small
	* @param x defines the row in which the node is set
	* @param y defines the index in which the node is set
	* @param node the node that is going to replace the old node at the index [x][y]
	*/
	UFUNCTION(BlueprintCallable)
	void Set(int x, int y, UNavNode* node);

	/*
	* @return the number of nodes excluding null nodes
	*/
	UFUNCTION(BlueprintCallable)
	int ValidNum();
	/*
	* @return the number of nodes including null nodes
	*/
	UFUNCTION(BlueprintCallable)
	int Num();

	/*
	* @return all nodes of the graph including null nodes
	*/
	UFUNCTION(BlueprintCallable)
	TArray<UNavNode*> GetNodeArray();

	/*
	* @return TArray of node locations and if it is a null node
	*/
	UFUNCTION(BlueprintCallable)
	TArray<FNodeVis> GetGraphVisualisation();


// Delegates
public:
	UPROPERTY(BlueprintAssignable)
	FGraphChangedDelegate OnGraphChanged;
};
