#include <iostream>
#include "GraphFileReader.h"

int main() {
    GraphFileReader graphFileReader("C:\\Users\\adamp\\source\\repos\\Algorythms Graph Project\\Algorythms Graph Project\\GraphData\\Graf1.txt");
    Graph * graph = graphFileReader.ReadGraph();

    std::cout << "Graph was load!" << std::endl;

    graph->FindAllComponents();

    std::cout << "Gras was searched" << std::endl;

    delete graph;
    return 0;
}
