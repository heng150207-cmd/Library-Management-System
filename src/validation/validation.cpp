#include "Validation.hpp"
#include <algorithm>

using namespace std;

bool Validation::isValidYear(const string& s) {
    if (s.empty()) return false;
    size_t start = (s[0]=='-') ? 1 : 0;
    if (start >= s.size()) return false;
    return all_of(s.begin()+start, s.end(), ::isdigit);
}
bool Validation::isNonEmpty(const string& s) {
    return !s.empty() && s.find_first_not_of(" \t\n\r") != string::npos;
}
bool Validation::isValidEmail(const string& s) {
    auto at = s.find('@'); auto dot = s.rfind('.');
    return (at!=string::npos && dot!=string::npos && at<dot && dot<s.size()-1);
}
bool Validation::isInRange(int choice, int min, int max) {
    return choice >= min && choice <= max;
}
