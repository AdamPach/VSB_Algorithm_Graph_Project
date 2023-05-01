//
// Created by adamp on 4/23/2023.
//

#include <queue>
#include <iostream>
#include "Graph.h"

Graph::Graph(){}

Graph::Graph(int n)
{
    this->AllNodes.reserve(n);
}

Graph::~Graph()
{

    for(auto component : Components)
        delete component;

    for(auto node : AllNodes)
        delete node;

    for(auto counter : GeneratedCounters)
        delete counter;
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

void Graph::FindAllComponents()
{
    bool undiscovered = false;
    Node * tmp = IsUndiscoveredNode(undiscovered);
    while (undiscovered) {
        Components.push_back(this->BFS(tmp));
        tmp = IsUndiscoveredNode(undiscovered);
    }
}

//Private Methods

Node * Graph::FindNode(int value)
{
    if(AllNodes.empty())
        return CreateNewNode(value, 0);
    int low = 0, high = AllNodes.size() - 1;
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

std::vector<Node *>* Graph::BFS(Node *root)
{
    std::queue<Node *> queue;
    root->SetColor(Node::NodeColor::Discovered);
    queue.push(root);
    std::vector<Node *>* component = new std::vector<Node *>();

    while (!queue.empty())
    {
        Node * currentNode = queue.front();
        currentNode->SetColor(Node::NodeColor::Processed);
        queue.pop();
        currentNode->SetIndex(component->size());
        component->push_back(currentNode);

        for(Node * searchedNode : *(currentNode->GetNeighbours()))
        {
            if(searchedNode->GetColor() == Node::NodeColor::Undiscovered)
            {
                searchedNode->SetColor(Node::NodeColor::Discovered);
                queue.push(searchedNode);
            }
        }
    }

    return component;
}

Node * Graph::IsUndiscoveredNode(bool & IsUndiscovered)
{
    for(Node * node : AllNodes)
    {
        if(node->GetColor() == Node::NodeColor::Undiscovered){
            IsUndiscovered = true;
            return node;
        }
    }
    IsUndiscovered = false;
    return nullptr;
}

std::vector<Node*> *Graph::GetGreatestComponent()
{
    if(Components.empty())
        return nullptr;
    std::vector<Node*> * greatestComponent = Components.at(0);

    for(auto component : Components)
    {
        if(greatestComponent->size() < component->size())
            greatestComponent = component;
    }
    return greatestComponent;
}

GraphCounter *Graph::CreateCounterForGreatestComponent()
{
    GraphCounter * graphCounter = new GraphCounter(this->GetGreatestComponent());
    GeneratedCounters.push_back(graphCounter);
    return graphCounter;
}

void Graph::PrintResult()
{
    std::cout << "--------------------Graph Results--------------------" << std::endl;
    std::cout << "Graph vertices: " << this->AllNodes.size() << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}
