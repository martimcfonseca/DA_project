/**
* @file MaxFlow.cpp
 * @brief Detailed implementation of the Edmonds-Karp algorithm and reporting functions.
 */

#include "MaxFlow.h"
#include <map>
#include <fstream>

/**
 * @brief Helper function to visit a node, update the BFS queue, and check if an edge is valid.
 *
 * @param q Queue to be updated if necessary.
 * @param e Edge to be analyzed.
 * @param w Vertex to be checked.
 * @param residual Residual capacity of the edge.
 *
 * @note **Time Complexity:** O(1).
 */
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


/**
 * @brief Searches for an augmenting path using Breadth-First Search (BFS).
 *
 * @param g Graph in which to find the augmenting path.
 * @param s Pointer to the source vertex of the graph.
 * @param t Pointer to the target vertex of the graph(sink).
 *
 * @note **Time Complexity:** O(V + E), where V is the number of vertices and
 * E is the number of edges traversed during the search.
 *
 * @return true if the target (t) was reached, false otherwise.
 */
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


/**
 * @brief Computes the minimum residual capacity along a found path.
 *
 * @param s Pointer to the source vertex of the path.
 * @param t Pointer to the target vertex of the path.
 *
 * @note **Time Complexity:** O(V) in the worst case (path traverses all vertices).
 */
template <class T>
double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);
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


/**
 * @brief Updates the flow (direct and residual) along the augmenting path.
 *
 * @param s Pointer to the source vertex of the path.
 * @param t Pointer to the target vertex of the path.
 * @param f Flow value to be added along the path.
 *
 * @note **Time Complexity:** O(V).
 */
template <class T>
void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f);
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

/**
 * @brief Processes the graph after the maximum flow computation and exports the assignment results.
 *
 * This function iterates through the graph edges to identify assignments between reviewers
 * and submissions (where flow > 0), organizes the data in maps for ordered output,
 * writes the results to a CSV file, and reports any missing reviews per submission.
 *
 * The output file contains:
 * - SubmissionId, ReviewerId, Match
 * - ReviewerId, SubmissionId, Match
 * - Total number of assignments
 * - Missing reviews per submission (if any)
 *
 * @param graph Reference to the processed flow graph.
 * @param data Reference to the input data.
 * @param outputFile Name of the output file where results will be written.
 *
 * @note **Time Complexity:** O(R × A + V + E), where R is the number of reviewers,
 * A is the average number of assignments per reviewer, V is the number of vertices,
 * and E is the number of edges in the graph.
 */
void printResults(const Graph<Node>& graph, const Input& data, const std::string& outputFile);

void printResults(const Graph<Node>& graph, const Input& data,const std::string& outputFile) {
    Node source{0, Node::Type::SOURCE};
    Node sink{0, Node::Type::SINK};

    // Maps for output
    // submissionId -> list of reviewerIds assigned
    std::map<int, std::vector<std::pair<int,int>>> subToRevs;
    // reviewerId -> list of submissionIds assignedl
    std::map<int, std::vector<std::pair<int,int>>> revToSubs;

    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "Erro ao abrir ficheiro: " << outputFile << std::endl;
        return;
    }

    // Read flows on sub->reviewer edges
    for (auto& rev : data.getReviewers()) {
        Node revNode{rev.id, Node::Type::REVIEWER, rev.primary, rev.secondary};
        Vertex<Node>* revVertex = graph.findVertex(revNode);
        if (!revVertex) continue;

        for (Edge<Node>* edge : revVertex->getIncoming()) {
            if (edge->getOrig()->getInfo().type == Node::Type::SUBMISSION
                && edge->getFlow() > 0) {
                int subId = edge->getOrig()->getInfo().id;
                int subPrimary = edge->getOrig()->getInfo().primary;
                int subSecondary = edge->getOrig()->getInfo().secondary;

                int matchDomain;
                if (rev.primary == subPrimary) matchDomain = subPrimary;
                else if (rev.primary == subSecondary) matchDomain = subSecondary;
                else if (rev.secondary == subPrimary) matchDomain = subPrimary;
                else matchDomain = subSecondary;
                subToRevs[subId].push_back({rev.id, matchDomain});
                revToSubs[rev.id].push_back({subId, matchDomain});
            }
        }
    }

    // #SubmissionId,ReviewerId,Match
    out << "#SubmissionId,ReviewerId,Match\n";
    for (auto& [subId, revIds] : subToRevs)
        for (auto& rev : revIds)
            out << subId << ", " << rev.first << ", " << rev.second << "\n";

    // #ReviewerId,SubmissionId,Match
    out << "#ReviewerId,SubmissionId,Match\n";
    for (auto& [revId, subIds] : revToSubs)
        for (auto& sub : subIds)
            out << revId << ", " << sub.first << ", " << sub.second << "\n";

    // Total assignments
    int total = 0;
    for (auto& [subId, revIds] : subToRevs) total += revIds.size();
    out << "#Total: " << total << "\n";

    // Missing reviews per submission
    std::vector<std::tuple<int,int,int>> miss;
    for (auto& edge : graph.findVertex(source)->getAdj()) {
        int missingFlow = data.getMinReviewsPerSubmission() - edge->getFlow();
        if (missingFlow > 0) {
            auto sub = edge->getDest()->getInfo();
            miss.push_back({sub.id,sub.primary,missingFlow});
        }
    }
    if (!miss.empty()) {
        out << "#SubmissionId,Domain,MissingReviews\n";
        for (auto& [subId, domain, count] : miss)
            out << subId << ", " << domain << ", " << count << "\n";
    }
}

template void edmondsKarp<Node>(Graph<Node> *g, Node source, Node target);