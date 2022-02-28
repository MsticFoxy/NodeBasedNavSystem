// Fill out your copyright notice in the Description page of Project Settings.


#include "NavGraph.h"

// Sets default values
ANavGraph::ANavGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANavGraph::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANavGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UNavGraphRow* ANavGraph::operator[](int i)
{
	if (i >= 0)
	{
		if (posRows.Num() > i)
		{
			return posRows[i];
		}
		return nullptr;
	}
	else
	{
		if (negRows.Num() >= -i)
		{
			return negRows[(-i) - 1];
		}
		return nullptr;
	}
	return nullptr;
}

void ANavGraph::Set(int x, int y, UNavNode* node)
{
	// setup for positive or negative array
	TArray<UNavGraphRow*>* sign;
	if (x >= 0)
	{
		sign = &posRows;
	}
	else
	{
		sign = &negRows;
		x = (-x) - 1;
	}
	// add rows if array is too short
	if (sign->Num() <= x)
	{
		for (int it = sign->Num(); it < x; it++)
		{
			sign->Add(NewObject<UNavGraphRow>());
		}
		UNavGraphRow* nr = NewObject<UNavGraphRow>();
		sign->Add(nr);
		nr->Set(y, node);
	}
	// remove outer empty rows
	else if (node->IsNull() && sign->Num() == x + 1)
	{
		(*sign)[x]->Set(y, node);
		if ((*sign)[x]->IsEmpty())
		{
			sign->RemoveAt(sign->Num()-1);
			for (int it = sign->Num() - 1; it >= 0; it--)
			{
				if ((*sign)[it]->IsEmpty())
				{
					sign->RemoveAt(sign->Num() - 1);
				}
				else
				{
					break;
				}
			}
		}
	}
	// modify existing array index
	else
	{
		(*sign)[x]->Set(y, node);
	}
	OnGraphChanged.Broadcast();
}

int ANavGraph::ValidNum()
{
	int n = 0;
	for (UNavGraphRow* r : negRows)
	{
		n += r->ValidNum();
	}
	for (UNavGraphRow* r : posRows)
	{
		n += r->ValidNum();
	}
	return n;
}

int ANavGraph::Num()
{
	int n = 0;
	for (UNavGraphRow* r : negRows)
	{
		n += r->Num();
	}
	for (UNavGraphRow* r : posRows)
	{
		n += r->Num();
	}
	return n;
}

FNodeVis::FNodeVis()
{

}
FNodeVis::FNodeVis(int _x, int _y, bool _isNull)
{
	x = _x;
	y = _y;
	isNull = _isNull;
}

TArray<FNodeVis> ANavGraph::GetGraphVisualisation()
{
	TArray<FNodeVis> ret;
	for (int x = 0; x < posRows.Num(); x++)
	{
			for (int y = 0; y < posRows[x]->posNodes.Num(); y++)
			{
				ret.Add(FNodeVis(x, y, posRows[x]->posNodes[y]->IsNull()));
			}
			for (int y = 0; y < posRows[x]->negNodes.Num(); y++)
			{
				ret.Add(FNodeVis(x, -(y + 1), posRows[x]->negNodes[y]->IsNull()));
			}
	}
	for (int x = 0; x < negRows.Num(); x++)
	{
		for (int y = 0; y < negRows[x]->posNodes.Num(); y++)
		{
			ret.Add(FNodeVis(-(x + 1), y, negRows[x]->posNodes[y]->IsNull()));
		}
		for (int y = 0; y < negRows[x]->negNodes.Num(); y++)
		{
			ret.Add(FNodeVis(-(x + 1), -(y + 1), negRows[x]->negNodes[y]->IsNull()));
		}
	}
	return ret;
}
