//
// Created by adamp on 4/23/2023.
//

#ifndef ALG_GRAPH_BIN_NODE_H
#define ALG_GRAPH_BIN_NODE_H


#include <vector>

class Node {
public:
    Node(int value);
    void CreateEdge(Node *);
    int GetValue();

    enum NodeColor { Undiscovered, Discovered, Processed };
private:
    int value;
    NodeColor nodeColor;
    std::vector<Node*> neighbours;
};


#endif //ALG_GRAPH_BIN_NODE_H
