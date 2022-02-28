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

	UFUNCTION(BlueprintCallable)
	void Set(int x, int y, UNavNode* node);
	UFUNCTION(BlueprintCallable)
	int ValidNum();
	UFUNCTION(BlueprintCallable)
	int Num();

	UPROPERTY(BlueprintAssignable)
	FGraphChangedDelegate OnGraphChanged;

	UFUNCTION(BlueprintCallable)
	TArray<FNodeVis> GetGraphVisualisation();
};
