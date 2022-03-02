// Fill out your copyright notice in the Description page of Project Settings.


#include "NavNode.h"
#include "NavGraph.h"

//UNavNode* UNavNode::nullNode;

UNavNode* UNavNode::Null()
{
    /*if (UNavNode::nullNode)
    {
        return UNavNode::nullNode;
    }*/
    UNavNode* nn = NewObject<UNavNode>();
    nn->isNullBool = true;
    return nn;
}

bool UNavNode::IsNull()
{
    return isNullBool;
}

int UNavNode::X()
{
    return x;
}

int UNavNode::Y()
{
    return y;
}

ANavGraph* UNavNode::Parent()
{
    return parent;
}

void UNavNode::SetNeighborRule(FNeighborRule rule)
{
    neighborRule = rule;
}

FNeighborRule UNavNode::GetNeighborRule()
{
    return neighborRule;
}

TArray<UNavNode*> UNavNode::GetNeighbors()
{
    TArray<UNavNode*> ret;
    for (FNeighCoord c : neighborRule.reach)
    {
        if (UNavNode* n = (*(*parent)[(x + c.x)])[y + c.y])
        {
            if (!n->IsNull())
            {
                ret.AddUnique(n);
            }
        }
    }
    return ret;
}
