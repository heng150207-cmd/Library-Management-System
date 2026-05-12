#include "Password.hpp"
#include <functional>
#include <sstream>
#include <iomanip>

using namespace std;

string Password::hash(const string& raw) {
    size_t h = std::hash<string>{}(raw);
    ostringstream oss; oss << hex << setw(16) << setfill('0') << h;
    return oss.str();
}
bool Password::verify(const string& raw, const string& stored) {
    return hash(raw) == stored;
}
