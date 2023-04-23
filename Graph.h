//
// Created by adamp on 4/23/2023.
//

#ifndef ALG_GRAPH_BIN_GRAPH_H
#define ALG_GRAPH_BIN_GRAPH_H


#include "Node.h"

class Graph {
public:
    Graph();
    Graph(int n);
    ~Graph();
    void AddNode(int nodeValue);
    void AddEdge(int nodeValue, int neighbourValue);
private:
    Node * FindNode(int value);
    Node * CreateNewNode(int value, int position);
    std::vector<Node*> AllNodes;
};


#endif //ALG_GRAPH_BIN_GRAPH_H
