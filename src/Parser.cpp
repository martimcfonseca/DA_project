//
// Created by marti on 16/03/2026.
//
/**
 * @file Parser.cpp
 * @brief Implementation of functions for parsing input files and building the flow graph.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Input.h"
#include "Graph.h"
#include "Parser.h"
using namespace std;

/**
 * @brief Parses a line representing a submission and adds it to the Input object.
 *
 * @param line CSV line containing submission data (id, title, authors, email, primary domain, secondary domain).
 * @param data Input object to populate.
 *
 * @note **Time Complexity:** O(1) .
 */
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

/**
 * @brief Parses a line representing a reviewer and adds it to the Input object.
 *
 * @param line CSV line containing reviewer data (id, name, email, primary domain, secondary domain).
 * @param data Input object to populate.
 *
 * @note **Time Complexity:** O(1) .
 */
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

/**
 * @brief Parses a line containing a numeric parameter.
 *
 * @param line CSV line with the parameter value.
 * @return int Parsed integer parameter.
 *
 * @note **Time Complexity:** O(1)
 */
int parseParameter(string& line) {
    stringstream ss(line);
    getline(ss,line,',');
    getline(ss,line,',');
    return stoi(line);
}

/**
 * @brief Parses a line containing a string parameter.
 *
 * @param line CSV line with the string value.
 * @return string Extracted string value.
 *
 * @note **Time Complexity:** O(1)
 */
string parseString(string& line) {
    stringstream ss(line);
    getline(ss,line,',');
    getline(ss,line,',');
    line = line.substr(2,line.size()-3);

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


/**
 * @brief Reads data from standard input and populates an Input object.
 *
 * The input format is assumed to follow the specification with sections for submissions, reviewers,
 * parameters, and execution modes. Lines starting with '#'.
 *
 * @return Input Populated Input object.
 *
 * @note **Time Complexity:** O(L), where L is the total number of lines read from stdin.
 */
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

/**
 * @brief Reads data from a CSV file and populates an Input object.
 *
 * @param filename Path to the input CSV file.
 * @return Input Populated Input object.
 *
 * @note **Time Complexity:** O(L), where L is the total number of lines in the file.
 */

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

/**
 * @brief Builds the flow network graph from the Input object.
 *
 * Creates vertices for source, sink, submissions, and reviewers. Adds edges:
 * - Source -> Submissions (capacity = minReviewsPerSubmission)
 * - Submissions -> Reviewers (capacity = 1, depending on domain/expertise rules)
 * - Reviewers -> Sink (capacity = maxReviewsPerReviewer)
 *
 * @param data Input object containing submissions, reviewers, and parameters.
 * @return Graph<Node> Constructed flow network graph.
 *
 * @note **Time Complexity:** O(S × R) in the worst case, where S is the number of submissions and R is the number of reviewers,
 * because each submission may potentially connect to each reviewer.
 */
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
        if (data.getGenerateAssignments() == 1 && data.getSecondarySubmissionDomain()==0 && data.getSecondaryReviewerExpertise()==0){
            for (auto& sub : subs) {
                if (rev.primary == sub.primary) {
                    graph.addEdge(sub,rev, 1);
                }
            }
        }
        else if (data.getGenerateAssignments() == 2 && data.getSecondarySubmissionDomain()==1 && data.getSecondaryReviewerExpertise()==0) {
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


