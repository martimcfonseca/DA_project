//
// Created by marti on 16/03/2026.
//

#ifndef DA_PROJECT_INPUT_H
#define DA_PROJECT_INPUT_H
#include <string>
#include <vector>

class Submission {
public:
    int id;
    std::string title;
    std::string authors;
    std::string email;
    int primary;
    int secondary;
};

class Reviewer {
public:
    int id;
    std::string name;
    std::string email;
    int primary;
    int secondary;
};

class Input {
private:
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;
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
    std::vector<Submission> getSubmissions() const ;
    std::vector<Reviewer> getReviewers() const ;
    int getMinReviewsPerSubmission() const ;
    int getMaxReviewsPerReviewer() const ;
    int getPrimaryReviewerExpertise() const ;
    int getSecondaryReviewerExpertise() const ;
    int getPrimarySubmissionDomain() const ;
    int getSecondarySubmissionDomain() const ;
    int getGenerateAssignments() const;
    int getRiskAnalysis() const;
    std::string getOutputFileName() const;

    void setSubmissions(std::vector<Submission>& submissions);
    void setReviewers(std::vector<Reviewer>& reviewers);
    void setMinReviewsPerSubmission(int minReviewsPerSubmission);
    void setMaxReviewsPerReviewer(int maxReviewsPerReviewer);
    void setPrimaryReviewerExpertise(int primaryReviewerExpertise);
    void setSecondaryReviewerExpertise(int secondaryReviewerExpertise);
    void setPrimarySubmissionDomain(int primarySubmissionDomain);
    void setSecondarySubmissionDomain(int secondarySubmissionDomain);
    void setGenerateAssignments(int generateAssignments);
    void setRiskAnalysis(int riskAnalysis);
    void setOutputFileName(const std::string& fileName);

    void addSubmission(const Submission& submission);
    void addReviewer(const Reviewer& reviewer);

};

#endif //DA_PROJECT_INPUT_H