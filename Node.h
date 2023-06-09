//
// Created by adamp on 4/23/2023.
//

#ifndef ALG_GRAPH_BIN_NODE_H
#define ALG_GRAPH_BIN_NODE_H


#include <vector>
/**
 * @brief Node is representation of one vertex in the graph
 * 
 */
class Node {
public:
    /**
     * @brief It is for defining if for the node discovery status
     * 
     */
    enum NodeColor { Undiscovered, Discovered, Processed };

    Node(int value);
    void CreateEdge(Node * newNeighbour);
    int GetValue();
    std::vector<Node*> * GetNeighbours();

    NodeColor GetColor();
    void SetColor(NodeColor color);

    void SetIndex(int newIndex);
    int GetIndex();
private:
    int value;
    NodeColor nodeColor;
    std::vector<Node*> neighbours;

    int indexInComponent;
};


#endif //ALG_GRAPH_BIN_NODE_H
