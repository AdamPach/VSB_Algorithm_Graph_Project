//
// Created by adamp on 4/24/2023.
//

#ifndef ALG_GRAPH_BIN_GRAPHCOUNTER_H
#define ALG_GRAPH_BIN_GRAPHCOUNTER_H


#include "Node.h"

class GraphCounter {
public:
    GraphCounter(std::vector<Node*>* component);
    ~GraphCounter();

    void PrintResults();

    void Count();
    void MultiThreadCount();

    int * results;
private:
    std::vector<Node*>* Component;
    //int** NodesDistances;

    int BFSGetEccentricity(Node * root, int * distances);
    static void ThreadEccentricity(Node *root, GraphCounter * counter, int * distances);
    void CheckMinAndMax(int newValue);

    bool Processed();


    int MaxEccentricity;
    int MinEccentricity;
};


#endif //ALG_GRAPH_BIN_GRAPHCOUNTER_H
