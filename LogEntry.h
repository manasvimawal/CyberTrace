#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <string>
using namespace std;

struct LogEntry {
    string timestamp;
    string level;
    string message;
    string ipAddress;
};

#endif