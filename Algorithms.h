#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <string>
#include <unordered_map>
#include "LogEntry.h"

using namespace std;

class Algorithms {
public:
    // HASHING
    static unordered_map<string, int> countFailedAttempts(
        const vector<LogEntry>& logs
    );

    // MERGE SORT
    static vector<pair<string, int>> mergeSortIPs(
        unordered_map<string, int> failedCounts
    );

    // BINARY SEARCH
    static int binarySearchIP(
        const vector<pair<string, int>>& sortedIPs,
        const string& targetIP
    );

    // LINEAR SEARCH
    static int linearSearchIP(
        const vector<pair<string, int>>& sortedIPs,
        const string& targetIP
    );

    // RABIN-KARP
    static vector<int> rabinKarpSearch(
        const string& text,
        const string& pattern
    );

    // PERFORMANCE COMPARISON
    static void compareSearchPerformance();
};

#endif