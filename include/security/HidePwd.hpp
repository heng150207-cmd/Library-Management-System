#pragma once
#include <string>

// ─────────────────────────────────────────────────────────────
//  HidePwd — cross-platform password input (no echo)
// ─────────────────────────────────────────────────────────────
class HidePwd {
public:
    // Read a password from stdin without echoing characters.
    // Shows '*' per character on supported platforms.
    static std::string readPassword();
};
