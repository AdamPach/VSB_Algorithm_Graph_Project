#include <iostream>
#include "GraphFileReader.h"

int main() {
    GraphFileReader graphFileReader("C:\\Users\\adamp\\source\\repos\\Algorythms Graph Project\\Algorythms Graph Project\\GraphData\\Graf1.txt");
    Graph * graph = graphFileReader.ReadGraph();

    graph->PrintResult();

    graph->FindAllComponents();

    GraphCounter * greatestComponentCounter = graph->CreateCounterForGreatestComponent();

    greatestComponentCounter->MultiThreadCount();
    greatestComponentCounter->PrintResults();

    delete graph;
    return 0;
}
