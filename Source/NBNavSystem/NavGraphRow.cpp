// Fill out your copyright notice in the Description page of Project Settings.


#include "NavGraphRow.h"

/*ANavNode* ANavGraphRow::operator[](int i)
{
	if (i >= 0)
	{
		if (posNodes.Num() > i)
		{
			return posNodes[i];
		}
		return nullptr;
	}
	else
	{
		int id = (-i) - 1;
		if (negNodes.Num() > id)
		{
			return negNodes[id];
		}
		return nullptr;
	}
	return nullptr;
}*/

ANavNode* ANavGraphRow::Get(int i)
{
	if (i >= 0)
	{
		if (posNodes.Num() > i)
		{
			return posNodes[i];
		}
		return nullptr;
	}
	else
	{
		if (negNodes.Num() > (-i) - 1)
		{
			return negNodes[(-i) - 1];
		}
		return nullptr;
	}
	return nullptr;
}

ANavGraphRow::ANavGraphRow()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	posNodes = TArray<ANavNode*>();
	negNodes = TArray<ANavNode*>();
}

void ANavGraphRow::Set(int i, ANavNode* node)
{
	// setup for positive or negative array
	TArray<ANavNode*>* sign;
	if (i >= 0)
	{
		sign = &posNodes;
	}
	else
	{
		sign = &negNodes;
		i = (-i) - 1;
	}
	// add nodes if array is too short
	if (sign->Num() <= i)
	{
		for (int it = sign->Num(); it < i; it++)
		{
			ANavNode* nul = ANavNode::Null(node->GetWorld());
			nul->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			sign->Add(nul);
		}
		sign->Add(node);
		validNum++;
	}
	// remove outer null nodes
	else if(node->IsNull() && sign->Num() == i+1)
	{
		sign->RemoveAt(sign->Num() - 1);
		for (int it = sign->Num()-1; it >= 0; it--)
		{
			if ((*sign)[it]->IsNull())
			{
				ANavNode* rm = (*sign)[sign->Num() - 1];
				sign->RemoveAt(sign->Num() - 1);
				rm->Destroy();
			}
			else
			{
				break;
			}
		}
		validNum--;
	}
	// modify existing array index
	else
	{
		if ((*sign)[i]->IsNull() && !node->IsNull())
		{
			validNum++;
		}
		else if (!(*sign)[i]->IsNull() && node->IsNull())
		{
			validNum--;
		}
		else if ((*sign)[i]->IsNull() && node->IsNull())
		{
			return;
		}
		ANavNode* rm = (*sign)[i];
		(*sign).RemoveAt(i);
		(*sign).EmplaceAt(i, node);
		rm->Destroy();
	}
	node->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

int ANavGraphRow::ValidNum()
{
	return validNum;
}

int ANavGraphRow::Num()
{
	return posNodes.Num() + negNodes.Num();
}

bool ANavGraphRow::IsEmpty()
{
	return Num() == 0;
}
