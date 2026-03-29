/**
* @mainpage Project Title
 *
 * @section intro_sec Introduction
 * This project is a submission-reviewer assignment system.
 * It reads submission and reviewer data from CSV files, checks if it is possible for every submission
 * to be reviewed by the minimum required number of reviewers, and also allows performing
 * a risk analysis in case a reviewer fails.
 *
 * @section usage_sec Usage
 * - Run the program in the terminal.
 * - Load input files through the menu.
 * - List submissions, reviewers, or parameters (if you want to see).
 * - Run the assignment computation and optionally perform risk analysis.
 *
 * @section structure_sec Code Structure
 * The project is organized as follows:
 * - \ref Input "Input.h/cpp" - handles reading CSV files and storing submissions, reviewers, and parameters.
 * - \ref Graph "Graph.h/cpp" - defines the graph structures.
 * - \ref MaxFlow.h "MaxFlow.h/cpp" - implements the Edmonds-Karp algorithm and outputs results.
 * - \ref RiskAnalysis.h "RiskAnalysis.h/cpp" - performs critical reviewer analysis.
 * - \ref Parser.h "Parser.h/cpp" - parses CSV files and builds the graph.
 * - \ref Menu.h "Menu.h/cpp" - displays the terminal menu and manages user actions.
 * - \ref main "main.cpp" - entry point of the program.
 * @section notes_sec Notes
 * - All algorithms are documented with their time complexity when relevant.
 */


/**
* @file main.cpp
 * @brief Entry point of the program. Determines whether the user wants to run
 * in menu mode or batch mode.
 */
#include <iostream>
#include <string>
#include "Input.h"
#include "Graph.h"
#include "Parser.h"
#include "Menu.h"
#include "MaxFlow.h"
#include "RiskAnalysis.h"


/**
 * @brief Main function that controls the program flow.
 * @param argc Number of arguments passed via the terminal.
 * @param argv Array of arguments passed via the terminal.
 * @return int Returns 0 on success and 1 on error.
 */

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