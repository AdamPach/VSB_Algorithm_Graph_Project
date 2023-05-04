//
// Created by adamp on 4/23/2023.
//

#include <iostream>
#include "GraphFileReader.h"


/**
 * @brief Construct a new Graph File Reader:: Graph File Reader object
 * 
 * @param fileName Define a filepath where is the graph saved
 */
GraphFileReader::GraphFileReader(std::string fileName)
{
    this->fileName = fileName;
}


/**
 * @brief Read graph from file which is defined in constructor
 * 
 * @return Graph* return a pointer to the graph
 */
Graph *GraphFileReader::ReadGraph()
{
    Graph * newGraph = new Graph();
    std::ifstream graphFile(this->fileName);
    int nodeValue = 0, neighbourValue = 0;
    while (!graphFile.eof())
    {
        graphFile >> nodeValue >> neighbourValue;
        newGraph->AddEdge(nodeValue, neighbourValue);
    }
    graphFile.close();
    return newGraph;
}