#include "MaxFlow.h"
#include <map>

template <class T>
void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
template <class T>
bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
    // Mark all vertices as not visited
    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    std::queue<Vertex<T>*> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        Vertex<T>* v = q.front();
        q.pop();
        for  (auto e : v->getAdj()) {
            testAndVisit(q, e, e->getDest(),e->getWeight()-e->getFlow());
        }
        for (auto e : v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(),e->getFlow());
        }
    }
    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
    double f = INF;
    Vertex<T>* v = t;
    while (v != s) {
        Edge<T>* e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }

    // Return the minimum residual capacity
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
    // Traverse the augmenting path and update the flow values accordingly
    Vertex<T>* v = t;
    while (v != s) {
        Edge<T>* e = v->getPath();
        if (e->getDest() == v) {
            e->setFlow(e->getFlow() + f);
            v = e->getOrig();
        } else {
            e->setFlow(e->getFlow() - f);
            v = e->getDest();
        }
    }
}

// Main function implementing the Edmonds-Karp algorithm
template <class T>
void edmondsKarp(Graph<T> *g, T source, T target) {
    // Find source and target vertices in the graph
    Vertex<T>* s = g->findVertex(source);
    Vertex<T>* t = g->findVertex(target);

    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setPath(nullptr);
        for (auto e : v->getAdj()) {
            e->setFlow(0);
        }
    }

   while (findAugmentingPath(g, s, t)) {
       double f = findMinResidualAlongPath(s, t);
       augmentFlowAlongPath(s, t, f);
   }
}

void printResults(const Graph<Node>& graph, const Input& data) {
    Node source{0, Node::Type::SOURCE};
    Node sink{0, Node::Type::SINK};

    // Maps for output
    // submissionId -> list of reviewerIds assigned
    std::map<int, std::vector<int>> subToRevs;
    // reviewerId -> list of submissionIds assigned
    std::map<int, std::vector<int>> revToSubs;

    // Read flows on sub->reviewer edges
    for (auto& rev : data.getReviewers()) {
        Node revNode{rev.id, Node::Type::REVIEWER, rev.primary, rev.secondary};
        Vertex<Node>* revVertex = graph.findVertex(revNode);
        if (!revVertex) continue;

        for (Edge<Node>* edge : revVertex->getIncoming()) {
            if (edge->getOrig()->getInfo().type == Node::Type::SUBMISSION
                && edge->getFlow() > 0) {
                int subId = edge->getOrig()->getInfo().id;
                subToRevs[subId].push_back(rev.id);
                revToSubs[rev.id].push_back(subId);
            }
        }
    }

    // #SubmissionId,ReviewerId,Match
    std::cout << "#SubmissionId,ReviewerId,Match\n";
    for (auto& [subId, revIds] : subToRevs)
        for (int revId : revIds)
            std::cout << subId << ", " << revId << ", 1\n";

    // #ReviewerId,SubmissionId,Match
    std::cout << "#ReviewerId,SubmissionId,Match\n";
    for (auto& [revId, subIds] : revToSubs)
        for (int subId : subIds)
            std::cout << revId << ", " << subId << ", 1\n";

    // Total assignments
    int total = 0;
    for (auto& [subId, revIds] : subToRevs) total += revIds.size();
    std::cout << "#Total: " << total << "\n";

    // Missing reviews per submission
    std::cout << "#SubmissionId,Domain,MissingReviews\n";
    for (auto& sub : data.getSubmissions()) {
        int assigned = subToRevs.count(sub.id) ? subToRevs[sub.id].size() : 0;
        int missing = data.getMinReviewsPerSubmission() - assigned;
        if (missing > 0)
            std::cout << sub.id << ", " << sub.primary << ", " << missing << "\n";
    }
}

template void edmondsKarp<Node>(Graph<Node> *g, Node source, Node target);