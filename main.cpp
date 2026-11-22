#include <iostream>
#include "LogAnalyzer.h"
#include "Algorithms.h"

using namespace std;

int main() {
    cout << "====================================\n";
    cout << "             CYBERTRACE              \n";
    cout << "      Suspicious Log Analyzer        \n";
    cout << "====================================\n";

    LogAnalyzer analyzer;

    if (!analyzer.loadLogs("sample_logs.txt")) {
        return 1;
    }

    int choice;

    do {
        cout << "\n========== CYBERTRACE MENU ==========\n";
        cout << "1. View all logs\n";
        cout << "2. View ranked suspicious IPs\n";
        cout << "3. Search IP address (Binary Search)\n";
        cout << "4. Search IP address (Linear Search)\n";
        cout << "5. Search suspicious keyword (Rabin-Karp)\n";
        cout << "6. Compare Linear vs Binary Search Performance\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                analyzer.displayLogs();
                break;

            case 2:
                analyzer.displayFailedAttempts();
                break;

            case 3:
                analyzer.searchIP();
                break;

            case 4:
                analyzer.searchIPLinear();
                break;

            case 5:
                analyzer.searchKeyword();
                break;

            case 6:
                Algorithms::compareSearchPerformance();
                break;

            case 7:
                cout << "Exiting CyberTrace. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}