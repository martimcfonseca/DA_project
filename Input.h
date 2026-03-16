//
// Created by marti on 16/03/2026.
//

#ifndef DA_PROJECT_INPUT_H
#define DA_PROJECT_INPUT_H
#include <string>
#include <vector>

class Input {
private:
    std::vector<std::vector<int>> submissions;
    std::vector<std::vector<int>> reviewers;
    int minReviewsPerSubmission;
    int maxReviewsPerReviewer;
    int primaryReviewerExpertise;
    int secondaryReviewerExpertise;
    int primarySubmissionDomain;
    int secondarySubmissionDomain;
    int generateAssignments;
    int riskAnalysis;
    std::string outputFileName;

public:
    std::vector<std::vector<int>> getSubmissions() const ;
    std::vector<std::vector<int>> getReviewers() const ;
    int getMinReviewsPerSubmission() const ;
    int getMaxReviewsPerReviewer() const ;
    int getPrimaryReviewerExpertise() const ;
    int getSecondaryReviewerExpertise() const ;
    int getPrimarySubmissionDomain() const ;
    int getSecondarySubmissionDomain() const ;
    int getGenerateAssignments() const;
    int getRiskAnalysis() const;
    std::string getOutputFileName() const;

    void setSubmissions(std::vector<std::vector<int>>& submissions);
    void setReviewers(std::vector<std::vector<int>>& reviewers);
    void setMinReviewsPerSubmission(int minReviewsPerSubmission);
    void setMaxReviewsPerReviewer(int maxReviewsPerReviewer);
    void setPrimaryReviewerExpertise(int primaryReviewerExpertise);
    void setSecondaryReviewerExpertise(int secondaryReviewerExpertise);
    void setPrimarySubmissionDomain(int primarySubmissionDomain);
    void setSecondarySubmissionDomain(int secondarySubmissionDomain);
    void setGenerateAssignments(int generateAssignments);
    void setRiskAnalysis(int riskAnalysis);
    void setOutputFileName(const std::string& fileName);

    void addSubmission(const std::vector<int>& submission);
    void addReviewer(const std::vector<int>& reviewer);

};

#endif //DA_PROJECT_INPUT_H