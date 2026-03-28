
/**
 * @file Input.cpp
 * @brief Implementation of the Input class for managing system input data.
 *
 * This file implements all getters and setters for the Input class, which
 * manages submissions, reviewers, flow constraint parameters, and output settings.
 */

#include "Input.h"
//
// Created by marti on 16/03/2026.
//

/**
 * @brief Returns the list of submissions.
 * @return Vector of Submission objects.
 */

std::vector<Submission> Input::getSubmissions() const  {
    return submissions;
}

/**
 * @brief Returns the list of reviewers.
 * @return Vector of Reviewer objects.
 */

std::vector<Reviewer> Input::getReviewers() const {
    return reviewers;
}

/**
 * @brief Returns the maximum number of reviews per reviewer.
 * @return Maximum number of reviews allowed per reviewer.
 */

int Input::getMaxReviewsPerReviewer() const {
    return maxReviewsPerReviewer;
}

/**
 * @brief Returns the minimum number of reviews per submission.
 * @return Minimum number of reviews required per submission.
 */

int Input::getMinReviewsPerSubmission() const {
    return minReviewsPerSubmission;
}

/**
 * @brief Returns the primary domain of the reviewer.
 */

int Input::getPrimaryReviewerExpertise() const {
    return primaryReviewerExpertise;
}

/**
 * @brief Returns the secondary domain of the reviewer.
 */

int Input::getSecondaryReviewerExpertise() const {
    return secondaryReviewerExpertise;
}

/**
 * @brief Returns the primary domain of the submission.
 */

int Input::getPrimarySubmissionDomain() const {
    return primarySubmissionDomain;
}

/**
 * @brief Returns the secondary domain of the submission.
 */

int Input::getSecondarySubmissionDomain() const {
    return secondarySubmissionDomain;
}

/**
 * @brief Returns the flag indicating whether assignments should be generated.
 */

int Input::getGenerateAssignments() const {
    return generateAssignments;
}

/**
 * @brief Returns the flag indicating whether risk analysis should be performed.
 */

int Input::getRiskAnalysis() const {
    return riskAnalysis;
}

/**
 * @brief Returns the name of the output file.
 */

std::string Input::getOutputFileName() const {
    return outputFileName;
}

/**
 * @brief Sets the list of submissions.
 * @param submissions Vector of Submission objects.
 */

void Input::setSubmissions(std::vector<Submission> &submissions) {
    this->submissions = submissions;
}

/**
 * @brief Sets the list of reviewers.
 * @param reviewers Vector of Reviewer objects.
 */

void Input::setReviewers(std::vector<Reviewer> &reviewers) {
    this->reviewers = reviewers;
}

/**
 * @brief Sets the minimum number of reviews per submission.
 */

void Input::setMinReviewsPerSubmission(int minReviewsPerSubmission) {
    this->minReviewsPerSubmission = minReviewsPerSubmission;
}

/**
 * @brief Sets the maximum number of reviews per reviewer.
 */

void Input::setMaxReviewsPerReviewer(int maxReviewsPerReviewer) {
    this->maxReviewsPerReviewer = maxReviewsPerReviewer;
}

/**
 * @brief Sets the primary domain of the reviewer.
 */


void Input::setPrimaryReviewerExpertise(int primaryReviewerExpertise) {
    this->primaryReviewerExpertise = primaryReviewerExpertise;
}

/**
 * @brief Sets the secondary domain of the reviewer.
 */

void Input::setSecondaryReviewerExpertise(int secondaryReviewerExpertise) {
    this->secondaryReviewerExpertise = secondaryReviewerExpertise;
}

/**
 * @brief Sets the primary domain of the submission.
 */

void Input::setPrimarySubmissionDomain(int primarySubmissionDomain) {
    this->primarySubmissionDomain = primarySubmissionDomain;
}

/**
 * @brief Sets the secondary domain of the submission.
 */

void Input::setSecondarySubmissionDomain(int secondarySubmissionDomain) {
    this->secondarySubmissionDomain = secondarySubmissionDomain;
}

/**
 * @brief Adds a submission to the list.
 */

void Input::addSubmission(const Submission &submission) {
    submissions.push_back(submission);
}

/**
 * @brief Adds a reviewer to the list.
 */

void Input::addReviewer(const Reviewer &reviewer) {
    reviewers.push_back(reviewer);
}

/**
 * @brief Sets generate assignments.
 */

void Input::setGenerateAssignments(int generateAssignments) {
    this->generateAssignments = generateAssignments;
}

/**
 * @brief Sets risk analysis.
 */

void Input::setRiskAnalysis(int riskAnalysis) {
    this->riskAnalysis = riskAnalysis;
}

/**
 * @brief Sets output filename.
 */
void Input::setOutputFileName(const std::string& outputFileName) {
    this->outputFileName = outputFileName;
}