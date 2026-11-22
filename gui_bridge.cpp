#include "LogAnalyzer.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Escape characters so strings are valid JSON
string escapeJSON(const string& s) {
    string result;

    for (char c : s) {
        switch (c) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default: result += c;
        }
    }

    return result;
}

int main() {
    LogAnalyzer analyzer;

    // Suppress terminal messages from loadLogs()
    ostringstream capturedOutput;
    streambuf* originalBuffer = cout.rdbuf();
    cout.rdbuf(capturedOutput.rdbuf());

    bool success = analyzer.loadLogs("sample_logs.txt");

    cout.rdbuf(originalBuffer);

    if (!success) {
        cout << "{\"error\":\"Failed to load logs\"}";
        return 1;
    }

    const vector<LogEntry>& logs = analyzer.getLogs();

    cout << "{\"logs\":[";

    for (size_t i = 0; i < logs.size(); i++) {
        const LogEntry& entry = logs[i];

        if (i > 0) cout << ",";

        cout << "{"
             << "\"timestamp\":\"" << escapeJSON(entry.timestamp) << "\","
             << "\"level\":\"" << escapeJSON(entry.level) << "\","
             << "\"message\":\"" << escapeJSON(entry.message) << "\","
             << "\"ipAddress\":\"" << escapeJSON(entry.ipAddress) << "\""
             << "}";
    }

    cout << "]}";

    return 0;
}
