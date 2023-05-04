//
// Created by adamp on 4/23/2023.
//

#include <queue>
#include <iostream>
#include "Graph.h"


/**
 * @brief Construct a new Graph:: Graph object
 * 
 */
Graph::Graph(){}

/**
 * @brief Construct a new Graph:: Graph object. Reserve a space for n Nodes
 * 
 * @param n Define how big Vector of nodes is supposed to be 
 */
Graph::Graph(int n)
{
    this->AllNodes.reserve(n);
}

/**
 * @brief Destroy the Graph:: Graph object. Deallocate all objects which are create on the heap
 * 
 */
Graph::~Graph()
{

    for(auto component : Components)
        delete component;

    for(auto node : AllNodes)
        delete node;

    for(auto counter : GeneratedCounters)
        delete counter;
}

/**
 * @brief Add node to the graph
 * 
 * @param nodeValue  Defines a node value
 */
void Graph::AddNode(int nodeValue)
{
    this->FindNode(nodeValue);
}

/**
 * @brief Create edge between nodes. And create nodes if they don't exist
 * 
 * @param nodeValue Defines the first node value
 * @param neighbourValue Second node value
 */
void Graph::AddEdge(int nodeValue, int neighbourValue)
{
    Node * node, * neighbour;
    node = this->FindNode(nodeValue);
    neighbour = this->FindNode(neighbourValue);
    node->CreateEdge(neighbour);
    if(node->GetValue() != neighbour->GetValue())
        neighbour->CreateEdge(node);
}

/**
 * @brief Start procedure of finding all nodes
 * 
 */
void Graph::FindAllComponents()
{
    bool undiscovered = false;
    Node * tmp = IsUndiscoveredNode(undiscovered);
    while (undiscovered) {
        Components.push_back(this->BFS(tmp));
        tmp = IsUndiscoveredNode(undiscovered);
    }
}

/**
 * @brief Binnary search of nodes. If the node doesn't exist, It will create one
 * 
 * @param value Value of node which is searched
 * @return Node* Reference at node in the graph
 */
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

/**
 * @brief Create a new node and insert it into the appropriate position
 * 
 * @param value Value of the new node
 * @param position Appropriate position where the node will be inserted 
 * @return Node* 
 */
Node * Graph::CreateNewNode(int value, int position)
{
    Node * newNode = new Node(value);
    this->AllNodes.insert(this->AllNodes.begin() + position, newNode);
    return newNode;
}

/**
 * @brief BFS algorithm, which find and create a new component of the Graph
 * 
 * @param root Starting point of BFS
 * @return std::vector<Node *>* Reference on the vector which holds all nodes related to the component
 */
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


/**
 * @brief Method helps to decide if All nodes are discovered
 * 
 * @param IsUndiscovered True if undiscovered node exists
 * @return Node* Returns referens to the node if graph is not fully discovered
 */
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

/**
 * @brief Find greatest component of the graph
 * 
 * @return std::vector<Node*>* Reference to the Component
 */
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

/**
 * @brief Create a new GraphCounter instance for the greatest component
 * 
 * @return GraphCounter* Reference for the greatest compontent. It is not reqired to deallocate the counter. Graph object manage it for you
 */
GraphCounter *Graph::CreateCounterForGreatestComponent()
{
    GraphCounter * graphCounter = new GraphCounter(this->GetGreatestComponent());
    GeneratedCounters.push_back(graphCounter);
    return graphCounter;
}

/**
 * @brief Print result of graph to the console
 * 
 */

void Graph::PrintResult()
{
    std::cout << "--------------------Graph Results--------------------" << std::endl;
    std::cout << "Graph vertices: " << this->AllNodes.size() << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}
