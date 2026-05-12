#pragma once
#include <string>

// ─────────────────────────────────────────────────────────────
//  Validation — input checking helpers
// ─────────────────────────────────────────────────────────────
class Validation {
public:
    // Returns true if s is a valid 4-digit year (e.g. 1990, -429)
    static bool isValidYear(const std::string& s);

    // Returns true if s is a non-empty, trimmed string
    static bool isNonEmpty(const std::string& s);

    // Returns true if s looks like an email address
    static bool isValidEmail(const std::string& s);

    // Returns true if integer choice is within [min, max]
    static bool isInRange(int choice, int min, int max);
};
