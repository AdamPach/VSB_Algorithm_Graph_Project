//
// Created by adamp on 4/23/2023.
//

#ifndef ALG_GRAPH_BIN_GRAPH_H
#define ALG_GRAPH_BIN_GRAPH_H


#include "Node.h"
#include "GraphCounter.h"

class Graph {
public:
    Graph();
    Graph(int n);
    ~Graph();
    void AddNode(int nodeValue);
    void AddEdge(int nodeValue, int neighbourValue);

    void PrintResult();

    void FindAllComponents();
    GraphCounter * CreateCounterForGreatestComponent();
private:
    Node * FindNode(int value);
    Node * CreateNewNode(int value, int position);
    std::vector<GraphCounter*> GeneratedCounters;
    std::vector<Node*> AllNodes;
    std::vector<std::vector<Node*>*> Components;

    //Searching

    std::vector<Node*>* BFS(Node * root);
    Node * IsUndiscoveredNode(bool & IsUndiscovered);
    std::vector<Node*> * GetGreatestComponent();

};


#endif //ALG_GRAPH_BIN_GRAPH_H
