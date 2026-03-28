//
// Created by cristiano on 27/03/26.
//
#include <iostream>
#include "RiskAnalysis.h"
#include <vector>
#include "MaxFlow.h"
#include "Parser.h"
#include <fstream>

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
    out << "#Risk Analysis: 1\n";
    for (int id : reviewers)
        out << id << ", ";


}

template void riskAnalysis<Node>(Graph<Node>*, Node, Node,const std::string& outputFile);
