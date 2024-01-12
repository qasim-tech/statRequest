#pragma once
#include "Request.hpp"
#include <vector>
#include <map>


/**
 * Resource request processing class
 * This class inherits from the Request class and adds functionality to
 * calculate statistics on the response times of requests.
 * To use, instantiate an object and call process() on a URI to get the response
*/
class StatRequest : public Request {
private:
    /**
     * Response times
     * Map URI to response times
    */
    std::map<std::string, std::vector<double>> responseTimes; // Map URI to response times
    /**
     * Maximum number of bins for histograms
    */
    int maxHistogramBins; // Maximum number of bins for histograms

public:
    /**
     * Get the mean response time for the specified URI
     * @param [in] uri The URI of the request endpoint
     * @return The mean response time
     */
    double getMeanResponseTime(const std::string& uri) const;
    /**
     * Get the standard deviation of the response times for the specified URI
     * @param [in] uri The URI of the request endpoint
     * @return The standard deviation of the response times
    */
    double getStandardDeviation(const std::string& uri) const;
    /**
     * Get the normalized histogram of the response times for the specified URI
     * @param [in] uri The URI of the request endpoint
     * @return The normalized histogram of the response times
    */
    std::vector<double> getNormalizedHistogram(const std::string& uri) const;
    /**
     * Process the request
     * @param [in] uri The URI of the request endpoint
     * @return The response data
    */
    std::string process(const std::string& uri);
    /**
     * Get the response times
     * @return The response times
    */
    std::map<std::string, std::vector<double>> getResponseTimes() const;
    /**
     * Set the response times
     * @param [in] rT The response times
    */
    void setResponseTimes(std::map<std::string, std::vector<double>>& rT);

    // Constructor to set the maximum number of bins for histograms
    StatRequest(int maxHistogramBins);
};