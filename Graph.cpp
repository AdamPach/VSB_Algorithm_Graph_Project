//
// Created by adamp on 4/23/2023.
//

#include "Graph.h"

Graph::Graph(){}

Graph::Graph(int n)
{
    this->AllNodes.reserve(n);
}

Graph::~Graph()
{
    for(auto node : AllNodes)
        delete node;
}
//Public Methods

void Graph::AddNode(int nodeValue)
{
    this->FindNode(nodeValue);
}

void Graph::AddEdge(int nodeValue, int neighbourValue)
{
    Node * node, * neighbour;
    node = this->FindNode(nodeValue);
    neighbour = this->FindNode(neighbourValue);
    node->CreateEdge(neighbour);
    if(node->GetValue() != neighbour->GetValue())
        neighbour->CreateEdge(node);
}

//Private Methods

Node * Graph::FindNode(int value)
{
    if(AllNodes.empty())
        return CreateNewNode(value, 0);
    unsigned long long low = 0, high = AllNodes.size() - 1;
    while( low <= high )
    {
        int middle = low + (high - low) / 2;

        Node * tmp = AllNodes.at(middle);

        if(tmp->GetValue() == value)
            return AllNodes.at(middle);

        if(tmp->GetValue() < value)
            low = middle + 1;
        else
            high = middle - 1;
    }

    return this->CreateNewNode(value, low);
}

Node * Graph::CreateNewNode(int value, int position)
{
    Node * newNode = new Node(value);
    this->AllNodes.insert(this->AllNodes.begin() + position, newNode);
    return newNode;
}