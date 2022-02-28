// Fill out your copyright notice in the Description page of Project Settings.


#include "NavGraphRow.h"

UNavNode* UNavGraphRow::operator[](int i)
{
	if (i >= 0)
	{
		if (posNodes.Num() > i)
		{
			return posNodes[i];
		}
		return UNavNode::Null();
	}
	else
	{
		if (negNodes.Num() >= -i)
		{
			return negNodes[(-i)-1];
		}
		return UNavNode::Null();
	}
	return UNavNode::Null();
}

void UNavGraphRow::Set(int i, UNavNode* node)
{
	// setup for positive or negative array
	TArray<UNavNode*>* sign;
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
			sign->Add(UNavNode::Null());
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
				sign->RemoveAt(sign->Num() - 1);
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
		(*sign).RemoveAt(i);
		(*sign).EmplaceAt(i, node);
	}
	
}

int UNavGraphRow::ValidNum()
{
	return validNum;
}

int UNavGraphRow::Num()
{
	return posNodes.Num() + negNodes.Num();
}

bool UNavGraphRow::IsEmpty()
{
	return Num() == 0;
}
