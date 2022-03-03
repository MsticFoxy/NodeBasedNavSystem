// Fill out your copyright notice in the Description page of Project Settings.


#include "NavNode.h"
#include "NavGraph.h"

//UNavNode* UNavNode::nullNode;

ANavNode::ANavNode()
{
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

ANavNode* ANavNode::Null(UWorld* world)
{
    ANavNode* nn = (ANavNode*)world->SpawnActor<ANavNode>(ANavNode::StaticClass(), FTransform());
    nn->isNullBool = true;
    return nn;
}

bool ANavNode::IsNull()
{
    return isNullBool;
}

int ANavNode::X()
{
    return x;
}

int ANavNode::Y()
{
    return y;
}

ANavGraph* ANavNode::Parent()
{
    return parent;
}

void ANavNode::SetNeighborRule(FNeighborRule rule)
{
    neighborRule = rule;
}

FNeighborRule ANavNode::GetNeighborRule()
{
    return neighborRule;
}

TArray<ANavNode*> ANavNode::GetNeighbors()
{
    TArray<ANavNode*> ret;
    for (FNeighCoord c : neighborRule.reach)
    {
        if (ANavNode* n = (*(*parent)[(x + c.x)])[y + c.y])
        {
            if (!n->IsNull())
            {
                ret.AddUnique(n);
            }
        }
    }
    return ret;
}
