#pragma once
#include <string>

// ─────────────────────────────────────────────────────────────
//  Logger — optional event / error logging
// ─────────────────────────────────────────────────────────────
class Logger {
public:
    static void info (const std::string& msg);
    static void warn (const std::string& msg);
    static void error(const std::string& msg);
};
