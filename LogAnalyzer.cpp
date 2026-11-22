#include "LogAnalyzer.h"
#include "Algorithms.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

bool LogAnalyzer::loadLogs(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open log file.\n";
        return false;
    }

    logs.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        LogEntry entry;

        ss >> entry.timestamp;
        string timePart;
        ss >> timePart;
        entry.timestamp += " " + timePart;

        ss >> entry.level;
        getline(ss, entry.message);

        if (!entry.message.empty() && entry.message[0] == ' ') {
            entry.message.erase(0, 1);
        }

        size_t ipPosition = entry.message.find("ip=");

        if (ipPosition != string::npos) {
            entry.ipAddress = entry.message.substr(ipPosition + 3);

            size_t spacePosition = entry.ipAddress.find(' ');

            if (spacePosition != string::npos) {
                entry.ipAddress = entry.ipAddress.substr(0, spacePosition);
            }
        } else {
            entry.ipAddress = "Unknown";
        }

        logs.push_back(entry);
    }

    file.close();

    cout << "Logs loaded successfully!\n";
    cout << "Total log records: " << logs.size() << "\n";

    return true;
}

void LogAnalyzer::displayLogs() {
    if (logs.empty()) {
        cout << "No logs loaded.\n";
        return;
    }

    cout << "\n========== LOG RECORDS ==========\n";

    for (const LogEntry& entry : logs) {
        cout << entry.timestamp << " | "
             << entry.level << " | "
             << entry.message << " | IP: "
             << entry.ipAddress << "\n";
    }
}

void LogAnalyzer::displayFailedAttempts() {
    unordered_map<string, int> failedCounts =
        Algorithms::countFailedAttempts(logs);

    vector<pair<string, int>> sortedIPs =
        Algorithms::mergeSortIPs(failedCounts);

    cout << "\n===== RANKED SUSPICIOUS IPs =====\n";

    if (sortedIPs.empty()) {
        cout << "No failed login attempts detected.\n";
        return;
    }

    for (const auto& pair : sortedIPs) {
        cout << "IP: " << pair.first
             << " | Failed attempts: " << pair.second << "\n";
    }
}

// BINARY SEARCH
void LogAnalyzer::searchIP() {
    unordered_map<string, int> failedCounts =
        Algorithms::countFailedAttempts(logs);

    vector<pair<string, int>> sortedIPs =
        Algorithms::mergeSortIPs(failedCounts);

    sort(sortedIPs.begin(), sortedIPs.end(),
         [](const pair<string, int>& a,
            const pair<string, int>& b) {
             return a.first < b.first;
         });

    string targetIP;

    cout << "\nEnter IP address to search: ";
    cin >> targetIP;

    int result = Algorithms::binarySearchIP(sortedIPs, targetIP);

    if (result != -1) {
        cout << "\nIP ADDRESS FOUND!\n";
        cout << "IP: " << sortedIPs[result].first << "\n";
        cout << "Failed attempts: " << sortedIPs[result].second << "\n";
    } else {
        cout << "\nIP address not found in failed login records.\n";
    }
}

// LINEAR SEARCH
void LogAnalyzer::searchIPLinear() {
    unordered_map<string, int> failedCounts =
        Algorithms::countFailedAttempts(logs);

    vector<pair<string, int>> sortedIPs =
        Algorithms::mergeSortIPs(failedCounts);

    string targetIP;

    cout << "\nEnter IP address to search: ";
    cin >> targetIP;

    int result = Algorithms::linearSearchIP(sortedIPs, targetIP);

    if (result != -1) {
        cout << "\nIP ADDRESS FOUND!\n";
        cout << "IP: " << sortedIPs[result].first << "\n";
        cout << "Failed attempts: " << sortedIPs[result].second << "\n";
    } else {
        cout << "\nIP address not found in failed login records.\n";
    }
}

// RABIN-KARP KEYWORD SEARCH
void LogAnalyzer::searchKeyword() {
    string keyword;

    cout << "\nEnter suspicious keyword to search: ";
    cin >> keyword;

    bool found = false;

    cout << "\n===== KEYWORD SEARCH RESULTS =====\n";

    for (const LogEntry& entry : logs) {
        vector<int> positions =
            Algorithms::rabinKarpSearch(entry.message, keyword);

        if (!positions.empty()) {
            found = true;

            cout << "\nTimestamp: " << entry.timestamp
                 << "\nLevel: " << entry.level
                 << "\nMessage: " << entry.message
                 << "\nIP: " << entry.ipAddress
                 << "\n";
        }
    }

    if (!found) {
        cout << "No logs containing \"" << keyword << "\" were found.\n";
    }
}