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
    return h_x;
}

int ANavNode::Y()
{
    return h_y;
}

ANavGraph* ANavNode::Parent()
{
    return h_parent;
}

void ANavNode::SetNeighborRule(FNeighborRule rule)
{
    h_neighborRule = rule;
}

FNeighborRule ANavNode::GetNeighborRule()
{
    return h_neighborRule;
}

TArray<ANavNode*> ANavNode::GetNeighbors()
{
    TArray<ANavNode*> ret;
    for (FNeighCoord c : h_neighborRule.reach)
    {
        if (ANavNode* n = h_parent->Get(h_x + c.x, h_y + c.y))
        {
            if (!n->IsNull())
            {
                ret.AddUnique(n);
            }
        }
    }
    return ret;
}

ANavNode* ANavNode::GetNeighbor(FNeighCoord direction)
{
    if (ANavNode* n = h_parent->Get(h_x + direction.x, h_y + direction.y))
    {
        if (!n->IsNull())
        {
            return n;
        }
    }
    return nullptr;
}
