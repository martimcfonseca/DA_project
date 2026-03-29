//
// Created by cristiano on 27/03/26.
//

/**
 * @file RiskAnalysis.h
 * @brief Responsible for performing risk analysis. Checks whether removing a reviewer
 * would leave submissions without the required reviewers, and identifies reviewers
 * who cannot be removed.
 * @note See the implementation in /ref RiskAnalysis.cpp "RiskAnalysis.cpp".
 */

#ifndef DA_PROJECT_RISKANALYSIS_H
#define DA_PROJECT_RISKANALYSIS_H
#include "Graph.h"
#include  "Input.h"


template <class T>
void riskAnalysis(Graph<T> *g, T source, T target,const std::string& outputFile);

#endif //DA_PROJECT_RISKANALYSIS_H
