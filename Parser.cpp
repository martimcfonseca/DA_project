//
// Created by marti on 16/03/2026.
//
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Input.h"
using namespace std;


void parseSubmission(string& line,Input& data) {
    vector<int> submission(3);
    stringstream ss(line);
    getline(ss,line,',');
    submission[0] = stoi(line);
    getline(ss,line,',');
    getline(ss,line,',');
    getline(ss,line,',');
    getline(ss,line,',');
    submission[1] = stoi(line);
    getline(ss,line,',');
    if (line.empty()) submission[2] = -1;
    else submission[2] = stoi(line);
    data.addSubmission(submission);
}

void parseReviewer(string& line, Input& data) {
    vector<int> reviewer(3);
    stringstream ss(line);
    getline(ss,line,',');
    reviewer[0] = stoi(line);
    getline(ss,line,',');
    getline(ss,line,',');
    getline(ss,line,',');
    reviewer[1] = stoi(line);
    getline(ss,line,',');
    if (line.empty()) reviewer[2] = -1;
    else reviewer[2] = stoi(line);
    data.addReviewer(reviewer);
}


int parseParameter(string& line) {
    stringstream ss(line);
    getline(ss,line,',');
    getline(ss,line,',');
    return stoi(line);
}

string parseFile(string& line) {
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
        for (int val : sub) {
            std::cout << val << " ";
        }
        std::cout << "]" << std::endl;
    }

    // Printing nested vectors: Reviewers
    std::cout << "\nReviewers:" << std::endl;
    for (const auto& rev : data.getReviewers()) {
        std::cout << "  [ ";
        for (int val : rev) {
            std::cout << val << " ";
        }
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


int main() {
    Input data;
    string line;

    getline(cin,line);
    getline(cin,line);
    getline(cin,line);

    while (line[0]!='#') {
        parseSubmission(line,data);
        getline(cin,line);
    }

    getline(cin,line);
    getline(cin,line);
    getline(cin,line);

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
    getline(cin,line);

    getline(cin,line);
    data.setGenerateAssignments(parseParameter(line));
    getline(cin,line);
    data.setRiskAnalysis(parseParameter(line));
    getline(cin,line);
    data.setOutputFileName(parseFile(line));


    printData(data);
    return 0;
}