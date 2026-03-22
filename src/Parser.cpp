//
// Created by marti on 16/03/2026.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Input.h"
#include "Graph.h"
using namespace std;

class Node {
public:
    int id;
    enum class Type { SOURCE, SINK, SUBMISSION, REVIEWER } type;
    int primary;
    int secondary;

    bool operator==(const Node& o) const {
        return id == o.id && type == o.type;
    }

    void printNode() const{
        std::cout << id << ' ';
        switch (type) {
            case Type::SOURCE: std::cout << "SOURCE";break;
            case Type::SINK: std::cout << "SINK";break;
            case Type::SUBMISSION: std::cout << "SUBMISSION";break;
            case Type::REVIEWER: std::cout << "REVIEWER";break;
        }
        cout << ' ' << primary << ' ' << secondary <<std::endl;
    }
};

void parseSubmission(string& line,Input& data) {
    Submission submission;
    stringstream ss(line);
    getline(ss,line,',');
    submission.id = stoi(line);
    getline(ss,line,',');
    submission.title = line;
    getline(ss,line,',');
    submission.authors = line;
    getline(ss,line,',');
    submission.email=line;
    getline(ss,line,',');
    submission.primary = stoi(line);
    getline(ss,line,',');
    if (line.size()==1 && line[0]==' ' || line.empty()) submission.secondary = -1;
    else submission.secondary = stoi(line);
    data.addSubmission(submission);
}

void parseReviewer(string& line, Input& data) {
    Reviewer reviewer;
    stringstream ss(line);
    getline(ss,line,',');
    reviewer.id = stoi(line);
    getline(ss,line,',');
    reviewer.name = line;
    getline(ss,line,',');
    reviewer.email = line;
    getline(ss,line,',');
    reviewer.primary = stoi(line);
    getline(ss,line,',');
    if (line.size()==1 && line[0]==' ' || line.empty()) reviewer.secondary = -1;
    else reviewer.secondary = stoi(line);
    data.addReviewer(reviewer);
}


int parseParameter(string& line) {
    stringstream ss(line);
    getline(ss,line,',');
    getline(ss,line,',');
    return stoi(line);
}

string parseString(string& line) {
    stringstream ss(line);
    getline(ss,line,',');
    getline(ss,line,',');
    return line;
}

void printData(Input& data) {
    std::cout << "--- Input Class Details ---" << std::endl;

    // Printing nested vectors: Submissions
    std::cout << "Submissions:" << std::endl;
    for (const auto& sub : data.getSubmissions()) {
        std::cout << "  [ ";
        std::cout << sub.id << ' ' << sub.title << ' ' << sub.authors << ' '
        << sub.email << ' ' << sub.primary << ' ' << sub.secondary;
        std::cout << "]" << std::endl;
    }

    // Printing nested vectors: Reviewers
    std::cout << "\nReviewers:" << std::endl;
    for (const auto& rev : data.getReviewers()) {
        std::cout << "  [ ";
        std::cout << rev.id << ' ' << rev.name << ' ' << rev.email << ' '
        << rev.primary << ' ' << rev.secondary;
        std::cout << "]" << std::endl;
    }

    // Printing scalar values
    std::cout << "\nConstraints & Expertise:" << std::endl;
    std::cout << "* Min Reviews Per Submission: " << data.getMinReviewsPerSubmission() << std::endl;
    std::cout << "* Max Reviews Per Reviewer:   " << data.getMaxReviewsPerReviewer() << std::endl;
    std::cout << "* Primary Reviewer Exp:       " << data.getPrimaryReviewerExpertise() << std::endl;
    std::cout << "* Secondary Reviewer Exp:     " << data.getSecondaryReviewerExpertise() << std::endl;
    std::cout << "* Primary Submission Domain:  " << data.getPrimarySubmissionDomain() << std::endl;
    std::cout << "* Secondary Submission Domain: " << data.getSecondarySubmissionDomain() << std::endl;
    std::cout << "\n--- Execution Modes & Output ---" << std::endl;
    // Printing as integers since they represent specific modes
    std::cout << "Assignment Mode:      " << data.getGenerateAssignments() << std::endl;
    std::cout << "Risk Analysis Mode:   " << data.getRiskAnalysis() << std::endl;
    std::cout << "Output File:          " << (data.getOutputFileName().empty() ? "[None]" : data.getOutputFileName()) << std::endl;
    std::cout << "---------------------------" << std::endl;
}


