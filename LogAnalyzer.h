#ifndef LOGANALYZER_H
#define LOGANALYZER_H

#include <vector>
#include <string>
#include "LogEntry.h"

using namespace std;

class LogAnalyzer {
private:
    vector<LogEntry> logs;

public:
    bool loadLogs(const string& filename);
    void displayLogs();
    void displayFailedAttempts();
    void searchIP();
    void searchIPLinear();
    void searchKeyword();

    // GUI access
    const vector<LogEntry>& getLogs() const {
        return logs;
    }
};

#endif