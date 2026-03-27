//
// Created by cristiano on 27/03/26.
//
#include <iostream>
#include "RiskAnalysis.h"
#include <vector>
#include "MaxFlow.h"
#include "Parser.h"

template <class T>
void riskAnalysis(Graph<T> *g, T source, T target) {

    std::vector<int> reviewers;

    edmondsKarp(g, source, target);
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

    std::cout << "teste" << std::endl;
    for (auto r : reviewers) {
        std::cout << r << " ";
    }


}

template void riskAnalysis<Node>(Graph<Node>*, Node, Node);