Input parseData() {
    Input data;
    string line;

    do {
        getline(cin,line);
    } while (line[0]=='#');

    while (line[0]!='#') {
        parseSubmission(line,data);
        getline(cin,line);
    }

    do {
        getline(cin,line);
    } while (line[0]=='#');

    while (line[0]!='#') {
        parseReviewer(line,data);
        getline(cin,line);
    }

    getline(cin,line);
    data.setMinReviewsPerSubmission(parseParameter(line));
    getline(cin,line);
    data.setMaxReviewsPerReviewer(parseParameter(line));
    getline(cin,line);
    data.setPrimaryReviewerExpertise(parseParameter(line));
    getline(cin,line);
    data.setSecondaryReviewerExpertise(parseParameter(line));
    getline(cin,line);
    data.setPrimarySubmissionDomain(parseParameter(line));
    getline(cin,line);
    data.setSecondarySubmissionDomain(parseParameter(line));

    do {
        getline(cin,line);
    } while (line[0]=='#');


    data.setGenerateAssignments(parseParameter(line));
    getline(cin,line);
    data.setRiskAnalysis(parseParameter(line));
    getline(cin,line);
    data.setOutputFileName(parseString(line));


    return data;
}

Input parseFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    Input data;
    string line;

    do {
        getline(file, line);
    } while (line[0] == '#');

    while (line[0] != '#') {
        parseSubmission(line, data);
        getline(file, line);
    }

    do {
        getline(file, line);
    } while (line[0] == '#');

    while (line[0] != '#') {
        parseReviewer(line, data);
        getline(file, line);
    }

    getline(file, line);
    data.setMinReviewsPerSubmission(parseParameter(line));
    getline(file, line);
    data.setMaxReviewsPerReviewer(parseParameter(line));
    getline(file, line);
    data.setPrimaryReviewerExpertise(parseParameter(line));
    getline(file, line);
    data.setSecondaryReviewerExpertise(parseParameter(line));
    getline(file, line);
    data.setPrimarySubmissionDomain(parseParameter(line));
    getline(file, line);
    data.setSecondarySubmissionDomain(parseParameter(line));

    do {
        getline(file, line);
    } while (line[0] == '#');

    data.setGenerateAssignments(parseParameter(line));
    getline(file, line);
    data.setRiskAnalysis(parseParameter(line));
    getline(file, line);
    data.setOutputFileName(parseString(line));

    return data;
}

Graph<Node> makeGraph(const Input& data) {
    Graph<Node> graph;
    Node source{0,Node::Type::SOURCE};
    Node sink{0,Node::Type::SINK};
    graph.addVertex(source);
    graph.addVertex(sink);

    std::vector<Node> subs;
    for (auto& sub : data.getSubmissions()) {
        Node node{sub.id,Node::Type::SUBMISSION,sub.primary,sub.secondary};
        graph.addVertex(node);
        subs.push_back(node);
        graph.addEdge(source,node,data.getMinReviewsPerSubmission());
    }

    for (auto& reviewer : data.getReviewers()) {
        Node rev{reviewer.id,Node::Type::REVIEWER,reviewer.primary,reviewer.secondary};
        graph.addVertex(rev);
        graph.addEdge(rev,sink,data.getMaxReviewsPerReviewer());
        if (data.getSecondarySubmissionDomain()==0 && data.getSecondaryReviewerExpertise()==0){
            for (auto& sub : subs) {
                if (rev.primary == sub.primary) {
                    graph.addEdge(sub,rev, 1);
                }
            }
        }
        else if (data.getSecondarySubmissionDomain()==1 && data.getSecondaryReviewerExpertise()==0) {
            for (auto& sub : subs) {
                if (rev.primary == sub.primary || rev.primary == sub.secondary) {
                    graph.addEdge(sub,rev,1);
                }
            }
        }
        else if (data.getSecondarySubmissionDomain()==0 && data.getSecondaryReviewerExpertise()==1) {
            for (auto& sub : subs) {
                if (rev.primary == sub.primary || rev.secondary == sub.primary) {
                    graph.addEdge(sub,rev,1);
                }
            }
        }
        else {
            for (auto& sub : subs) {
                if (rev.primary == sub.primary || rev.secondary == sub.primary ||
                    rev.primary==sub.secondary || (rev.secondary==sub.secondary && rev.secondary!=-1)) {
                    graph.addEdge(sub,rev,1);
                }
            }
        }
    }
    return graph;
}


int main() {
    Input data = parseData();
    Graph<Node> graph = makeGraph(data);
    printData(data);

    for (auto v : graph.getVertexSet()) {
        if (v->getInfo().type == Node::Type::SUBMISSION) {
            cout << "submission ";
            v->getInfo().printNode();
            for (auto& e : v->getAdj()) {
                e->getDest()->getInfo().printNode();
            }
        }
    }
    return 0;
}