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

/*ANavGraphRow* ANavGraph::operator[](int i)
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
}*/

ANavNode* ANavGraph::Get(int x, int y)
{
	if (x >= 0)
	{
		if (posRows.Num() > x)
		{
			return posRows[x]->Get(y);
		}
		return nullptr;
	}
	else
	{
		if (negRows.Num() >= -x)
		{
			return negRows[(-x) - 1]->Get(y);
		}
		return nullptr;
	}
	return nullptr;
}

void ANavGraph::Set(int x, int y, ANavNode* node)
{
	// setup for positive or negative array
	TArray<ANavGraphRow*>* sign;
	int trueX = x;
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
			ANavGraphRow* nr = (ANavGraphRow*)GetWorld()->SpawnActor<ANavGraphRow>(ANavGraphRow::StaticClass(), FTransform());
			sign->Add(nr);
			nr->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
		ANavGraphRow* nr = (ANavGraphRow*)GetWorld()->SpawnActor<ANavGraphRow>(ANavGraphRow::StaticClass(), FTransform());
		sign->Add(nr);
		nr->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
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
	node->h_x = trueX;
	node->h_y = y;
	node->h_parent = this;
	node->SetActorLocation(FVector(trueX*100, y*100,0));
	OnGraphChanged.Broadcast();
}

void ANavGraph::ClearGraph()
{
	TArray<ANavNode*> rm = GetNodeArray();
	
	for (int i = rm.Num()-1; i >= 0; i--)
	{
		ANavNode* n = rm[i];
		rm.RemoveAt(i);
		if (n != nullptr)
		{
			n->Destroy();
		}
	}

	TArray<ANavGraphRow*> rrm;
	rrm.Append(posRows);
	rrm.Append(negRows);
	posRows.Empty();
	negRows.Empty();
	for (int i = rrm.Num() - 1; i >= 0; i--)
	{
		ANavGraphRow* n = rrm[i];
		rrm.RemoveAt(i);
		if (n != nullptr)
		{
			n->Destroy();
		}
	}
}

void ANavGraph::GetBounds(int& boundsX, int& boundsY)
{
	boundsX = FMath::Max(posRows.Num(), negRows.Num());
	for (ANavGraphRow* r : posRows)
	{
		int max = FMath::Max(r->posNodes.Num(), r->negNodes.Num());
		boundsY = FMath::Max(boundsY, max);
	}
}

int ANavGraph::ValidNum()
{
	int n = 0;
	for (ANavGraphRow* r : negRows)
	{
		n += r->ValidNum();
	}
	for (ANavGraphRow* r : posRows)
	{
		n += r->ValidNum();
	}
	return n;
}

int ANavGraph::Num()
{
	int n = 0;
	for (ANavGraphRow* r : negRows)
	{
		n += r->Num();
	}
	for (ANavGraphRow* r : posRows)
	{
		n += r->Num();
	}
	return n;
}

TArray<ANavNode*> ANavGraph::GetNodeArray()
{
	TArray<ANavNode*> ret;
	for (ANavGraphRow* r : posRows)
	{
		ret.Append(r->posNodes);
		ret.Append(r->negNodes);
	}
	for (ANavGraphRow* r : negRows)
	{
		ret.Append(r->posNodes);
		ret.Append(r->negNodes);
	}
	
	return ret;
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

void ANavGraph::Destroyed()
{
	Super::Destroyed();
	ClearGraph();
}
