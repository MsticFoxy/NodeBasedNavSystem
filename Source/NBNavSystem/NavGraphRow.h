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

	UFUNCTION(BlueprintCallable)
	void Set(int i, UNavNode* node);
	UFUNCTION(BlueprintCallable)
	int ValidNum();
	UFUNCTION(BlueprintCallable)
	int Num();
	UFUNCTION(BlueprintCallable)
	bool IsEmpty();

	friend class ANavGraph;

};
