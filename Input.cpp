#include "Input.h"
//
// Created by marti on 16/03/2026.
//

std::vector<std::vector<int> > Input::getSubmissions() const  {
    return submissions;
}

std::vector<std::vector<int> > Input::getReviewers() const {
    return reviewers;
}

int Input::getMaxReviewsPerReviewer() const {
    return maxReviewsPerReviewer;
}

int Input::getMinReviewsPerSubmission() const {
    return minReviewsPerSubmission;
}

int Input::getPrimaryReviewerExpertise() const {
    return primaryReviewerExpertise;
}

int Input::getSecondaryReviewerExpertise() const {
    return secondaryReviewerExpertise;
}

int Input::getPrimarySubmissionDomain() const {
    return primarySubmissionDomain;
}

int Input::getSecondarySubmissionDomain() const {
    return secondarySubmissionDomain;
}

int Input::getGenerateAssignments() const {
    return generateAssignments;
}

int Input::getRiskAnalysis() const {
    return riskAnalysis;
}

std::string Input::getOutputFileName() const {
    return outputFileName;
}

void Input::setSubmissions(std::vector<std::vector<int>>& submissions) {
    this->submissions = submissions;
}

void Input::setReviewers(std::vector<std::vector<int> >& reviewers) {
    this->reviewers = reviewers;
}

void Input::setMinReviewsPerSubmission(int minReviewsPerSubmission) {
    this->minReviewsPerSubmission = minReviewsPerSubmission;
}

void Input::setMaxReviewsPerReviewer(int maxReviewsPerReviewer) {
    this->maxReviewsPerReviewer = maxReviewsPerReviewer;
}

void Input::setPrimaryReviewerExpertise(int primaryReviewerExpertise) {
    this->primaryReviewerExpertise = primaryReviewerExpertise;
}

void Input::setSecondaryReviewerExpertise(int secondaryReviewerExpertise) {
    this->secondaryReviewerExpertise = secondaryReviewerExpertise;
}

void Input::setPrimarySubmissionDomain(int primarySubmissionDomain) {
    this->primarySubmissionDomain = primarySubmissionDomain;
}

void Input::setSecondarySubmissionDomain(int secondarySubmissionDomain) {
    this->secondarySubmissionDomain = secondarySubmissionDomain;
}

void Input::addSubmission(const std::vector<int>& submission) {
    submissions.push_back(submission);
}

void Input::addReviewer(const std::vector<int>& reviewer) {
    reviewers.push_back(reviewer);
}

void Input::setGenerateAssignments(int generateAssignments) {
    this->generateAssignments = generateAssignments;
}
void Input::setRiskAnalysis(int riskAnalysis) {
    this->riskAnalysis = riskAnalysis;
}
void Input::setOutputFileName(const std::string& outputFileName) {
    this->outputFileName = outputFileName;
}