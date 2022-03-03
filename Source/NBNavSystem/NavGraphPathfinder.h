// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NavNode.h"
#include "NavGraph.h"
#include "NavGraphPathfinder.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NBNAVSYSTEM_API UNavGraphPathfinder : public UObject
{
	GENERATED_BODY()
	
protected:
	// the NavGraph this pathfinder is setup for
	UPROPERTY(EditAnywhere)
	ANavGraph* navGraph;

public:

	/*
	* Sets up the Pathfinder including binding to OnGraphChanged Delegate
	* @param graph the NavGraph this pathfinder is getting setup for
	* @return if the setup was successful
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool SetupPathfinder(ANavGraph* graph);

	/*
	* Gets called when the NavGraph got changed
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnGraphChanged();

	/*
	* Finds the path from the start node to the end node
	* @param start the node from which the pathfinder starts
	* @param end the destination node of the pathfinder
	* @return the path from the start node to the end node
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<ANavNode*> FindPath(ANavNode* start, ANavNode* end);

	/*
	* Clears bindings and does necissary cleanup
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndPathfinder();
};
