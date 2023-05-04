//
// Created by adamp on 4/24/2023.
//

#ifndef ALG_GRAPH_BIN_GRAPHCOUNTER_H
#define ALG_GRAPH_BIN_GRAPHCOUNTER_H

#define NUM_OF_THREADS 1000

#include "Node.h"

/**
 * @brief Wraps all neccesseary stuff for counting the results of component
 * 
 */
class GraphCounter {
public:
    GraphCounter(std::vector<Node*>* component);
    ~GraphCounter();

    void PrintResults();

    void Count();
    void MultiThreadCount();

    /**
     * @brief Serves as place where all results of Eccentricity are stored
     * 
     */
    int * results;
private:
    std::vector<Node*>* Component;
    
    int BFSGetEccentricity(Node * root, int * distances);
    static void ThreadEccentricity(Node *root, GraphCounter * counter, int * distances);
    void CheckMinAndMax(int newValue);

    int MaxEccentricity;
    int MinEccentricity;
};


#endif //ALG_GRAPH_BIN_GRAPHCOUNTER_H
