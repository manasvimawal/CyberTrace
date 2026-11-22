#include "Algorithms.h"
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std;

// HASHING: COUNT FAILED ATTEMPTS
unordered_map<string, int> Algorithms::countFailedAttempts(
    const vector<LogEntry>& logs
) {
    unordered_map<string, int> counts;

    for (const LogEntry& log : logs) {
        if (log.level == "FAILED") {
            counts[log.ipAddress]++;
        }
    }

    return counts;
}

// MERGE SORT: RANK IPs BY FAILED ATTEMPTS
vector<pair<string, int>> Algorithms::mergeSortIPs(
    unordered_map<string, int> failedCounts
) {
    vector<pair<string, int>> ips(failedCounts.begin(), failedCounts.end());

    sort(ips.begin(), ips.end(),
         [](const pair<string, int>& a,
            const pair<string, int>& b) {
             return a.second > b.second;
         });

    return ips;
}

// BINARY SEARCH
int Algorithms::binarySearchIP(
    const vector<pair<string, int>>& sortedIPs,
    const string& targetIP
) {
    int left = 0;
    int right = static_cast<int>(sortedIPs.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (sortedIPs[mid].first == targetIP) {
            return mid;
        }

        if (sortedIPs[mid].first < targetIP) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

// LINEAR SEARCH
int Algorithms::linearSearchIP(
    const vector<pair<string, int>>& sortedIPs,
    const string& targetIP
) {
    for (int i = 0; i < static_cast<int>(sortedIPs.size()); i++) {
        if (sortedIPs[i].first == targetIP) {
            return i;
        }
    }

    return -1;
}

// RABIN-KARP STRING SEARCH
vector<int> Algorithms::rabinKarpSearch(
    const string& text,
    const string& pattern
) {
    vector<int> positions;

    if (pattern.empty() || pattern.length() > text.length()) {
        return positions;
    }

    const int base = 256;
    const int prime = 101;

    int patternHash = 0;
    int textHash = 0;
    int h = 1;

    for (int i = 0; i < static_cast<int>(pattern.length()) - 1; i++) {
        h = (h * base) % prime;
    }

    for (int i = 0; i < static_cast<int>(pattern.length()); i++) {
        patternHash = (base * patternHash + pattern[i]) % prime;
        textHash = (base * textHash + text[i]) % prime;
    }

    for (int i = 0; i <= static_cast<int>(text.length()) -
         static_cast<int>(pattern.length()); i++) {

        if (patternHash == textHash) {
            bool match = true;

            for (int j = 0; j < static_cast<int>(pattern.length()); j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                positions.push_back(i);
            }
        }

        if (i < static_cast<int>(text.length()) -
            static_cast<int>(pattern.length())) {

            textHash = (base * (textHash - text[i] * h)
                        + text[i + pattern.length()]) % prime;

            if (textHash < 0) {
                textHash += prime;
            }
        }
    }

    return positions;
}

// PERFORMANCE COMPARISON
void Algorithms::compareSearchPerformance() {
    vector<int> sizes = {1000, 10000, 50000, 100000};
    int repetitions = 100;

    cout << "\n===== PERFORMANCE COMPARISON =====\n";
    cout << "Repeated trials: " << repetitions << "\n\n";

    for (int size : sizes) {
        vector<pair<string, int>> testData;

        // Generate padded IP addresses
        for (int i = 1; i <= size; i++) {
            string number = to_string(i);

            while (number.length() < 6) {
                number = "0" + number;
            }

            testData.push_back({
                "192.168.1." + number,
                i
            });
        }

        string targetIP = testData.back().first;

        // LINEAR SEARCH TIMING
        auto linearStart = chrono::high_resolution_clock::now();

        for (int i = 0; i < repetitions; i++) {
            linearSearchIP(testData, targetIP);
        }

        auto linearEnd = chrono::high_resolution_clock::now();

        auto linearTime = chrono::duration_cast<chrono::microseconds>(
            linearEnd - linearStart
        ).count();

        // BINARY SEARCH TIMING
        auto binaryStart = chrono::high_resolution_clock::now();

        for (int i = 0; i < repetitions; i++) {
            binarySearchIP(testData, targetIP);
        }

        auto binaryEnd = chrono::high_resolution_clock::now();

        auto binaryTime = chrono::duration_cast<chrono::microseconds>(
            binaryEnd - binaryStart
        ).count();

        cout << "Dataset size: " << size << "\n";
        cout << "Linear Search: " << linearTime
             << " microseconds total\n";
        cout << "Binary Search: " << binaryTime
             << " microseconds total\n";
        cout << "-----------------------------\n";
    }
}