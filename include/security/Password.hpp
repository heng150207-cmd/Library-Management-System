#pragma once
#include <string>

// ─────────────────────────────────────────────────────────────
//  Password — simple password hashing / comparison
// ─────────────────────────────────────────────────────────────
class Password {
public:
    // Return a hashed version of raw (e.g. SHA-256 or simple hash)
    static std::string hash(const std::string& raw);

    // Return true if raw matches the stored hash
    static bool verify(const std::string& raw, const std::string& stored);
};
