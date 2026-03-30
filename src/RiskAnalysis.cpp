//
// Created by cristiano on 27/03/26.
//

/**
 * @file RiskAnalysis.cpp
 * @brief Implementation of the risk analysis functions.
 */

#include <iostream>
#include "RiskAnalysis.h"
#include <vector>
#include "MaxFlow.h"
#include "Parser.h"
#include <fstream>


/**
 * @brief Implementation of the risk analysis algorithm.
 *
 * This algorithm identifies "critical reviewers". For each reviewer in the graph:
 * 1. Temporarily removes their capacity (setWeight(0)).
 * 2. Recalculates the Maximum Flow using the Edmonds-Karp algorithm.
 * 3. If the total flow decreases, the reviewer is marked as critical.
 * 4. Restores the original capacity for the next test.
 *
 * @note **Detailed Time Complexity:** O(R × (V · E²)), where R is the number of reviewers.
 * This is the most computationally expensive operation in the system, as it runs Edmonds-Karp repeatedly.
 */

template <class T>
void riskAnalysis(Graph<T> *g, T source, T target,const std::string& outputFile) {

    std::vector<int> reviewers;

    Vertex<T>* s = g->findVertex(source);
    double expectedFlow = 0;
    for (auto e : s->getAdj()) {
        expectedFlow += e->getFlow();
    }


    for (auto v : g->getVertexSet()) {
        if (v->getInfo().type == Node::Type::REVIEWER) {
            int capacidade;
            for (auto e : v->getAdj()) {
                capacidade = e->getWeight();
                e->setWeight(0);
            }

            for (auto e : v->getIncoming()) {
                e->setFlow(0);
            }

            edmondsKarp(g, source, target);
            double newFlow = 0;
            for (auto e : s->getAdj()) {
                newFlow += e->getFlow();
            }

            for (auto e : v->getAdj()) {
                e->setWeight(capacidade);
            }


            if (newFlow != expectedFlow) {
                reviewers.push_back(v->getInfo().id);
            }

        }

    }

    std::ofstream out(outputFile, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Erro ao abrir ficheiro: " << outputFile << std::endl;
        return;
    }
    out << "#Risk Analysis: 1" << std::endl;
    if (!reviewers.empty()) {
        out << reviewers[0];
        for (int i = 1; i < reviewers.size(); i++) {
            out << ", " << reviewers[i];
        }
        out << '\n';
    }
}

template void riskAnalysis<Node>(Graph<Node>*, Node, Node,const std::string& outputFile);
