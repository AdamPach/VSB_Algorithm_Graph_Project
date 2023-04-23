//
// Created by adamp on 4/23/2023.
//

#ifndef ALG_GRAPH_BIN_GRAPHFILEREADER_H
#define ALG_GRAPH_BIN_GRAPHFILEREADER_H


#include <string>
#include <fstream>
#include "Graph.h"

class GraphFileReader {
public:
    GraphFileReader(std::string fileName);
    Graph * ReadGraph();
private:
    std::string fileName;
};


#endif //ALG_GRAPH_BIN_GRAPHFILEREADER_H
