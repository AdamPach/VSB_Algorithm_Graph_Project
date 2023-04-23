//
// Created by adamp on 4/23/2023.
//

#include <iostream>
#include "GraphFileReader.h"

GraphFileReader::GraphFileReader(std::string fileName)
{
    this->fileName = fileName;
}

Graph *GraphFileReader::ReadGraph()
{
    Graph * newGraph = new Graph();
    std::ifstream graphFile(this->fileName);
    int nodeValue = 0, neighbourValue = 0, counter = 0;
    while (!graphFile.eof())
    {
        graphFile >> nodeValue >> neighbourValue;
        newGraph->AddEdge(nodeValue, neighbourValue);
        counter++;
    }
    graphFile.close();
    return newGraph;
}