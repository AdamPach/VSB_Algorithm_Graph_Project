//
// Created by adamp on 4/23/2023.
//

#include "Node.h"

Node::Node(int value)
{
    this->value = value;
    this->nodeColor = NodeColor::Undiscovered;
}

void Node::CreateEdge(Node * newNeighbour)
{
    this->neighbours.push_back(newNeighbour);
}

int Node::GetValue()
{
    return this->value;
}