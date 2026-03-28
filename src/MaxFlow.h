
/**
 * @file MaxFlow.h
 * @brief Declarations of the maximum flow algorithm and functions to write the results to the output file.
 */

#ifndef DA_PROJECT_MAXFLOW_H
#define DA_PROJECT_MAXFLOW_H

#include "Graph.h"
#include "Parser.h"

/**
 * @brief Implements the Edmonds-Karp algorithm to compute the maximum flow.
 *
 * The algorithm uses a breadth-first search (BFS) to find augmenting paths in the residual graph,
 * updating capacities until no more paths exist from the source to the target.
 *
 * @param g Pointer to the graph (flow network).
 * @param source Source node.
 * @param target Target node (sink).
 *
 * @note **Time Complexity:** O(V · E²), where V is the number of vertices and E is the number of edges.
 * This is because each BFS takes O(E) and the number of augmenting paths in the worst case is O(V · E).
 */

template <class T>
void edmondsKarp(Graph<T> *g, T source, T target);


/**
 * @brief Processes the graph after the flow calculation and exports the results.
 *
 * @param graph Reference to the processed graph.
 * @param data Reference to the input data (for mapping names/titles).
 * @param outputFile Name of the output file.
 */
void printResults(const Graph<Node>& graph, const Input& data,const std::string& outputFile);

#endif //DA_PROJECT_MAXFLOW_H