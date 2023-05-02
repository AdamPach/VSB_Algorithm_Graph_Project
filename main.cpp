#include <iostream>
#include "GraphFileReader.h"

int main()
{
    std::string filename;
    std::cout << "Enter file of graph: ";
    getline(std::cin, filename);

    GraphFileReader graphFileReader(filename);
    Graph * graph = graphFileReader.ReadGraph();

    graph->PrintResult();

    graph->FindAllComponents();

    GraphCounter * greatestComponentCounter = graph->CreateCounterForGreatestComponent();

    greatestComponentCounter->MultiThreadCount();
    greatestComponentCounter->PrintResults();

    delete graph;
    return 0;
}
