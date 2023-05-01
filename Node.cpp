//
// Created by adamp on 4/23/2023.
//

#include "Node.h"

Node::Node(int value)
{
    this->value = value;
    this->nodeColor = NodeColor::Undiscovered;
    this->indexInComponent = -1;
}

void Node::CreateEdge(Node * newNeighbour)
{
    this->neighbours.push_back(newNeighbour);
}

int Node::GetValue()
{
    return this->value;
}

std::vector<Node *> *Node::GetNeighbours()
{
    return &this->neighbours;
}

Node::NodeColor Node::GetColor()
{
    return this->nodeColor;
}

void Node::SetColor(NodeColor color)
{
    this->nodeColor = color;
}

void Node::SetIndex(int newIndex)
{
    this->indexInComponent = newIndex;
}

int Node::GetIndex() {
    return indexInComponent;
}
