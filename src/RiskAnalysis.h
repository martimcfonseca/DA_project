//
// Created by cristiano on 27/03/26.
//

/**
 * @file RiskAnalysis.h
 * @brief Responsible for performing risk analysis. Checks whether removing a reviewer
 * would leave submissions without the required reviewers, and identifies reviewers
 * who cannot be removed.
 */

#ifndef DA_PROJECT_RISKANALYSIS_H
#define DA_PROJECT_RISKANALYSIS_H
#include "Graph.h"
#include  "Input.h"

/**
 * @brief Performs risk analysis by simulating the failure of each reviewer individually,
 * identifies reviewers that cannot fail, and writes their IDs to the output file.
 *
 * @param g Graph used to execute the algorithms.
 * @param source Source node of the graph.
 * @param target Target node of the graph (sink).
 * @param outputFile File to write the important reviewers' IDs.
 * @note **Time complexity:** O(R * (V * E^2)), where R = number of reviewers,
 * V = number of vertices, and E = number of edges.
 */

template <class T>
void riskAnalysis(Graph<T> *g, T source, T target,const std::string& outputFile);

#endif //DA_PROJECT_RISKANALYSIS_H
