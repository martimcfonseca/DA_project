//
// Created by cristiano on 19/03/26.
//

#ifndef DA_PROJECT_APP_H
#define DA_PROJECT_APP_H

#include <string>
#include <vector>

#include "Graph.h"
using namespace std;


enum class NodeType { SOURCE, SINK, SUBMISSION, REVIEWER };

struct NodeInfo {
    NodeType    type;
    int         id;
    int         primaryTopic;
    int         secondaryTopic;  // 0 se nao existir

    bool operator==(const NodeInfo& other) const {
        return type == other.type && id == other.id;
    }
};


struct Submission {
    int         id;
    std::string title;
    std::string authors;
    std::string email;
    int         primaryTopic;
    int         secondaryTopic;  // -1 se nao tiver
};

struct Reviewer {
    int         id;
    std::string name;
    std::string email;
    int         primaryTopic;
    int         secondaryTopic;  // -1 se nao tiver
};

struct Parameters {
    int         minReviewsPerSubmission    = 0;
    int         maxReviewsPerReviewer      = 0;
    int         primaryReviewerExpertise   = 0;
    int         secondaryReviewerExpertise = 0;
    int         primarySubmissionDomain    = 0;
    int         secondarySubmissionDomain  = 0;
    int         generateAssignments        = 0;
    int         riskAnalysis               = 0;
    std::string outputFileName             = "output.csv";
};


class App {

public:
    bool loadfile(string filename);  // basicamente colocar o codigo do parse
    void listSubmissions();
    void listReviewers  ();
    void listParameters ();

    void generateAssignments(string outputFile);
    void runRiskAnalysis    (string outputFile);


private:
    Graph<NodeInfo> g;
    Parameters parameters;
    vector<Submission> submissions;
    vector<Reviewer> reviewers;

    void creatGraph();




};


#endif //DA_PROJECT_APP_H