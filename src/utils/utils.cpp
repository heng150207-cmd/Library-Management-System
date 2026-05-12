#include "Utils.hpp"
#include <iostream>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

void clearScreen() { system("cls"); }

void pauseScreen() {
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearScreen();
}

string currentDate() {
    time_t t = time(nullptr); tm* lt = localtime(&t);
    char buf[12];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d",
             lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday);
    return buf;
}

void clearInput() { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower); return s;
}
