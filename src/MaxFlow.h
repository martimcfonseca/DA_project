
/**
 * @file MaxFlow.h
 * @brief Declarations of the maximum flow algorithm and functions to write the results to the output file.
 * @note See the implementation in \ref MaxFlow.cpp "MaxFLow.cpp"
 */

#ifndef DA_PROJECT_MAXFLOW_H
#define DA_PROJECT_MAXFLOW_H

#include "Graph.h"
#include "Parser.h"


template <class T>
void edmondsKarp(Graph<T> *g, T source, T target);

void printResults(const Graph<Node>& graph, const Input& data,const std::string& outputFile);

#endif //DA_PROJECT_MAXFLOW_H