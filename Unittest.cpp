#include "StatRequest.hpp"
#include <iostream>
#include <cassert>

void runUnitTests() {
    // Create a StatisticalRequest object
    StatRequest statRequest(20); // Assuming 20 as the maximum number of histogram bins

    // Simulate processing requests
    for (int i = 0; i < 100; ++i) {
        statRequest.process("uri1");
        statRequest.process("uri2");
    }

    // Test mean response time
    assert(statRequest.getMeanResponseTime("uri1") > 0);
    assert(statRequest.getMeanResponseTime("uri2") > 0);

    // Test standard deviation
    assert(statRequest.getStandardDeviation("uri1") > 0);
    assert(statRequest.getStandardDeviation("uri2") > 0);

    // Test normalized histogram
    std::vector<double> histogramUri1 = statRequest.getNormalizedHistogram("uri1");
    std::vector<double> histogramUri2 = statRequest.getNormalizedHistogram("uri2");

    // Ensure the first element is non zero, ensuring no edges are zero
    assert(histogramUri1[0] > 0);
    assert(histogramUri2[0] > 0);
}

int main() {
    runUnitTests();
    std::cout << "All tests passed!\n";
    return 0;
}