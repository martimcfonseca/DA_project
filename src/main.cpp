#include <iostream>
#include <string>
#include "Input.h"
#include "Graph.h"
#include "Parser.h"
#include "Menu.h"
#include "MaxFlow.h"
#include "RiskAnalysis.h"

int main(int argc, char* argv[]) {


    if (argc == 4 && std::string(argv[1]) == "-b") {   //Modo batch "-b"
        std::string inputFile  = argv[2];
        std::string outputFile = argv[3];

        try {
            Input data        = parseFile(inputFile);
            Graph<Node> graph = makeGraph(data);

            Node source{0, Node::Type::SOURCE};
            Node sink{0, Node::Type::SINK};
            if (data.getRiskAnalysis()!=0) {
                edmondsKarp(&graph,source,sink);
                printResults(graph,data,outputFile);
                riskAnalysis(&graph,source,sink,outputFile);
            }
            else {
                edmondsKarp(&graph,source,sink);
                printResults(graph,data,outputFile);
            }

        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }

        return 0;
    }

    if (argc == 1) {   //Menu para o utlizador
        Input data;
        Graph<Node> graph;
        bool loaded = false;
        runMenu(data,graph,loaded);
        return 0;
    }
    return 0;
}