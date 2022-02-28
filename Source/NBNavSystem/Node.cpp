// Fill out your copyright notice in the Description page of Project Settings.


#include "NavNode.h"

UNavNode* UNavNode::nullNode;

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
