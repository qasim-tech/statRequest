#include "StatRequest.hpp"
#include <cmath>
#include <chrono>
#include <iostream>
#include <algorithm>

StatRequest::StatRequest(int maxHistogramBins) : maxHistogramBins(maxHistogramBins) {
}

std::map<std::string, std::vector<double>> StatRequest::getResponseTimes() const {
    return responseTimes;
}

void StatRequest::setResponseTimes(std::map<std::string, std::vector<double>>& rT)  {
    responseTimes = rT;
}

double StatRequest::getMeanResponseTime(const std::string& uri) const {
    // Implementation to calculate and return the mean response time for the specified URI
    std::map<std::string, std::vector<double>> rT = getResponseTimes();
    double meanResponseTime = 0.0;
    
    // Calculate the sum of response times for the specified URI
    for (const auto& responseTime : rT[uri]) {
        meanResponseTime += responseTime;
    }
    
    // Divide the sum by the number of response times to get the mean
    if (!rT[uri].empty()) {
        meanResponseTime /= rT[uri].size();
    }
    
    return meanResponseTime;
}

double StatRequest::getStandardDeviation(const std::string& uri) const {
    std::map<std::string, std::vector<double>> rT = getResponseTimes();
    double meanResponseTime = getMeanResponseTime(uri);
    double sumSquaredDifferences = 0.0;
    
    // Calculate the sum of squared differences from the mean
    for (const auto& responseTime : rT[uri]) {
        double difference = responseTime - meanResponseTime;
        sumSquaredDifferences += difference * difference;
    }
    
    // Divide the sum by the number of response times and take the square root to get the standard deviation
    if (!rT[uri].empty()) {
        double variance = sumSquaredDifferences / rT[uri].size();
        return std::sqrt(variance);
    }
    
    return 0.0; // Return 0 if there are no response times
}

std::vector<double> StatRequest::getNormalizedHistogram(const std::string& uri) const {
    std::map<std::string, std::vector<double>> rT = getResponseTimes();
    std::vector<double> histogram(maxHistogramBins, 0);
    std::vector<double> normalizedHistogram;

    // Calculate the maximum and minimum response times for the specified URI
    double maxResponseTime = *std::max_element(rT[uri].begin(), rT[uri].end());
    double minResponseTime = *std::min_element(rT[uri].begin(), rT[uri].end());

    // Calculate the range of response times
    double range = maxResponseTime - minResponseTime;

    // Calculate the width of each bin
    double binWidth = range / maxHistogramBins;

    if (binWidth == 0.0) {
        return normalizedHistogram; // Return an empty histogram if the range is 0
    }

    // Generate the histogram
    for (const auto& responseTime : rT[uri]) {
        int binIndex = static_cast<int>((responseTime - minResponseTime) / binWidth);
        histogram[binIndex]++;
    }

    int start = 0;
    int end = histogram.size() - 1;

    // Trim the histogram by removing empty bins from the start
    while (start<=end && histogram[start] == 0) {
        start++;
    }
    // Trim the histogram by removing empty bins from the end
    while (start<=end && histogram[end] == 0) {
        end--;
    }

    // Copy the non-empty bins to the normalized histogram
    for (int i = start; i <= end; i++) {
        normalizedHistogram.push_back(histogram[i]/rT[uri].size());
    }

    return normalizedHistogram;
}

// Override the process method to record response times
std::string StatRequest::process(const std::string& uri) {
    auto start = std::chrono::high_resolution_clock::now();

    Request::process(uri); // Call the base class method

    auto finish = std::chrono::high_resolution_clock::now();
    double responseTime = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    std::map<std::string, std::vector<double>> rT = getResponseTimes();
    rT[uri].push_back(responseTime); // Record the response time
    StatRequest::setResponseTimes(rT);

    return "Sample response.";
}